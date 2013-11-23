/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <cmath>

#include "mcommon/Gender.hpp"

#include "mfit/modules/General.hpp"
#include "mfit/Engine.hpp"

using namespace mcommon ;

namespace mfit {

  const std::string General::key = "mfit::General" ;

  std::string General::getKey( ) {
    return key ;
  }

  Quantity General::avg( Quantity a, Quantity b ) {
    Quantity c = a.convert( b.unit() ) ;
    return Quantity(( c.magnitude( ) + b.magnitude( ) ) / 2, b.unit( ) ) ; 
  }

  Gender General::getGender( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsGender( cfg, "/person/gender" ) ;
  }

  Quantity General::getWeight( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, "/person/measurements/weight", LBS ) ;
  }

  Quantity General::getHeight( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, "/person/measurements/height", INCHES ) ;
  }

  Quantity General::getNeck( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, "/person/measurements/neck", INCHES ) ;
  }

  Quantity General::getWaist( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, "/person/measurements/waist", INCHES ) ;
  }

  Quantity General::getHips( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, "/person/measurements/hips", INCHES ) ;
  }

  Quantity General::getThigh( const pugi::xml_document& cfg ) {
    return avg( getThighLeft( cfg ), getThighRight( cfg ) ) ;
  }

  Quantity General::getThighLeft( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, 
        "/person/measurements/thigh[@side='left']", INCHES ) ;
  }

  Quantity General::getThighRight( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, 
        "/person/measurements/thigh[@side='right']", INCHES ) ;
  }

  Quantity General::getForearm( const pugi::xml_document& cfg ) {
    return avg( getForearmLeft( cfg ), getForearmRight( cfg ) ) ;
  }

  Quantity General::getForearmLeft( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, 
        "/person/measurements/forearm[@side='left']", INCHES ) ;
  }

  Quantity General::getForearmRight( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, 
        "/person/measurements/forearm[@side='right']", INCHES ) ;
  }

  Quantity General::getWrist( const pugi::xml_document& cfg ) {
    return avg( getWristLeft( cfg ), getWristRight( cfg ) ) ;
  }

  Quantity General::getWristLeft( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, 
        "/person/measurements/wrist[@side='left']", INCHES ) ;
  }

  Quantity General::getWristRight( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, 
        "/person/measurements/wrist[@side='right']", INCHES ) ;
  }

  Quantity General::getCalf( const pugi::xml_document& cfg ) {
    return avg( getCalfLeft( cfg ), getCalfRight( cfg ) ) ;
  }

  Quantity General::getCalfLeft( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, 
        "/person/measurements/calf[@side='left']", INCHES ) ;
  }

  Quantity General::getCalfRight( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, 
        "/person/measurements/calf[@side='right']", INCHES ) ;
  }

  Quantity General::getBicepFlexedRight( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/biceps[@type='flexed' and @side='right']", INCHES ) ;
  }

  Quantity General::getBicepFlexedLeft( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/biceps[@type='flexed' and @side='left']", INCHES ) ;
  }

  Quantity General::getAge( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg, "/person/age", YEARS ) ;
  }

  void General::process( std::ostream& out,
      const pugi::xml_document& cfg ) const {
    out << "General Stats" << std::endl ;

    Quantity weight = getWeight( cfg ) ;
    Quantity height = getHeight( cfg ) ;
    Quantity neck = getNeck( cfg ) ;
    Quantity waist = getWaist( cfg ) ;
    Quantity hips = getHips( cfg ) ;
    Quantity bicepFlexedRight = getBicepFlexedRight( cfg ) ;
    Quantity bicepFlexedLeft = getBicepFlexedLeft( cfg ) ;

    Quantity bmrHarrisBenedict(General::bmrHarrisBenedict( cfg ) ) ;
    Quantity bmrRozaShizgal(General::bmrRozaShizgal( cfg ) ) ;

    float bmi(General::bmi( cfg ) ) ;

    out << "\tYour Weight is " << weight << std::endl
      << "\tYour Height is " << height << std::endl
      << "\tYour Neck is " << neck << std::endl
      << "\tYour Waist is " << waist << std::endl
      << "\tYour Hips are " << hips << std::endl
      << "\tYour Bicep Right Flexed is " << bicepFlexedRight << std::endl
      << "\tYour Bicep Left Flexed is " << bicepFlexedLeft << std::endl
      << "\tYour BMI is " << bmi << std::endl
      << "\tYour Harris Benedict BMR is " << bmrHarrisBenedict << std::endl
      << "\tYour Roza Shizgal BMR is " << bmrRozaShizgal << std::endl ;

    greekIdeal(out, cfg) ;
    
    out << "\tYou ideal weight is:" << std::endl << "\t\t"
        << idealBodyWeightBrocaIndex( cfg )
        << " according to the Broca Index." << std::endl << "\t\t" 
        << idealBodyWeightDevine( cfg )
        << " according to the Devine Formula." << std::endl << "\t\t" 
        << idealBodyWeightRobinson( cfg )
        << " according to the Robinson Formula." << std::endl << "\t\t" 
        << idealBodyWeightMiller( cfg )
        << " according to the Miller Formula." << std::endl ;

  }

  Quantity General::bmrRozaShizgal( const pugi::xml_document& cfg ) {
    Quantity weight = getWeight( cfg ).convert(KG) ;
    Quantity height = getHeight( cfg ).convert(CM) ;
    Quantity age = getAge( cfg ).convert(YEARS) ;
    Gender gender = getGender( cfg ) ;

    float cals ;
    switch ( gender ) {
      case Male:
        cals = (weight.magnitude()*13.397)+(height.magnitude()*4.799)
          - (age.magnitude()*5.677) + 88.362;
        break ;
      default:
        cals = (weight.magnitude()*9.247) + (height.magnitude()*4.799)
          - (age.magnitude()*4.330) + 447.593;
        break ;
    }

    return Quantity( cals, CALORIES) ;
  }

  Quantity General::bmrHarrisBenedict( const pugi::xml_document& cfg ) {
    Quantity weight = getWeight( cfg ).convert(KG) ;
    Quantity height = getHeight( cfg ).convert(CM) ;
    Quantity age = getAge( cfg ).convert(YEARS) ;
    Gender gender = getGender( cfg ) ;

    float cals ;
    switch ( gender ) {
      case Male:
        cals = (weight.magnitude()*13.7516)+(height.magnitude()*5.0033)
          - (age.magnitude()*6.755) + 66.4730;
        break ;
      default:
        cals = (weight.magnitude()*9.5634) + (height.magnitude()*1.8496)
          - (age.magnitude()*4.6756) + 655.0955;
        break ;
    }

    return Quantity( cals, CALORIES) ;
  }

  float General::bmi( const pugi::xml_document& cfg ) {
    Quantity weight = getWeight( cfg ).convert( LBS ) ;
    Quantity height = getHeight( cfg ).convert( INCHES ) ;

    float height2 = height.magnitude()*height.magnitude() ;
    float bmi = weight.magnitude()/height2*703 ;

    return bmi ;
  }

  Quantity General::metsToCalories( Quantity mets, Quantity time,
      const pugi::xml_document& cfg ) {
    Quantity weight = getWeight( cfg ).convert(KG) ;
    return Quantity( mets.magnitude()*weight.magnitude()*
        time.convert(SECONDS).magnitude(), CALORIES) ;
  }

  Quantity General::idealBodyWeightBrocaIndex( const pugi::xml_document& cfg ) {
    Quantity height = getHeight( cfg ).convert(CM) ;
    return Quantity( height.magnitude()-100, KG).convert(LBS) ;
  }

  Quantity General::idealBodyWeightDevine( const pugi::xml_document& cfg ) {
    Quantity height = getHeight( cfg ).convert(INCHES) ;

    Gender gender = getGender( cfg ) ;

    switch ( gender ) {
      case Male:
        return Quantity(2.3*(height.magnitude()-60)+50, KG).convert(LBS) ;
      default:
        return Quantity(2.3*(height.magnitude()-60)+45.5, KG).convert(LBS) ;
    }
  }

  Quantity General::idealBodyWeightRobinson( const pugi::xml_document& cfg ) {
    Quantity height = getHeight( cfg ).convert(INCHES) ;

    Gender gender = getGender( cfg ) ;

    switch ( gender ) {
      case Male:
        return Quantity(1.9*(height.magnitude()-60)+52, KG).convert(LBS) ;
      default:
        return Quantity(1.7*(height.magnitude()-60)+49, KG).convert(LBS) ;
    }
  }

  Quantity General::idealBodyWeightMiller( const pugi::xml_document& cfg ) {
    Quantity height = getHeight( cfg ).convert(INCHES) ;

    Gender gender = getGender( cfg ) ;

    switch ( gender ) {
      case Male:
        return Quantity(1.41*(height.magnitude()-60)+56.2, KG).convert(LBS) ;
      default:
        return Quantity(1.36*(height.magnitude()-60)+53.1, KG).convert(LBS) ;
    }
  }

  void General::greekIdeal( std::ostream& out, const pugi::xml_document& cfg ) {
    Quantity wrist = getWrist( cfg ) ;

    Quantity idealchest =  wrist * 6.5 ;
    Quantity idealwaist =  idealchest * 0.7 ;
    Quantity idealhip =  idealchest * 0.85 ;
    Quantity idealbicep =  idealchest * 0.36 ;
    Quantity idealforearm =  idealchest * 0.29 ;
    Quantity idealthigh =  idealchest * 0.53 ;
    Quantity idealcalve =  idealchest * 0.34 ;
    Quantity idealneck =  idealchest * 0.37 ;

    out << "\tAccording to the Greeks this would be your ideal measurements:" << std::endl 
      << "\t\tIdeal Chest " << idealchest << std::endl
      << "\t\tIdeal Waist " << idealwaist << std::endl
      << "\t\tIdeal Hip " << idealhip << std::endl
      << "\t\tIdeal Bicep " << idealbicep << std::endl
      << "\t\tIdeal Forearm " << idealforearm << std::endl
      << "\t\tIdeal Thigh " << idealthigh << std::endl
      << "\t\tIdeal Calve " << idealcalve << std::endl
      << "\t\tIdeal Neck " << idealneck << std::endl ;
  }

}

