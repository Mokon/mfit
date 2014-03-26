/* Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"
#include "mcommon/Gender.hpp"

#include "mfit/Module.hpp"

namespace mfit {

  class GreekIdeal : public Module {

    public:

      GreekIdeal( ) ;

      virtual ~GreekIdeal( ) = default ;

      GreekIdeal( const GreekIdeal& ) = delete ;

      GreekIdeal& operator=( const GreekIdeal& ) = delete ;

      virtual std::string getKey( ) ;

      static const std::string key ;

      static mcommon::Gender getGender( const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getGreekIdealChest(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getGreekIdealWaist(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getGreekIdealHip(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getGreekIdealBicep(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getGreekIdealForearm(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getGreekIdealThigh(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getGreekIdealCalf(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getGreekIdealNeck(
          const pugi::xml_document& cfg ) ;

  } ;

}

