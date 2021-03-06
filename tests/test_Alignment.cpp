/*
  alignlib - a library for aligning protein sequences

  $Id: test_Alignment.cpp,v 1.4 2004/06/02 12:11:38 aheger Exp $

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

/** Test alignata objects
 */

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

#include <time.h>

#include "alignlib.h"
#include "Alignment.h"
#include "AlignmentIterator.h"
#include "HelpersAlignment.h"
#include "AlignlibDebug.h"

#define BOOST_TEST_MODULE
#include <boost/test/included/unit_test.hpp>
using boost::unit_test::test_suite;

using namespace std;
using namespace alignlib;

bool isIdentical(
		const HAlignment & a,
		const HAlignment & b,
		bool inverse = false)
{

	AlignmentIterator it1(a->begin());
	AlignmentIterator it1_end(a->end());

	AlignmentIterator it2(b->begin());
	AlignmentIterator it2_end(b->end());

	bool is_identical = true;

	for (; it1 != it1_end; ++it1, ++it2)
	{
		if (!inverse)
		{
			if (it1->mRow != it2->mRow && it1->mCol != it2->mCol)
				is_identical = false;
		} else
		{
			if (it1->mRow != it2->mCol && it1->mCol != it2->mRow)
				is_identical = false;
		}
	}

	return is_identical;
}

void checkMove( const HAlignment & a )
{
	{
		HAlignment a_clone( a->getNew() );
		a_clone->moveAlignment( 0, 0);
		a_clone->moveAlignment( 1, 1);
		a_clone->moveAlignment( -1, -1);
		BOOST_CHECK_EQUAL( checkAlignmentIdentity( a_clone, a->getNew() ), true);
	}

	{
		HAlignment a_clone( a->getClone() );
		a_clone->moveAlignment( 0, 0);
		a_clone->moveAlignment( 2, 2);
		a_clone->moveAlignment( -2, -2);
		BOOST_CHECK_EQUAL( checkAlignmentIdentity( a_clone, a ), true);
	}

	if (!a->isEmpty())
	{
		HAlignment a_clone( a->getClone() );
		a_clone->moveAlignment( -a->getRowFrom(), -a->getColFrom());
		BOOST_CHECK_EQUAL( a_clone->getRowFrom(), 0);
		BOOST_CHECK_EQUAL( a_clone->getColFrom(), 0);
		a_clone->moveAlignment( a->getRowFrom(), a->getColFrom());
		BOOST_CHECK_EQUAL( checkAlignmentIdentity( a_clone, a ), true);
	}

	if (!a->isEmpty())
	{
		HAlignment a_clone( a->getClone() );
		BOOST_CHECK_THROW( a_clone->moveAlignment( -a->getRowTo(), 0), AlignlibException);
		BOOST_CHECK_THROW( a_clone->moveAlignment( 0, -a->getColTo()), AlignlibException);
	}
}


