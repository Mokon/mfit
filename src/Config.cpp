/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <vector>
#include <iostream>

#include "Config.hpp"
#include "mfit/Run.hpp"

namespace mfit {

  static std::vector<Run> runs ;

  void initStats( Stats& stats ) {

    runs = std::vector<Run> {
      Run(12, 6.4),
      Run(1, 8.0),
    };

    stats[Run::STAT_RUNS] = &runs ;
  }

}

