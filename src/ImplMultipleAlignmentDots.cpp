/*
  alignlib - a library for aligning protein sequences

  $Id: ImplMultipleAlignmentDots.cpp,v 1.3 2004/03/19 18:23:41 aheger Exp $

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
#include <fstream>
#include <iomanip>
#include <vector>
#include "alignlib.h"
#include "AlignlibDebug.h"

#include "HelpersProfile.h"
#include "ImplMultipleAlignmentDots.h"
#include "HelpersMultipleAlignment.h"
#include "AlignException.h"
#include "Alignatum.h"
#include "Alignandum.h"
#include "Alignata.h"
#include "HelpersAlignata.h"
#include "AlignataIterator.h"

#ifdef WITH_DMALLOC
#include <dmalloc.h>
#endif

using namespace std;

namespace alignlib {

/** factory functions */
//---------------------------------------------------------< constructors and destructors >--------------------------------------
ImplMultipleAlignmentDots::ImplMultipleAlignmentDots ( bool compress_unaligned_columns,
						       int max_insertion_length) : 
  mLength(0), mRenderer( NULL ),
  mCompressUnalignedColumns( compress_unaligned_columns),
  mMaxInsertionLength( max_insertion_length) {
}
		       
//--------------------------------------------------------------------------------------------------------------
ImplMultipleAlignmentDots::~ImplMultipleAlignmentDots () {
  freeMemory();
}

//--------------------------------------------------------------------------------------------------------------
ImplMultipleAlignmentDots::ImplMultipleAlignmentDots (const ImplMultipleAlignmentDots & src ) : 
    mLength (src.mLength), 
    mRenderer( src.mRenderer), 
    mCompressUnalignedColumns( src.mCompressUnalignedColumns ),
    mMaxInsertionLength( src.mMaxInsertionLength )
{

  // clear old entries
  freeMemory();

  // add clones of the new entries
  for (unsigned int row = 0; row < src.mRows.size(); row++) 
    mRows.push_back( MaliRow( src.mRows[row].mAlignatumInput->getClone(), 
			      src.mRows[row].mMapMali2Alignatum->getClone(), 
			      src.mRows[row].mAlignatumOutput->getClone()));

}

//--------------------------------------------------------------------------------------------------------------
void ImplMultipleAlignmentDots::freeMemory() 
{
  debug_func_cerr(5);

  
  unsigned int nrows = mRows.size();

  for (unsigned int row = 0; row < nrows; ++row) {
    delete mRows[row].mAlignatumInput;
    delete mRows[row].mMapMali2Alignatum;
    delete mRows[row].mAlignatumOutput;
  }

  mRows.clear();

}

//--------------------------------------------------------------------------------------------------------------
Position ImplMultipleAlignmentDots::getLength() const {
  updateRows();
  return mLength;
}

//--------------------------------------------------------------------------------------------------------------
void ImplMultipleAlignmentDots::setLength( Position length) {
  if (mLength != 0)
    throw AlignException("In ImplMultipleAlignmentDots.cpp: length given for DotsMali");
  mLength = 0;
}

//--------------------------------------------------------------------------------------------------------------
int ImplMultipleAlignmentDots::getWidth() const {
  return mRows.size();
}

//-----------------------------------------------------------------------------------------------------------  
const std::string & ImplMultipleAlignmentDots::operator[]( int row ) const {
  updateRows();
  return mRows[row].mAlignatumOutput->getStringReference();
}

//-----------------------------------------------------------------------------------------------------------
Alignatum * ImplMultipleAlignmentDots::getRow( int row ) const {
  updateRows();
  return mRows[row].mAlignatumOutput;
}

//-----------------------------------------------------------------------------------------------------------
void ImplMultipleAlignmentDots::clear() {
  freeMemory();
  mLength = 0;
  mRenderer = NULL;
}

//-----------------------------------------------------------------------------------------------------------
void ImplMultipleAlignmentDots::eraseRow( int row ) {
    //!! to be implemented
}

