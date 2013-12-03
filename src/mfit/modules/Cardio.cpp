/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include "mcommon/Log.hpp"

#include "mfit/modules/Cardio.hpp"
#include "mfit/modules/General.hpp"
#include "mfit/modules/Measurements.hpp"
#include "mfit/Engine.hpp"

using namespace mcommon ;

namespace mfit {

  Cardio::Cardio( ) {
    add( "Your average speed for your best run was", getAverageSpeed ) ;
    add( "You were on the treadmill for", getTreadmillTime ) ;
    add( "\tand you traveled", getTreadmillDistance ) ;
    add( "\tand you spent", getTreadmillMETS ) ;
    add( "\tand you burnt", getTreadmillCals ) ;
    add( "Given this pace it would take you", "\tto travel", getTimeToTravel ) ;
    add( "Given this pace you would travel", "\tin", getDistanceTraveled ) ;
    add( { "This means that for your given age your run time percentile is",
        "\tgiven a run length of",
        "\tand given a run time of" },
        getAgeGrade ) ;
  }

  std::string Cardio::getKey( ) {
    return key ;
  }

  float Cardio::getGradient( const pugi::xml_document& cfg ) {
    return Engine::getAttributeAs<float>( cfg,
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
      DLOG(INFO) << xpath << " " <<  it.node().name() << " "
        << it.node().child("speed").last_child().value() << std::endl ;

      float time = boost::lexical_cast<float>(
          it.node().child("time").last_child().value());
      float speed = boost::lexical_cast<float>(
          it.node().child("speed").last_child().value());
      runs.push_back( Run(time, speed) );
      tTime += runs.back().time;
      tDis += runs.back().distance ;
    }
  }

  std::shared_ptr<Quantity> Cardio::getTreadmillDistance(
      const pugi::xml_document& cfg ) {
    Quantity weight = *Measurements::getWeight( cfg ) ;
    std::vector<Run> treadmillRuns ;
    Quantity tDis ;
    Quantity tTime ;
    getRuns(cfg, "/person/excercises/cardio/runs[@type='treadmill']/run",
        treadmillRuns, tTime, tDis) ;

    return std::shared_ptr<Quantity>( new Quantity(tDis) ) ;
  }

  std::shared_ptr<Quantity> Cardio::getTreadmillTime(
      const pugi::xml_document& cfg ) {
    Quantity weight = *Measurements::getWeight( cfg ) ;
    std::vector<Run> treadmillRuns ;
    Quantity tDis ;
    Quantity tTime ;
    getRuns(cfg, "/person/excercises/cardio/runs[@type='treadmill']/run",
        treadmillRuns, tTime, tDis) ;

    return std::shared_ptr<Quantity>( new Quantity(tTime) ) ;
  }

  std::shared_ptr<Quantity> Cardio::getTreadmillMETS(
      const pugi::xml_document& cfg ) {
    float gradient = Cardio::getGradient( cfg ) ;
    Quantity weight = *Measurements::getWeight( cfg ) ;
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
    return std::shared_ptr<Quantity>( new Quantity(cal/we/t*60, METS) ) ;
  }

  std::shared_ptr<Quantity> Cardio::getTreadmillCals(
      const pugi::xml_document& cfg ) {
    float gradient = Cardio::getGradient( cfg ) ;
    Quantity weight = *Measurements::getWeight( cfg ) ;
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
    return std::shared_ptr<Quantity>(
        new Quantity((gas*1000.0/60.0+17.5)*t*we/1000.0, CALORIES) ) ;
  }

  std::shared_ptr<Quantity> Cardio::getAverageSpeed(
      const pugi::xml_document& cfg ) {
    std::vector<Run> runs ;
    Quantity tDis ;
    Quantity tTime ;
    getRuns(cfg, "/person/excercises/cardio/runs[@type='best']/run",
        runs, tTime, tDis) ;

    return std::shared_ptr<Quantity>(
        new Quantity( tDis.convert(MILES).magnitude()/
          tTime.convert(HOURS).magnitude(), MPH ) ) ;
  }

  void Cardio::getDistanceTraveled( const pugi::xml_document& cfg,
      std::list<std::pair<std::shared_ptr<mcommon::Value>,
      std::shared_ptr<mcommon::Value> > >& values ) {
    std::list<std::shared_ptr<Quantity> > qvalues ;
    Engine::getNodesAsQuantity( cfg,
        "/person/excercises/cardio/compute/distanceTraveledIn/time", qvalues ) ;

    Quantity avgSpeed(*getAverageSpeed(cfg)) ;

    for( auto time : qvalues ) {
    values.push_back( std::make_pair( std::shared_ptr<Quantity>(
        new Quantity( time->convert(HOURS).magnitude()*
          avgSpeed.convert(MPH).magnitude(), MILES ) ), time ) ) ;
    }
  }

  void Cardio::getTimeToTravel( const pugi::xml_document& cfg,
      std::list<std::pair<std::shared_ptr<mcommon::Value>,
      std::shared_ptr<mcommon::Value> > >& values ) {
    std::list<std::shared_ptr<Quantity> > qvalues ;
    Engine::getNodesAsQuantity( cfg,
        "/person/excercises/cardio/compute/timeToTravel/distance", qvalues ) ;

    Quantity avgSpeed(*getAverageSpeed(cfg)) ;

    for( auto dis : qvalues ) {
      values.push_back( std::make_pair(
            std::shared_ptr<Quantity>(
              new Quantity( dis->convert(MILES).magnitude( )/
                avgSpeed.convert(MPH).magnitude( ), HOURS ) ),  dis ) ) ;
    }
  }

  void Cardio::getAgeGrade( const pugi::xml_document& cfg,
      std::list<std::list<std::shared_ptr<mcommon::Value> > >& values ) {
    Quantity age = General::getAge( cfg )->convert(YEARS) ;
    Gender gender = General::getGender( cfg ) ;
    Quantity avgSpeed(*getAverageSpeed(cfg)) ;

    std::list<std::shared_ptr<Quantity> > distances ;
    Engine::getNodesAsQuantity( cfg,
        "/person/excercises/cardio/compute/ageGrade/distance", distances ) ;

    for( auto dis : distances ) {
      std::list<std::shared_ptr<Value> > avalues ;

      std::shared_ptr<Quantity> time(
          new Quantity( dis->convert(MILES).magnitude( )/
            avgSpeed.convert(MPH).magnitude( ), HOURS ) )  ;

      // TODO this need to be redone so it works with all cfg... EventType evt(et1MILES);
      float ag = std[gender][21] /
        factors[gender][0][(int)std::round(age.magnitude()-5)] /
        time->convert(SECONDS).magnitude() * 100.0f ;
      avalues.push_back( std::shared_ptr<Quantity>(
            new Quantity( ag, PERCENTAGE ) ) ) ;
      avalues.push_back( time ) ;
      avalues.push_back( dis ) ;
      values.push_back( avalues ) ;
    }
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

