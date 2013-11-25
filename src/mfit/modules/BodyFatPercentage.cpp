/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

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

  void BodyFatPercentage::process( std::ostream& out,
      const pugi::xml_document& cfg ) const {
    out << "Body Fat Percentage Stats" << std::endl ;

    float bfp3Site(BodyFatPercentage::bfp3Site( cfg ) ) ;
    float bfp7Site(BodyFatPercentage::bfp7Site( cfg ) ) ;
    float bfpHeritageBMI(BodyFatPercentage::bfpHeritageBMI( cfg ) ) ;
    float bfpConvertBailey(BodyFatPercentage::bfpConvertBailey( cfg ) ) ;
    float bfpHodgdonBeckett(BodyFatPercentage::bfpHodgdonBeckett( cfg ) ) ;
    float bfpUSNavy(BodyFatPercentage::bfpUSNavy( cfg ) ) ;
    float bfpUSMarines(BodyFatPercentage::bfpUSMarines( cfg ) ) ;
    float bfpYMCA(BodyFatPercentage::bfpYMCA( cfg ) ) ;
    float bfpYMCAModified(BodyFatPercentage::bfpYMCAModified( cfg ) ) ;

    out
      << "\tYour 3 Site Skinfold Body Fat Percentage is "
      << bfp3Site
      << "% (" << bfpToClassification(bfp3Site, cfg) << ")." << std::endl
      << "\tYour 7 Site Skinfold Body Fat Percentage is "
      << bfp7Site
      << "% (" << bfpToClassification(bfp7Site, cfg) << ")." << std::endl
      << "\tYour Heritage BMI Formula Body Fat Percentage is "
      << bfpHeritageBMI
      << "% (" << bfpToClassification(bfpHeritageBMI, cfg) << ")." << std::endl
      << "\tYour Convert Baily Formula Body Fat Percentage is "
      << bfpConvertBailey
      << "% (" << bfpToClassification(bfpConvertBailey, cfg) << ")." << std::endl
      << "\tYour Hodgone Becket Formula Body Fat Percentage is "
      << bfpHodgdonBeckett
      << "% (" << bfpToClassification(bfpHodgdonBeckett, cfg) << ")." << std::endl
      << "\tYour US Navy Formula Body Fat Percentage is "
      << bfpUSNavy
      << "% (" << bfpToClassification(bfpUSNavy, cfg) << ")." << std::endl
      << "\tYour US Marines Formula Body Fat Percentage is "
      << bfpUSMarines
      << "% (" << bfpToClassification(bfpUSMarines, cfg) << ")." << std::endl
      << "\tYour YMCA Formula Body Fat Percentage is "
      << bfpYMCA 
      << "% (" << bfpToClassification(bfpYMCA, cfg) << ")." << std::endl 
      << "\tYour YMCA Modified Formula Body Fat Percentage is "
      << bfpYMCAModified 
      << "% (" << bfpToClassification(bfpYMCAModified, cfg) << ")." << std::endl ;
  }

  Quantity BodyFatPercentage::getTicepsSkinfold( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/ticeps", INCHES ) ;
  }

  Quantity BodyFatPercentage::getChestSkinfold( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/chest", INCHES ) ;
  }

  Quantity BodyFatPercentage::getMidaxillarySkinfold( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/midaxillary", INCHES ) ;
  }

  Quantity BodyFatPercentage::getSubscapularSkinfold( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/subscapular", INCHES ) ;
  }

  Quantity BodyFatPercentage::getSuprailiacSkinfold( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/suprailiac", INCHES ) ;
  }

  Quantity BodyFatPercentage::getAbdominalSkinfold( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/abdominal", INCHES ) ;
  }

  Quantity BodyFatPercentage::getThighSkinfold( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/thigh", INCHES ) ;
  }

  Quantity BodyFatPercentage::getSuprailumSkinfold( const pugi::xml_document& cfg ) {
    return Engine::getNodeAsQuantity( cfg,
        "/person/measurements/skinfolds/suprailum", INCHES ) ;
  }

  float siriEquation( float bodyDensity ) {
    return (495.0/bodyDensity)-450.0 ;
  }

  float BodyFatPercentage::bfp3Site( const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    float age = General::getAge( cfg ).convert(YEARS).magnitude( ) ;
    float sum = 0 ;
    sum += getThighSkinfold( cfg ).magnitude( ) ;

    float bd ;
    switch ( gender ) {
      case Male:
        sum += getChestSkinfold( cfg ).magnitude( ) ;
        sum += getAbdominalSkinfold( cfg ).magnitude( ) ;
        bd = 1.10938 - 0.0008267*sum + 0.0000016*sum*sum - 0.0002574*age;
        break ;
      default:
        sum += getTicepsSkinfold( cfg ).magnitude( ) ;
        sum += getSuprailiacSkinfold( cfg ).magnitude( ) ;
        bd = 1.0994921 - 0.0009929*sum + 0.0000023*sum*sum - 0.0001392*age ;
        break ;
    }
    return siriEquation( bd ) ;
  }

  float BodyFatPercentage::bfp7Site( const pugi::xml_document& cfg ) {
    float sum = 0 ;
    Gender gender = General::getGender( cfg ) ;
    float age = General::getAge( cfg ).convert(YEARS).magnitude( ) ;
    sum += getChestSkinfold( cfg ).magnitude( ) ;
    sum += getMidaxillarySkinfold( cfg ).magnitude( ) ;
    sum += getTicepsSkinfold( cfg ).magnitude( ) ;
    sum += getSubscapularSkinfold( cfg ).magnitude( ) ;
    sum += getAbdominalSkinfold( cfg ).magnitude( ) ;
    sum += getSuprailiacSkinfold( cfg ).magnitude( ) ;
    sum += getThighSkinfold( cfg ).magnitude( ) ;
    //sum += getSuprailumSkinfold( cfg ).magnitude( ) ;

    float bd ;
    switch ( gender ) {
      case Male:
        bd = 1.112 - 0.00043499*sum + 0.00000055*sum*sum - 0.00028826*age ;
      default:
        bd = 1.097 - 0.00046971*sum + 0.00000056*sum*sum - 0.00012828*age ;
    }
    return siriEquation( bd ) ;
  }

  std::string BodyFatPercentage::bfpToClassification( const float bfp,
      const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    switch ( gender ) {
      case Male:
        if( bfp < 2 ) {
          return "Deadly" ;
        } else if( bfp >= 2 && bfp < 6 ) {
          return "Essential Fat" ;
        } else if( bfp >= 6 && bfp < 14 ) {
          return "Athletic" ;
        } else if( bfp >= 14 && bfp < 18 ) {
          return "Fitness" ;
        } else if( bfp >= 18 && bfp < 25 ) {
          return "Average" ;
        } else {
          return "Obese" ;
        }
      default:
        if( bfp < 10 ) {
          return "Deadly" ;
        } else if( bfp >= 10 && bfp < 14 ) {
          return "Essential Fat" ;
        } else if( bfp >= 14 && bfp < 21 ) {
          return "Athletic" ;
        } else if( bfp >= 21 && bfp < 25 ) {
          return "Fitness" ;
        } else if( bfp >= 25 && bfp < 32 ) {
          return "Average" ;
        } else {
          return "Obese" ;
        }
    }
  }

  float BodyFatPercentage::bfpHeritageBMI( const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    float age = General::getAge( cfg ).convert(YEARS).magnitude( ) ;
    float height = Measurements::getHeight( cfg )->convert(INCHES).magnitude( );
    float weight = Measurements::getWeight( cfg )->convert(LBS).magnitude() ;

    switch ( gender ) {
      case Male: 
        return (977.17*weight/pow(height,2)) + 0.16*age - 19.34 ;
      default: 
        return (977.17*weight/pow(height,2)) + 0.16*age - 9 ;
    }
  }

  float BodyFatPercentage::bfpConvertBailey( const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    float age = General::getAge( cfg ).convert(YEARS).magnitude( ) ;
    float hips = Measurements::getHips( cfg )->convert(INCHES).magnitude( ) ;
    float wrist = Measurements::getWrist( cfg )->convert(INCHES).magnitude( ) ;

    switch ( gender ) {
      case Male: {
                   float waist = Measurements::getWaist( cfg )->convert(INCHES).magnitude( ) ;
                   float forearm = Measurements::getForearm( cfg )->convert(INCHES).magnitude( ) ;
                   if( age <= 30 ) {
                     return waist + 0.5*hips - 3*forearm - wrist ;
                   } else {
                     return waist + 0.5*hips - 2.7*forearm - wrist ;
                   }
                 }
      default: {
                 float thigh = Measurements::getThigh( cfg )->convert(INCHES).magnitude( ) ;
                 float calf = Measurements::getCalf( cfg )->convert(INCHES).magnitude( ) ;
                 if( age <= 30 ) {
                   return hips + 0.8*thigh - 2*calf - wrist ;
                 } else {
                   return hips + thigh - 2*calf - wrist ;
                 }
               }
    }
  }

  float BodyFatPercentage::bfpHodgdonBeckett( const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    float height = Measurements::getHeight( cfg )->convert(INCHES).magnitude( ) * 2.54 ;
    float waist = Measurements::getWaist( cfg )->convert(INCHES).magnitude( ) * 2.54 ;
    float neck = Measurements::getNeck( cfg )->convert(INCHES).magnitude( ) * 2.54 ;

    switch ( gender ) {
      case Male:
        return 495.0/(1.0324-0.19077*
            (log10(waist-neck))+0.15456*(log10(height)))-450.0 ;
      default:
        float hip = Measurements::getHips( cfg )->convert(INCHES).magnitude( ) * 2.54 ;
        return 495.0/(1.29579-0.35004*
            (log10(waist+hip-neck))+0.22100*(log10(height)))-450 ;
    }
  }

  float BodyFatPercentage::bfpUSNavy( const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    float height = Measurements::getHeight( cfg )->convert(INCHES).magnitude() ;
    float waist = Measurements::getWaist( cfg )->convert(INCHES).magnitude() ;
    float neck = Measurements::getNeck( cfg )->convert(INCHES).magnitude() ;

    switch ( gender ) {
      case Male:
        return 86.010*log10(waist-neck)-70.041*log10(height) + 36.76;
      default:
        float hip = Measurements::getHips( cfg )->convert(INCHES).magnitude( ) ;
        return 163.205*log10(waist+hip-neck)-97.684*log10(height)-78.387;
    }
  }

  float BodyFatPercentage::bfpUSMarines( const pugi::xml_document& cfg ) {
    (void)cfg ; /* TODO find formula */
    return 0 ;
  }

  float BodyFatPercentage::bfpYMCA( const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    float weight = Measurements::getWeight( cfg )->convert(LBS).magnitude() ;
    float waist = Measurements::getWaist( cfg )->convert(INCHES).magnitude() ;

    switch ( gender ) {
      case Male:
        return (-98.42+4.15*waist-0.082*weight)/weight*100.0 ;
      default:
        return (-76.76+ 4.15*waist-0.082*weight)/weight*100.0 ;
    }
  }

  float BodyFatPercentage::bfpYMCAModified( const pugi::xml_document& cfg ) {
    Gender gender = General::getGender( cfg ) ;
    float weight = Measurements::getWeight( cfg )->convert(LBS).magnitude() ;
    float waist = Measurements::getWaist( cfg )->convert(INCHES).magnitude() ;

    switch ( gender ) {
      case Male:
        return (-94.42+4.15*waist-0.082*weight)/weight*100.0 ;
      default: {
                 float hips = Measurements::getHips( cfg )->convert(INCHES).magnitude( ) ;
                 float wrist = Measurements::getWrist( cfg )->convert(INCHES).magnitude( ) ;
                 float forearm = Measurements::getForearm( cfg )->convert(INCHES).magnitude( ) ;
                 return ( 0.268 * weight - 0.318 * wrist + 0.157 * waist + 0.245 * hips
                     - 0.434 * forearm - 8.987 ) / weight * 100.0 ;
               }
    }
  }
}

