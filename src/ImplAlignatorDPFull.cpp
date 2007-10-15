/*
  alignlib - a library for aligning protein sequences

  $Id: ImplAlignatorDPFull.cpp,v 1.1 2005/02/24 11:08:24 aheger Exp $

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
#include "alignlib.h"
#include "AlignlibDebug.h"
#include "AlignException.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>      


#include "SubstitutionMatrix.h"
#include "HelpersSubstitutionMatrix.h"
#include "ImplSubstitutionMatrixAA.h"

#include "Alignata.h"
#include "HelpersAlignata.h"

#include "Alignandum.h"
#include "ImplAlignatorDPFull.h"
#include "Alignator.h"

//implementation of Alignandum-objects
#include "ImplSequence.h"
#include "ImplProfile.h"

#include "ImplTranslator.h" // for direct access to mask_code


#ifdef WITH_DMALLOC
#include <dmalloc.h>
#endif

using namespace std;

namespace alignlib
{

  Alignator * makeAlignatorDPFull( AlignmentType alignment_type,
				   Score gop, Score gep,
				   bool penalize_left,
				   bool penalize_right )
  {
    return new ImplAlignatorDPFull( alignment_type, gop, gep, gop, gep,
				    penalize_left, penalize_right, penalize_left, penalize_right);
  }
  
  /* How to write a fast algorithm:
     My design objective here was to not duplicate the algorithmic code without penalizing too much
     for function indirection. It the way I do it below, there is one indirection for every call to
     calculate a match function, except for sequence-sequence comparisons, where there would have been
     two.

  */
       
  //<--------------< Global functions and pointers for fast determination of match score. >-------
  // I don't know how to use member functions as function pointers. After all, this is what inheritence is for. A possibility would be
  // to automatically subclass an alignator-object.However, I do not like this idea, since this assumes that the parent has information 
  // about the child. On the other hand, via the inlining mechanism a function call could be saved. The problem is when you want to change
  // the algorithm by overloading align. Then the parent functions () do not know, what the child is. Therefore I use the static 
  // functions. Maybe it is possible to separate the algorithm and the type-decision into different classes that interact.
  //
  // The danger of static functions is that the global pointers are unsafe, i.e. there exist just one copy for all alignator-objects, and
  // this code will never be threadsafe.
  //----------------------------------------------------------------------------------------------

  ImplAlignatorDPFull::ImplAlignatorDPFull( AlignmentType alignment_type, 
					    Score row_gop, Score row_gep, 
					    Score col_gop, Score col_gep,
					    bool penalize_row_left, bool penalize_row_right,
					    bool penalize_col_left, bool penalize_col_right) :
    ImplAlignatorDP( alignment_type, row_gop, row_gep, col_gop, col_gep,
		     penalize_row_left, penalize_row_right, penalize_col_left, penalize_col_right ), 
    mTraceMatrix(NULL), mTraceRowStarts(NULL), mRowFrom(0),
    mRowLast(0), mColLast(0)
  {
  }
  
  //----------------------------------------------------------------------------------------------
  ImplAlignatorDPFull::ImplAlignatorDPFull( const ImplAlignatorDPFull & src ) : ImplAlignatorDP( src ) 
{
  debug_func_cerr(5);


    mTraceMatrix = NULL;
    mTraceRowStarts = NULL;
    mRowFrom = 0;
    mRowLast = 0;
    mColLast = 0;

    mPenalizeRowLeft = src.mPenalizeRowLeft;
    mPenalizeRowRight = src.mPenalizeRowRight;
    mPenalizeColLeft = src.mPenalizeColLeft;
    mPenalizeColRight = src.mPenalizeColRight;
    
  }

  //------------------------------------------------------------------------------------------------
  ImplAlignatorDPFull::~ImplAlignatorDPFull() 
{
  debug_func_cerr(5);


  }

  //------------------------------------------------------------------------------------------------
  void ImplAlignatorDPFull::startUp(const Alignandum * row, const Alignandum *col, Alignata * ali)
  
