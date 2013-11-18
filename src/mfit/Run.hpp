/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"
#include "mcommon/Gender.hpp"
#include "mfit/General.hpp"
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

      static mcommon::Quantity treadmillMETS( const Stats& stats ) ;
      
      static mcommon::Quantity treadmillCals( const Stats& stats ) ;

      static mcommon::Quantity timeToTravelDistance( const Stats& stats,
          const mcommon::Quantity distance ) ;

      static mcommon::Quantity distanceTraveledIn( const Stats& stats,
          const mcommon::Quantity time ) ;

      static float ageGrade( const Stats& stats,
          const mcommon::Quantity distance, const mcommon::Quantity time ) ;

      static const std::string STAT_RUNS ;
      
      static const std::string STAT_RUNS_TOTAL_TIME ;
      
      static const std::string STAT_RUNS_TOTAL_DISTANCE ;
      
      static const std::string STAT_RUNS_TREAD ;
      
      static const std::string STAT_RUNS_TOTAL_TIME_TREAD ;
      
      static const std::string STAT_RUNS_TOTAL_DISTANCE_TREAD ;


      static const std::string STAT_GRADIENT ;

    private:

      static const float std[mcommon::GENDER_MAX][33] ;

      static const float factors[1][1][98] ;

      enum EventType {
        et5KM=0,
        et6KM=0,
        et4MILE=0,
        et8KM=0,
        et5MILE=0,
        et10KM=0,
        et12KM=1,
        et15KM=2,
        et10MILE=3,
        et20KM=4,
        etHALFMARATHON=5,
        et25KM=6,
        et30KM=7,
        etMARATHON=8,
        et50KM=8,
        et50MILE=8,
        et100KM=8,
        et150KM=8,
        et100MILE=8,
        et200KM=8,
        // Track Events
        et1500M=9,
        et1MILES=9,
        et2000M=9,
        et3000M=9,
        et2MILES=9,
        et4000M=9,
        et3MILES=9,
        et5000M=9,
        et6000M=9,
        //et4MILES=9,
        et8000M=9,
        et5MILES=9,
        et10000M=9,
        EVENT_TYPE_MAX=10,
      } ;

  } ;

}

