/*
  alignlib - a library for aligning protein sequences

  $Id: test_MultipleAlignment.cpp,v 1.6 2004/06/02 12:11:38 aheger Exp $

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

/** Test the MultipleAlignment - object
 */

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

#include "Alignatum.h"
#include "HelpersAlignatum.h"
#include "MultipleAlignment.h"
#include "HelpersMultipleAlignment.h"
#include "AlignlibDebug.h"
#include "Weightor.h"
#include "HelpersWeightor.h"

using namespace std;
using namespace alignlib;

void testWeightor( Weightor * weightor ) 
{
	std::auto_ptr<MultipleAlignment> mali(makeMultipleAlignment());

	mali->add(makeAlignatumFromString("AAAAAAAAAAAAA"));
	mali->add(makeAlignatumFromString("AAAAAAAAAAAAA"));
	mali->add(makeAlignatumFromString("AAAAAAAAAAAAA"));
	
	SequenceWeights * weights = weightor->calculateWeights( *mali );
	
	for (int i = 0; i < mali->getWidth(); ++i)
		std::cout << (*weights)[i] << std::endl;

	delete weights;
}


int main () 
{
	std::cout << "----- testing NoWeightor ---------" << std::endl;
	{
		std::auto_ptr<Weightor>weightor(makeNoWeightor());	
		testWeightor( &*weightor );
	}

	std::cout << "----- testing WeightorHenikoff ---------" << std::endl;
	{
		std::auto_ptr<Weightor>weightor(makeWeightorHenikoff());	
		testWeightor( &*weightor );
	}
	
	std::cout << "----- testing WeightorHenikoffKimmen ---------" << std::endl;
	{
		std::auto_ptr<Weightor>weightor(makeWeightorHenikoffKimmen());	
		testWeightor( &*weightor );
	}
	
}