{
  debug_func_cerr(5);


    
    ImplAlignatorDP::startUp(row, col, ali);  

    mRowLast = 0;
    mColLast = 0;
    
    //---------------------------------------------
    // setup Traceback-matrix
    // - matrix can have variable length per row
    // - there is a 0 element in each col (col_front - 1).

    mTraceRowStarts = new TraceIndex[mIterator->row_size() + 1];
    mTraceRowStarts[0] = 0;
    Iterator2D::const_iterator rit(mIterator->row_begin()), rend(mIterator->row_end());
    mRowFrom = *rit;
    TraceIndex matrix_size = 0;
    for (unsigned x = 1; rit != rend; ++rit, ++x)
      {
	matrix_size += 1 + mIterator->col_size( *rit );
	mTraceRowStarts[x] = matrix_size;
	debug_cerr( 5, "x=" << x << " matrix_size=" << matrix_size << " col_size=" << mIterator->col_size(*rit));
      }
    
    mTraceMatrix = new TraceEntry[matrix_size];
    for (TraceIndex i = 0; i < matrix_size; i++)
      mTraceMatrix[i] = TB_STOP;
    
  }
  
  //--------------------------------------------------------------------------------------------------------------
  void ImplAlignatorDPFull::cleanUp(const Alignandum * row, const Alignandum *col, Alignata * ali)
  {
    if (mTraceMatrix != NULL) { delete [] mTraceMatrix; mTraceMatrix = NULL; }
    if (mTraceRowStarts != NULL) { delete [] mTraceRowStarts; mTraceRowStarts = NULL; }    
    
    ImplAlignatorDP::cleanUp(row, col, ali);
  }       

  //-------------------------------------< BackTrace >----------------------------------------------------------------------

  // wrapping around for col but not for row, because otherwise there could be an infinite loop.
