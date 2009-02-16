// This file has been generated by Py++.

#include "boost/python.hpp"
#include "includes.h"
#include "iostream"
#include "cstdio"
#include "Fragmentor.pypp.hpp"

namespace bp = boost::python;

void register_Fragmentor_class(){

    { //::alignlib::Fragmentor
        typedef bp::class_< alignlib::Fragmentor, boost::noncopyable > Fragmentor_exposer_t;
        Fragmentor_exposer_t Fragmentor_exposer = Fragmentor_exposer_t( "Fragmentor", bp::no_init );
        bp::scope Fragmentor_scope( Fragmentor_exposer );
        { //::alignlib::Fragmentor::fragment
        
            typedef ::alignlib::HFragmentVector ( ::alignlib::Fragmentor::*fragment_function_type )( ::alignlib::HAlignment &,::alignlib::HAlignandum const &,::alignlib::HAlignandum const & ) ;
            
            Fragmentor_exposer.def( 
                "fragment"
                , fragment_function_type( &::alignlib::Fragmentor::fragment )
                , ( bp::arg("dest"), bp::arg("row"), bp::arg("col") ) );
        
        }
        { //::alignlib::Fragmentor::getClone
        
            typedef ::alignlib::HFragmentor ( ::alignlib::Fragmentor::*getClone_function_type )(  ) const;
            
            Fragmentor_exposer.def( 
                "getClone"
                , getClone_function_type( &::alignlib::Fragmentor::getClone ) );
        
        }
        { //::alignlib::Fragmentor::getNew
        
            typedef ::alignlib::HFragmentor ( ::alignlib::Fragmentor::*getNew_function_type )(  ) const;
            
            Fragmentor_exposer.def( 
                "getNew"
                , getNew_function_type( &::alignlib::Fragmentor::getNew ) );
        
        }
        bp::register_ptr_to_python< boost::shared_ptr< alignlib::Fragmentor > >();
    }

}
