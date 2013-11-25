/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"

namespace mfit {

  enum OneRepMaxModel {
    Brzcki,
    Baechle,
    DosRemedios,
    ONE_REP_MAX_MODEL_MAX
  } ;

  class WeightRepSet {

    public:

      WeightRepSet( ) ;

      virtual ~WeightRepSet( ) = default ;

      WeightRepSet( const WeightRepSet& ) = default ;

      WeightRepSet& operator=( const WeightRepSet& ) = default ;

      WeightRepSet( mcommon::Quantity weight, int sets, int reps ) ;

      WeightRepSet convert( int reps, enum OneRepMaxModel model) ;
      
      static float oneRepMaxPercentage[ONE_REP_MAX_MODEL_MAX][15] ;

      friend std::ostream& operator<<( std::ostream& out,
          const WeightRepSet& o ) ;

    private:
      
      mcommon::Quantity weight ;

      int sets ;

      int reps ;

  } ;
  
}
