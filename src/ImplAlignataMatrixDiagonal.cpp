/*
  alignlib - a library for aligning protein sequences

  $Id: ImplAlignataMatrixDiagonal.cpp,v 1.3 2004/06/02 12:11:37 aheger Exp $

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
#include <algorithm>
#include <set>
#include "alignlib.h"
#include "AlignlibDebug.h"
#include "ImplAlignataMatrixDiagonal.h"
#include "AlignataIterator.h"
#include "AlignException.h"

#ifdef WITH_DMALLOC
#include <dmalloc.h>
#endif

using namespace std;

namespace alignlib {
  
  /** 
      The whole thing could be quicker, if the diagonal was precalculated as well.
  */

#define NODOT -1

//------------------------------factory functions -----------------------------
Alignata * makeAlignataMatrixDiagonal( long ndots ) {
  return new ImplAlignataMatrixDiagonal( ndots);
}

//------------------------------------< constructors and destructors >-----
ImplAlignataMatrixDiagonal::ImplAlignataMatrixDiagonal( long ndots ) : ImplAlignataMatrix( ndots), mNumDiagonals(0) 
{
  debug_func_cerr(5);

}

ImplAlignataMatrixDiagonal::ImplAlignataMatrixDiagonal( const ImplAlignataMatrixDiagonal& src) : 
  ImplAlignataMatrix( src ), mNumDiagonals(src.mNumDiagonals) 
{
  debug_func_cerr(5);

}

ImplAlignataMatrixDiagonal::~ImplAlignataMatrixDiagonal( ) 
{
  debug_func_cerr(5);

}

//------------------------------------------------------------------------------------------------------------
ImplAlignataMatrixDiagonal * ImplAlignataMatrixDiagonal::getNew() const {
    return new ImplAlignataMatrixDiagonal();
}
    
ImplAlignataMatrixDiagonal * ImplAlignataMatrixDiagonal::getClone() const {
    return new ImplAlignataMatrixDiagonal( *this );
}

//--------------> mapping functions <----------------------------------------------------------------------------
Position ImplAlignataMatrixDiagonal::mapRowToCol( Position pos ) const {

    if (mChangedLength) calculateLength();

    if (pos > mRowTo || pos < mRowFrom) 
	return 0;

    // find the row with the smallest diagonal
    Dot dot, next_dot;
    Dot next_diagonal = 1;
    Position diagonal =0;

    Dot ndots = mPairs.size(); 

    for (diagonal = 0; diagonal < mNumDiagonals; diagonal++, next_diagonal++) {
        dot = mIndex[diagonal];
      
	if (next_diagonal < mNumDiagonals)
	  next_dot = mIndex[next_diagonal];
	else
	  next_dot = ndots;
	
	if (dot != NODOT) {
	    // go along one diagonal
	    while ( dot < next_dot && 
		    mPairs[dot]->mRow < pos && 
		    dot < ndots) 
		dot++;
	    
	    if (dot < ndots && mPairs[dot]->mRow == pos) 
		return mPairs[dot]->mCol;
	}
    }

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------- 
/* sort Residuepairs(dots) in mPairs by diagonal and then by column. Sorting is done in place using quick-sort. It might be
   faster to only sort the indices (as I did in the old version) and then copy it into a new memory location
*/

void ImplAlignataMatrixDiagonal::sortDots() const {
    
  Position x, from, to;
  Dot ndots = mPairs.size(); 

  /* sort indices on diagonal */
  sortDotsByDiagonal( 0, ndots - 1);
  
  /* sort indices in diagonal */
  from = 0;
  while ( from < ndots ) {
    x    = calculateDiagonal(*mPairs[from]);
    to   = from + 1;

    /* find end of row */
    while ( (to < ndots) && (x == calculateDiagonal(*mPairs[to])) ) { to++; } 

    /* and sort per column */
    sortDotsByRow( from, to - 1 );
    from = to;
  }
  
}

//--------------------------------------------------------------------------------------------------------------
// build the index
void ImplAlignataMatrixDiagonal::buildIndex() const {
  Position i;

  mNumDiagonals = (mColTo - mColFrom + 1) + (mRowTo - mRowFrom + 1) + 1;
  Dot ndots = mPairs.size(); 

  //  allocate and initialize memory memory 
  allocateIndex( mNumDiagonals );
  for (i = 0; i < mNumDiagonals; i++) { mIndex[i] = NODOT; }   
  
  
  Dot first_dot = 0;
  Diagonal diagonal = calculateNormalizedDiagonal( *mPairs[0], mRowFrom, mColFrom);
  Diagonal min_diagonal = -(mRowTo - mRowFrom + 1);

  // update mIndex
  for (i = 0; i < ndots; i++) {
    if(diagonal != calculateNormalizedDiagonal(*mPairs[i], mRowFrom, mColFrom)) {
      
      mIndex[diagonal - min_diagonal] = first_dot;
      first_dot	= i;
      diagonal = calculateNormalizedDiagonal(*mPairs[i], mRowFrom, mColFrom);
    }
  }

  mIndex[diagonal - min_diagonal] = first_dot;

}


} // namespace alignlib