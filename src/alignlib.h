/*
  alignlib - a library for aligning protein sequences

  $Id: alignlib.h,v 1.5 2005/02/24 11:07:25 aheger Exp $

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

/** 
    some global defines
    define
	DEBUG, if debugging should be turned on
	TCO, if TCO alignments should be allowed
 */


#if HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef _ALIGNLIB_H
#define _ALIGNLIB_H 1

#include <vector>

namespace alignlib
{

// forward declarations
class Alignata; 


#define MAX_NDOTS    1000000        /* maximum number of dots */
#define MAX_SEQLEN   30000	     /* maximum sequence length */
#define MAX_INSERTLENGTH 30	     /* maximum length of insert before truncating in output */
#define MAX_LEAVES	10000	     /* maximum number of leaves to have in a tree */
#define MAX_DIAGONAL 999999		/* the maximum diagonal there can be */

#define TYPE_LEAF_WEIGHT double		/* weights of leaves */
#define TYPE_EDGE_WEIGHT double		/* weights of edges */
#define TYPE_EDGE int			/* type of edges */

/* out of bound position for alignments */
#define LOWER_BOUNDS_POSITION   0
#define UPPER_BOUNDS_POSITION	10000000

/* type for the internal representation of residues */  
typedef unsigned char Residue;

/** type in which calculations are done
 */
typedef double Score;

/** type of a diagonal index. Has to be a signed type, as diagonals can be positive or negative
 */
typedef long Diagonal;	

/* type of a dot index, has to be signed, since NODOT is -1 */
typedef long Dot;	

/* type of a fragment index, has to be signed, since NOFRAGMENT is -1 */
typedef long Fragment;	

/* type of a position in a sequence, negative positions are invalid positions*/
typedef int Position;	

/* invalid position */
#define NO_POS -1


/* type of sequence weights */
typedef double SequenceWeight;

/* type for substitution matrices */
#define MATRIXWIDTH_AA  21		     /* width of ordinary substitution matrix, 20 amino acid residues + 1 mask-character */
#define MATRIXWIDTH_TCO 4

typedef Score ScoreColumn[MATRIXWIDTH_AA];  

/* type of one entry in a profile */
#define PROFILEWIDTH 20					/* width of profile, 4 for NA, 20 for AA */
#define MASK_VALUE -10					/* value used, for masking a profile-entry */
typedef double ProfileScore; 
typedef ProfileScore ProfileColumn[PROFILEWIDTH];

/* type of counts, no speed difference between float and double
    I have to use real values, since I the counts correspond to
    weighted counts */
typedef double Count;
typedef Count CountColumn[PROFILEWIDTH];

/* type of one entry in a frequencies-table */
typedef double Frequency;
typedef Frequency FrequencyColumn[PROFILEWIDTH];		// frequencies have to be double  
typedef std::vector<Frequency>Frequencies;
typedef std::vector<Frequencies>ProfileFrequencies;
typedef std::vector<SequenceWeight>SequenceWeights;
/** alignment types */
enum AlignmentType
{
	ALIGNMENT_LOCAL, ALIGNMENT_WRAP, ALIGNMENT_GLOBAL
};

/** how to map residues
 * STRICT: do not find adjacent residues
 * LEFT: map to left (smaller residue numbers) until a match is found
 * RIGHT: map to right (larger residue numbers) until a match is found
 */
enum SearchType
{
	NO_SEARCH, LEFT, RIGHT
};

enum LinkageType
{
	SINGLE_LINKAGE,
	COMPLETE_LINKAGE,
	AVERAGE_LINKAGE,          // = UPGMA
	UPGMA,                    // = unweighted pair group method average (UPGMA), see Theodoridis & Koutroumbas, p411
	WPGMA,                    // = weighted pair group method average (WPGMA), as above
	UPGMC,                    // = unweighted pair group method centroid (UPGMC), as above
	WPGMC                     // = weighted pair group method centroid (UPGMC), as above
};

// List of objects that allow saving state information
enum MagicNumberType
{
	MNNoType,
	MNImplAlignandum,
	MNImplSequence,
	MNImplProfile,
};

/* type of a height of a node in the tree */
typedef double TreeHeight;

/* type of a weight of an edge in the tree */
typedef double TreeWeight;

/* type of a node */
typedef unsigned long Node;


struct Coordinate 
{
	unsigned long row;
	unsigned long col;
};

typedef double PhyloMatrixValue;

typedef unsigned long PhyloMatrixSize;

/** A vector of aligned fragmens */
typedef std::vector<Alignata*> FragmentVector;

} 

#endif /* _ALIGNLIB_H */

