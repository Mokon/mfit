/* Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include "mcommon/Exception.hpp"
#include "mcommon/Quantity.hpp"

namespace mfit {

  enum OneRepMaxModel {
    Brzcki,
    Baechle,
    DosRemedios,
    Average,
    ONE_REP_MAX_MODEL_MAX,
  } ;

  DEFINE_EXCEPTION_CLASS( UnhandledRepException ) ;

  class WeightRepSet : public mcommon::Value {

    public:

      WeightRepSet( ) ;

      virtual ~WeightRepSet( ) = default ;

      WeightRepSet( const WeightRepSet& ) = default ;

      WeightRepSet& operator=( const WeightRepSet& ) = default ;

      WeightRepSet( mcommon::Quantity weight, int sets, int reps ) ;

      WeightRepSet convert( int reps, enum OneRepMaxModel model) ;

      virtual std::ostream& out( std::ostream& o ) const ;
      
      WeightRepSet operator *( const float& rhs ) ;
      
      static std::string oneRepMaxModelString[ONE_REP_MAX_MODEL_MAX] ;

      int getReps( ) ;

    private:
  
      static float getPerc( int reps, enum OneRepMaxModel model ) ;

      static float oneRepMaxPercentage[ONE_REP_MAX_MODEL_MAX][15] ;

      mcommon::Quantity weight ;

      int sets ;

      int reps ;

  } ;

}