#define PREVCOL { if (--col < 1) col = mColLength; }  
  void ImplAlignatorDPFull::traceBack( const Alignandum * prow, const Alignandum * pcol, Alignata * result) 
{
  debug_func_cerr(5);

 
    int t;

#ifdef DEBUG
    {
      std::cout << "Trace matrix" << endl;
      
      {
	std::cout << setw(6) << " ";
	for (Position c = 0; c <= mIterator->col_size(); ++c) cout << setw(4) << c;
	std::cout << endl;
      }

      Iterator2D::const_iterator rit(mIterator->row_begin()), rend(mIterator->row_end());
      for (; rit != rend; ++rit)
	{
	  Position row = *rit;
	  cout << setw(6) << row;	  
	  Iterator2D::const_iterator cit(mIterator->col_begin(row)), cend(mIterator->col_end(row));
	  for (Position col = 0; col <= mIterator->col_size(); ++col)
	    {
	      cout << setw(4);
	      switch (mTraceMatrix[getTraceIndex(row,col)])
		{
		case TB_STOP:      cout << "o" ; break;
		case TB_DELETION:  cout << "<" ; break;
		case TB_INSERTION: cout << "^" ; break;
		case TB_MATCH:     cout << "=" ; break;
		case TB_WRAP:	   cout << "@" ; break;
		default: cout << "#"; break;
		}
	    }
	  std::cout << endl;
	}
      std::cout << "traceback starts in cell ("<< mRowLast << "," << mColLast << ") with score " << mScore << std::endl;
    }
    
#endif
 
    Position col = mColLast;
    Position row = mRowLast;
    int ngaps = 0;

    t = mTraceMatrix[getTraceIndex(row,col)];

    while ( t != TB_STOP && row > 0) 
{
  debug_func_cerr(5);

      switch (t) {
      case TB_DELETION :
	col--;
	ngaps++;
	if (col < 1) 
	  row--;
	break;
      case TB_INSERTION :
	ngaps++;
	row--;
	break;
      case TB_MATCH :
	result->addPair( new ResiduePAIR( row, col, mScorer->getScore( row, col)));
	row--;
	col--;
	break;
      case TB_WRAP :
	col = mIterator->col_back( row );
	break;
      default:
	throw AlignException("Unknown matrix command in TraceBack");
	break;
      }
      t = mTraceMatrix[getTraceIndex(row,col)];
    }
    result->setScore ( mScore );
  }  

  //---------------------------------< the actual alignment algorithm >-------------------------------------------

  //-----------------------------------------------------------------------------------  
  void ImplAlignatorDPFull::performAlignment( const Alignandum * prow, const Alignandum * pcol, Alignata * ali)
  {

    Score row_gop = getRowGop();
    Score row_gep = getRowGep();
    Score col_gop = getColGop();
    Score col_gep = getColGep();

    Score c, e, d, s;                  // helper variables
    c = e = d = s = 0;
    
    Score row_m = row_gop + row_gep;
    Score col_m = col_gop + col_gep;

    /*
      ------> col
      | CC-> 
      | DD->
      |
      |
      row
    
      For each cell:
        s   mCC/mDD   
         \  |
          \ |
      c/e-- x
    
      c/mCC: last op was match
      e/mDD: last op was gap
    */
  
    //---> Initialise affine penalty arrays <--------------------------
    
    //-----------------------------------------------------------------
    {
      
      Position row = mIterator->row_front();
      Iterator2D::const_iterator cit(mIterator->col_begin(row)), cend(mIterator->col_end(row));
      mCC[0] = 0;
	  
      switch (mAlignmentType)
	{
	case ALIGNMENT_LOCAL:
	  for (; cit != cend; ++cit)
	    {
	      Position col = *cit;	    
	      mCC[col]   = 0;
	      mDD[col]   = row_gop;                               // score for horizontal gap opening
	    }
	  mCC[mIterator->col_back()] = col_gop;
	  break;
	case ALIGNMENT_WRAP:      
	  for (; cit != cend; ++cit)
	    {
	      Position col = *cit;	    
	      mCC[col]   = 0;
	      mDD[col]   = row_gop;                               // score for horizontal gap opening
	    }
	  mCC[mIterator->col_back()] = col_gop;
	  break;
	case ALIGNMENT_GLOBAL:
	  /* set initial values for upper border */      
	  if (mPenalizeRowLeft)
	    {
	      for (; cit != cend; ++cit)
		{
		  Position col = *cit;	    
		  mCC[col]   = row_gop + row_gep * col;
		  mDD[col]   = mCC[col];                              // add score for gap opening
		}
	    }
	  else
	    {
	      for (; cit != cend; ++cit)
		{
		  Position col = *cit;	    		
		  mCC[col]   = 0;
		  mDD[col]   = row_gop;                               // add score for gap opening
		}
	    }
	}
    }
    
    //----------------------------> Calculate dynamic programming matrix <----------------------------
    //----------------------------> iterate over rowumns <--------------------------------------------
    Iterator2D::const_iterator rit(mIterator->row_begin()), rend(mIterator->row_end());

#ifdef DEBUG
    std::cout << "maximum size= "
	      << mIterator->row_front() << "-" <<  mIterator->row_back() << ":" << mIterator->row_size() << " " 
	      << mIterator->col_front() << "-" <<  mIterator->col_back() << ":" << mIterator->col_size() << std::endl;
    std::cout << mPenalizeRowLeft << " " << mPenalizeRowRight << " " << mPenalizeColLeft << " " << mPenalizeColRight << std::endl;
#endif
    

    for (; rit != rend; ++rit)
      {
	Position row = *rit;
	Position row_length = mIterator->row_size();
	Position row_from   = mIterator->row_front( row );
	Position col_length = mIterator->col_size( row );

	Iterator2D::const_iterator cit(mIterator->col_begin(row)), cend(mIterator->col_end(row));
	Position col_from = *cit;
	
	switch (mAlignmentType)
	  {
	  case ALIGNMENT_LOCAL:
	    s = mCC[col_from - 1];
	    mCC[col_from - 1] = c = 0;
	    e = col_gop;  // penalty for opening a vertical gap
	    break;
	  case ALIGNMENT_WRAP:
	    // the wrapping around part	  
	    if (mCC[col_length] > 0)
	      {
		mCC[col_from - 1] = c = mCC[col_length];
		mTraceMatrix[getTraceIndex(row-1,0)] = TB_WRAP;
	      }
	    else
	      {
		mCC[col_from - 1] = c = 0;
	      }
	    
	    s = mCC[col_from - 1];
	    e = col_gop; // penalty for opening a vertical gap
	    break;
	  case ALIGNMENT_GLOBAL:
	    /* set initial values for left border */
	    if (mPenalizeColLeft)
	    {
	      e = c = col_gop + col_gep * row;
	      s = mCC[col_from-1];
	      mCC[0] += col_gep;
	      if (row == row_from)
		mCC[0] += col_gop;
	    }
	    else
	      {
		s = 0;
		c = 0;
		e = col_gop;
	      }
	    break;
	  }

	//-------------------------> iterate over cols <------------------------------------------------	
	for (; cit != cend; ++cit)
	  {
	    Position col = *cit;

	    //---------------------------> calculate scores <--------------------------------------------
	    // c contains score of cell left
	    // s contains score for cell [row-1, col-1]
	    // e is better of: score for opening a vertical gap or score for extending a vertical gap: use col-gap-penalties
	    if ((c =   c      + col_m) > (e =      e   + col_gep))  e = c;
	    // d is better of: score for opening a horizontal gap or score for extending a horizontal gap
	    if ((c = mCC[col] + row_m) > (d = mDD[col] + row_gep))  d = c;
	    
	    // c is score for a match
	    c = s + mScorer->getScore(row,col);

	    // put into c the best of all possible cases
	    if (e > c) c = e;
	    if (d > c) c = d;
	    
	    //--------------------------> recurrence relation <-------------------------------------------------
	    if (mAlignmentType == ALIGNMENT_LOCAL && c <= 0)
	      {
		c = 0;                                                  // the local alignment part
	      }
	    else
	      {
		if ( c == d )                   // horizontal gap
		  mTraceMatrix[getTraceIndex(row,col)] = TB_INSERTION;
		else if ( c == e )              // vertical gap
		  mTraceMatrix[getTraceIndex(row,col)] = TB_DELETION;
		else                           // match
		  mTraceMatrix[getTraceIndex(row,col)] = TB_MATCH;
	      }

#ifdef DEBUG
	    std::cout << " row=" << row << " col=" << col << " c=" << c << " e=" << e << " d=" << d << " s=" << s
		      << " mCC=" << mCC[col] << " mDD=" << mDD[col]
		      << " index=" << getTraceIndex(row,col) <<  " ";
	    
	    if ( c == d )                   // horizontal gap
	      std::cout << "insertion" << std::endl;
	    else if ( c == e )              // vertical gap
	      std::cout << "deletion" << std::endl;
	    else                           // match
	      std::cout << "match" << std::endl;	      
#endif
	    
	    s = mCC[col];
	    mCC[col] = c;                                              // save new score for next i
	    mDD[col] = d;

	    /* retrieve maximum score. If penalty has to be paid for right end-gaps, 
	       then restrict search correspondingly;
	    */
	    if (mAlignmentType == ALIGNMENT_GLOBAL)
	      {
		if (mPenalizeRowRight && row < row_length) 
		  continue;
		if (mPenalizeColRight && col < col_length) 
		  continue;
	      }
	    
	    if (mScore < c)
	      {                                            // save maximum
		mScore   = c;
		mRowLast = row;
		mColLast = col;
	      }
	  }
      }
    
    traceBack(prow, pcol, ali);
  }
  
} // namespace alignlib