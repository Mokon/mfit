/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <vector>
#include <iostream>

#include "Config.hpp"
#include "mfit/Run.hpp"
#include "mfit/General.hpp"

using namespace mcommon ;

namespace mfit {

  void initStats( Stats& stats ) {

    static std::vector<Run> runs = std::vector<Run> {
      Run(12, 6.4),
      Run(1, 8.0),
    };
    static Quantity weight(215, LBS) ;
    static Quantity height(73, INCHES) ;

    stats[Run::STAT_RUNS] = &runs ;
    stats[General::STAT_WEIGHT] = &weight ;
    stats[General::STAT_HEIGHT] = &height ;
  }

}