//------------------------------------------------------------------------------------
/* add single entry to *this multiple alignment given an alignment.
   in the alignment, the other alignment is in row, *this alignment is in col.
   In contrast to the next method, here src has not to be realigned
*/
void ImplMultipleAlignmentDots::add( Alignatum * src,
				     const Alignata * alignment,
				     bool mali_is_in_row,
				     bool insert_gaps_mali,
				     bool insert_gaps_alignatum,
				     bool use_end_mali,
				     bool use_end_alignatum) 
{
  debug_func_cerr(5);


  Alignata * ali = NULL;

  
  if (alignment == NULL)
    {
      ali = makeAlignataVector();
      fillAlignataIdentity( ali, 1, src->getTrueLength(), 0);
    }
  else
    ali = alignment->getClone();

  mRows.push_back( MaliRow( src, ali ));
  mLength = 0;
}

//------------------------------------------------------------------------------------
/** Add a full multiple alignment to the another alignment.
*/
void ImplMultipleAlignmentDots::add( const MultipleAlignment * src,
				     const Alignata * alignment,
				     bool mali_is_in_row,
				     bool insert_gaps_mali,
				     bool insert_gaps_alignatum,
				     bool use_end_mali,
				     bool use_end_alignatum) 
{
  debug_func_cerr(5);

  
  // do not add empty mali
  if (src->getWidth() == 0) 
    return;
  
  const ImplMultipleAlignmentDots * src_mali = dynamic_cast<const ImplMultipleAlignmentDots*>(src);

  if (!src_mali) {
    std::cerr << "tried to add not a multiple alignment dots object to multiple alignment dots." << std::endl;
    std::cerr << "kill the programmer." << std::endl;
    exit(1);
  }

  for (int x = 0; x < src_mali->getWidth(); ++x) {
    Alignatum * alignatum = src_mali->mRows[x].mAlignatumInput;

    Alignata * map_mali2src = makeAlignataVector();

    if (mali_is_in_row)
      combineAlignata( map_mali2src,
		       alignment,
		       src_mali->mRows[x].mMapMali2Alignatum,
		       CR);
    else
      combineAlignata( map_mali2src,
		       alignment,
		       src_mali->mRows[x].mMapMali2Alignatum,
		       RR);
    
    add( alignatum, map_mali2src,
	 true,
	 insert_gaps_mali, insert_gaps_alignatum,
	 use_end_mali, use_end_alignatum);
    
    delete map_mali2src;
    
  }
  
  mLength = 0;  
  
}

//---------------------------------------------------------------------------------------
// return consensus string of multiple alignment
std::string ImplMultipleAlignmentDots::getConsensusString() const 
{
  debug_func_cerr(5);


  std::string result("");
  
  Alignandum * profile = makeProfile( this );

  for( int column = 1; column <= mLength; column++)
    result += profile->asChar( column );

  delete profile;
  return (result);
}

//---------------------------------------------------------------------------------------
MultipleAlignment * ImplMultipleAlignmentDots::getClone() const {
  return new ImplMultipleAlignmentDots( *this );
}    

//---------------------------------------------------------------------------------------
MultipleAlignment * ImplMultipleAlignmentDots::getNew() const {
  return new ImplMultipleAlignmentDots();
}    

//---------------------------------------------------------------------------------------
bool ImplMultipleAlignmentDots::isEmpty() const {
    return mRows.empty();
}

//---------------------------------------------------------------------------------------
void ImplMultipleAlignmentDots::registerRenderer( const Renderer * renderer) {
  mRenderer = renderer;
}
    
//---------------------------------------------------------< Input/Output routines >--------

//------------------------------------------------------------------------------------
 void ImplMultipleAlignmentDots::write( std::ostream & output,
					Position segment_from, 
					Position segment_to) const 
{
  debug_func_cerr(5);


  updateRows();
  
  for (unsigned int row = 0; row < mRows.size(); row++) {
    mRows[row].mAlignatumOutput->writeRow( output, segment_from, segment_to, mRenderer );
    output << endl;
  }

}

