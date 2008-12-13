// This file has been generated by Py++.

#include "boost/python.hpp"
#include "includes.h"
#include "iostream"
#include "cstdio"
#include "Alignment.pypp.hpp"

namespace bp = boost::python;

void register_Alignment_class(){

    { //::alignlib::Alignment
        typedef bp::class_< alignlib::Alignment, boost::noncopyable > Alignment_exposer_t;
        Alignment_exposer_t Alignment_exposer = Alignment_exposer_t( "Alignment", bp::no_init );
        bp::scope Alignment_scope( Alignment_exposer );
        { //::alignlib::Alignment::addDiagonal
        
            typedef void ( ::alignlib::Alignment::*addDiagonal_function_type )( ::alignlib::Position,::alignlib::Position,::alignlib::Position ) ;
            
            Alignment_exposer.def( 
                "addDiagonal"
                , addDiagonal_function_type( &::alignlib::Alignment::addDiagonal )
                , ( bp::arg("row_from"), bp::arg("row_to"), bp::arg("col_offset")=(int)(0) ) );
        
        }
        { //::alignlib::Alignment::addPair
        
            typedef void ( ::alignlib::Alignment::*addPair_function_type )( ::alignlib::ResiduePair const & ) ;
            
            Alignment_exposer.def( 
                "addPair"
                , addPair_function_type( &::alignlib::Alignment::addPair )
                , ( bp::arg("pair") ) );
        
        }
        { //::alignlib::Alignment::addPair
        
            typedef void ( ::alignlib::Alignment::*addPair_function_type )( ::alignlib::Position,::alignlib::Position,::alignlib::Score ) ;
            
            Alignment_exposer.def( 
                "addPair"
                , addPair_function_type( &::alignlib::Alignment::addPair )
                , ( bp::arg("row"), bp::arg("col"), bp::arg("score")=0 ) );
        
        }
        { //::alignlib::Alignment::back
        
            typedef ::alignlib::ResiduePair ( ::alignlib::Alignment::*back_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "back"
                , back_function_type( &::alignlib::Alignment::back ) );
        
        }
        { //::alignlib::Alignment::begin
        
            typedef ::alignlib::AlignmentIterator ( ::alignlib::Alignment::*begin_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "begin"
                , begin_function_type( &::alignlib::Alignment::begin ) );
        
        }
        { //::alignlib::Alignment::clear
        
            typedef void ( ::alignlib::Alignment::*clear_function_type )(  ) ;
            
            Alignment_exposer.def( 
                "clear"
                , clear_function_type( &::alignlib::Alignment::clear ) );
        
        }
        { //::alignlib::Alignment::end
        
            typedef ::alignlib::AlignmentIterator ( ::alignlib::Alignment::*end_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "end"
                , end_function_type( &::alignlib::Alignment::end ) );
        
        }
        { //::alignlib::Alignment::front
        
            typedef ::alignlib::ResiduePair ( ::alignlib::Alignment::*front_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "front"
                , front_function_type( &::alignlib::Alignment::front ) );
        
        }
        { //::alignlib::Alignment::getClone
        
            typedef ::alignlib::HAlignment ( ::alignlib::Alignment::*getClone_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "getClone"
                , getClone_function_type( &::alignlib::Alignment::getClone ) );
        
        }
        { //::alignlib::Alignment::getColFrom
        
            typedef ::alignlib::Position ( ::alignlib::Alignment::*getColFrom_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "getColFrom"
                , getColFrom_function_type( &::alignlib::Alignment::getColFrom ) );
        
        }
        { //::alignlib::Alignment::getColTo
        
            typedef ::alignlib::Position ( ::alignlib::Alignment::*getColTo_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "getColTo"
                , getColTo_function_type( &::alignlib::Alignment::getColTo ) );
        
        }
        { //::alignlib::Alignment::getLength
        
            typedef ::alignlib::Position ( ::alignlib::Alignment::*getLength_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "getLength"
                , getLength_function_type( &::alignlib::Alignment::getLength ) );
        
        }
        { //::alignlib::Alignment::getNew
        
            typedef ::alignlib::HAlignment ( ::alignlib::Alignment::*getNew_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "getNew"
                , getNew_function_type( &::alignlib::Alignment::getNew ) );
        
        }
        { //::alignlib::Alignment::getNumAligned
        
            typedef ::alignlib::Position ( ::alignlib::Alignment::*getNumAligned_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "getNumAligned"
                , getNumAligned_function_type( &::alignlib::Alignment::getNumAligned ) );
        
        }
        { //::alignlib::Alignment::getNumGaps
        
            typedef ::alignlib::Position ( ::alignlib::Alignment::*getNumGaps_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "getNumGaps"
                , getNumGaps_function_type( &::alignlib::Alignment::getNumGaps ) );
        
        }
        { //::alignlib::Alignment::getPair
        
            typedef ::alignlib::ResiduePair ( ::alignlib::Alignment::*getPair_function_type )( ::alignlib::ResiduePair const & ) const;
            
            Alignment_exposer.def( 
                "getPair"
                , getPair_function_type( &::alignlib::Alignment::getPair )
                , ( bp::arg("p") ) );
        
        }
        { //::alignlib::Alignment::getRowFrom
        
            typedef ::alignlib::Position ( ::alignlib::Alignment::*getRowFrom_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "getRowFrom"
                , getRowFrom_function_type( &::alignlib::Alignment::getRowFrom ) );
        
        }
        { //::alignlib::Alignment::getRowTo
        
            typedef ::alignlib::Position ( ::alignlib::Alignment::*getRowTo_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "getRowTo"
                , getRowTo_function_type( &::alignlib::Alignment::getRowTo ) );
        
        }
        { //::alignlib::Alignment::getScore
        
            typedef ::alignlib::Score ( ::alignlib::Alignment::*getScore_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "getScore"
                , getScore_function_type( &::alignlib::Alignment::getScore ) );
        
        }
        { //::alignlib::Alignment::isEmpty
        
            typedef bool ( ::alignlib::Alignment::*isEmpty_function_type )(  ) const;
            
            Alignment_exposer.def( 
                "isEmpty"
                , isEmpty_function_type( &::alignlib::Alignment::isEmpty ) );
        
        }
        { //::alignlib::Alignment::mapColToRow
        
            typedef ::alignlib::Position ( ::alignlib::Alignment::*mapColToRow_function_type )( ::alignlib::Position,::alignlib::SearchType ) const;
            
            Alignment_exposer.def( 
                "mapColToRow"
                , mapColToRow_function_type( &::alignlib::Alignment::mapColToRow )
                , ( bp::arg("pos"), bp::arg("search")=::alignlib::NO_SEARCH ) );
        
        }
        { //::alignlib::Alignment::mapRowToCol
        
            typedef ::alignlib::Position ( ::alignlib::Alignment::*mapRowToCol_function_type )( ::alignlib::Position,::alignlib::SearchType ) const;
            
            Alignment_exposer.def( 
                "mapRowToCol"
                , mapRowToCol_function_type( &::alignlib::Alignment::mapRowToCol )
                , ( bp::arg("pos"), bp::arg("search")=::alignlib::NO_SEARCH ) );
        
        }
        { //::alignlib::Alignment::moveAlignment
        
            typedef void ( ::alignlib::Alignment::*moveAlignment_function_type )( ::alignlib::Position,::alignlib::Position ) ;
            
            Alignment_exposer.def( 
                "moveAlignment"
                , moveAlignment_function_type( &::alignlib::Alignment::moveAlignment )
                , ( bp::arg("row_offset"), bp::arg("col_offset") ) );
        
        }
        { //::alignlib::Alignment::removeColRegion
        
            typedef void ( ::alignlib::Alignment::*removeColRegion_function_type )( ::alignlib::Position,::alignlib::Position ) ;
            
            Alignment_exposer.def( 
                "removeColRegion"
                , removeColRegion_function_type( &::alignlib::Alignment::removeColRegion )
                , ( bp::arg("from"), bp::arg("to") ) );
        
        }
        { //::alignlib::Alignment::removePair
        
            typedef void ( ::alignlib::Alignment::*removePair_function_type )( ::alignlib::ResiduePair const & ) ;
            
            Alignment_exposer.def( 
                "removePair"
                , removePair_function_type( &::alignlib::Alignment::removePair )
                , ( bp::arg("pair") ) );
        
        }
        { //::alignlib::Alignment::removeRowRegion
        
            typedef void ( ::alignlib::Alignment::*removeRowRegion_function_type )( ::alignlib::Position,::alignlib::Position ) ;
            
            Alignment_exposer.def( 
                "removeRowRegion"
                , removeRowRegion_function_type( &::alignlib::Alignment::removeRowRegion )
                , ( bp::arg("from"), bp::arg("to") ) );
        
        }
        { //::alignlib::Alignment::setScore
        
            typedef void ( ::alignlib::Alignment::*setScore_function_type )( ::alignlib::Score ) ;
            
            Alignment_exposer.def( 
                "setScore"
                , setScore_function_type( &::alignlib::Alignment::setScore )
                , ( bp::arg("score") ) );
        
        }
        { //::alignlib::Alignment::switchRowCol
        
            typedef void ( ::alignlib::Alignment::*switchRowCol_function_type )(  ) ;
            
            Alignment_exposer.def( 
                "switchRowCol"
                , switchRowCol_function_type( &::alignlib::Alignment::switchRowCol ) );
        
        }
        { //::alignlib::Alignment::write
        
            typedef void ( ::alignlib::Alignment::*write_function_type )( ::std::ostream & ) const;
            
            Alignment_exposer.def( 
                "write"
                , write_function_type( &::alignlib::Alignment::write )
                , ( bp::arg("output") ) );
        
        }
        Alignment_exposer.def( bp::self_ns::str( bp::self ) );
        bp::register_ptr_to_python< boost::shared_ptr< alignlib::Alignment > >();
    }

}
