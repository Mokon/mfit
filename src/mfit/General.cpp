/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <cmath>

#include "mfit/General.hpp"
#include "mcommon/Gender.hpp"

using namespace mcommon ;

namespace mfit {

  float General::bmi( const Stats& stats ) {
    Quantity weight = stats.get<Quantity>(STAT_WEIGHT)->convert(LBS) ;
    Quantity height = stats.get<Quantity>(STAT_HEIGHT)->convert(INCHES) ;

    float height2 = height.magnitude()*height.magnitude() ;
    float bmi = weight.magnitude()/height2*703 ;

    return bmi ;
  }

  float General::bfp( const Stats& stats ) {
    Gender* gender = stats.get<Gender>(STAT_GENDER) ;
    float height = stats.get<Quantity>(STAT_HEIGHT)->convert(INCHES).magnitude() *2.54;
    float waist = stats.get<Quantity>(STAT_WAIST)->convert(INCHES).magnitude() *2.54;
    float neck = stats.get<Quantity>(STAT_NECK)->convert(INCHES).magnitude() *2.54;

    switch ( *gender ) {
      case Male:
        return 495.0/(1.0324-0.19077*
            (log10(waist-neck))+0.15456*(log10(height)))-450.0 ;
      default:
        float hip = stats.get<Quantity>(STAT_HIPS)->convert(INCHES).magnitude() *2.54;
        return 495.0/(1.29579-0.35004*
            (log10(waist+hip-neck))+0.22100*(log10(height)))-450 ;
    }
  }

  Quantity General::metsToCalories( Quantity mets, Quantity time,
      const Stats& stats ) {
    Quantity weight = stats.get<Quantity>(STAT_WEIGHT)->convert(KG) ;
    return Quantity( mets.magnitude()*weight.magnitude()*
        time.convert(SECONDS).magnitude(), CALORIES) ;
  }

  const std::string General::STAT_WEIGHT = "weight" ;

  const std::string General::STAT_HEIGHT = "height" ;

  const std::string General::STAT_AGE = "age" ;

  const std::string General::STAT_GENDER = "gender" ;

  const std::string General::STAT_NECK = "neck" ;

  const std::string General::STAT_WAIST = "waist" ;

  const std::string General::STAT_HIPS = "hips" ;

  const std::string General::STAT_THIGH_LEFT = "thigh_left" ;

  const std::string General::STAT_THIGH_RIGHT = "thigh_right" ;

  const std::string General::STAT_BICEP_LEFT = "bicep_left" ;

  const std::string General::STAT_BICEP_RIGHT = "bicep_right" ;

  const std::string General::STAT_BELT_LINE = "belt_line" ;

  const std::string General::STAT_BLOOD_PRESURE_SYSTOLIC = "blood_preasure_systolic" ;

  const std::string General::STAT_BLOOD_PRESURE_DIASTOLIC = "blood_preasure_diastolic" ;

  const std::string General::STAT_CHEST = "chest" ;

  const std::string General::STAT_CALF_LEFT = "calf_left" ;

  const std::string General::STAT_CALF_RIGHT = "calf_right" ;

  const std::string General::STAT_FOREARM_LEFT = "forearm_left" ;

  const std::string General::STAT_FOREARM_RIGHT = "forearm_right" ;

  const std::string General::STAT_WRIST = "wrist" ;

  const std::string General::STAT_ELBOW_BREATH = "elbow_breath" ;

  const std::string General::STAT_BICEP_LEFT_FLEXED = "bicep_left_flexed" ;

  const std::string General::STAT_BICEP_RIGHT_FLEXED = "bicep_right_flexed" ;

}

