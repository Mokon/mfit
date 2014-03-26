/* Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"

#include "mfit/Module.hpp"

namespace mfit {

  enum ActivityLevel {
    Sedentary,
    LightlyActive,
    ModeratelyActive,
    VeryActive,
    ExtraActive,
    ACTIVITY_LEVEL_MAX
  } ;

  class Calories : public Module {

    public:

      Calories( ) ;

      virtual ~Calories( ) = default ;

      Calories( const Calories& ) = delete ;

      Calories& operator=( const Calories& ) = delete ;

      virtual std::string getKey( ) ;

      static const std::string key ;

      void addBMR( std::string hdr, Statistic::ValueGetter get ) ;

      static std::shared_ptr<mcommon::Quantity> metsToCalories(
          const std::shared_ptr<mcommon::Quantity> mets,
          const std::shared_ptr<mcommon::Quantity> time,
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> weightCaloriesBurnt(
          const pugi::xml_document& cfg ) ; 

      static std::shared_ptr<mcommon::Quantity> getBMRKatchMcCardie(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBMRHarrisBenedict(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBMRMifflinStJeor(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBMRRozaShizgal(
          const pugi::xml_document& cfg ) ;

      static Statistic::ValueGetter getModelFunc( Statistic::ValueGetter get,
          ActivityLevel model ) ;

      static std::shared_ptr<mcommon::Quantity> getModel(
          Statistic::ValueGetter get, const pugi::xml_document& cfg,
          ActivityLevel model ) ;

    private:

      static const float bmrMultipliers[ACTIVITY_LEVEL_MAX] ;

  } ;

}

