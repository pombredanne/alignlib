// This file has been generated by Py++.

#include "boost/python.hpp"
#include "includes.h"
#include "iostream"
#include "cstdio"
#include "Regularizor.pypp.hpp"

namespace bp = boost::python;

void register_Regularizor_class(){

    { //::alignlib::Regularizor
        typedef bp::class_< alignlib::Regularizor, boost::noncopyable > Regularizor_exposer_t;
        Regularizor_exposer_t Regularizor_exposer = Regularizor_exposer_t( "Regularizor", bp::no_init );
        bp::scope Regularizor_scope( Regularizor_exposer );
        { //::alignlib::Regularizor::fillFrequencies
        
            typedef void ( ::alignlib::Regularizor::*fillFrequencies_function_type )( ::alignlib::FrequencyMatrix &,::alignlib::CountMatrix const &,::alignlib::HEncoder const & ) const;
            
            Regularizor_exposer.def( 
                "fillFrequencies"
                , fillFrequencies_function_type( &::alignlib::Regularizor::fillFrequencies )
                , ( bp::arg("frequencies"), bp::arg("counts"), bp::arg("translator") ) );
        
        }
        { //::alignlib::Regularizor::getClone
        
            typedef ::alignlib::HRegularizor ( ::alignlib::Regularizor::*getClone_function_type )(  ) const;
            
            Regularizor_exposer.def( 
                "getClone"
                , getClone_function_type( &::alignlib::Regularizor::getClone ) );
        
        }
        { //::alignlib::Regularizor::getNew
        
            typedef ::alignlib::HRegularizor ( ::alignlib::Regularizor::*getNew_function_type )(  ) const;
            
            Regularizor_exposer.def( 
                "getNew"
                , getNew_function_type( &::alignlib::Regularizor::getNew ) );
        
        }
        bp::register_ptr_to_python< boost::shared_ptr< alignlib::Regularizor > >();
    }

}
