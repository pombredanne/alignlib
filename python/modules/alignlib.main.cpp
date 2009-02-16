// This file has been generated by Py++.

#include "boost/python.hpp"

#include "boost/python/suite/indexing/vector_indexing_suite.hpp"

#include "includes.h"

#include "iostream"

#include "cstdio"

#include "modules/Alignandum.pypp.hpp"

#include "modules/Alignator.pypp.hpp"

#include "modules/Alignatum.pypp.hpp"

#include "modules/AlignatumVector.pypp.hpp"

#include "modules/Alignment.pypp.hpp"

#include "modules/AlignmentFormat.pypp.hpp"

#include "modules/AlignmentFormatBlat.pypp.hpp"

#include "modules/AlignmentFormatBlocks.pypp.hpp"

#include "modules/AlignmentFormatDiagonals.pypp.hpp"

#include "modules/AlignmentFormatEmissions.pypp.hpp"

#include "modules/AlignmentFormatExplicit.pypp.hpp"

#include "modules/AlignmentIterator.pypp.hpp"

#include "modules/Coordinate.pypp.hpp"

#include "modules/CountVector.pypp.hpp"

#include "modules/DistanceMatrix.pypp.hpp"

#include "modules/Distor.pypp.hpp"

#include "modules/EVDParameters.pypp.hpp"

#include "modules/Encoder.pypp.hpp"

#include "modules/Fragmentor.pypp.hpp"

#include "modules/Iterator2D.pypp.hpp"

#include "modules/LogOddor.pypp.hpp"

#include "modules/MatrixDouble.pypp.hpp"

#include "modules/MatrixInt.pypp.hpp"

#include "modules/MatrixUInt.pypp.hpp"

#include "modules/MultAlignment.pypp.hpp"

#include "modules/MultAlignmentFormat.pypp.hpp"

#include "modules/MultAlignmentFormatPlain.pypp.hpp"

#include "modules/MultipleAlignator.pypp.hpp"

#include "modules/MultipleAlignment.pypp.hpp"

#include "modules/NormalDistributionParameters.pypp.hpp"

#include "modules/PositionVector.pypp.hpp"

#include "modules/Profile.pypp.hpp"

#include "modules/Regularizor.pypp.hpp"

#include "modules/ResiduePair.pypp.hpp"

#include "modules/Scorer.pypp.hpp"

#include "modules/Segment.pypp.hpp"

#include "modules/Sequence.pypp.hpp"

#include "modules/Toolkit.pypp.hpp"

#include "modules/Tree.pypp.hpp"

#include "modules/Treetor.pypp.hpp"

#include "modules/Weightor.pypp.hpp"

#include "modules/alignlib_enumerations.pypp.hpp"

#include "modules/alignlib_free_functions.pypp.hpp"

#include "modules/vector_less__double__greater_.pypp.hpp"

#include "modules/vector_less__std_scope_string__greater_.pypp.hpp"

#include "modules/vector_less__unsigned_char__greater_.pypp.hpp"

namespace bp = boost::python;

class std_obuf: public std::streambuf 
        {
      public:
        std_obuf(std::FILE* file): m_file(file) {}
      protected:
        std::streambuf::int_type overflow(std::streambuf::int_type c) 
        {
          return std::fputc(c, m_file) ==EOF? std::streambuf::traits_type::eof(): c;
        }
      private:
        FILE* m_file;
      };

    class std_ibuf: public std::streambuf 
        {
      public:
          std_ibuf(std::FILE* file): m_file(file) {}
      protected:
          std::streambuf::int_type underflow() { 
           int c = std::getc(m_file);
           if (c != EOF) 
               std::ungetc(c, m_file);
            return c;
           }

          std::streambuf::int_type uflow() {
           return std::getc(m_file);
          }

          std::streambuf::int_type pbackfail(int c = EOF) {
            return c != EOF ? std::ungetc(c, m_file) : EOF;
          }
    private:
          FILE* m_file;      
          
      };

alignlib::HAlignandum wrapper_for_load_Alignandum( PyObject * fp )
      {
          if (!PyFile_Check(fp))
          {
              throw boost::python::error_already_set();
          }
         std::FILE * f = PyFile_AsFile(fp);   
         std_ibuf buf(f);
         std::istream is(&buf);
         if (is.peek() == EOF)
             return alignlib::HAlignandum();
         else
             return alignlib::HAlignandum (alignlib::loadAlignandum( is ));
      }

alignlib::HEncoder wrapper_for_load_Encoder( PyObject * fp )
      {
          if (!PyFile_Check(fp))
          {
              throw boost::python::error_already_set();
          }
         std::FILE * f = PyFile_AsFile(fp);   
         std_ibuf buf(f);
         std::istream is(&buf);
         if (is.peek() == EOF)
             return alignlib::HEncoder();
         else
             return alignlib::HEncoder (alignlib::loadEncoder( is ));
      }