void checkInsert( const HAlignment & a )
{
	if (a->isEmpty()) return;

	int insert = 3;
	// insert at start of row
	{
		HAlignment a_clone(a->getClone());
		a_clone->insertRow( 0, insert);
		BOOST_CHECK_EQUAL( a->getRowFrom() + insert, a_clone->getRowFrom() );
		BOOST_CHECK_EQUAL( a->getRowTo() + insert, a_clone->getRowTo());
		BOOST_CHECK_EQUAL( a->getColFrom(), a_clone->getColFrom() );
		BOOST_CHECK_EQUAL( a->getColTo(), a_clone->getColTo() );
	}

	// insert in middle of row
	{
		HAlignment a_clone(a->getClone());
		Position middle = (Position)((a_clone->getRowTo() - a_clone->getRowFrom()) / 2);
		a_clone->insertRow( middle, insert);
		BOOST_CHECK_EQUAL( a->getRowFrom(), a_clone->getRowFrom() );
		BOOST_CHECK_EQUAL( a->getRowTo() + insert, a_clone->getRowTo() );
		BOOST_CHECK_EQUAL( NO_POS, a_clone->mapRowToCol( middle ) );
		BOOST_CHECK_EQUAL( a->mapRowToCol( middle ), a_clone->mapRowToCol( middle + insert ) );
		BOOST_CHECK_EQUAL( a->getColFrom(), a_clone->getColFrom() );
		BOOST_CHECK_EQUAL( a->getColTo(), a_clone->getColTo() );
	}

	// insert at end of row: no insertion
	{
		HAlignment a_clone(a->getClone());
		a_clone->insertRow( a_clone->getRowTo(), insert);
		BOOST_CHECK_EQUAL( a->getRowFrom(), a_clone->getRowFrom() );
		BOOST_CHECK_EQUAL( a->getRowTo(), a_clone->getRowTo() );
		BOOST_CHECK_EQUAL( a->getColFrom(), a_clone->getColFrom() );
		BOOST_CHECK_EQUAL( a->getColTo(), a_clone->getColTo() );
	}

	// insert before row start: the whole alignment shifts
	{
		HAlignment a_clone(a->getClone());
		a_clone->insertRow( a_clone->getRowFrom() - 1, insert);
		BOOST_CHECK_EQUAL( a->getRowFrom() + insert, a_clone->getRowFrom() );
		BOOST_CHECK_EQUAL( a->getRowTo() + insert, a_clone->getRowTo());
		BOOST_CHECK_EQUAL( a->getColFrom(), a_clone->getColFrom() );
		BOOST_CHECK_EQUAL( a->getColTo(), a_clone->getColTo() );
	}

	// insert at start of col
	{
		HAlignment a_clone(a->getClone());
		a_clone->insertCol( 0, insert);
		BOOST_CHECK_EQUAL( a->getColFrom() + insert, a_clone->getColFrom() );
		BOOST_CHECK_EQUAL( a->getColTo() + insert, a_clone->getColTo());
		BOOST_CHECK_EQUAL( a->getRowFrom(), a_clone->getRowFrom() );
		BOOST_CHECK_EQUAL( a->getRowTo(), a_clone->getRowTo() );
	}

	// insert in middle of row
	{
		HAlignment a_clone(a->getClone());
		Position middle = (Position)((a_clone->getColTo() - a_clone->getColFrom()) / 2);
		a_clone->insertCol( middle, insert);
		BOOST_CHECK_EQUAL( a->getColFrom(), a_clone->getColFrom() );
		BOOST_CHECK_EQUAL( a->getColTo() + insert, a_clone->getColTo() );
		BOOST_CHECK_EQUAL( NO_POS, a_clone->mapColToRow( middle ) );
		BOOST_CHECK_EQUAL( a->mapColToRow( middle ), a_clone->mapColToRow( middle + insert ) );
		BOOST_CHECK_EQUAL( a->getRowFrom(), a_clone->getRowFrom() );
		BOOST_CHECK_EQUAL( a->getRowTo(), a_clone->getRowTo() );
	}

	// insert at end of row: no insertion
	{
		HAlignment a_clone(a->getClone());
		a_clone->insertCol( a_clone->getColTo(), insert);
		BOOST_CHECK_EQUAL( a->getColFrom(), a_clone->getColFrom() );
		BOOST_CHECK_EQUAL( a->getColTo(), a_clone->getColTo() );
		BOOST_CHECK_EQUAL( a->getRowFrom(), a_clone->getRowFrom() );
		BOOST_CHECK_EQUAL( a->getRowTo(), a_clone->getRowTo() );
	}

	// insert before Col start: the whole alignment shifts
	{
		HAlignment a_clone(a->getClone());
		a_clone->insertCol( a_clone->getColFrom() - 1, insert);
		BOOST_CHECK_EQUAL( a->getColFrom() + insert, a_clone->getColFrom() );
		BOOST_CHECK_EQUAL( a->getColTo() + insert, a_clone->getColTo());
		BOOST_CHECK_EQUAL( a->getRowFrom(), a_clone->getRowFrom() );
		BOOST_CHECK_EQUAL( a->getRowTo(), a_clone->getRowTo() );
	}

}

