/*
  alignlib - a library for aligning protein sequences

  $Id: ImplAlignataMatrixRow.h,v 1.3 2004/03/19 18:23:40 aheger Exp $

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

#ifndef IMPL_ALIGNATA_MATRIX_ROW_H
#define IMPL_ALIGNATA_MATRIX_ROW_H 1

#include <iosfwd>
#include "alignlib.h"
#include "ImplAlignataMatrix.h"

namespace alignlib {

class Alignandum;

/** @brief dotplot with dots sorted by row and then col.

    @author Andreas Heger
    @version $Id: ImplAlignataMatrixRow.h,v 1.3 2004/03/19 18:23:40 aheger Exp $
*/
class ImplAlignataMatrixRow : public ImplAlignataMatrix {

    friend class ConstIterator;
    friend class ImplAlignatorDots;
    
 public:
    //------------------> constructors / destructors <---------------------------------------------------------
    /** constructor */
    ImplAlignataMatrixRow( long ndots = 0);
    
    /** copy constructor */
    ImplAlignataMatrixRow( const ImplAlignataMatrixRow &src );

    /** destructor */
    virtual ~ImplAlignataMatrixRow();

    //------------------------------------------------------------------------------------------------------------
    virtual ImplAlignataMatrixRow * getNew() const;
    
    /** return an identical copy */
    virtual ImplAlignataMatrixRow * getClone() const;

    //------------------------------------------------------------------------------------------------------------
    /** maps a residue from row to column. returns 0, if not found. This is quick, since there is 
	only one lookup in the array needed.*/
    virtual Position mapRowToCol( Position pos ) const;

 protected:
    /** build index */
    virtual void buildIndex() const;

    /** sort Dots by row and col */
    virtual void sortDots() const;

    
};

						  

}

#endif /* _ALIGNATA_H */