BOOST_PYTHON_MODULE(alignlib){
    register_enumerations();

    register_CountVector_class();

    register_vector_less__unsigned_char__greater__class();

    register_vector_less__std_scope_string__greater__class();

    register_PositionVector_class();

    register_vector_less__double__greater__class();

    register_AlignatumVector_class();

    register_Alignandum_class();

    register_Alignator_class();

    register_Alignatum_class();

    register_Alignment_class();

    register_AlignmentFormat_class();

    register_AlignmentFormatBlocks_class();

    register_AlignmentFormatBlat_class();

    register_AlignmentFormatDiagonals_class();

    register_AlignmentFormatEmissions_class();

    register_AlignmentFormatExplicit_class();

    register_AlignmentIterator_class();

    register_Coordinate_class();

    register_DistanceMatrix_class();

    register_Distor_class();

    register_EVDParameters_class();

    register_Encoder_class();

    register_Fragmentor_class();

    register_Iterator2D_class();

    register_LogOddor_class();

    register_MatrixDouble_class();

    register_MatrixInt_class();

    register_MatrixUInt_class();

    register_MultAlignment_class();

    register_MultAlignmentFormat_class();

    register_MultAlignmentFormatPlain_class();

    register_MultipleAlignator_class();

    register_MultipleAlignment_class();

    register_NormalDistributionParameters_class();

    register_Profile_class();

    register_Regularizor_class();

    register_ResiduePair_class();

    register_Scorer_class();

    register_Segment_class();

    register_Sequence_class();

    register_Toolkit_class();

    register_Tree_class();

    register_Treetor_class();

    register_Weightor_class();

    bp::def( "loadAlignandum", wrapper_for_load_Alignandum );

    bp::def( "loadEncoder", wrapper_for_load_Encoder );

    { //::std::vector<HAlignment, std::allocator<HAlignment> >
            typedef bp::class_< std::vector<alignlib::HAlignment, std::allocator<alignlib::HAlignment> > > FragmentVector_exposer_t;
            FragmentVector_exposer_t FragmentVector_exposer = FragmentVector_exposer_t( "FragmentVector" );
            bp::scope FragmentVector_scope( FragmentVector_exposer );
            FragmentVector_exposer.def( bp::vector_indexing_suite< ::std::vector<alignlib::HAlignment, std::allocator<alignlib::HAlignment> >, true >() );
            }
    
            bp::register_ptr_to_python< boost::shared_ptr<alignlib::FragmentVector> >();

    { //::std::vector<HAlignandum, std::allocator<HAlignandum> >
            typedef bp::class_< std::vector<alignlib::HAlignandum, std::allocator<alignlib::HAlignandum> > > AlignandumVector_exposer_t;
            AlignandumVector_exposer_t AlignandumVector_exposer = AlignandumVector_exposer_t( "AlignandumVector" );
            bp::scope AlignandumVector_scope( AlignandumVector_exposer );
            AlignandumVector_exposer.def( bp::vector_indexing_suite< ::std::vector<alignlib::HAlignandum, std::allocator<alignlib::HAlignandum> >, true >() );
            }
    
            bp::register_ptr_to_python< boost::shared_ptr<alignlib::AlignandumVector> >();

    { //::std::vector<HAlignatum, std::allocator<HAlignatum> >
            typedef bp::class_< std::vector<alignlib::HAlignatum, std::allocator<alignlib::HAlignatum> > > AlignatumVector_exposer_t;
            AlignatumVector_exposer_t AlignatumVector_exposer = AlignatumVector_exposer_t( "AlignatumVector" );
            bp::scope AlignatumVector_scope( AlignatumVector_exposer );
            AlignatumVector_exposer.def( bp::vector_indexing_suite< ::std::vector<alignlib::HAlignatum, std::allocator<alignlib::HAlignatum> >, true >() );
            }
    
            bp::register_ptr_to_python< boost::shared_ptr<alignlib::AlignatumVector> >();

    { //::std::vector<std::string, std::allocator<std::string> >
            typedef bp::class_< std::vector<std::string, std::allocator<std::string> > > StringVector_exposer_t;
            StringVector_exposer_t StringVector_exposer = StringVector_exposer_t( "StringVector" );
            bp::scope StringVector_scope( StringVector_exposer );
            StringVector_exposer.def( bp::vector_indexing_suite< ::std::vector<std::string, std::allocator<std::string> >, true >() );
            }
    
            bp::register_ptr_to_python< boost::shared_ptr<alignlib::StringVector> >();

    { //::std::vector<int, std::allocator<int> >
            typedef bp::class_< std::vector<int, std::allocator<int> > > CountVector_exposer_t;
            CountVector_exposer_t CountVector_exposer = CountVector_exposer_t( "CountVector" );
            bp::scope CountVector_scope( CountVector_exposer );
            CountVector_exposer.def( bp::vector_indexing_suite< ::std::vector<int, std::allocator<int> >, true >() );
            }
    
            bp::register_ptr_to_python< boost::shared_ptr<alignlib::CountVector> >();

    register_free_functions();
}