void checkMap( const HAlignment & a )
{
	if (a->isEmpty()) return;

	{
		HAlignment clone(a->getClone());
		clone->map( a, RR);
		BOOST_CHECK_EQUAL( clone->getNumAligned(), a->getNumAligned() );
		AlignmentIterator it(clone->begin()), end(clone->end());
		for (;it!=end;++it)
			BOOST_CHECK_EQUAL( it->mRow, it->mCol );
	}

	{
		HAlignment clone(a->getClone());
		clone->map( a, CC);
		BOOST_CHECK_EQUAL( clone->getNumAligned(), a->getNumAligned() );
		AlignmentIterator it(clone->begin()), end(clone->end());
		for (;it!=end;++it)
			BOOST_CHECK_EQUAL( it->mRow, it->mCol );
	}

	{
		HAlignment clone(a->getClone());
		clone->map( a, RC);
		AlignmentIterator it(a->begin()), end(a->end());
		for (;it!=end;++it)
		{
			if (it->mRow == it->mCol)
				BOOST_CHECK_EQUAL( it->mRow, clone->mapRowToCol(it->mRow) );
			else if (a->mapColToRow( it->mRow ) != NO_POS)
				BOOST_CHECK_EQUAL( a->mapColToRow(it->mRow), clone->mapColToRow(it->mCol) );
			else
				BOOST_CHECK_EQUAL( NO_POS, clone->mapColToRow(it->mCol) );
		}
	}

	{
		HAlignment clone(a->getClone());
		clone->map( a, CR);
		AlignmentIterator it(a->begin()), end(a->end());
		for (;it!=end;++it)
		{
			if (it->mRow == it->mCol)
				BOOST_CHECK_EQUAL( it->mRow, clone->mapRowToCol(it->mRow) );
			else if (a->mapRowToCol( it->mCol ) != NO_POS)
				BOOST_CHECK_EQUAL( a->mapRowToCol(it->mCol), clone->mapRowToCol(it->mRow) );
			else
				BOOST_CHECK_EQUAL( NO_POS, clone->mapRowToCol(it->mRow) );
		}
	}


}


