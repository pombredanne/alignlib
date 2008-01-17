/*
  alignlib - a library for aligning protein sequences

  $Id: ImplAlignatorGroupies.cpp,v 1.2 2004/01/07 14:35:34 aheger Exp $

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
#include <math.h>
#include "alignlib_fwd.h"
#include "alignlib_interfaces.h"
#include "AlignlibDebug.h"
#include "Alignandum.h"
#include "Alignment.h"
#include "Matrix.h"
#include "ImplAlignatorGroupies.h"
#include "AlignmentIterator.h"
#include "HelpersAlignment.h"
#include "Iterator2D.h"
#include "Scorer.h"
#include "HelpersIterator2D.h"
#include "HelpersAlignator.h"

using namespace std;

namespace alignlib 
{

HAlignator makeAlignatorGroupies(
		const Position tube_size,
		const HAlignator & alignator_dots,
		const HAlignator & alignator_gaps,
		const Score & gop,
		const Score & gep)
{
	return HAlignator( new ImplAlignatorGroupies(
			tube_size, alignator_dots, alignator_gaps, gop, gep ) );
}

HAlignator makeAlignatorGroupies()
{
	HAlignator alignator_gaps( makeAlignatorDPFull( ALIGNMENT_GLOBAL, -10, -2 ) );
	HAlignator alignator_dots( makeAlignatorTuples( 3 ));
	
	return HAlignator( new ImplAlignatorGroupies(
			30, alignator_dots, alignator_gaps,
			-10, -2) );
}
  
  //---------------------------------------------------------< constructors and destructors >--------------------------------------
	ImplAlignatorGroupies::ImplAlignatorGroupies (
			const Position tube_size,
			const HAlignator & alignator_dots,
			const HAlignator & alignator_gaps,
			const Score & gop,
			const Score & gep) : ImplAlignator(),
			mTubeSize( tube_size ),
			mAlignatorDots( alignator_dots),
			mAlignatorGaps( alignator_gaps ),
			mGop(gop),
			mGep(gep)
	  {
	  }

	
  ImplAlignatorGroupies::~ImplAlignatorGroupies () 
  {
  }
  
  ImplAlignatorGroupies::ImplAlignatorGroupies (const ImplAlignatorGroupies & src ) : 
	  ImplAlignator(src),
	  mTubeSize( src.mTubeSize ),
	  mAlignatorDots( src.mAlignatorDots ),
	  mAlignatorGaps( src.mAlignatorGaps ),
	  mGop( src.mGop ),
	  mGep( src.mGep )
  {
  }
  
  //--------------------------------------------------------------------------------------------------------
  HAlignator ImplAlignatorGroupies::getClone() const 
  {
   return HAlignator( new ImplAlignatorGroupies( *this ) );
  }
  
  void ImplAlignatorGroupies::align( 
		  HAlignment & result,
		  const HAlignandum & row, 
		  const HAlignandum & col) 
  {
    
    startUp(result, row, col );
    
    Position lrow = row->getLength();
    Position lcol = col->getLength();

    // collect dots (with score)
    HAlignment dots(makeAlignmentMatrixUnsorted());
    mAlignatorDots->align( dots, row, col);

    debug_cerr( 5, "-> there are " << dots->getLength() << " dots " );

    // calculate maximum diagonal
    AlignmentIterator it(dots->begin());
    AlignmentIterator it_end(dots->end());

    Position max_diag = lrow * lcol + 1;
    std::vector<int> diagonals( max_diag,0);
    for (; it != it_end; ++it)
    {	
    	Position diagonal = it->mCol - it->mRow + lrow;
    	assert( diagonal < max_diag);
    	assert( diagonal >= 0);
    	diagonals[diagonal] += 1;
    }	

    Position best_diag = 0;
    for (Position x = 0; x < max_diag; x++)
    {
    	if (diagonals[best_diag] < diagonals[x])
    		max_diag = x;
    }

    best_diag -= lrow;

    HAlignment new_dots( makeAlignmentMatrixRow() );

    copyAlignment( new_dots, dots, 
    		NO_POS, NO_POS, NO_POS, NO_POS,
    		best_diag - mTubeSize,
    		best_diag + mTubeSize );

    debug_cerr( 5, "-> there are " << new_dots->getLength() << " dots after filtering" );
    debug_cerr( 5, "-> tube used: " << best_diag - mTubeSize << " to " <<  best_diag + mTubeSize );

    HAlignator p(makeAlignatorDummy( new_dots ));
      
    HAlignator alignator( makeAlignatorDotsSquared( p, mGop, mGep) );

    alignator->align( result, row, col );

    // fill gaps
    fillAlignmentGaps( result, mAlignatorGaps, row, col );
    
    cleanUp(result, row, col );
  }
  

} // namespace alignlib
