/*
  alignlib - a library for aligning protein sequences

  $Id: ImplAlignatorTuples.cpp,v 1.2 2004/01/07 14:35:34 aheger Exp $

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


#include <iterator>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <set>
#include <math.h>
#include "alignlib.h"
#include "AlignlibDebug.h"
#include "Alignandum.h"
#include "SubstitutionMatrix.h"
#include "ImplAlignatorTuples.h"
#include "ImplAlignataMatrix.h"
#include "HelpersSubstitutionMatrix.h"

#ifdef WITH_DMALLOC
#include <dmalloc.h>
#endif

using namespace std;

namespace alignlib
{
  
  // map for mapping strings (tuples) to sequenceposotions.
  typedef map<string, vector<Position> > TUPLES;
  
  /*---------------------factory functions ---------------------------------- */
  Alignator * makeAlignatorTuples( int ktuple )
  {
    return new ImplAlignatorTuples( ktuple );
  }
  
  //---------------------------------------------------------< constructors and destructors >--------------------------------------
  ImplAlignatorTuples::ImplAlignatorTuples ( int ktuple ) : 
    ImplAlignator(), mKtuple(ktuple) {
  }
		       
  ImplAlignatorTuples::~ImplAlignatorTuples () {
  }
  
  ImplAlignatorTuples::ImplAlignatorTuples (const ImplAlignatorTuples & src ) : 
    ImplAlignator(src), mKtuple( src.mKtuple) {
  }

  //---------------------------------------------> Alignment <-----------------------------------------
  
  Alignata * ImplAlignatorTuples::align( const Alignandum * row, const Alignandum * col, Alignata * result) 
{
  debug_func_cerr(5);

    
    startUp(row, col, result);
    
    TUPLES tuples;
  
    // 1. create map of tuples of length ktuple for row_sequence (this is a map of vectors)
    int row_len = row->getLength();
    
    // get some sort of string representation for the sequences (i.e., consensus-string for profiles)
    std::string row_sequence = row->asString();      
    
    // xrow and xcol are positions in the string and are therefore starting at 0.
    
    for (int xrow = 0; xrow <= (row_len - mKtuple); xrow++)
      tuples[row_sequence.substr(xrow, mKtuple)].push_back(xrow);
    
#ifdef DEBUG
    cout << "Tuples " << endl;
    for (TUPLES::iterator it = tuples.begin(); it != tuples.end(); ++it) {
      cout << (*it).first << endl;
      vector<int> & v = tuples[(*it).first];
      copy(v.begin(), v.end(), std::ostream_iterator<int>(cout, " "));
      cout << endl;
    }
#endif
    
    // 2. look up tuples in col_sequence and add dots to a set, so that they are unique
    int col_len = col->getLength();
    std::string col_sequence = col->asString();
    
    // set of newly generated aligned residue pairs. The residue pair is encoded as
    // (column_length) * (row) + (column). This step is needed, so all pairs are unique.
    
    set<Position> newdots;                                                              
    
    // go through object in col
    for (Position xcol = 0; xcol <= (col_len - mKtuple); xcol++)
      {
	
	// build tuple
	std::string tuple = col_sequence.substr( xcol, mKtuple);
	
	// look up tuple
	if ( tuples.find(tuple) != tuples.end() ) {
	  // if tuple was there, iterate through all rows and add aligned residues
	  vector<Position>& rows = tuples[tuple];
	  
	  for (vector<Position>::iterator it = rows.begin(); it != rows.end(); ++it) {
	    
	    for (Position i = 0; i < mKtuple; i++) {
	      Position code = ((*it) + i) * col_len + xcol + i;
	      newdots.insert( code );
	    }
	  }
	}
      }
    
    // Add dots from set to dots, nice side-effect: 
    // the dots are already sorted by row and then by column !!
    
    Score total_score = 0;
    for (set<int>::iterator it = newdots.begin(); it != newdots.end(); ++it) {
      int xrow = (*it) / col_len + 1;
      int xcol = (*it) % col_len + 1;
      Score score =  mScorer->getScore( xrow, xcol);
      
      total_score += score;
      result->addPair( new ResiduePAIR( xrow, xcol, score));
    }
    
    result->setScore( total_score );
    
    cleanUp(row, col, result);
    
    return result;
  }
  
} // namespace alignlib