/*
  alignlib - a library for aligning protein sequences

  $Id: ImplMultAlignment.h,v 1.5 2004/03/19 18:23:41 aheger Exp $

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

#ifndef IMPL_MULT_ALIGNMENT_H
#define IMPL_MULT_ALIGNMENT_H 1

#include <iosfwd>
#include <string>
#include <list>

#include "alignlib_fwd.h"
#include "MultAlignment.h"

namespace alignlib
{
/**
    @short Implementation class for multiple alignments.

    This class keeps a vector of Alignatum objects. If a new
    @ref Alignatum object is added, gaps have to be added to all previously added
    @ref Alignatum objects, so this can be a costly operation. However, this class
    is efficient for pile-up alignments, with an ungapped query sequence at the
    top.

    @author Andreas Heger
    @version $Id$
*/
class ImplMultAlignment : public MultAlignment
{

  // class member functions
 public:

    // constructors and desctructors
    /** empty constructor
     */
    ImplMultAlignment  ();

    /** copy constructor */
    ImplMultAlignment  (const ImplMultAlignment &);

    /** destructor */
    virtual ~ImplMultAlignment ();

    //---------------------------------------------------------------------------------------
    /*------- accessors --------------------------------------------------------------------*/

    /** returns the length (number of columns) of the multiple alignment.
     *
     * All objects in a multiple alignment have the same length.
     *
     * @return the length (aligned positions) of the multiple alignment. */
    virtual Position getLength() const;

    /** returns the number of sequences in this multiple alignment.
     *
     * @return number of sequences in alignment.
     */
    virtual int getNumSequences() const;

    /** returns a row of the multiple alignment.
     *
     * @param row row of multiple alignment.
     * return multiple alignment
    */
    virtual const HAlignment operator[]( int row ) const ;

    /** returns a row of the multiple alignment.
     *
     * @param row row of multiple alignment.
     * return a @ref Alignatum object
    */
    virtual const HAlignment getRow( int row ) const;

    /** erases an row from the multiple alignment
     *
     * @param row row to erase.
     * */
    virtual void eraseRow( int row );

    /** return true, if a column is aligned.
     *
     * Unaligned columns result from adding
     * new sequences to the multiple alignment.
     *
     * @return true, if column @col is aligned.
     * */
    virtual bool isAligned( const Position & col );

    /* ------------------ mutators ----------------------------------------------------------- */

    /** add an @ref Alignment object to the multiple alignment.
     *
     * The alignment object maps the sequence to multiple alignment columns.
     *
	@param src	 @ref Alignment object to add.
	@param alignment @ref Alignment that maps src to mali.
    */
    virtual void add(
    		const HAlignment & map_mali2sequence );

    /** add a @ref MultAlignment object to the multiple alignment.
     *
     * The alignment object maps the sequence to multiple alignment columns.
     * Note that some alignment information can be potentially lost. If two
     * sequence positions are aligned in @param src, but that column is not
     * in map_mali2sequence, then the alignment of these two residues is lost.
     *
	@param src	 @ref Alignment object to add.
	@param alignment @ref Alignment that maps src to mali.
    */
    virtual void add(
    		const HMultAlignment & src,
    		const HAlignment & map_mali2sequence );


    /** returns true, if the alignment is empty.
     *
     * @return true, if the alignment is emtpy.
     * */
    virtual bool isEmpty() const;

    /** clears the multiple alignment
    */
    virtual void clear();

    /** returns a clone of this object
     * @return a copy of this object.
     * */
    virtual HMultAlignment getClone() const;

    /** returns a new object of this type.
     * @return a new object of this type.
     * */
    virtual HMultAlignment getNew() const ;

    /** write the multiple alignment to a stream
     *
     * @param output output stream.
    */
    virtual void write( std::ostream & output ) const ;

 protected:
    /** free all memory. Tell all stored objects to destruct themselves */
    virtual void freeMemory();

    /** I store an array of handles to alignatum objects. */
    mutable std::vector<HAlignment> mRows;

    /** flag for recording aligned columns */
    mutable std::vector<bool> mIsAligned;

    /** the length of the multiple alignment */
    mutable int mLength;

 private:

	 /** update the aligned flag mapping onto new */
	 virtual void updateAligned(
			 const HAlignment & map_mali2sequence );

};


}

#endif /* IMPL_MULTIPLE_ALIGNMENT_H */

