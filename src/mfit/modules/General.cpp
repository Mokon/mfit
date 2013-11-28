/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <cmath>

#include "mfit/modules/General.hpp"
#include "mfit/modules/Measurements.hpp"
#include "mfit/Engine.hpp"
#include "mfit/Statistic.hpp"

using namespace mcommon ;

namespace mfit {

  const std::string General::key = "mfit::General" ;

  General::General( ) {
    add( "Your age is", getAge ) ;
    add( "Your BMI is", getBMI ) ;
    add( "Your Broca Index ideal weight is", getIdealBodyWeightBrocaIndex ) ;
    add( "Your Devine Formula ideal weight is", getIdealBodyWeightDevine ) ;
    add( "Your Robinson Formula ideal weight is", getIdealBodyWeightRobinson );
    add( "Your Miller Formula ideal weight is", getIdealBodyWeightMiller ) ;
  }

  std::string General::getKey( ) {
    return key ;
  }

  std::shared_ptr<Quantity> General::avg( std::shared_ptr<Quantity> a,
      std::shared_ptr<Quantity> b ) {
    Quantity c = a->convert( b->unit() ) ;
    return std::shared_ptr<Quantity>(
        new Quantity(( c.magnitude( ) + b->magnitude( ) ) / 2, b->unit( ) ) ) ;
  }

  Gender General::getGender( const pugi::xml_document& cfg ) {
    return Engine::getNodeAs<Gender>( cfg, "/person/gender" ) ;
  }

  std::shared_ptr<Quantity> General::getAge( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, "/person/age" ) ;
  }

  void General::process( std::ostream& out,
      const pugi::xml_document& cfg ) const {
    print( out, "Your Gender is",  getGender( cfg ) ? "Female" : "Male" ) ;
  }

  std::shared_ptr<Quantity> General::getBMI( const pugi::xml_document& cfg ) {
    Quantity weight = Measurements::getWeight( cfg )->convert( LBS ) ;
    Quantity height = Measurements::getHeight( cfg )->convert( INCHES ) ;

    float height2 = height.magnitude()*height.magnitude() ;
    float bmi = weight.magnitude()/height2*703 ;

    return std::shared_ptr<Quantity>( new Quantity( bmi, NONE ) ) ;
  }

  std::shared_ptr<Quantity> General::getIdealBodyWeightBrocaIndex(
      const pugi::xml_document& cfg ) {
    Quantity height = Measurements::getHeight( cfg )->convert(CM) ;
    Quantity ret = Quantity( height.magnitude()-100, KG).convert(LBS)  ;
    return std::shared_ptr<Quantity>( new Quantity(ret) ) ;
  }

  std::shared_ptr<Quantity> General::getIdealBodyWeightDevine(
      const pugi::xml_document& cfg ) {
    Quantity height = Measurements::getHeight( cfg )->convert(INCHES) ;
    Gender gender = getGender( cfg ) ;

    Quantity ret ;
    switch ( gender ) {
      case Male:
        ret = Quantity(2.3*(height.magnitude()-60)+50, KG).convert(LBS)  ;
        break ;
      default:
        ret = Quantity(2.3*(height.magnitude()-60)+45.5, KG).convert(LBS) ;
        break ;
    }
    return std::shared_ptr<Quantity>( new Quantity(ret) ) ;
  }

  std::shared_ptr<Quantity> General::getIdealBodyWeightRobinson(
      const pugi::xml_document& cfg ) {
    Quantity height = Measurements::getHeight( cfg )->convert(INCHES) ;
    Gender gender = getGender( cfg ) ;

    Quantity ret ;
    switch ( gender ) {
      case Male:
        ret = Quantity(1.9*(height.magnitude()-60)+52, KG).convert(LBS) ;
        break ;
      default:
        ret = Quantity(1.7*(height.magnitude()-60)+49, KG).convert(LBS) ;
        break ;
    }
    return std::shared_ptr<Quantity>( new Quantity(ret) ) ;
  }

  std::shared_ptr<Quantity> General::getIdealBodyWeightMiller(
      const pugi::xml_document& cfg ) {
    Quantity height = Measurements::getHeight( cfg )->convert(INCHES) ;
    Gender gender = getGender( cfg ) ;

    Quantity ret ;
    switch ( gender ) {
      case Male:
        ret = Quantity(1.41*(height.magnitude()-60)+56.2, KG).convert(LBS) ;
        break ;
      default:
        ret = Quantity(1.36*(height.magnitude()-60)+53.1, KG).convert(LBS) ;
        break ;
    }
    return std::shared_ptr<Quantity>( new Quantity(ret) ) ;
  }

}

