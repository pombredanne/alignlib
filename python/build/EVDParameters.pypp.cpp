// This file has been generated by Py++.

#include "boost/python.hpp"
#include "includes.h"
#include "iostream"
#include "cstdio"
#include "EVDParameters.pypp.hpp"

namespace bp = boost::python;

void register_EVDParameters_class(){

    { //::alignlib::EVDParameters
        typedef bp::class_< alignlib::EVDParameters > EVDParameters_exposer_t;
        EVDParameters_exposer_t EVDParameters_exposer = EVDParameters_exposer_t( "EVDParameters" );
        bp::scope EVDParameters_scope( EVDParameters_exposer );
        { //::alignlib::EVDParameters::getK
        
            typedef double ( ::alignlib::EVDParameters::*getK_function_type )(  ) ;
            
            EVDParameters_exposer.def( 
                "getK"
                , getK_function_type( &::alignlib::EVDParameters::getK ) );
        
        }
        { //::alignlib::EVDParameters::getLambda
        
            typedef double ( ::alignlib::EVDParameters::*getLambda_function_type )(  ) ;
            
            EVDParameters_exposer.def( 
                "getLambda"
                , getLambda_function_type( &::alignlib::EVDParameters::getLambda ) );
        
        }
        EVDParameters_exposer.def_readwrite( "mK", &alignlib::EVDParameters::mK );
        EVDParameters_exposer.def_readwrite( "mLambda", &alignlib::EVDParameters::mLambda );
    }

}
