/*
  alignlib - a library for aligning protein sequences

  $Id: ImplAlignatorIterative.cpp,v 1.2 2004/01/07 14:35:34 aheger Exp $

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
#include "alignlib.h"
#include "AlignlibDebug.h"
#include "Alignandum.h"

#include "Alignator.h"

#include "Alignata.h"
#include "HelpersAlignata.h"

#include "ImplAlignatorIterative.h"

using namespace std;

namespace alignlib 
{

  Alignator * makeAlignatorIterative( 
		  const Alignator * alignator, 
		  Score min_score )
  {
    return new ImplAlignatorIterative( alignator, min_score );
  }
  
  //---------------------------------------------------------< constructors and destructors >--------------------------------------
  ImplAlignatorIterative::ImplAlignatorIterative ( const Alignator * alignator, Score min_score) : 
	  ImplAlignator(), mMinScore( min_score ),
  	mAlignator ( alignator->getClone() )
  {
  }
  
  ImplAlignatorIterative::~ImplAlignatorIterative ()
  {
	  delete mAlignator;
  }
  
  ImplAlignatorIterative::ImplAlignatorIterative (const ImplAlignatorIterative & src ) :
    ImplAlignator(src), mMinScore( src.mMinScore), mAlignator(src.mAlignator->getClone())
  {
  }

  //--------------------------------------------------------------------------------------------------------
  ImplAlignatorIterative * ImplAlignatorIterative::getClone() const 
  {
   return new ImplAlignatorIterative( *this );
  }
  
  
  Alignata * ImplAlignatorIterative::align( const Alignandum * row, const Alignandum * col, Alignata * result) 
  {
      debug_func_cerr(5);
      
      startUp(row, col, result );
    
     /* since src1 and src2 are const, I have to create two work-copies, 
        so that the boundaries can be changed. */

      Alignandum * copy_row = row->getClone();
      Alignandum * copy_col = col->getClone();
      
      // start aligning by calling recursively performIterativeAlignmentStep
      alignIteratively( result, copy_row, copy_col );

      delete copy_row;
      delete copy_col;

      cleanUp( row, col, result );
    
      return result;
  }

  void ImplAlignatorIterative::alignIteratively( 
		  	Alignata * dest, 
  			Alignandum * row, 
  			Alignandum * col )
  {
    debug_func_cerr(5);
    
    // do alignment with current boundaries of the objects, but remember them
    Position from_1 = row->getFrom();
    Position from_2 = col->getFrom();

    Position to_1 = row->getTo();
    Position to_2 = col->getTo();

    debug_cerr(5, "aligning in regions (" << from_1 << "-" << to_1 <<") -> (" << from_2 << "-" << to_2 << ")" );

    if (from_1 > to_1 || from_2 > to_2)
      return;

    Alignata * result = dest->getNew();

    mAlignator->align( row, col, result );

    if (result->getScore() > mMinScore) 
    {

        addAlignata2Alignata( dest, result );

        debug_cerr( 5, "new alignment\n" << *result )
        debug_cerr( 5, "new alignment coordinates: row=" << result->getRowFrom() << " " << result->getRowTo()  
      		  	<< " col=" << result->getColFrom() << " " << result->getColTo() );      
        debug_cerr( 5, "current alignment\n" << *result )      

        Position from_1_result = result->getRowFrom();
        Position from_2_result = result->getColFrom();
        Position to_1_result   = result->getRowTo();
        Position to_2_result   = result->getColTo();
        
        // align in region before current alignment
        row->useSegment( from_1, from_1_result);
        col->useSegment( from_2, from_2_result);
        alignIteratively( dest, row, col );
        
        // align in region after current alignment
        row->useSegment( to_1_result, to_1);
        col->useSegment( to_2_result, to_2);
        
        alignIteratively( dest, row, col );

    }
    delete result;
  } 
  
  

} // namespace alignlib