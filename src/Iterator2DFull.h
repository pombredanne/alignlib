/*
  alignlib - a library for aligning protein sequences

  $Id: Fragmentor.h,v 1.3 2004/03/19 18:23:40 aheger Exp $

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


#if HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef ITERATOR2DFull_H
#define ITERATOR2DFull_H 1

#include "alignlib.h"
#include "Iterator2D.h"
namespace alignlib 
{

  class ImplIterator2DFull: Iterator2D
	{
	public:
      
      /** empty constructor */
      ImplIterator2DFull(); 
    
      /** destructor */
      virtual ~ImplIterator2DFull ();
      
      /** copy constructor */
      ImplIterator2DFull( const ImplIterator2DFull & src);

      const_iterator row_begin ( Position col = 0 );
      const_iterator row_end   ( Position col = 0 );      
      const_iterator col_begin ( Position row = 0 );
      const_iterator col_end   ( Position row = 0 );      
    };
}

#endif /* ITERATOR2D_H */