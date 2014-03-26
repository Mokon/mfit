/* Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved */

#include <cmath>

#include "mcommon/Gender.hpp"

#include "mfit/modules/BodyFatPercentage.hpp"
#include "mfit/modules/General.hpp"
#include "mfit/modules/Measurements.hpp"
#include "mfit/Engine.hpp"

using namespace mcommon ;

namespace mfit {

  const std::string BodyFatPercentage::key = "mfit::BodyFatPercentage" ;

  std::string BodyFatPercentage::getKey( ) {
    return key ;
  }

  std::shared_ptr<ValueString> BodyFatPercentage::getBFPToClassification(
      Statistic::ValueGetter get, const pugi::xml_document& cfg ) {
    std::shared_ptr<Quantity> bfp
      = std::dynamic_pointer_cast<Quantity>( get( cfg ) ) ;

    std::string ret ;
    Gender gender = General::getGender( cfg ) ;
    switch ( gender ) {
      case Male:
        if( bfp->magnitude() < 2 ) {
          ret = "Deadly" ;
        } else if( bfp->magnitude() >= 2 && bfp->magnitude() < 6 ) {
          ret = "Essential Fat" ;
        } else if( bfp->magnitude() >= 6 && bfp->magnitude() < 14 ) {
          ret = "Athletic" ;
        } else if( bfp->magnitude() >= 14 && bfp->magnitude() < 18 ) {
          ret = "Fitness" ;
        } else if( bfp->magnitude() >= 18 && bfp->magnitude() < 25 ) {
          ret = "Average" ;
        } else {
          ret = "Obese" ;
        }
        break ;
      default:
        if( bfp->magnitude() < 10 ) {
          ret = "Deadly" ;
        } else if( bfp->magnitude() >= 10 && bfp->magnitude() < 14 ) {
          ret = "Essential Fat" ;
        } else if( bfp->magnitude() >= 14 && bfp->magnitude() < 21 ) {
          ret = "Athletic" ;
        } else if( bfp->magnitude() >= 21 && bfp->magnitude() < 25 ) {
          ret = "Fitness" ;
        } else if( bfp->magnitude() >= 25 && bfp->magnitude() < 32 ) {
          ret = "Average" ;
        } else {
          ret = "Obese" ;
        }
        break ;
    }

    return std::shared_ptr<ValueString>( new ValueString( ret ) ) ;
  }

  BodyFatPercentage::BodyFatPercentage( ) {
    addBFP( "Your 3 Site Skinfold Body Fat Percentage is", getBFP3Site ) ;
    addBFP( "Your 7 Site Skinfold Body Fat Percentage is", getBFP7Site ) ;
    addBFP( "Your Heritage BMI Formula Body Fat Percentage is", getBFPHeritageBMI ) ;
    addBFP( "Your Convert Baily Formula Body Fat Percentage is", getBFPConvertBailey ) ;
    addBFP( "Your Hodgone Becket Formula Body Fat Percentage is", getBFPHodgdonBeckett ) ;
    addBFP( "Your US Navy Formula Body Fat Percentage is", getBFPUSNavy ) ;
    addBFP( "Your YMCA Formula Body Fat Percentage is", getBFPYMCA ) ;
    addBFP( "Your YMCA Modified Formula Body Fat Percentage is", getBFPYMCAModified ) ;
    add( "Your tricep skinfold measurement is", getTicepsSkinfold ) ;
    add( "Your chest skinfold measurement is", getChestSkinfold ) ;
    add( "Your midaxillary skinfold measurement is", getMidaxillarySkinfold ) ;
    add( "Your subscapular skinfold measurement is", getSubscapularSkinfold ) ;
    add( "Your suprailiac skinfold measurement is", getSuprailiacSkinfold ) ;
    add( "Your abdominal skinfold measurement is", getAbdominalSkinfold ) ;
    add( "Your thigh skinfold measurement is", getThighSkinfold ) ;
    add( "Your suprailum skinfold measurement is", getSuprailumSkinfold ) ;
  }

  void BodyFatPercentage::addBFP( std::string hdr, Statistic::ValueGetter get ) {
    add( hdr, get ) ;
    add( "\twhich is categorized",  getBFPFunc( get ) ) ;
  }

