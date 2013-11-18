/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <cmath>

#include "mcommon/Log.hpp"
#include "mcommon/Quantity.hpp"

#include "mfit/Engine.hpp"
#include "mfit/Stats.hpp"
#include "mfit/Run.hpp"
#include "mfit/General.hpp"

using namespace mcommon ;

namespace mfit {

  Engine::Engine( const Stats& stats ) : stats(stats) {
  }

  static inline void hl( ) {
    CONSOLE( )
      << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      << std::endl ;
  }

  static inline void shl( std::string sh ) {
    hl( ) ;
    CONSOLE( ) << sh << std::endl ;
    hl( ) ;
  }

  void Engine::process( ) {
    hl( ) ;
    CONSOLE( ) << "The mfit analytics engine is processing your stats."
      << std::endl ;

    shl("General Stats") ;
    Quantity weight = *stats.get<Quantity>(General::STAT_WEIGHT) ;
    Quantity height = *stats.get<Quantity>(General::STAT_HEIGHT) ;
    Quantity neck = *stats.get<Quantity>(General::STAT_NECK) ;
    Quantity waist = *stats.get<Quantity>(General::STAT_WAIST) ;
    Quantity hips = *stats.get<Quantity>(General::STAT_HIPS) ;
    float bmi(General::bmi( stats ) ) ;
    float bfp(General::bfp( stats ) ) ;

    CONSOLE( ) << "\tYour Weight is " << weight << std::endl
               << "\tYour Height is " << height << std::endl
               << "\tYour Neck is " << neck << std::endl
               << "\tYour Waist is " << waist << std::endl
               << "\tYour Hips are " << hips << std::endl
               << "\tYour BMI is " << bmi << std::endl
               << "\tYour Body Fat Percentage is " << bfp << std::endl ;

    shl("Run Stats") ;
    Quantity as( Run::averageSpeed( stats ) ) ;
    CONSOLE( ) << "\tYour average speed for your best run was " << as << "."
      << std::endl ;

    Quantity dis1dot5( 1, MILES ) ;
    Quantity time( 12, MINUTES ) ;

    Quantity dti( Run::distanceTraveledIn( stats, time ) ) ;
    Quantity tttd( Run::timeToTravelDistance( stats, dis1dot5 ) ) ;

    Quantity tttds( std::round(std::fmod(
            tttd.convert(SECONDS).magnitude(), 60)), SECONDS) ;
    Quantity tttdm( std::trunc(tttd.convert(MINUTES).magnitude()), MINUTES ) ;
    
    CONSOLE( ) << "\tKeeping this pace in " << time << " you will travel "
      << dti  << "." << std::endl
      << "\tAnd you will travel " << dis1dot5 << " in " << tttdm 
      << " and " << tttds << std::endl ;
    
    Quantity dis1( 1, MILES ) ;
    tttd = Quantity( Run::timeToTravelDistance( stats, dis1 ) ) ;

    float ag( Run::ageGrade( stats, dis1, tttd ) ) ;

    CONSOLE( ) << "\tThis means for your given age your run time percentile is "
      << ag << " for " << dis1 << "." << std::endl ;

    shl( "Treadmill Stats" ) ;

    Quantity mets( Run::treadmillMETS( stats ) ) ;
    Quantity cals( Run::treadmillCals( stats ) ) ;
    Quantity tDis = *stats.get<Quantity>(Run::STAT_RUNS_TOTAL_DISTANCE_TREAD);
    Quantity tTime = *stats.get<Quantity>(Run::STAT_RUNS_TOTAL_TIME_TREAD);

    CONSOLE( ) 
      << "\tYou were on the treadmill for " << tDis << " and "
      << tTime.convert(MINUTES) << "." << std::endl
      << "\tThis means you spent " << mets << " or " << cals << std::endl ;
  }

}