// tests for both empty and full alignments
void testAlignment( HAlignment & a, int * row_pairs, int * col_pairs, int npairs )
{
	for (int x = 0; x < npairs; ++x)
		a->addPair( row_pairs[x], col_pairs[x], 1.0 );

	std::map<Position,int>pairs;

	for (int i = 0; i < npairs; ++i)
		pairs[row_pairs[i] * 100+col_pairs[i]] = 0;

	{
		ostringstream result;
		result << *a;
	}

	{
		AlignmentIterator it(a->begin());
		AlignmentIterator it_end(a->end());
		int x = 0;
		int found = 0;
		for (; it != it_end; x++, it++)
		{
			Position k = it->mRow * 100 + it->mCol;
			if (pairs.find(k) != pairs.end())
				++found;
		}
		BOOST_CHECK_EQUAL( pairs.size(), found);
	}

	{
		AlignmentIterator it(a->begin());
		AlignmentIterator it_end(a->end());
		int x = 0;
		int found = 0;
		for (; it != it_end; x++, ++it)
		{
			Position k = it->mRow * 100 + it->mCol;
			if (pairs.find(k) != pairs.end())
				++found;
		}
		BOOST_CHECK_EQUAL( pairs.size(), found);
	}

	{
		int result = a->getNumGaps(); result++;
	}

	{
		int result = a->getLength(); result++;
	}

	{
		Score result = a->getScore(); result+=1;
	}

	{
		a->setScore( 12.0 );
		BOOST_CHECK_EQUAL( a->getScore(), 12 );
	}

	{
		HAlignment a_clone(a->getClone());
		BOOST_CHECK_EQUAL( a_clone->getScore(), a->getScore() );
		BOOST_CHECK_EQUAL(a_clone->getLength(), a->getLength() );
		BOOST_CHECK_EQUAL(a_clone->getNumGaps(), a->getNumGaps() );
		BOOST_CHECK_EQUAL(isIdentical( a, a_clone ), true );
	}

	{
		HAlignment a_new(a->getNew());
		BOOST_CHECK_EQUAL( a_new->getScore() , 0 );
		BOOST_CHECK_EQUAL( a_new->getLength() , 0 );
		BOOST_CHECK_EQUAL( a_new->getNumGaps() , 0 );
	}

	if (!a->isEmpty())
	{
		Position pos = 0;
		for( int x = 0; x < npairs; ++x)
		{
			// check gaps
			while ( pos < row_pairs[x])
				BOOST_CHECK_EQUAL(a->mapRowToCol( pos++),NO_POS);
			// check aligned
			BOOST_CHECK_EQUAL(a->mapRowToCol( pos++ ), col_pairs[x]);
		}
	}

	if (!a->isEmpty())
	{
		Position pos = 0;
		for( int x = 0; x < npairs; ++x)
		{
			// check gaps
			while ( pos < col_pairs[x])
				BOOST_CHECK_EQUAL(a->mapColToRow( pos++),NO_POS);
			// check aligned
			BOOST_CHECK_EQUAL(a->mapColToRow( pos++), row_pairs[x]);
		}
	}

	{
		HAlignment a_clone(a->getClone());
		a_clone->switchRowCol();
		BOOST_CHECK_EQUAL(a_clone->getColFrom(), a->getRowFrom());
		BOOST_CHECK_EQUAL(a_clone->getColTo(), a->getRowTo());
		BOOST_CHECK_EQUAL(a_clone->getRowFrom(), a->getColFrom());
		BOOST_CHECK_EQUAL(a_clone->getRowTo(), a->getColTo());
		BOOST_CHECK_EQUAL(a_clone->getLength(), a->getLength());
		BOOST_CHECK_EQUAL(a_clone->getNumGaps(), a->getNumGaps());
		BOOST_CHECK_EQUAL(a_clone->getNumAligned(), a->getNumAligned());
		BOOST_CHECK_EQUAL(a_clone->getScore(), a->getScore());
	}

	// test inserting of residues
	checkInsert( a );

	// testing moving of an alignment
	checkMove( a );

	// test removing all pairs
	{
		HAlignment a_clone(a->getClone());

		AlignmentIterator it(a->begin());
		AlignmentIterator it_end(a->end());

		int naligned = a_clone->getNumAligned();
		for (; it != it_end; ++it)
		{
			a_clone->removePair( *it );
			BOOST_CHECK_EQUAL( a_clone->getNumAligned(), --naligned );
		}
		BOOST_CHECK_EQUAL(a_clone->getLength(), 0 );
		BOOST_CHECK_EQUAL(a_clone->getNumGaps() , 0);
		BOOST_CHECK_EQUAL(a_clone->getNumAligned() , 0);
		BOOST_CHECK_EQUAL(a_clone->isEmpty(), true );
	}

	{
		HAlignment a_clone( a->getClone());
		a_clone->clear();
		BOOST_CHECK_EQUAL(a_clone->getScore(), 0);
		BOOST_CHECK_EQUAL(a_clone->getLength(), 0 );
		BOOST_CHECK_EQUAL(a_clone->getNumGaps() , 0);
		BOOST_CHECK_EQUAL(a_clone->getNumAligned() , 0);
		BOOST_CHECK_EQUAL(a_clone->isEmpty(), true );
	}

	checkMap( a );

	if ( a->isEmpty() )
		return;

	BOOST_CHECK_EQUAL( (*(a->begin())).mRow, a->getRowFrom() );
	BOOST_CHECK_EQUAL( a->front().mRow, a->getRowFrom() );

	BOOST_CHECK_EQUAL( (*(a->begin())).mCol, a->getColFrom() );
	BOOST_CHECK_EQUAL( a->front().mCol, a->getColFrom() );


}


