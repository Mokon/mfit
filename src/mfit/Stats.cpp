/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <vector>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <pugixml.hpp>

#include "mcommon/Gender.hpp"
#include "mfit/Run.hpp"
#include "mfit/General.hpp"

using namespace mcommon ;

namespace mfit {

  static inline float selectA( pugi::xml_document& cfg, std::string xpath) {
    pugi::xpath_node xpnode = cfg.select_single_node(xpath.c_str()) ;
    return boost::lexical_cast<float>(xpnode.attribute().value());
  }

  static inline Quantity select( pugi::xml_document& cfg, std::string xpath,
      Unit unit ) {
    pugi::xpath_node xpnode = cfg.select_single_node(xpath.c_str()) ;
    float val = boost::lexical_cast<float>(xpnode.node().last_child().value());
    return Quantity(val, unit);
  }

  static inline Gender selectGender( pugi::xml_document& cfg ) {
    pugi::xpath_node xpnode = cfg.select_single_node("/person/gender") ;
    if( strcmp( xpnode.node().last_child().value(),  "Male" ) == 0 ) {
      return Male ;
    } else {
      return Female ;
    }
  }

  static inline void getRuns( pugi::xml_document& cfg, std::string xpath, 
      std::vector<Run>& runs ) {

    pugi::xpath_node_set xruns = cfg.select_nodes(xpath.c_str());

    for ( auto it : xruns ) {
      float time = boost::lexical_cast<float>(it.node().child("time").last_child().value());
      float speed = boost::lexical_cast<float>(it.node().child("speed").last_child().value());
      runs.push_back( Run(time, speed) );
    }
  }

  Stats::Stats( ) {
    pugi::xml_document cfg ;
    cfg.load_file("cfg/config.xml").description() ;

    static std::vector<Run> treadmillRuns ;
    getRuns(cfg, "/person/runs[@type='treadmill']/run", treadmillRuns) ;
    static std::vector<Run> bestRuns ;
    getRuns(cfg, "/person/runs[@type='best']/run", bestRuns) ;

    static Gender gender = selectGender( cfg ) ;
    static Quantity weight = select(cfg, "/person/weight", LBS) ;
    static Quantity height = select(cfg, "/person/height", INCHES) ;
    static Quantity neck = select(cfg, "/person/neck", INCHES) ;
    static Quantity waist = select(cfg, "/person/waist", INCHES) ;
    static Quantity hips = select(cfg, "/person/hips", INCHES) ;
    static Quantity age = select(cfg, "/person/age", YEARS) ;
    static float gradient = selectA(cfg, "/person/runs[@type='treadmill']/@gradient") ;

    static Quantity tDisB( 0, MILES ) ;
    static Quantity tTimeB( 0, HOURS ) ;

    for( auto e : bestRuns ) {
      tTimeB += e.time ;
      tDisB += e.distance ;
    }

    static Quantity tDisT( 0, MILES ) ;
    static Quantity tTimeT( 0, HOURS ) ;

    for( auto e : treadmillRuns ) {
      tTimeT += e.time ;
      tDisT += e.distance ;
    }

    /*
     (*this)[General::STAT_THIGH_LEFT ;
     (*this)[General::STAT_THIGH_RIGHT ;
     (*this)[General::STAT_BICEP_LEFT ;
     (*this)[General::STAT_BICEP_RIGHT ;
     (*this)[General::STAT_BELT_LINE ;
     (*this)[General::STAT_BLOOD_PRESURE_SYSTOLIC ;
     (*this)[General::STAT_BLOOD_PRESURE_DIASTOLIC ;
     (*this)[General::STAT_CHEST ;
     (*this)[General::STAT_CALF_LEFT ;
     (*this)[General::STAT_CALF_RIGHT ;
     (*this)[General::STAT_FOREARM_LEFT ;
     (*this)[General::STAT_FOREARM_RIGHT ;
     (*this)[General::STAT_WRIST ;
     (*this)[General::STAT_ELBOW_BREATH ;
     (*this)[General::STAT_BICEP_LEFT_FLEXED ;
     (*this)[General::STAT_BICEP_RIGHT_FLEXED ;
     */
    (*this)[Run::STAT_RUNS] = &bestRuns ;
    (*this)[Run::STAT_RUNS_TOTAL_TIME] = &tTimeB ;
    (*this)[Run::STAT_RUNS_TOTAL_DISTANCE] = &tDisB ;
    (*this)[Run::STAT_RUNS_TREAD] = &treadmillRuns ;
    (*this)[Run::STAT_RUNS_TOTAL_TIME_TREAD] = &tTimeT ;
    (*this)[Run::STAT_RUNS_TOTAL_DISTANCE_TREAD] = &tDisT ;
    (*this)[Run::STAT_GRADIENT] = &gradient ;
    (*this)[General::STAT_WEIGHT] = &weight ;
    (*this)[General::STAT_HEIGHT] = &height ;
    (*this)[General::STAT_NECK] = &neck ;
    (*this)[General::STAT_WAIST]= &waist ;
    (*this)[General::STAT_HIPS] = &hips ;
    (*this)[General::STAT_GENDER] = &gender ;
    (*this)[General::STAT_AGE] = &age ;
  }

}

