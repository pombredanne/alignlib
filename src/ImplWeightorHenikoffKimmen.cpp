/*
  alignlib - a library for aligning protein sequences

  $Id: ImplWeightorHenikoffKimmen.cpp,v 1.2 2004/01/07 14:35:36 aheger Exp $

  Copyright (C) 2004 Andreas Heger
  
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <iostream>
#include "alignlib.h"
#include "AlignlibDebug.h"

#include "Weightor.h"
#include "ImplWeightorHenikoffKimmen.h"
#include "MultipleAlignment.h"
#include "HelpersTranslator.h"
#include "Translator.h"

#ifdef WITH_DMALLOC
#include <dmalloc.h>
#endif

using namespace std;

namespace alignlib {

    /** factory functions */
  Weightor * makeWeightorHenikoffKimmen() { return new ImplWeightorHenikoffKimmen(getDefaultTranslator());}

//---------------------------------------------------------< constructors and destructors >--------------------------------------
ImplWeightorHenikoffKimmen::ImplWeightorHenikoffKimmen ( const Translator * translator) : ImplWeightorHenikoff(translator) {
}
		       
ImplWeightorHenikoffKimmen::~ImplWeightorHenikoffKimmen () {
}

ImplWeightorHenikoffKimmen::ImplWeightorHenikoffKimmen (const ImplWeightorHenikoffKimmen & src ) : ImplWeightorHenikoff(src) {
}

//--------------------------------------------------------------------------------------------------------------------------------
SequenceWeight * ImplWeightorHenikoffKimmen::calculateWeights( const MultipleAlignment & src ) const 
{
  debug_func_cerr(5);


  //!! to do: Right now I have to translate twice. This could be improved by making a temporary
  // copy (at the expense of memory, though)

  typedef int MY_Count[PROFILEWIDTH];
  
  int nsequences = src.getWidth();
  Position length = src.getLength();

  Position column;
  int i, j;
  
  //-----------------> calculate counts for each column and amino acid<----------------------
  MY_Count * counts = new MY_Count[length + 1];

  for (j = 0; j <= length; j++) 
    for ( i = 0; i < PROFILEWIDTH; i++) 
      counts[j][i] = 0;

  Residue residue; 
  for (i = 0; i < nsequences; i++) {
    const std::string & sequence = src[i];
    for (column = 0; column < length; column++)
      if ((residue = mTranslator->encode(sequence[column])) < PROFILEWIDTH) 
	counts[column][residue]++;
  }

  //-----------------> calculate types per column <------------------------------------------
  int * ntypes = new int[length];

  for (column = 0; column < length; column++) {
    ntypes[column] = 0;
    for (i = 0; i < PROFILEWIDTH; i++) 
      if (counts[column][i] > 0)
	ntypes[column]++;
  }
  //---------------> calculate sequence weights <------------------------------------------
  SequenceWeight * weights = new SequenceWeight[nsequences];

  for (i = 0; i < nsequences; i++) {
    weights[i] = 0;
    for (column = 0; column < length; column++) {
	const std::string & sequence = src[i];			// sum up, but skip gaps and masked characters
	if ( (residue = mTranslator->encode(sequence[column])) < PROFILEWIDTH) 
	  weights[i] += (SequenceWeight)(1.0 / ((double)counts[column][residue] * (double)ntypes[column]));
    }
  }
   
  //---------------> clean up------------------------------------------------------------
  delete [] counts;
  delete [] ntypes;

  //---------------> rescale weights, so that they sum to the number of nsequences <---------------------------
  //!! to do: modify this class and the one above, so that I do not have this code duplication. too tired now
  rescaleWeights( weights, nsequences, nsequences);

  return weights;
}

} // namespace alignlib