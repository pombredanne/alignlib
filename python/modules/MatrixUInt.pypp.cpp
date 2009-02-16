// This file has been generated by Py++.

#include "boost/python.hpp"
#include "includes.h"
#include "iostream"
#include "cstdio"
#include "MatrixUInt.pypp.hpp"

namespace bp = boost::python;

void register_MatrixUInt_class(){

    { //::alignlib::Matrix< unsigned int >
        typedef bp::class_< alignlib::Matrix< unsigned int > > MatrixUInt_exposer_t;
        MatrixUInt_exposer_t MatrixUInt_exposer = MatrixUInt_exposer_t( "MatrixUInt", bp::init< unsigned int, unsigned int, bp::optional< unsigned int > >(( bp::arg("r"), bp::arg("c"), bp::arg("default_value")=(unsigned int)(0) )) );
        bp::scope MatrixUInt_scope( MatrixUInt_exposer );
        MatrixUInt_exposer.def( bp::init< alignlib::Matrix< unsigned int > const & >(( bp::arg("src") )) );
        { //::alignlib::Matrix< unsigned int >::addValue
        
            typedef alignlib::Matrix< unsigned int > exported_class_t;
            typedef void ( exported_class_t::*addValue_function_type )( unsigned int,unsigned int,unsigned int const & ) ;
            
            MatrixUInt_exposer.def( 
                "addValue"
                , addValue_function_type( &::alignlib::Matrix< unsigned int >::addValue )
                , ( bp::arg("row"), bp::arg("col"), bp::arg("value") ) );
        
        }
        { //::alignlib::Matrix< unsigned int >::getClone
        
            typedef alignlib::Matrix< unsigned int > exported_class_t;
            typedef ::boost::shared_ptr< alignlib::Matrix< unsigned int > > ( exported_class_t::*getClone_function_type )(  ) const;
            
            MatrixUInt_exposer.def( 
                "getClone"
                , getClone_function_type( &::alignlib::Matrix< unsigned int >::getClone ) );
        
        }
        { //::alignlib::Matrix< unsigned int >::getNew
        
            typedef alignlib::Matrix< unsigned int > exported_class_t;
            typedef ::boost::shared_ptr< alignlib::Matrix< unsigned int > > ( exported_class_t::*getNew_function_type )(  ) const;
            
            MatrixUInt_exposer.def( 
                "getNew"
                , getNew_function_type( &::alignlib::Matrix< unsigned int >::getNew ) );
        
        }
        { //::alignlib::Matrix< unsigned int >::getNumCols
        
            typedef alignlib::Matrix< unsigned int > exported_class_t;
            typedef unsigned int ( exported_class_t::*getNumCols_function_type )(  ) const;
            
            MatrixUInt_exposer.def( 
                "getNumCols"
                , getNumCols_function_type( &::alignlib::Matrix< unsigned int >::getNumCols ) );
        
        }
        { //::alignlib::Matrix< unsigned int >::getNumRows
        
            typedef alignlib::Matrix< unsigned int > exported_class_t;
            typedef unsigned int ( exported_class_t::*getNumRows_function_type )(  ) const;
            
            MatrixUInt_exposer.def( 
                "getNumRows"
                , getNumRows_function_type( &::alignlib::Matrix< unsigned int >::getNumRows ) );
        
        }
        { //::alignlib::Matrix< unsigned int >::getValue
        
            typedef alignlib::Matrix< unsigned int > exported_class_t;
            typedef unsigned int ( exported_class_t::*getValue_function_type )( unsigned int,unsigned int ) const;
            
            MatrixUInt_exposer.def( 
                "getValue"
                , getValue_function_type( &::alignlib::Matrix< unsigned int >::getValue )
                , ( bp::arg("row"), bp::arg("col") ) );
        
        }
        { //::alignlib::Matrix< unsigned int >::operator=
        
            typedef alignlib::Matrix< unsigned int > exported_class_t;
            typedef ::alignlib::Matrix< unsigned int > & ( exported_class_t::*assign_function_type )( ::alignlib::Matrix< unsigned int > const & ) ;
            
            MatrixUInt_exposer.def( 
                "assign"
                , assign_function_type( &::alignlib::Matrix< unsigned int >::operator= )
                , ( bp::arg("src") )
                , bp::return_self< >() );
        
        }
        MatrixUInt_exposer.def( bp::self == bp::self );
        { //::alignlib::Matrix< unsigned int >::permuteCols
        
            typedef alignlib::Matrix< unsigned int > exported_class_t;
            typedef void ( exported_class_t::*permuteCols_function_type )( ::std::vector< unsigned int > & ) ;
            
            MatrixUInt_exposer.def( 
                "permuteCols"
                , permuteCols_function_type( &::alignlib::Matrix< unsigned int >::permuteCols )
                , ( bp::arg("map_new2old") ) );
        
        }
        { //::alignlib::Matrix< unsigned int >::permuteRows
        
            typedef alignlib::Matrix< unsigned int > exported_class_t;
            typedef void ( exported_class_t::*permuteRows_function_type )( ::std::vector< unsigned int > & ) ;
            
            MatrixUInt_exposer.def( 
                "permuteRows"
                , permuteRows_function_type( &::alignlib::Matrix< unsigned int >::permuteRows )
                , ( bp::arg("map_new2old") ) );
        
        }
        { //::alignlib::Matrix< unsigned int >::setValue
        
            typedef alignlib::Matrix< unsigned int > exported_class_t;
            typedef void ( exported_class_t::*setValue_function_type )( unsigned int,unsigned int,unsigned int const & ) ;
            
            MatrixUInt_exposer.def( 
                "setValue"
                , setValue_function_type( &::alignlib::Matrix< unsigned int >::setValue )
                , ( bp::arg("row"), bp::arg("col"), bp::arg("value") ) );
        
        }
        { //::alignlib::Matrix< unsigned int >::swapRows
        
            typedef alignlib::Matrix< unsigned int > exported_class_t;
            typedef void ( exported_class_t::*swapRows_function_type )( unsigned int,unsigned int ) ;
            
            MatrixUInt_exposer.def( 
                "swapRows"
                , swapRows_function_type( &::alignlib::Matrix< unsigned int >::swapRows )
                , ( bp::arg("x"), bp::arg("y") ) );
        
        }
        bp::register_ptr_to_python< boost::shared_ptr< alignlib::Matrix<unsigned int> > >();
    }

}
