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
import unittest
from alignlib import *
import sys

class AlignlibExceptionTestCase( unittest.TestCase ):

    def __init__(self, *args, **kwargs):
        unittest.TestCase.__init__(self, *args, **kwargs )

    def setUp( self ):
        pass
        
    def testException( self ):
        r = makeAlignmentVector()
        sys.stderr = None
        f = AlignmentFormatEmissions()
        self.failUnlessRaises( RuntimeError, f.copy, r )
                            
def suite():
    suite = unittest.TestSuite()
    suite.addTest(AlignlibExceptionTestCase)
    return suite

if __name__ == "__main__":
    unittest.main()

