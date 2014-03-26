/* Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved */

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

      static std::shared_ptr<mcommon::Quantity> getTreadmillPace(
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

      static const float factors[mcommon::GENDER_MAX][23][98] ;
  
      static int getFactorIndex( mcommon::Gender g,
          mcommon::Quantity distance ) ;
      
      static int getStdIndex( mcommon::Quantity distance ) ;

  } ;

}

