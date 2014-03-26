/* Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved */

#include "mfit/modules/weights/WeightRepSet.hpp"

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

  std::string WeightRepSet::oneRepMaxModelString[ONE_REP_MAX_MODEL_MAX] = {
    "Brzcki",
    "Baechle",
    "DosRemedios",
    "average",
  } ;

  float WeightRepSet::getPerc( int reps, enum OneRepMaxModel model ) {
    if( reps >= 15 ) {
      throw UnhandledRepException("model does not handle the given rep count");
    }
    float perc = 0 ;
    switch( model ) {
      case Average:
        {
          float t = 0 ;
          for( int i = 0 ; i < ONE_REP_MAX_MODEL_MAX - 1 ; i++ ) {
            perc = oneRepMaxPercentage[i][reps-1] ;
            if( perc == 0 ) {
              throw UnhandledRepException("model does not handle the given rep count");
            }
            t += perc ;
          }
          return t/(ONE_REP_MAX_MODEL_MAX - 1) ;
        }
      default:
        perc = oneRepMaxPercentage[model][reps-1] ;
        if( perc == 0 ) {
          throw UnhandledRepException("model does not handle the given rep count");
        }
        return perc ;
    }
  }

  WeightRepSet WeightRepSet::convert( int reps, enum OneRepMaxModel model) {
    float perc = getPerc( this->reps, model ) ;
    float mag = weight.magnitude()/(perc/100.f) ;
    perc = getPerc( reps, model ) ;
    mag *= perc/100.0 ;
    return WeightRepSet( Quantity( mag, weight.unit()), sets, reps ) ;
  }

  WeightRepSet WeightRepSet::operator *( const float& rhs ) {
    WeightRepSet ret(*this);
    ret.weight = weight*rhs ;
    return ret ;
  }

  int WeightRepSet::getReps( ) {
    return reps ;
  }

  std::ostream& WeightRepSet::out( std::ostream& o ) const {
    return o << "Weight: " << weight
      << ", Sets: " << sets << ", Reps: " << reps ;
  }

}

