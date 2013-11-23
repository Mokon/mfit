/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <cmath>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include "mfit/modules/Cardio.hpp"
#include "mfit/modules/General.hpp"
#include "mfit/Engine.hpp"

using namespace mcommon ;

namespace mfit {

  std::string Cardio::getKey( ) {
    return key ;
  }

  void Cardio::process( std::ostream& out,
      const pugi::xml_document& cfg ) const {
    out << "Cardio" << std::endl ;

    out << "\tRun Stats" << std::endl ;

    Quantity as( averageSpeed( cfg ) ) ;
    out << "\t\tYour average speed for your best run was " << as << "."
      << std::endl ;

    Quantity dis1dot5( 1.5, MILES ) ;
    Quantity time( 15, MINUTES ) ;

    Quantity dti( distanceTraveledIn( cfg, time ) ) ;
    Quantity tttd( timeToTravelDistance( cfg, dis1dot5 ) ) ;

    Quantity tttds( std::round(std::fmod(
            tttd.convert(SECONDS).magnitude(), 60)), SECONDS) ;
    Quantity tttdm( std::trunc(tttd.convert(MINUTES).magnitude()), MINUTES ) ;

    out << "\t\tKeeping this pace in " << time << " you will travel "
      << dti  << "." << std::endl
      << "\t\tAnd you will travel " << dis1dot5 << " in " << tttdm 
      << " and " << tttds << std::endl ;

    Quantity dis1( 1, MILES ) ;
    tttd = Quantity( timeToTravelDistance( cfg, dis1 ) ) ;
    float ag( ageGrade( cfg, dis1, tttd ) ) ;

    out << "\t\tThis means for your given age your run time percentile is "
      << ag << " for " << dis1 << "." << std::endl ;

    out << "\tTreadmill Stats" << std::endl ;

    Quantity mets( treadmillMETS( cfg ) ) ;
    Quantity cals( treadmillCals( cfg ) ) ;

    std::vector<Run> treadmillRuns ;
    Quantity tDis ;
    Quantity tTime ;
    getRuns(cfg, "/person/excercises/cardio/runs[@type='treadmill']/run",
        treadmillRuns, tTime, tDis) ;

    out << "\t\tYou were on the treadmill for " << tDis << " and "
      << tTime.convert(MINUTES) << "." << std::endl
      << "\t\tThis means you spent " << mets << " or " << cals << std::endl ;

    std::vector<Run> bestRuns ;
    getRuns(cfg, "/person/excercises/cardio/runs[@type='best']/run", bestRuns,
        tTime, tDis) ;

  }
  
  float Cardio::getGradient( const pugi::xml_document& cfg ) {
    return Engine::getAttributeAsFloat( cfg,
        "/person/excercises/cardio/runs[@type='treadmill']/@gradient" ) ;
  }

  const std::string Cardio::key = "mfit::Cardio" ;

  void Cardio::getRuns( const pugi::xml_document& cfg,
      const std::string xpath, std::vector<Run>& runs, Quantity& tTime,
      Quantity& tDis ) {
    tDis = Quantity( 0, MILES ) ;
    tTime = Quantity( 0, HOURS ) ;

    pugi::xpath_node_set xruns = cfg.select_nodes(xpath.c_str());

    for ( auto it : xruns ) {
#if 0
    std::cout << xpath << " " <<  it.node().name() << " " << it.node().child("speed").last_child().value() << std::endl ;
#endif
      float time = boost::lexical_cast<float>(it.node().child("time").last_child().value());
      float speed = boost::lexical_cast<float>(it.node().child("speed").last_child().value());
      runs.push_back( Run(time, speed) );
      tTime += runs.back().time;
      tDis += runs.back().distance ;
    }
  }

  Quantity Cardio::treadmillMETS( const pugi::xml_document& cfg ) {
    float gradient = Cardio::getGradient( cfg ) ;
    Quantity weight = General::getWeight( cfg ) ;
    std::vector<Run> treadmillRuns ;
    Quantity tDis ;
    Quantity tTime ;
    getRuns(cfg, "/person/excercises/cardio/runs[@type='treadmill']/run",
        treadmillRuns, tTime, tDis) ;

    float dis = tDis.convert(KM).magnitude( ) ;
    float we = weight.convert(KG).magnitude( ) ;
    float t = tTime.convert(MINUTES).magnitude( ) ;
    float sp = dis/t*60.0; // KMH
    float gas =  sp + sp*gradient*9.0/200.0 ; 
    float cal=(gas*1000.0/60.0+17.5)*t*we/1000.0 ;
    return Quantity(cal/we/t*60, METS) ;
  }

