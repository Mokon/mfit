/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <cmath>

#include "mcommon/Gender.hpp"

#include "mfit/modules/GreekIdeal.hpp"
#include "mfit/modules/Measurements.hpp"
#include "mfit/Engine.hpp"

using namespace mcommon ;

namespace mfit {

  const std::string GreekIdeal::key = "mfit::GreekIdeal" ;

  GreekIdeal::GreekIdeal( ) {
    add( "According to the Greeks your ideal chest would be", getGreekIdealChest ) ;
    add( "According to the Greeks your ideal waist would be", getGreekIdealWaist ) ;
    add( "According to the Greeks your ideal hips would be", getGreekIdealHip ) ;
    add( "According to the Greeks your ideal biceps would be", getGreekIdealBicep ) ;
    add( "According to the Greeks your ideal forearms would be", getGreekIdealForearm ) ;
    add( "According to the Greeks your ideal thighs would be", getGreekIdealThigh ) ;
    add( "According to the Greeks your ideal calves would be", getGreekIdealCalf ) ;
    add( "According to the Greeks your ideal neck would be", getGreekIdealNeck ) ;
  }

  std::string GreekIdeal::getKey( ) {
    return key ;
  }

  std::shared_ptr<Quantity> GreekIdeal::getGreekIdealChest(
      const pugi::xml_document& cfg ) {
      return std::shared_ptr<Quantity>(
          new Quantity( (*Measurements::getWrist( cfg ))*6.5 ) ) ;
  }

  std::shared_ptr<Quantity> GreekIdeal::getGreekIdealWaist(
      const pugi::xml_document& cfg ) {
      return std::shared_ptr<Quantity>(
          new Quantity( (*Measurements::getWrist( cfg ))*6.5*0.7 ) ) ;
  }

  std::shared_ptr<Quantity> GreekIdeal::getGreekIdealHip(
      const pugi::xml_document& cfg ) {
      return std::shared_ptr<Quantity>(
          new Quantity( (*Measurements::getWrist( cfg ))*6.5*0.85 ) ) ;
  }

  std::shared_ptr<Quantity> GreekIdeal::getGreekIdealBicep(
      const pugi::xml_document& cfg ) {
      return std::shared_ptr<Quantity>(
          new Quantity( (*Measurements::getWrist( cfg ))*6.5*0.36 ) ) ;
  }

  std::shared_ptr<Quantity> GreekIdeal::getGreekIdealForearm(
      const pugi::xml_document& cfg ) {
      return std::shared_ptr<Quantity>(
          new Quantity( (*Measurements::getWrist( cfg ))*6.5*0.29 ) ) ;
  }

  std::shared_ptr<Quantity> GreekIdeal::getGreekIdealThigh(
      const pugi::xml_document& cfg ) {
      return std::shared_ptr<Quantity>(
          new Quantity( (*Measurements::getWrist( cfg ))*6.5*0.53 ) ) ;
  }

  std::shared_ptr<Quantity> GreekIdeal::getGreekIdealCalf(
      const pugi::xml_document& cfg ) {
      return std::shared_ptr<Quantity>(
          new Quantity( (*Measurements::getWrist( cfg ))*6.5*0.34 ) ) ;
  }

  std::shared_ptr<Quantity> GreekIdeal::getGreekIdealNeck(
      const pugi::xml_document& cfg ) {
      return std::shared_ptr<Quantity>(
          new Quantity( (*Measurements::getWrist( cfg ))*6.5*0.37 ) ) ;
  }

}

