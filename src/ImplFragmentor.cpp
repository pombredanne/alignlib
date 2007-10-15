/*
  alignlib - a library for aligning protein sequences

  $Id: ImplFragmentor.cpp,v 1.3 2004/01/07 14:35:35 aheger Exp $

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

#include "Alignata.h"
#include "HelpersAlignata.h"

#include "Alignandum.h"
#include "AlignException.h"

#include "SubstitutionMatrix.h"

#include "ImplFragmentor.h"

#ifdef WITH_DMALLOC
#include <dmalloc.h>
#endif

using namespace std;

namespace alignlib {


//----------------------------------------------------------------------------------------------------
  
ImplFragmentor::ImplFragmentor() {
}    

ImplFragmentor::~ImplFragmentor() 
{
  debug_func_cerr(5);


}

ImplFragmentor::ImplFragmentor( const ImplFragmentor & src ) {
}

//--------------------------------------------------------------------------------------------------------
Position ImplFragmentor::getRowLength() { return mRowLength; }
Position ImplFragmentor::getColLength() { return mColLength; }

//-------------------------------------------------------------------------------------------------------
void ImplFragmentor::startUp( const Alignandum * row, const Alignandum * col, Alignata * ali) 
{
  debug_func_cerr(5);

    row->prepare();
    col->prepare();
    
    mRowLength = row->getLength();
    mColLength = col->getLength();

    mFragments = new FragmentVector();
  
}

//--------------------------------------------------------------------------------------------------------
void ImplFragmentor::cleanUp(const Alignandum * row, const Alignandum *col, Alignata * ali) 
{
  debug_func_cerr(5);

  
  // correct the alignment for offsets
  // I am not sure, why put this code here. Moving
  // is performed by ImplAlignator 
//      
//    Position row_offset =  row->getFrom() - 1;
//    Position col_offset =  col->getFrom() - 1;

//    if (row_offset > 0 || col_offset > 0) {  
    
//      FragmentVector::iterator it(mFragments->begin()), it_end(mFragments->end());
//      for (; it!=it_end; ++it) 
//        (*it)->moveAlignment( row_offset, col_offset);
//    }

}

//--------------------------------------------------------------------------------------------------------
FragmentVector * ImplFragmentor::fragment(const Alignandum * row, const Alignandum * col, Alignata * ali) {

  startUp(row, col, ali);

  performFragmentation( row, col, ali);
  
  cleanUp( row, col, ali);

  return mFragments;
}

} // namespace alignlib












