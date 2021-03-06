/* Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <pugixml.hpp>

#include "mcommon/Quantity.hpp"

#include "mfit/Module.hpp"
#include "mfit/Statistic.hpp"
#include "mfit/modules/ValueString.hpp"

namespace mfit {

  class BodyFatPercentage : public Module {

    public:

      BodyFatPercentage( ) ;

      virtual ~BodyFatPercentage( ) = default ;

      BodyFatPercentage( const BodyFatPercentage& ) = delete ;

      BodyFatPercentage& operator=( const BodyFatPercentage& ) = delete ;

      virtual std::string getKey( ) ;

      static const std::string key ;

      static std::shared_ptr<ValueString> getBFPToClassification(
          Statistic::ValueGetter get, const pugi::xml_document& cfg ) ;

      void addBFP( std::string hdr, Statistic::ValueGetter get ) ;

      static Statistic::ValueGetter getBFPFunc( Statistic::ValueGetter get ) ;

      static std::shared_ptr<mcommon::Quantity> siriEquation(
          float bodyDensity ) ;

      static std::shared_ptr<mcommon::Quantity> getTicepsSkinfold(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getChestSkinfold(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getMidaxillarySkinfold(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getSubscapularSkinfold(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getSuprailiacSkinfold(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getAbdominalSkinfold(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getThighSkinfold(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getSuprailumSkinfold(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBFP3Site(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBFP7Site(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBFPHeritageBMI(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBFPConvertBailey(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBFPHodgdonBeckett(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBFPUSNavy(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBFPYMCA(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBFPYMCAModified(
          const pugi::xml_document& cfg ) ;

  } ;

}