  Quantity Cardio::treadmillCals( const pugi::xml_document& cfg ) {
    float gradient = Cardio::getGradient( cfg ) ;
    Quantity weight = General::getWeight( cfg ) ;
    std::vector<Run> treadmillRuns ;
    Quantity tDis ;
    Quantity tTime ;
    getRuns(cfg, "/person/excercises/cardio/runs[@type='treadmill']/run",
        treadmillRuns, tTime, tDis) ;

    float dis = tDis.convert(KM).magnitude( ) ;
    float we = weight.convert(KG).magnitude( ) ;
    float t = tTime.convert(MINUTES).magnitude( ) ;
    float sp = dis/t*60.0; // KMH
    float gas =  sp + sp*gradient*9.0/200.0 ; 
    return Quantity((gas*1000.0/60.0+17.5)*t*we/1000.0, CALORIES) ;
  }

  Quantity Cardio::averageSpeed( const pugi::xml_document& cfg ) {
    std::vector<Run> runs ;
    Quantity tDis ;
    Quantity tTime ;
    getRuns(cfg, "/person/excercises/cardio/runs[@type='best']/run",
        runs, tTime, tDis) ;

    return Quantity( tDis.convert(MILES).magnitude()/
        tTime.convert(HOURS).magnitude(), MPH ) ;
  }

  Quantity Cardio::distanceTraveledIn( const pugi::xml_document& cfg,
      const Quantity time ) {
    Quantity avgSpeed(averageSpeed(cfg)) ;
    return Quantity( time.convert(HOURS).magnitude()*
        avgSpeed.convert(MPH).magnitude(), MILES ) ;
  }

  Quantity Cardio::timeToTravelDistance( const pugi::xml_document& cfg,
      const Quantity dis ) {
    Quantity avgSpeed(averageSpeed(cfg)) ;
    return Quantity( dis.convert(MILES).magnitude( )/
        avgSpeed.convert(MPH).magnitude( ), HOURS ) ;
  }

  float Cardio::ageGrade( const pugi::xml_document& cfg, const Quantity distance,
      const Quantity time ) {
    Quantity age = General::getAge( cfg ).convert(YEARS) ;
    Gender gender = General::getGender( cfg ) ;

    // TODO this need to be redone so it works with all cfg...
    //EventType evt(et1MILES);
    (void)distance;
    return std[gender][21] /
      factors[gender][0][(int)std::round(age.magnitude()-5)] /
      time.convert(SECONDS).magnitude() * 100.0f ;
  }

  const float Cardio::std[GENDER_MAX][33] = {
    { 774,940,1011,1272,1280,1611,1951,2469,2663,3358,3553,4259,5179,7495,9080,
      16080,21360,36300,39850,52800,205.8,222.6,283.2,440,474.6,598,730,757,919,
      1247,1255,1580 },
    { 888,1073,1154,1445,1452,1820,2200,2772,2981,3738,3950,4712,5696,8125,9820,
      17760,23591,39700,43500,57600,232.47,251.6,321.5,501.42,541.5,683,833,
      864.68,1051,1132,1425,1435,1801.09},
  } ;

  const float Cardio::factors[1][1][98] = { {
    { .6526,.6899,.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,
      .955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,.9999,.9991,.9975,.9952,.9922,
      .9885,.984,.9788,.9729,.9662,.9592,.9521,.9451,.938,.931,.924,.9169,.9099,
      .9028,.8958,.8888,.8817,.8747,.8676,.8606,.8536,.8465,.8395,.8324,.8254,
      .8184,.8113,.8043,.7972,.7902,.7832,.7761,.7691,.762,.755,.7479,.7402,
      .7319,.723,.7134,.7031,.6923,.6808,.6687,.6559,.6425,.6285,.6138,.5985,
      .5825,.566,.5488,.5309,.5124,.4933,.4735,.4531,.4321,.4104,.3881,.3652,
      .3416,.3174,.2926,.2671,.2409,.2142,.1868 },
  } } ; 
}

