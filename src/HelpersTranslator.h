/*
  alignlib - a library for aligning protein sequences

  $Id: HelpersTranslator.h,v 1.2 2004/01/07 14:35:33 aheger Exp $

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

#ifndef HELPERS_TRANSLATOR_H
#define HELPERS_TRANSLATOR_H 1

#include "alignlib_fwd.h"
#include "alignlib_default.h"
#include "alignlib.h"

namespace alignlib 
{
    
    /** Helper functions for class Alignment:
	
	1. factory functions
	
	2. accessor functions for default objects
	
	3. convenience functions
    */
    class Translator;
    
    /* -------------------------------------------------------------------------------------------------------------------- */
    /* 1. factory functions */
    const HTranslator getTranslator( const AlphabetType & alphabet );

    /* -------------------------------------------------------------------------------------------------------------------- */
    /* 2. accessor functions for default objects */
    /** return the library wide translator */
    DEFINE_DEFAULT( HTranslator, getDefaultTranslator, setDefaultTranslator );
    
    /* -------------------------------------------------------------------------------------------------------------------- */
    /* 3. convenience functions */

    /** load a Translator object from stream. 
     * 
     * Returns NULL on EOF.
     */	
    const HTranslator loadTranslator( std::istream & stream );

}

#endif	/* HELPERS_TRANSLATOR_H */
