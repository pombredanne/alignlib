// This file has been generated by Py++.

#include "boost/python.hpp"

#include "boost/python/suite/indexing/vector_indexing_suite.hpp"

#include "includes.h"

#include "iostream"

#include "cstdio"

#include "build/Alignandum.pypp.hpp"

#include "build/Alignator.pypp.hpp"

#include "build/Alignatum.pypp.hpp"

#include "build/Alignment.pypp.hpp"

#include "build/AlignmentFormat.pypp.hpp"

#include "build/AlignmentFormatBlat.pypp.hpp"

#include "build/AlignmentFormatBlocks.pypp.hpp"

#include "build/AlignmentFormatDiagonals.pypp.hpp"

#include "build/AlignmentFormatEmissions.pypp.hpp"

#include "build/AlignmentFormatExplicit.pypp.hpp"

#include "build/AlignmentIterator.pypp.hpp"

#include "build/Coordinate.pypp.hpp"

#include "build/DistanceMatrix.pypp.hpp"

#include "build/Distor.pypp.hpp"

#include "build/EVDParameters.pypp.hpp"

#include "build/Encoder.pypp.hpp"

#include "build/Fragmentor.pypp.hpp"

#include "build/Iterator2D.pypp.hpp"

#include "build/Labels.pypp.hpp"

#include "build/LogOddor.pypp.hpp"

#include "build/MatrixDouble.pypp.hpp"

#include "build/MatrixInt.pypp.hpp"

#include "build/MatrixUInt.pypp.hpp"

#include "build/MultipleAlignment.pypp.hpp"

#include "build/NormalDistributionParameters.pypp.hpp"

#include "build/PositionVector.pypp.hpp"

#include "build/Profile.pypp.hpp"

#include "build/Regularizor.pypp.hpp"

#include "build/ResiduePair.pypp.hpp"

#include "build/Scorer.pypp.hpp"

#include "build/Sequence.pypp.hpp"

#include "build/Tree.pypp.hpp"

#include "build/Treetor.pypp.hpp"

#include "build/Weightor.pypp.hpp"

#include "build/alignlib_enumerations.pypp.hpp"

#include "build/alignlib_free_functions.pypp.hpp"

#include "build/vector_less__double__greater_.pypp.hpp"

#include "build/vector_less__unsigned_char__greater_.pypp.hpp"

#include "build/vector_less__unsigned_int__greater_.pypp.hpp"

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

template<class T>
      void wrapper_for_save(const T & a, PyObject* fp) 
      {
        if (!PyFile_Check(fp)) 
        {
          throw boost::python::error_already_set();
        }
        std::FILE* f = PyFile_AsFile(fp);
        std_obuf buf(f);
        std::ostream os(&buf);
        a.save( os );
      }

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

    register_vector_less__unsigned_int__greater__class();

    register_vector_less__unsigned_char__greater__class();

    register_Labels_class();

    register_PositionVector_class();

    register_vector_less__double__greater__class();

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

    register_MultipleAlignment_class();

    register_NormalDistributionParameters_class();

    register_Profile_class();

    register_Regularizor_class();

    register_ResiduePair_class();

    register_Scorer_class();

    register_Sequence_class();

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

    register_free_functions();
}

