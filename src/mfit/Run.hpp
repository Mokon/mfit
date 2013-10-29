/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"
#include "mfit/Stats.hpp"

namespace mfit {

  class Run {

    public:

      Run( mcommon::Quantity time, mcommon::Quantity speed ) ;

      Run( float time, float speed ) ;

      mcommon::Quantity time ;

      mcommon::Quantity speed ;

      mcommon::Quantity distance ;

      static mcommon::Quantity averageSpeed( const Stats& stats ) ;
  
      static mcommon::Quantity timeToTravelDistance( const Stats& stats,
          const mcommon::Quantity distance ) ;
      
      static mcommon::Quantity distanceTraveledIn( const Stats& stats,
          const mcommon::Quantity time ) ;
 
      static const std::string STAT_RUNS ;

  } ;

}

