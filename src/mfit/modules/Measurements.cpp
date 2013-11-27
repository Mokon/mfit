/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <cmath>
#include <memory>

#include "mfit/modules/Measurements.hpp"
#include "mfit/modules/General.hpp"
#include "mfit/Engine.hpp"
#include "mfit/Statistic.hpp"

using namespace mcommon ;

namespace mfit {

  const std::string Measurements::key = "mfit::Measurements" ;

  Measurements::Measurements( ) {
    add( "Your height is", getHeight ) ;
    add( "Your weight is", getWeight ) ;
    add( "Your neck is", getNeck ) ;
    add( "Your waist is",  getWaist ) ;
    add( "Your hips are", getHips ) ;
    add( "Your biceps are", getBicep ) ;
    add( "Your right bicep is", getBicepRight ) ;
    add( "Your left bicep is", getBicepLeft ) ;
    add( "Your biceps flexed are", getBicepFlexed ) ;
    add( "Your right bicep flexed is", getBicepFlexedRight ) ;
    add( "Your left bicep flexed is", getBicepFlexedLeft ) ;
    add( "Your thighs are", getThigh ) ;
    add( "Your right thigh is", getThighRight ) ;
    add( "Your left thigh is", getThighLeft ) ;
    add( "Your forearms are", getForearm ) ;
    add( "Your right forearm is", getForearmRight ) ;
    add( "Your left forearm is", getForearmLeft ) ;
    add( "Your wrists are", getWrist ) ;
    add( "Your right wrist is", getWristRight ) ;
    add( "Your left wrist is", getWristLeft ) ;
    add( "Your calfs are", getCalf ) ;
    add( "Your right calf is", getCalfRight ) ;
    add( "Your left calf is", getCalfLeft ) ;
  }

  std::string Measurements::getKey( ) {
    return key ;
  }

  std::shared_ptr<Quantity> Measurements::getWeight(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg,
        "/person/measurements/weight", LBS ) ;
  }

  std::shared_ptr<Quantity> Measurements::getHeight(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg,
        "/person/measurements/height", INCHES ) ;
  }

  std::shared_ptr<Quantity> Measurements::getNeck(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg,
        "/person/measurements/neck", INCHES ) ;
  }

  std::shared_ptr<Quantity> Measurements::getWaist(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg,
        "/person/measurements/waist", INCHES ) ;
  }

  std::shared_ptr<Quantity> Measurements::getHips(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg,
        "/person/measurements/hips", INCHES ) ;
  }

  std::shared_ptr<Quantity> Measurements::getThigh(
      const pugi::xml_document& cfg ) {
    return General::avg( getThighLeft( cfg ), getThighRight( cfg ) ) ;
  }

  std::shared_ptr<Quantity> Measurements::getThighLeft(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg, 
        "/person/measurements/thigh[@side='left']", INCHES ) ;
  }

  std::shared_ptr<Quantity> Measurements::getThighRight(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg, 
        "/person/measurements/thigh[@side='right']", INCHES ) ;
  }

  std::shared_ptr<Quantity> Measurements::getForearm(
      const pugi::xml_document& cfg ) {
    return General::avg( getForearmLeft( cfg ), getForearmRight( cfg ) ) ;
  }

  std::shared_ptr<Quantity> Measurements::getForearmLeft(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg, 
        "/person/measurements/forearm[@side='left']", INCHES ) ;
  }

  std::shared_ptr<Quantity> Measurements::getForearmRight(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg, 
        "/person/measurements/forearm[@side='right']", INCHES ) ;
  }

  std::shared_ptr<Quantity> Measurements::getWrist(
      const pugi::xml_document& cfg ) {
    return General::avg( getWristLeft( cfg ), getWristRight( cfg ) ) ;
  }

  std::shared_ptr<Quantity> Measurements::getWristLeft(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg, 
        "/person/measurements/wrist[@side='left']", INCHES ) ;
  }

  std::shared_ptr<Quantity> Measurements::getWristRight(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg, 
        "/person/measurements/wrist[@side='right']", INCHES ) ;
  }

  std::shared_ptr<Quantity> Measurements::getCalf(
      const pugi::xml_document& cfg ) {
    return General::avg( getCalfLeft( cfg ), getCalfRight( cfg ) ) ;
  }

  std::shared_ptr<Quantity> Measurements::getCalfLeft(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg, 
        "/person/measurements/calf[@side='left']", INCHES ) ;
  }

  std::shared_ptr<Quantity> Measurements::getCalfRight(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg, 
        "/person/measurements/calf[@side='right']", INCHES ) ;
  }
  
  std::shared_ptr<Quantity> Measurements::getBicep(
      const pugi::xml_document& cfg ) {
    return General::avg( getBicepLeft( cfg ), getBicepRight( cfg ) ) ;
  }

  std::shared_ptr<Quantity> Measurements::getBicepRight(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg,
        "/person/measurements/biceps[@type!='flexed' and @side='right']", INCHES ) ;
  }

  std::shared_ptr<Quantity> Measurements::getBicepLeft(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg,
        "/person/measurements/biceps[@type!='flexed' and @side='left']", INCHES ) ;
  }
  
  std::shared_ptr<Quantity> Measurements::getBicepFlexed(
      const pugi::xml_document& cfg ) {
    return General::avg( getBicepFlexedLeft( cfg ), getBicepFlexedRight( cfg ) ) ;
  }

  std::shared_ptr<Quantity> Measurements::getBicepFlexedRight(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg,
        "/person/measurements/biceps[@type='flexed' and @side='right']", INCHES ) ;
  }

  std::shared_ptr<Quantity> Measurements::getBicepFlexedLeft(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantityPtr( cfg,
        "/person/measurements/biceps[@type='flexed' and @side='left']", INCHES ) ;
  }

}