void testAlignmentSpecific1( HAlignment & a, int * row_pairs, int * col_pairs, int npairs )
{
	{
		if (!a->isEmpty())
		{
			HAlignment a_clone(a->getClone());

			a_clone->removeRowRegion( 3, 5);
			BOOST_CHECK_EQUAL( a_clone->getRowFrom() , 5 );
			BOOST_CHECK_EQUAL( a_clone->getColFrom() , 6 );

			a_clone->removeRowRegion( 10, 14);
			BOOST_CHECK_EQUAL( a_clone->getRowTo() , 10);
			BOOST_CHECK_EQUAL( a_clone->getColTo() , 11);
			a_clone->removeRowRegion( 0, 20 );
			BOOST_CHECK_EQUAL( a_clone->getLength() ,  0 );
			BOOST_CHECK_EQUAL( a_clone->isEmpty(), true);
		}

		{
			HAlignment a_clone(a->getClone());
			a_clone->removeRowRegion(-1, -3);
			a_clone->removeRowRegion(20, 30);
			a_clone->removeRowRegion(0, 2);
			a_clone->removeRowRegion(1, 2);
			a_clone->removeRowRegion(2, 1);
			BOOST_CHECK_EQUAL( a_clone->getLength() ,  a->getLength() );
		}
	}

	{
		int i = 0;

		HAlignment  a_clone(a->getClone());

		for (i = 0; i < a->getColTo() + 5; i+=3)
			a_clone->removeColRegion(i, i+3);
	}

}

void testAlignmentSpecific2( HAlignment & a, int * row_pairs, int * col_pairs, int npairs )
{
	{
		if (!a->isEmpty())
		{
			HAlignment a_clone(a->getClone());

			a_clone->removeRowRegion( 3, 20);
			BOOST_CHECK_EQUAL( a_clone->getRowFrom() , 0 );
			BOOST_CHECK_EQUAL( a_clone->getColFrom() , 0 );
		}

		{
			HAlignment a_clone(a->getClone());
			a_clone->removeRowRegion(-1, -3);
			a_clone->removeRowRegion(20, 30);
			BOOST_CHECK_EQUAL( a_clone->getLength(), a->getLength() );
		}
	}

	{
		int i = 0;
		HAlignment  a_clone(a->getClone());
		for (i = 0; i < a->getColTo() + 5; i+=3)
			a_clone->removeColRegion(i, i+3);
	}

}


//----------------------------------------------------------
// main test routine for a pairwise alignment
void runTests( HAlignment & a )
{
	testAlignment( a, NULL, NULL, 0 );

	// test for an alignment with gaps
	{
		Position row_pairs[9] = {3,4,5,6,8,9,10,12,13};
		Position col_pairs[9] = {3,4,6,7,8,10,11,12,13};

		testAlignment( a, row_pairs, col_pairs, 9 );
		testAlignmentSpecific1( a, row_pairs, col_pairs, 9 );
	}

	a->clear();
	// test for alignment starting at 0
	{
		Position row_pairs[6] = {0,1,2,3,4,5};
		Position col_pairs[6] = {0,1,2,3,4,5};

		testAlignment( a, row_pairs, col_pairs, 6 );
		testAlignmentSpecific2( a, row_pairs, col_pairs, 6 );
	}
}

// testing a case that caused an assertion failure in AlignmentBlocks
BOOST_AUTO_TEST_CASE( test_AlignmentBlocksBug1 )
{
	HAlignment ali(makeAlignmentBlocks());
	AlignmentFormatEmissions( 2104866,
			"+94352",
			0,
			"+20-14248+128-1887+254-2742+181-5354+208-1904+117-1506+85-1306+151-2072+133-92+182-502+62-1098+129-2260+91-1095+90-2761+141-710+105-897+47-320+8-1460+124-160+57-1099+147-1890+188-8182+145-76+132-766+151-7948+151-306+108-2812+193-1778+195-651+397-3129+124-3623+98-2371+209-1613+1828-6214+134-1033+83-1701+190" ).copy( ali);
	ali->mapRowToCol( 2189261 );
	ali->mapRowToCol( 2199194 );

}

#define create_test( name, factory ) \
	BOOST_AUTO_TEST_CASE( name ) { HAlignment a(factory()); runTests(a); }

create_test( Vector, makeAlignmentVector );
create_test( Set, makeAlignmentSet );
create_test( Hash, makeAlignmentHash );
create_test( HashDiagonal, makeAlignmentHashDiagonal );
create_test( SetCol, makeAlignmentSetCol );
create_test( MatrixRow, makeAlignmentMatrixRow );
create_test( MatrixDiagonal, makeAlignmentMatrixDiagonal );
create_test( MatrixUnsorted, makeAlignmentMatrixUnsorted );
create_test( Blocks, makeAlignmentBlocks );
