/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include <vector>

#include "mcommon/Quantity.hpp"
#include "mcommon/Gender.hpp"

#include "mfit/Module.hpp"
#include "mfit/modules/Run.hpp"

namespace mfit {

  class Cardio : public Module {

    public:

      Cardio( ) ;

      virtual ~Cardio( ) = default ;

      Cardio( const Cardio& ) = delete ;

      Cardio& operator=( const Cardio& ) = delete ;

      virtual std::string getKey( ) ;

      static const std::string key ;

      static void getRuns( const pugi::xml_document& cfg,
          const std::string xpath, std::vector<Run>& runs,
          mcommon::Quantity& tTime, mcommon::Quantity& tDis ) ;

      static std::shared_ptr<mcommon::Quantity> getAverageSpeed(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getTreadmillDistance(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getTreadmillTime(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getTreadmillMETS(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getTreadmillCals(
          const pugi::xml_document& cfg ) ;

      static void getTimeToTravel( const pugi::xml_document& cfg,
          std::list<std::pair<std::shared_ptr<mcommon::Value>,
          std::shared_ptr<mcommon::Value> > >& values ) ;

      static void getDistanceTraveled( const pugi::xml_document& cfg,
          std::list<std::pair<std::shared_ptr<mcommon::Value>,
          std::shared_ptr<mcommon::Value> > >& values ) ;

      static void getAgeGrade( const pugi::xml_document& cfg,
          std::list<std::list<std::shared_ptr<mcommon::Value> > >& values ) ;

    private:

      static float getGradient( const pugi::xml_document& cfg ) ;

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