  Statistic::ValueGetter BodyFatPercentage::getBFPFunc(
      Statistic::ValueGetter get ) {
    return [get]( const pugi::xml_document& cfg )
      -> std::shared_ptr<mcommon::Value> {
        return getBFPToClassification( get, cfg ) ;
      } ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getTicepsSkinfold(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/ticeps" ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getChestSkinfold(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/chest" ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getMidaxillarySkinfold(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/midaxillary" ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getSubscapularSkinfold(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/subscapular" ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getSuprailiacSkinfold(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/suprailiac" ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getAbdominalSkinfold(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/abdominal" ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getThighSkinfold(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/thigh" ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getSuprailumSkinfold(
      const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/suprailum" ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::siriEquation(
      float bodyDensity ) {
    return std::shared_ptr<Quantity>(
        new Quantity((495.0/bodyDensity)-450.0, PERCENTAGE ) ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getBFP3Site(
      const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    float age = General::getAge( cfg )->convert(YEARS).magnitude( ) ;
    float sum = 0 ;
    sum += getThighSkinfold( cfg )->magnitude( ) ;

    float bd ;
    switch ( gender ) {
      case Male:
        sum += getChestSkinfold( cfg )->magnitude( ) ;
        sum += getAbdominalSkinfold( cfg )->magnitude( ) ;
        bd = 1.10938 - 0.0008267*sum + 0.0000016*sum*sum - 0.0002574*age;
        break ;
      default:
        sum += getTicepsSkinfold( cfg )->magnitude( ) ;
        sum += getSuprailiacSkinfold( cfg )->magnitude( ) ;
        bd = 1.0994921 - 0.0009929*sum + 0.0000023*sum*sum - 0.0001392*age ;
        break ;
    }
    return siriEquation( bd ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getBFP7Site(
      const pugi::xml_document& cfg ) {
    float sum = 0 ;
    Gender gender = General::getGender( cfg ) ;
    float age = General::getAge( cfg )->convert(YEARS).magnitude( ) ;
    sum += getChestSkinfold( cfg )->magnitude( ) ;
    sum += getMidaxillarySkinfold( cfg )->magnitude( ) ;
    sum += getTicepsSkinfold( cfg )->magnitude( ) ;
    sum += getSubscapularSkinfold( cfg )->magnitude( ) ;
    sum += getAbdominalSkinfold( cfg )->magnitude( ) ;
    sum += getSuprailiacSkinfold( cfg )->magnitude( ) ;
    sum += getThighSkinfold( cfg )->magnitude( ) ;

    float bd ;
    switch ( gender ) {
      case Male:
        bd = 1.112 - 0.00043499*sum + 0.00000055*sum*sum - 0.00028826*age ;
      default:
        bd = 1.097 - 0.00046971*sum + 0.00000056*sum*sum - 0.00012828*age ;
    }
    return siriEquation( bd ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getBFPHeritageBMI(
      const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    float age = General::getAge( cfg )->convert(YEARS).magnitude( ) ;
    float height = Measurements::getHeight( cfg )->convert(INCHES).magnitude( );
    float weight = Measurements::getWeight( cfg )->convert(LBS).magnitude() ;

    float ret ;
    switch ( gender ) {
      case Male:
        ret = (977.17*weight/pow(height,2)) + 0.16*age - 19.34 ;
        break ;
      default:
        ret = (977.17*weight/pow(height,2)) + 0.16*age - 9 ;
        break ;
    }
    return std::shared_ptr<Quantity>( new Quantity( ret, PERCENTAGE ) ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getBFPConvertBailey(
      const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    float age = General::getAge( cfg )->convert(YEARS).magnitude( ) ;
    float hips = Measurements::getHips( cfg )->convert(INCHES).magnitude( ) ;
    float wrist = Measurements::getWrist( cfg )->convert(INCHES).magnitude( ) ;

    float ret ;
    switch ( gender ) {
      case Male:
        {
          float waist = Measurements::getWaist( cfg )->convert(INCHES).magnitude( ) ;
          float forearm = Measurements::getForearm( cfg )->convert(INCHES).magnitude( ) ;
          if( age <= 30 ) {
            ret = waist + 0.5*hips - 3*forearm - wrist ;
          } else {
            ret = waist + 0.5*hips - 2.7*forearm - wrist ;
          }
          break ;
        }
      default:
        {
          float thigh = Measurements::getThigh( cfg )->convert(INCHES).magnitude( ) ;
          float calf = Measurements::getCalf( cfg )->convert(INCHES).magnitude( ) ;
          if( age <= 30 ) {
            ret = hips + 0.8*thigh - 2*calf - wrist ;
          } else {
            ret = hips + thigh - 2*calf - wrist ;
          }
          break ;
        }
    }
    return std::shared_ptr<Quantity>( new Quantity( ret, PERCENTAGE ) ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getBFPHodgdonBeckett(
      const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    float height = Measurements::getHeight( cfg )->convert(CM).magnitude( ) ;
    float waist = Measurements::getWaist( cfg )->convert(CM).magnitude( ) ;
    float neck = Measurements::getNeck( cfg )->convert(CM).magnitude( ) ;

    float ret ;
    switch ( gender ) {
      case Male:
        ret = 495.0/(1.0324-0.19077*
            (log10(waist-neck))+0.15456*(log10(height)))-450.0 ;
        break ;
      default:
        float hip = Measurements::getHips( cfg )->convert(CM).magnitude( ) ;
        ret = 495.0/(1.29579-0.35004*
            (log10(waist+hip-neck))+0.22100*(log10(height)))-450 ;
        break ;
    }
    return std::shared_ptr<Quantity>( new Quantity( ret, PERCENTAGE ) ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getBFPUSNavy(
      const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    float height = Measurements::getHeight( cfg )->convert(INCHES).magnitude() ;
    float waist = Measurements::getWaist( cfg )->convert(INCHES).magnitude() ;
    float neck = Measurements::getNeck( cfg )->convert(INCHES).magnitude() ;

    float ret ;
    switch ( gender ) {
      case Male:
        ret = 86.010*log10(waist-neck)-70.041*log10(height) + 36.76;
        break ;
      default:
        float hip = Measurements::getHips( cfg )->convert(INCHES).magnitude( ) ;
        ret = 163.205*log10(waist+hip-neck)-97.684*log10(height)-78.387;
        break ;
    }
    return std::shared_ptr<Quantity>( new Quantity( ret, PERCENTAGE ) ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getBFPYMCA(
      const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    float weight = Measurements::getWeight( cfg )->convert(LBS).magnitude() ;
    float waist = Measurements::getWaist( cfg )->convert(INCHES).magnitude() ;

    float ret ;
    switch ( gender ) {
      case Male:
        ret = (-98.42+4.15*waist-0.082*weight)/weight*100.0 ;
        break ;
      default:
        ret = (-76.76+ 4.15*waist-0.082*weight)/weight*100.0 ;
        break ;
    }
    return std::shared_ptr<Quantity>( new Quantity( ret, PERCENTAGE ) ) ;
  }

  std::shared_ptr<Quantity> BodyFatPercentage::getBFPYMCAModified(
      const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    float weight = Measurements::getWeight( cfg )->convert(LBS).magnitude() ;
    float waist = Measurements::getWaist( cfg )->convert(INCHES).magnitude() ;

    float ret ;
    switch ( gender ) {
      case Male:
        ret = (-94.42+4.15*waist-0.082*weight)/weight*100.0 ;
        break ;
      default:
        {
          float hips = Measurements::getHips( cfg )->convert(INCHES).magnitude( ) ;
          float wrist = Measurements::getWrist( cfg )->convert(INCHES).magnitude( ) ;
          float forearm = Measurements::getForearm( cfg )->convert(INCHES).magnitude( ) ;
          ret = ( 0.268 * weight - 0.318 * wrist + 0.157 * waist + 0.245 * hips
              - 0.434 * forearm - 8.987 ) / weight * 100.0 ;
          break ;
        }
    }
    return std::shared_ptr<Quantity>( new Quantity( ret, PERCENTAGE ) ) ;
  }
}

