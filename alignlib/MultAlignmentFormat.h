#ifndef Mult_ALIGNMENT_FORMAT_H_
#define Mult_ALIGNMENT_FORMAT_H_

//--------------------------------------------------------------------------------
// Project alignlib
//
// Copyright (C) 2000 Andreas Heger All rights reserved
//
// Author: Andreas Heger <heger@ebi.ac.uk>
//
// $Id$
//--------------------------------------------------------------------------------

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <iosfwd>
#include <string>

#include "alignlib_fwd.h"

namespace alignlib
{

/**
 *
 * @defgroup MulitpleAlignmentFormats MultAlignment formats.
 * @{
 *
 * MulitpleAlignment formats convert @ref MulitpleAlignment objects into various text based formats and back.
 * Member data is publicly available for easy access in your own formatting functions.
 *
 * Usage example:
 * @code
 *
 * @endcode
 */

/** Base class for Mult alignment formats.
 *
 * 	This is a convenience structure for importing/exporting
 *	Mult alignments.
 *
 *  This class keeps track of alignment coordinates.
 *
 *  @author Andreas Heger
 *  @version $Id$
 *  @short Base class for Mult alignment formats.
 *
 */
struct MultAlignmentFormat
{
	// class member functions
	friend std::ostream & operator<<( std::ostream &, const MultAlignmentFormat &);
	friend std::istream & operator>>( std::istream &, MultAlignmentFormat &);

	// constructors and desctructors
	MultAlignmentFormat ();

	MultAlignmentFormat(
			const HMultAlignment & src,
			const HStringVector & sequences );

	MultAlignmentFormat( std::istream & src);

	MultAlignmentFormat( const std::string & src);

	/** copy constructor */
	MultAlignmentFormat( const MultAlignmentFormat &);

	virtual ~MultAlignmentFormat();

	/** fill format from Mult alignment
	 *
	 *	@param src Mult alignment to parse
	 */
	virtual void fill(
			const HMultAlignment & src,
			const HStringVector & sequences);

	/** fill alignment from format
	 *
	 * @param dest Alignment
	 * @param templ template @ref Alignment to use in multiplea alignment
	 */
	virtual void copy( HMultAlignment & dest,
			const HAlignment & templ) const;

	/** save alignment to stream
	 */
	virtual void save( std::ostream & ) const;

	/** load alignment from stream
	 */
	virtual void load( std::istream &);

	/** Representation of the mali using Alignatum objects
	 */
	AlignatumVector mData;

};

/**
	Plain Mult alignment format.

	The mali is output in rows.

   	@author Andreas Heger
   	@version $Id$
   	@short Plain Mult alignment format

*/
struct MultAlignmentFormatPlain : public MultAlignmentFormat
{
	// constructors and desctructors
	MultAlignmentFormatPlain ();

	MultAlignmentFormatPlain(
			const HMultAlignment & src,
			const HStringVector & sequences );

	MultAlignmentFormatPlain( std::istream & src);

	MultAlignmentFormatPlain( const std::string & src);

	/** copy constructor */
	MultAlignmentFormatPlain (const MultAlignmentFormatPlain &);

	virtual ~MultAlignmentFormatPlain ();

	/** fill blocks from alignment
		@param src Alignment to parse
	 */
	virtual void fill(
			const HMultAlignment & src,
			const HStringVector & sequences);

	/** save alignment to stream
	 */
	virtual void save( std::ostream & ) const;

	/** load alignment from stream
	 */
	virtual void load( std::istream &);

};


/** @} */

}

#endif
