/*
  alignlib - a library for aligning protein sequences

  $Id: HelpersSubstitutionMatrix.cpp,v 1.2 2004/01/07 14:35:33 aheger Exp $

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


#include "alignlib.h"
#include "AlignlibDebug.h"

#include "HelpersIterator2D.h"

#ifdef WITH_DMALLOC
#include <dmalloc.h>
#endif

using namespace std;

namespace alignlib {

  static const Iterator2D * DEFAULT_ITERATOR2D = makeIterator2DFull();
  
  /** gets the default Iterator2D object */ 
  const Iterator2D * getDefaultIterator2D() {
    return DEFAULT_ITERATOR2D;
  }

  /** sets the default Iterator2D object */
  const Iterator2D * setDefaultIterator2D( const Iterator2D * iterator2D ) {
    const Iterator2D * t = DEFAULT_ITERATOR2D;
    DEFAULT_ITERATOR2D = iterator2D;
    return t;
  }
}
