# alignlib - a library for aligning protein sequences
# 
# $Id: test_Alignment.py,v 1.3 2004/01/23 17:34:58 aheger Exp $
# 
# Copyright (C) 2004 Andreas Heger
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
import unittest, sys
from alignlib import *

class MatrixCase( unittest.TestCase ):

    def setUp( self ):

        self.mNumRows = 10
        self.mNumCols = 20

        self.mValue = 1.4
        self.mMatrix = MatrixDouble( self.mNumRows, self.mNumCols, 1.4 )

    def testDimensions(self):
        
        self.assertEqual( self.mNumRows, self.mMatrix.getNumRows() )
        self.assertEqual( self.mNumCols, self.mMatrix.getNumCols() )
        for r in range( self.mNumRows ):
            for c in range( self.mNumCols ):
                self.assertEqual( self.mValue, self.mMatrix.getValue( r, c ) )

class MatrixIntCase( MatrixCase ):
    
    def setUp( self ):

        MatrixCase.setUp( self )

        self.mValue = 1
        self.mMatrix = MatrixInt( self.mNumRows, self.mNumCols, self.mValue )
         

def suite():
    suite = unittest.TestSuite()
    suite.addTest(MatrixTestCase)
    suite.addTest(MatrixIntTestCase)
    return suite

if __name__ == "__main__":
    unittest.main()


        





