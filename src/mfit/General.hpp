/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"
#include "mfit/Stats.hpp"

namespace mfit {

  class General {

    public:

      static float bmi( const Stats& stats ) ;
  
      static const std::string STAT_WEIGHT ;

      static const std::string STAT_HEIGHT ;

  } ;

}

