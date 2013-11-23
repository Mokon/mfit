/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"

namespace mfit {

  class Run {

    public:
      
      Run( ) ;

      Run( mcommon::Quantity time, mcommon::Quantity speed ) ;

      Run( float time, float speed ) ;

      mcommon::Quantity time ;

      mcommon::Quantity speed ;

      mcommon::Quantity distance ;

  } ;

}

