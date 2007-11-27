/*
  alignlib - a library for aligning protein sequences

  $Id: ImplAlignatorSimilarity.cpp,v 1.2 2004/01/07 14:35:34 aheger Exp $

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
#include "Alignata.h"
#include "SubstitutionMatrix.h"
#include "ImplAlignatorSimilarity.h"

#include "Iterator2D.h"
#include "HelpersIterator2D.h"

#ifdef WITH_DMALLOC
#include <dmalloc.h>
#endif

using namespace std;

namespace alignlib {

  Alignator * makeAlignatorSimilarity()
  {
    return new ImplAlignatorSimilarity();
  }
  
  //---------------------------------------------------------< constructors and destructors >--------------------------------------
  ImplAlignatorSimilarity::ImplAlignatorSimilarity () : ImplAlignator() {
  }
  
  ImplAlignatorSimilarity::~ImplAlignatorSimilarity () {
  }
  
  ImplAlignatorSimilarity::ImplAlignatorSimilarity (const ImplAlignatorSimilarity & src ) : ImplAlignator(src) {
  }
  
  //--------------------------------------------------------------------------------------------------------
  ImplAlignatorSimilarity * ImplAlignatorSimilarity::getClone() const 
  {
   return new ImplAlignatorSimilarity( *this );
  }
  
  Alignata * ImplAlignatorSimilarity::align( const Alignandum * row, const Alignandum * col, Alignata * result) {
    
    startUp(row, col, result );
    
    Score score, total_score = 0;
    
    Iterator2D * it2d = mIterator->getNew( row, col );
    
    Iterator2D::const_iterator rit(it2d->row_begin()), rend(it2d->row_end());
    
    for (; rit != rend; ++rit)
      {
	Position r = *rit;
	
	Iterator2D::const_iterator cit(it2d->col_begin(r)), cend(it2d->col_end(r));
	for (; cit != cend; ++cit)
	  {
	    Position c = *cit;
	    if ( (score = mScorer->getScore( r, c ) > 0) )
	      {
		result->addPair( new ResiduePAIR( r, c, score ));
		total_score += score;
	      }
	  }
      }
    
    result->setScore( total_score );
    
    cleanUp(row, col, result );
    
    return result;
  
  }
  

} // namespace alignlib
