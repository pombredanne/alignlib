/*
  alignlib - a library for aligning protein sequences

  $Id: ImplMultipleAlignment.h,v 1.5 2004/03/19 18:23:41 aheger Exp $

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

#ifndef IMPL_MULTIPLE_ALIGNMENT_H
#define IMPL_MULTIPLE_ALIGNMENT_H 1

#include <iosfwd>
#include <string>
#include <list>

#include "alignlib.h" 
#include "MultipleAlignment.h"

namespace alignlib {

class Alignandum;
class Alignatum;
class Alignata;	
class Renderer;


/**
    @short Implementation class for multiple alignments.

    This class keeps a vector of Alignatum objects. If a new
    @ref Alignatum object is added, gaps have to be added to all previously added
    @ref Alignatum objects, so this can be a costly operation. However, this class
    is efficient for pile-up alignments, with an ungapped query sequence at the
    top.
    
    @author Andreas Heger
    @version $Id: ImplMultipleAlignment.h,v 1.5 2004/03/19 18:23:41 aheger Exp $
*/
class ImplMultipleAlignment : public MultipleAlignment {

  // class member functions
 public:

    // constructors and desctructors
    /** empty constructor 
     */
    ImplMultipleAlignment  ();

    /** copy constructor */
    ImplMultipleAlignment  (const ImplMultipleAlignment &);

    /** destructor */
    virtual ~ImplMultipleAlignment ();

    //---------------------------------------------------------------------------------------
    /*------- accessors --------------------------------------------------------------------*/
    /** returns the length of the multiple alignment. All objects in a multiple alignment have
	the same length */
    virtual Position getLength() const;

    /** sets the length of the multiple alignment. Raises an exception, if the mali is not empty
	*/
    virtual void setLength( Position length);

    /** returns the width of the multiple alignment, i.e., the number of objects in this multiple
	alignment */
    virtual int getWidth() const;
    
    /** returns a const reference to the object at row in the multiple alignment. This allows treating
	the multiple alignment as a two-dimensional matrix. Since string does define operator[] as well, you
	can access the symbol in column c and row r by calling 
	symbol =  multiple_alignment[r][c]
    */
    virtual const std::string & operator[]( int row ) const;		

    /** returns a pointer to the object at row from the multiple alignment. The pointer is not const,
	so you are free to do all sort of ugly stuff.*/
    virtual Alignatum * getRow( int row ) const;
    
    /** erases an entry form the multiple alignment */
    virtual void eraseRow( int row );

    /* ------------------ mutators ----------------------------------------------------------- */

    /*------------------- functions for adding new members to the multiple alignment---------*/

    /** add an aligned object to the multiple alignment. Ownership of this object is transferred to
	the multiple alignment. 
	@param src	       pointer to the aligned object to be added.
	@param alignment pointer to the alignment used for combining these two objects. If it is
		       not supplied, then it is assumed, that it is the identity alignment. In
		       that case src has to have the same length the multiple alignment. Note, the
		       multiple alignment is in col, the src is in row of the multiple alignment, so
		       when calling the member-function Alignata::Map() with a residue from
		       src, you get the correct position in the multiple alignment.
    */
    virtual void add( Alignatum * src,
		      const Alignata * alignment = NULL,
		      bool mali_is_in_row = true,
		      bool insert_gaps_mali = true,
		      bool insert_gaps_alignatum= true,
		      bool use_end_mali = false,
		      bool use_end_alignatum = false);

    /** add the contents of a multiple alignment to the multiple alignment by mapping it through an alignment
	@param src	       pointer to the unaligned object to be added.
	@param alignment pointer to the alignment used for combining these two objects. If it is
		       not supplied, then it is assumed, that it is the identity alignment. In
		       that case src has to have the same length the multiple alignment. Note, the
		       multiple alignment is in col, the src is in row of the multiple alignment, so
		       when calling the member-function Alignata::Map() with a residue from
		       src, you get the correct position in the multiple alignment.
     */
    virtual void add( const MultipleAlignment * src,
		      const Alignata * alignment = NULL,
		      bool mali_is_in_row = true,
		      bool insert_gaps_mali = true,
		      bool insert_gaps_alignatum= true,
		      bool use_end_mali = false,
		      bool use_end_alignatum = false);
    
    /** returns the consensus string for the multiple alignment */
    virtual std::string getConsensusString () const ;			

    /** register a new renderer */
    virtual void registerRenderer( const Renderer * renderer );

    /** returns true, if there are no aligned objects in this alignment */
    virtual bool isEmpty() const;

    /** clears the multiple alignment */
    virtual void clear();

    /** returns a clone of this object */
    virtual MultipleAlignment * getClone() const;
    
    /** returns an empty version of this object */
    virtual MultipleAlignment * getNew() const;

    /** Write the multiple alignment to a stream
     */
    virtual void write( std::ostream & output, 
			Position segment_from = 0, 
			Position segment_to = 0) const ;

    /** Read a multiple alignment form a stream. I am not quite sure
	how this will work, because there might be different @ref Alignata
	objects in there.
     */
    virtual void read( std::istream & );
    
 protected:
    /** free all memory. Tell all stored objects to destruct themselves */
    void freeMemory();

 private:
    /** the length of the multiple alignment */
    mutable int mLength;                       
    
    /** I store an array of vectors. The pointers can not be const, because sequences are told to rescale. */
    std::vector<Alignatum *> mRows;             

    /** the Renderer */
    const Renderer * mRenderer;
    
};


}

#endif /* IMPL_MULTIPLE_ALIGNMENT_H */
