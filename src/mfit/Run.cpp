/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <cmath>
#include <vector>
#include <iostream>

#include "mfit/Run.hpp"

using namespace mcommon ;

namespace mfit {
      
  const std::string Run::STAT_RUNS = "runs" ;

  Run::Run( Quantity time, Quantity speed ) : time(time), speed(speed), 
  distance( Quantity( time.convert(HOURS).magnitude() *
        speed.convert(MPH).magnitude(), MILES )) {
  }

  Run::Run( float time, float speed ) : Run(Quantity(time,MINUTES),
      Quantity(speed,MPH)) {
  }

  Quantity Run::averageSpeed( const Stats& stats ) {
    std::vector<Run>* runs = static_cast<std::vector<Run>*>(
        stats.find(STAT_RUNS)->second);
    if(runs == NULL ) {
      throw StatMissingException( STAT_RUNS ) ;
    }

    Quantity tDis( 0, MILES ) ;
    Quantity tTime( 0, HOURS ) ;

    for( auto e : *runs ) {
      tTime += e.time ;
      tDis += e.distance ;
    }

    return Quantity( tDis.convert(MILES).magnitude()/
        tTime.convert(HOURS).magnitude(), MPH ) ;
  }

  Quantity Run::distanceTraveledIn( const Stats& stats, const Quantity time ) {
    Quantity avgSpeed(averageSpeed(stats)) ;
    return Quantity( time.convert(HOURS).magnitude()*
        avgSpeed.convert(MPH).magnitude(), MILES ) ;
  }

  Quantity Run::timeToTravelDistance( const Stats& stats, const Quantity dis ) {
    Quantity avgSpeed(averageSpeed(stats)) ;
    return Quantity( dis.convert(MILES).magnitude( )/
        avgSpeed.convert(MPH).magnitude( ), HOURS ) ;
  }

}

