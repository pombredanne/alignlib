/*
  alignlib - a library for aligning protein sequences

  $Id: HelpersAlignandum.cpp,v 1.2 2004/01/07 14:35:32 aheger Exp $

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
#include <stdio.h>

#include "alignlib.h"
#include "AlignlibDebug.h"
#include "AlignException.h"
#include "Alignandum.h"
#include "Translator.h"
#include "HelpersTranslator.h"
#include "HelpersRegularizor.h"
#include "HelpersLogOddor.h"
#include "ImplSequence.h"
#include "ImplProfile.h"

using namespace std;

namespace alignlib 
{

	Alignandum * loadAlignandum( std::istream & input) 
	{		
		// read Alignandum type
		MagicNumberType magic_number;
		
		if (input.eof()) return NULL;

		input.read( (char*)&magic_number, sizeof(MagicNumberType) );
		
		if (input.eof()) return NULL;
		
		Alignandum * result = NULL;
		
		switch (magic_number)
		{
			case MNImplProfile : 
			{
				ImplProfile * r = new ImplProfile( 
						getDefaultTranslator(), 
						getDefaultRegularizor(),
						getDefaultLogOddor()
						);
				r->load(input);
				result = r;
				break;
			}
			case MNImplSequence :
			{
				ImplSequence * r = new ImplSequence( getDefaultTranslator() );
				r->load( input );
				result = r;
				break;
			}
			default:
				throw AlignException( "unknown object found in stream" );
		}	
		return result;
	}	
	
} // namespace alignlib
