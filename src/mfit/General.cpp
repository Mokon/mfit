/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include "mfit/General.hpp"

namespace mfit {

  float General::bmi( const Stats& stats ) {
    using namespace mcommon ;

    Quantity* weight = getStat<Quantity>(stats, STAT_WEIGHT) ;
    Quantity* height = getStat<Quantity>(stats, STAT_HEIGHT) ;

    float height2 = height->magnitude()*height->magnitude() ;
    float bmi = weight->magnitude()/height2*703 ;

    return bmi ;
  }

  const std::string General::STAT_WEIGHT = "weight" ;

  const std::string General::STAT_HEIGHT = "height" ;

}

