/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"

#include "mfit/Module.hpp"

namespace mfit {

  class Measurements : public Module {

    public:

      Measurements( ) ;

      virtual ~Measurements( ) = default ;

      Measurements( const Measurements& ) = delete ;

      Measurements& operator=( const Measurements& ) = delete ;

      virtual std::string getKey( ) ;

      static const std::string key ;

      static std::shared_ptr<mcommon::Quantity> getWeight(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getHeight(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getNeck(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getChest(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getWaist(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getHips(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getThigh(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getThighLeft(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getThighRight(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getForearm(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getForearmLeft(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getForearmRight(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getWrist(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getWristLeft(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getWristRight(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getCalf(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getCalfLeft(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getCalfRight(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBicep(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBicepRight(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBicepLeft(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBicepFlexed(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBicepFlexedRight(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBicepFlexedLeft(
          const pugi::xml_document& cfg ) ;

  } ;

}

