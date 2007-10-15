/*
  alignlib - a library for aligning protein sequences

  $Id: ImplAlignatorDP.cpp,v 1.1 2005/02/24 11:08:24 aheger Exp $

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
#include <iomanip>
#include <limits>

#include "alignlib.h"
#include "AlignlibDebug.h"
#include "AlignException.h"

#include "SubstitutionMatrix.h"
#include "HelpersSubstitutionMatrix.h"
#include "ImplSubstitutionMatrixAA.h"

#include "Alignata.h"
#include "HelpersAlignata.h"

#include "Alignandum.h"
#include "Alignator.h"
#include "ImplAlignatorDP.h"

//implementation of Alignandum-objects
#include "ImplSequence.h"
#include "ImplProfile.h"

#include "ImplTranslator.h" // for direct access to mask_code



#ifdef WITH_DMALLOC
#include <dmalloc.h>
#endif

using namespace std;

namespace alignlib {
  
  /* How to write a fast algorithm:
     My design objective here was to not duplicate the algorithmic code without penalizing too much
     for function indirection. It the way I do it below, there is one indirection for every call to
     calculate a match function, except for sequence-sequence comparisons, where there would have been
     two.

    */
       
//<--------------< Global functions and pointers for fast determination of match score. >-------------------------------------------
// I don't know how to use member functions as function pointers. After all, this is what inheritence is for. A possibility would be
// to automatically subclass an alignator-object.However, I do not like this idea, since this assumes that the parent has information 
// about the child. On the other hand, via the inlining mechanism a function call could be saved. The problem is when you want to change
// the algorithm by overloading align. Then the parent functions () do not know, what the child is. Therefore I use the static 
// functions. Maybe it is possible to separate the algorithm and the type-decision into different classes that interact.
//
// The danger of static functions is that the global pointers are unsafe, i.e. there exist just one copy for all alignator-objects, and
// this code will never be threadsafe.
//-----------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------------
  ImplAlignatorDP::ImplAlignatorDP( AlignmentType alignment_type, 
				    Score row_gop, Score row_gep, 
				    Score col_gop, Score col_gep,
				    bool penalize_row_left, bool penalize_row_right,
				    bool penalize_col_left, bool penalize_col_right) :
    ImplAlignator(),
    mCC(NULL), 
    mDD(NULL),
    mAlignmentType(alignment_type),
    mPenalizeRowLeft( penalize_row_left ),
    mPenalizeRowRight( penalize_row_right ),
    mPenalizeColLeft( penalize_col_left ),
    mPenalizeColRight( penalize_col_right ),
    mRowGop( row_gop ), mRowGep( row_gep ),
    mColGop( col_gop ), mColGep( col_gep )
  {
    if (mColGop == 0)
      {
	mColGop = mRowGop;
	mColGep = mRowGep;
      }
  }
  
  //----------------------------------------------------------------------------------------------------------------------------------------
  ImplAlignatorDP::ImplAlignatorDP( const ImplAlignatorDP & src ) :
    ImplAlignator( src ),
    mRowGop( src.mRowGop), mRowGep( src.mRowGep), mColGop( src.mColGop), mColGep( src.mColGep)
  
{
  debug_func_cerr(5);

    mCC = NULL;
    mDD = NULL;
    
  }

  //----------------------------------------------------------------------------------------------------------------------------------------
  ImplAlignatorDP::~ImplAlignatorDP()
  
{
  debug_func_cerr(5);

  }

  void ImplAlignatorDP::setRowGop( Score gop ) { mRowGop = gop;} 
  void ImplAlignatorDP::setRowGep( Score gep ) { mRowGep = gep;}
  void ImplAlignatorDP::setColGop( Score gop ) { mColGop = gop;}
  void ImplAlignatorDP::setColGep( Score gep ) {mColGep = gep; }

  Score ImplAlignatorDP::getRowGop() { return mRowGop; }
  Score ImplAlignatorDP::getRowGep() { return mRowGep; }
  Score ImplAlignatorDP::getColGop() { return mColGop; }
  Score ImplAlignatorDP::getColGep() { return mColGep; }

  //----------------------------------------------------------------------------------------------------------------------------------------
  Alignata * ImplAlignatorDP::align(const Alignandum * row, const Alignandum * col, Alignata * result)
  
{
  debug_func_cerr(5);


  /* try casting down the hiearchy of Alignandum-objects and then using a switch statement 
     register the correct match function. There are different implementations for this:
     1. multiple dispatch, but then everytime I write code for aligning/creating dots, ...
     I have to add new corresponding functions in Alignandum objects. I rather like the code
     in one file, even if it is large.
     2. using an emulated virtual table. This is an elegant solution (see Meyers), but needs
     a lot of coding.
     I do not expect, that there will be many more other Alignandum-objects, so I use the
     dynamics_cast-way.
  */
  
    startUp(row, col, result);
    
    performAlignment(row, col, result);
    
    cleanUp(row, col, result);
    
    return result;
  }
  
  //------------------------------------------------------------------------------------------
void ImplAlignatorDP::startUp(const Alignandum * row, const Alignandum *col, Alignata * ali) {

  ImplAlignator::startUp(row, col, ali);  

  mRowLength = mIterator->row_size();
  mColLength = mIterator->col_size();
  
  //----------------------------------------------------------------------------------------
  mCC    = new Score[mColLength + 1];
  mDD    = new Score[mColLength + 1];

  for (Position x = 0; x < mColLength +1; ++x)
    {
      mCC[x] = mDD[x] = -std::numeric_limits<Score>::max();
    }

  mScore = -std::numeric_limits<Score>::max();
#ifdef DEBUG
    // cout << "Substitution-Matrix used" << endl << *mSubstitutionMatrix;
#endif
}
//----------------------------------------------------------------------------------------------------------------------------------------
void ImplAlignatorDP::cleanUp(const Alignandum * row, const Alignandum *col, Alignata * ali)
{
    
  if (mCC != NULL)    { delete [] mCC; mCC = NULL; }
  if (mDD != NULL)    { delete [] mDD; mDD = NULL; }
    
  ImplAlignator::cleanUp(row, col, ali);

}       

} // namespace alignlib