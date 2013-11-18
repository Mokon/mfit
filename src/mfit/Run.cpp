/* Copyright (C) 2013 David 'Mokon' Bond,0. All Rights Reserved */

#include <cmath>
#include <vector>
#include <iostream>

#include "mcommon/Gender.hpp"
#include "mfit/Run.hpp"
#include "mfit/General.hpp"

using namespace mcommon ;

namespace mfit {
  
  const std::string Run::STAT_RUNS = "runs" ;

  const std::string Run::STAT_RUNS_TOTAL_TIME = "runs_total_time" ;

  const std::string Run::STAT_RUNS_TOTAL_DISTANCE = "runs_total_distance" ;

  const std::string Run::STAT_RUNS_TREAD = "runs_tread" ;

  const std::string Run::STAT_RUNS_TOTAL_TIME_TREAD = "runs_total_time_tread" ;

  const std::string Run::STAT_RUNS_TOTAL_DISTANCE_TREAD = "runs_total_distance_tread" ;


  const std::string Run::STAT_GRADIENT = "gradient" ;

  Run::Run( Quantity time, Quantity speed ) : time(time), speed(speed),
  distance( Quantity( time.convert(HOURS).magnitude() *
        speed.convert(MPH).magnitude(), MILES )) {
  }

  Run::Run( float time, float speed ) : Run(Quantity(time, MINUTES),
      Quantity(speed, MPH)) {
  }

  Quantity Run::treadmillMETS( const Stats& stats ) {
    float* gradient = stats.get<float>(STAT_GRADIENT) ;
    Quantity* weight = stats.get<Quantity>(General::STAT_WEIGHT) ;
    Quantity* tDis = stats.get<Quantity>(STAT_RUNS_TOTAL_DISTANCE_TREAD);
    Quantity* tTime = stats.get<Quantity>(STAT_RUNS_TOTAL_TIME_TREAD);

    float dis = tDis->convert(KM).magnitude( ) ;
    float we = weight->convert(KG).magnitude( ) ;
    float t = tTime->convert(MINUTES).magnitude( ) ;
    float sp = dis/t*60.0; // KMH
    float gas =  sp + sp*(*gradient)*9.0/200.0 ; 
    float cal=(gas*1000.0/60.0+17.5)*t*we/1000.0 ;
    return Quantity(cal/we/t*60, METS) ;
  }
  
  Quantity Run::treadmillCals( const Stats& stats ) {
    float* gradient = stats.get<float>(STAT_GRADIENT) ;
    Quantity* weight = stats.get<Quantity>(General::STAT_WEIGHT) ;
    Quantity* tDis = stats.get<Quantity>(STAT_RUNS_TOTAL_DISTANCE_TREAD);
    Quantity* tTime = stats.get<Quantity>(STAT_RUNS_TOTAL_TIME_TREAD);

    float dis = tDis->convert(KM).magnitude( ) ;
    float we = weight->convert(KG).magnitude( ) ;
    float t = tTime->convert(MINUTES).magnitude( ) ;
    float sp = dis/t*60.0; // KMH
    float gas =  sp + sp*(*gradient)*9.0/200.0 ; 
    return Quantity((gas*1000.0/60.0+17.5)*t*we/1000.0, CALORIES) ;
  }

  Quantity Run::averageSpeed( const Stats& stats ) {
    Quantity* tDis = stats.get<Quantity>(STAT_RUNS_TOTAL_DISTANCE);
    Quantity* tTime = stats.get<Quantity>(STAT_RUNS_TOTAL_TIME);

    return Quantity( tDis->convert(MILES).magnitude()/
        tTime->convert(HOURS).magnitude(), MPH ) ;
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
     
  float Run::ageGrade( const Stats& stats, const Quantity distance,
      const Quantity time ) {
  // TODO this need to be redone so it works with all stats...
    Gender* gender = stats.get<Gender>(General::STAT_GENDER) ;
    Quantity* age = stats.get<Quantity>(General::STAT_AGE) ;
    //EventType evt(et1MILES);
    (void)distance;
    return std[*gender][21] /
      factors[*gender][0][(int)std::round(age->convert(YEARS).magnitude()-5)] /
      time.convert(SECONDS).magnitude() * 100.0f ;
  }

  const float Run::std[GENDER_MAX][33] = {
    { 774,940,1011,1272,1280,1611,1951,2469,2663,3358,3553,4259,5179,7495,9080,
      16080,21360,36300,39850,52800,205.8,222.6,283.2,440,474.6,598,730,757,919,
      1247,1255,1580 },
    { 888,1073,1154,1445,1452,1820,2200,2772,2981,3738,3950,4712,5696,8125,9820,
      17760,23591,39700,43500,57600,232.47,251.6,321.5,501.42,541.5,683,833,
      864.68,1051,1132,1425,1435,1801.09},
  } ;

  const float Run::factors[1][1][98] = { {
    { .6526,.6899,.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,.9999,.9991,.9975,.9952,.9922,.9885,.984,.9788,.9729,.9662,.9592,.9521,.9451,.938,.931,.924,.9169,.9099,.9028,.8958,.8888,.8817,.8747,.8676,.8606,.8536,.8465,.8395,.8324,.8254,.8184,.8113,.8043,.7972,.7902,.7832,.7761,.7691,.762,.755,.7479,.7402,.7319,.723,.7134,.7031,.6923,.6808,.6687,.6559,.6425,.6285,.6138,.5985,.5825,.566,.5488,.5309,.5124,.4933,.4735,.4531,.4321,.4104,.3881,.3652,.3416,.3174,.2926,.2671,.2409,.2142,.1868 },
  } } ; 

}
