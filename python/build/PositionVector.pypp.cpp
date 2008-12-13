// This file has been generated by Py++.

#include "boost/python.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"
#include "includes.h"
#include "iostream"
#include "cstdio"
#include "PositionVector.pypp.hpp"

namespace bp = boost::python;

void register_PositionVector_class(){

    { //::std::vector< int >
        typedef bp::class_< std::vector< int > > PositionVector_exposer_t;
        PositionVector_exposer_t PositionVector_exposer = PositionVector_exposer_t( "PositionVector" );
        bp::scope PositionVector_scope( PositionVector_exposer );
        PositionVector_exposer.def( bp::vector_indexing_suite< ::std::vector< int >, true >() );
    }

}
