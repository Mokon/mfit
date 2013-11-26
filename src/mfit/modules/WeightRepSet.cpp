/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <stdexcept>

#include "mfit/modules/WeightRepSet.hpp"

using namespace mcommon ;

namespace mfit {

  WeightRepSet::WeightRepSet( ) : sets(0), reps(0) {
  }

  WeightRepSet::WeightRepSet( mcommon::Quantity weight, int sets, int reps ) :
    weight(weight), sets(sets), reps(reps) {
    }

  float WeightRepSet::oneRepMaxPercentage[ONE_REP_MAX_MODEL_MAX][15] = {
    { 100, 95, 90, 88, 86, 83, 80, 78, 76, 75, 72, 70, 0, 0,  0 },
    { 100, 95, 93, 90, 87, 85, 83, 80, 77, 75,  0, 67, 0, 0, 65 },
    { 100, 92, 90, 87, 85, 82,  0, 75,  0, 70,  0, 65, 0, 0, 60 },
  } ;

  WeightRepSet WeightRepSet::convert( int reps, enum OneRepMaxModel model) {
    if( this->reps > 15 ) {
      throw std::runtime_error("model does not handle the given rep count");
    }

    float perc = oneRepMaxPercentage[model][this->reps-1] ;
    if( perc == 0 ) {
      throw std::runtime_error("model does not handle the given rep count");
    }
    float mag = weight.magnitude()/(perc/100.f) ;

    if( reps > 15 ) {
      throw std::runtime_error("model does not handle the given rep count");
    }

    perc = oneRepMaxPercentage[model][reps-1] ;
    if( perc == 0 ) {
      throw std::runtime_error("model does not handle the given rep count");
    }

    mag *= perc/100.0 ;

    return WeightRepSet( Quantity( mag, weight.unit()), sets, reps ) ;
  }

  std::ostream& WeightRepSet::out( std::ostream& o ) const {
    return o << "Weight: " << weight
      << ", Sets: " << sets << ", Reps: " << reps ;
  }

}

