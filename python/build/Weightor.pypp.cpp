// This file has been generated by Py++.

#include "boost/python.hpp"
#include "includes.h"
#include "iostream"
#include "cstdio"
#include "Weightor.pypp.hpp"

namespace bp = boost::python;

void register_Weightor_class(){

    { //::alignlib::Weightor
        typedef bp::class_< alignlib::Weightor, boost::noncopyable > Weightor_exposer_t;
        Weightor_exposer_t Weightor_exposer = Weightor_exposer_t( "Weightor", bp::no_init );
        bp::scope Weightor_scope( Weightor_exposer );
        { //::alignlib::Weightor::fillCounts
        
            typedef void ( ::alignlib::Weightor::*fillCounts_function_type )( ::alignlib::CountMatrix &,::alignlib::HMultipleAlignment const &,::alignlib::HEncoder const & ) const;
            
            Weightor_exposer.def( 
                "fillCounts"
                , fillCounts_function_type( &::alignlib::Weightor::fillCounts )
                , ( bp::arg("counts"), bp::arg("src"), bp::arg("translator") ) );
        
        }
        bp::register_ptr_to_python< boost::shared_ptr< alignlib::Weightor > >();
    }

}
