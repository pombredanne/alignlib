/*
  alignlib - a library for aligning protein sequences

  $Id: ImplRegularizorDirichlet.h,v 1.2 2004/01/07 14:35:35 aheger Exp $

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

#ifndef IMPL_REGULARIZOR_DIRICHLET_H
#define IMPL_REGULARIZOR_DIRICHLET_H 1

#include "alignlib.h"
#include "Regularizor.h"

namespace alignlib 
{

#define PROFILEWIDTH 20
#define NCOMPONENTS 9

    typedef double TYPE_WA_COLUMN[NCOMPONENTS];
    typedef double TYPE_A_COLUMN[PROFILEWIDTH];
    typedef double TYPE_BETA_DIFFERENCES[NCOMPONENTS];

  /** Implementation of a class that regularizes count columns based
      on the 9-component Dirichlet-mixture by Kimmen Sjoerlander. This
      profile is only defined for the 20 amino acid residues.
      
      @author Andreas Heger
      @version $Id: ImplRegularizorDirichlet.h,v 1.2 2004/01/07 14:35:35 aheger Exp $
      @short protocol class for sequence weighters
      
  */

class ImplRegularizorDirichlet : public Regularizor 
{
 public:
    // constructors and desctructors

    /** default constructor */
    ImplRegularizorDirichlet  ( Count fade_cutoff );
    
    /** copy constructor */
    ImplRegularizorDirichlet  (const ImplRegularizorDirichlet &);

    /** destructor */
    virtual ~ImplRegularizorDirichlet ();
    
    /** copy the counts into the frequencies and regularize them by doing so. */
    virtual void fillFrequencies( FrequencyMatrix & frequencies, 
				  				  const CountMatrix & counts ) const; 

 private:

    /** the cutoff used for fading out the Dirichlet-mixture */
    Count mFadeCutoff;

 protected:
    /** helper array, contains the |a_j|. Static, because I need only one for all regularizers. 
	declaring the array puts it not in the heap. Can not be private, because derived classes
	need to access it. The same applies to mA.
    */
    TYPE_WA_COLUMN mWa;

    /** pointer to the mixture components */
    TYPE_A_COLUMN * mA;

    /** helper array, contains lgamma(|a_j]) */
    double * mLGamma_Wa;
    
    /** helper array, contains sum_i(lgamma(a_ji) */
    double * mSumLGamma_Ai;

    /** This function encapsulates that part of the algorithm, that needs to access the lgamma-function. It
	has been externalized, so that it can be overloaded to implement different speed-ups.
	
	It returns the maximum difference.

	The implemention here uses the lgamma-function directly and is therefore quite slow.
    */
    virtual double calculateBetaDifferences(  TYPE_BETA_DIFFERENCES beta_differences, const Count * n, Count ntotal ) const;
    
    /** fill one frequencies column with the Dirichlet-Mixture */
    virtual void fillColumn( Frequency * frequencies, 
			     		     TYPE_BETA_DIFFERENCES beta_differences, 
			     		     const Count * n, 
			     		     Count ntotal ) const;
    
};

}

#endif /* IMPL_REGULARIZOR_DIRICHLET_H */

