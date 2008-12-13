// This file has been generated by Py++.

#include "boost/python.hpp"
#include "includes.h"
#include "iostream"
#include "cstdio"
#include "Alignator.pypp.hpp"

namespace bp = boost::python;

void register_Alignator_class(){

    { //::alignlib::Alignator
        typedef bp::class_< alignlib::Alignator, boost::noncopyable > Alignator_exposer_t;
        Alignator_exposer_t Alignator_exposer = Alignator_exposer_t( "Alignator", bp::no_init );
        bp::scope Alignator_scope( Alignator_exposer );
        { //::alignlib::Alignator::align
        
            typedef void ( ::alignlib::Alignator::*align_function_type )( ::alignlib::HAlignment &,::alignlib::HAlignandum const &,::alignlib::HAlignandum const & ) ;
            
            Alignator_exposer.def( 
                "align"
                , align_function_type( &::alignlib::Alignator::align )
                , ( bp::arg("dest"), bp::arg("row"), bp::arg("col") ) );
        
        }
        { //::alignlib::Alignator::getClone
        
            typedef ::alignlib::HAlignator ( ::alignlib::Alignator::*getClone_function_type )(  ) const;
            
            Alignator_exposer.def( 
                "getClone"
                , getClone_function_type( &::alignlib::Alignator::getClone ) );
        
        }
        { //::alignlib::Alignator::setIterator2D
        
            typedef void ( ::alignlib::Alignator::*setIterator2D_function_type )( ::alignlib::HIterator2D const & ) ;
            
            Alignator_exposer.def( 
                "setIterator2D"
                , setIterator2D_function_type( &::alignlib::Alignator::setIterator2D )
                , ( bp::arg("iterator") ) );
        
        }
        { //::alignlib::Alignator::setScorer
        
            typedef void ( ::alignlib::Alignator::*setScorer_function_type )( ::alignlib::HScorer const & ) ;
            
            Alignator_exposer.def( 
                "setScorer"
                , setScorer_function_type( &::alignlib::Alignator::setScorer )
                , ( bp::arg("scorer") ) );
        
        }
        bp::register_ptr_to_python< boost::shared_ptr< alignlib::Alignator > >();
    }

}
