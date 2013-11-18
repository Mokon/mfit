/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"

#include "mfit/Stats.hpp"

namespace mfit {

  class General {

    public:
  
      static mcommon::Quantity metsToCalories( mcommon::Quantity mets,
        mcommon::Quantity time, const Stats& stats ) ;

      static float bmi( const Stats& stats ) ;
      
      static float bfp( const Stats& stats ) ;
  
      static const std::string STAT_WEIGHT ;

      static const std::string STAT_HEIGHT ;

      static const std::string STAT_AGE ;
      
      static const std::string STAT_GENDER ;

      static const std::string STAT_NECK ;

      static const std::string STAT_WAIST ;

      static const std::string STAT_HIPS ;

      static const std::string STAT_THIGH_LEFT ;

      static const std::string STAT_THIGH_RIGHT ;

      static const std::string STAT_BICEP_LEFT ;

      static const std::string STAT_BICEP_RIGHT ;

      static const std::string STAT_BELT_LINE ;

      static const std::string STAT_BLOOD_PRESURE_SYSTOLIC ;

      static const std::string STAT_BLOOD_PRESURE_DIASTOLIC ;

      static const std::string STAT_CHEST ;

      static const std::string STAT_CALF_LEFT ;

      static const std::string STAT_CALF_RIGHT ;

      static const std::string STAT_FOREARM_LEFT ;

      static const std::string STAT_FOREARM_RIGHT ;

      static const std::string STAT_WRIST ;

      static const std::string STAT_ELBOW_BREATH ;

      static const std::string STAT_BICEP_LEFT_FLEXED ;

      static const std::string STAT_BICEP_RIGHT_FLEXED ;

  } ;

}