//-----------------------------------------------------------------------------------
void ImplMultipleAlignmentDots::read( std::istream & input) {
    //!! to be implemented
}

//---------------------------------------------------------------------------------------
void ImplMultipleAlignmentDots::updateRows() const {

  // do nothing, if no changes
  if (mLength != 0) return;

  Position mali_length = 0;

  // find number of aligned columns in mali
  for (unsigned int x = 0; x < mRows.size(); ++x) 
    mali_length = std::max( mali_length, mRows[x].mMapMali2Alignatum->getRowTo());

  // find total/maximum insertions before a given mali column
  std::vector<int> gaps(mali_length + 1, 0);
  {
    for (unsigned int x = 0; x < mRows.size(); ++x) {
      Alignata * ali = mRows[x].mMapMali2Alignatum;

      Position last_col = ali->getColFrom();
      
      for (Position row = ali->getRowFrom() + 1; row <= ali->getRowTo(); ++row) {
	Position col = ali->mapRowToCol(row);
	if (col != 0) {
	  if (mCompressUnalignedColumns) {
	    if (mMaxInsertionLength >= 0)
	      gaps[row] = std::min( std::max( gaps[row], col - last_col - 1 ), mMaxInsertionLength);
	    else
	      gaps[row] = std::max( gaps[row], col - last_col - 1 );
	  } else {
	    gaps[row] += col - last_col - 1;
	  }
	  last_col = col;
	}
      }
    }
  }

#ifdef DEBUG
  debug_cerr( 5, "length=" << mali_length );  
  for (unsigned int x = 1; x < gaps.size(); ++x) 
    debug_cerr( 5, "col=" << x << " gaps=" << gaps[x]);
#endif

  Alignata * map_mali2representation = makeAlignataVector(); 
  {
    Position y = 1;
    for (Position x = 1; x <= mali_length; ++x) {
      y += gaps[x];
      map_mali2representation->addPair( x, y++, 0 );
    }
  }

#ifdef DEBUG
  std::cout << "map_mali2representation\n" << *map_mali2representation << std::endl;
#endif
  
  mLength = map_mali2representation->getColTo();

  std::vector<int>used_gaps(mali_length + 1, 0);

  for (unsigned int x = 0; x < mRows.size(); ++x) {
    
    delete mRows[x].mAlignatumOutput;
    mRows[x].mAlignatumOutput = mRows[x].mAlignatumInput->getClone();
    
    Alignata * map_alignatum2representation = makeAlignataVector(); 
    
    combineAlignata( map_alignatum2representation, mRows[x].mMapMali2Alignatum, map_mali2representation, RR);

    // map alignatum-object
    if (mCompressUnalignedColumns) {
      mRows[x].mAlignatumOutput->mapOnAlignment( map_alignatum2representation, 
						 mLength,
						 true );
    } else {
      Alignata * ali = mRows[x].mMapMali2Alignatum;
      // add pairs for gaps 
      Position last_col = ali->getColFrom();
      for (Position row = ali->getRowFrom() + 1; row <= ali->getRowTo(); ++row) {

	Position col = ali->mapRowToCol(row);

	if (col != 0) {
	  unsigned int u = map_mali2representation->mapRowToCol(row) - gaps[row] + used_gaps[row];
	  unsigned int d = col - last_col - 1;
	  while (col - last_col - 1 > 0) {
	    map_alignatum2representation->addPair( ++last_col, u++, 0);
	  }
	  used_gaps[row] += d;
	  last_col = col;
	}
      }				   
      mRows[x].mAlignatumOutput->mapOnAlignment( map_alignatum2representation, 
						 mLength,
						 false );	
      
    }

#ifdef DEBUG    
    std::cout << "map_alignatum2representation\n" << *map_alignatum2representation << std::endl;
#endif

    delete map_alignatum2representation;
  }

  delete map_mali2representation;
}

} // namespace alignlib




