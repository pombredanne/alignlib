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

#ifndef IMPL_SCORER_SEQUENCE_SEQUENCE_H
#define IMPL_SCORER_SEQUENCE_SEQUENCE_H 1

#include "alignlib.h"
#include "ImplScorer.h"
namespace alignlib
{

  class Alignandum;
  class SubstitutionMatrix;
  
  //----------------------------------------------------------------
  class ImplScorerSequenceSequence : public ImplScorer 
  {
    public:
      
      /** empty constructor */
      ImplScorerSequenceSequence( const Alignandum * row, const Alignandum * col,
				  const SubstitutionMatrix * matrix); 
    
      /** destructor */
      virtual ~ImplScorerSequenceSequence ();
      
      /** copy constructor */
      ImplScorerSequenceSequence( const ImplScorerSequenceSequence & src);

      /** return a copy of the same iterator
       */
      virtual Scorer * getClone() const;
      
      /** return a new score of same type initialized with row and col
       */
      virtual Scorer * getNew( const Alignandum * row, const Alignandum * col) const;
    
      virtual Score getScore( Position row,
				 Position col ) const;

  protected:
      /** pointer to member data of row/col : AlignandumSequence */
      const Residue * mRowSequence; 
      const Residue * mColSequence;
      const SubstitutionMatrix * mSubstitutionMatrix ;
  };
  
}


#endif /* SCORER_H */