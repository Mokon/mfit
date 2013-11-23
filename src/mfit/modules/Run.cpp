/* Copyright (C) 2013 David 'Mokon' Bond,0. All Rights Reserved */

#include "mfit/modules/Run.hpp"

using namespace mcommon ;

namespace mfit {

  Run::Run( Quantity time, Quantity speed ) : time(time), speed(speed),
  distance( Quantity( time.convert(HOURS).magnitude() *
        speed.convert(MPH).magnitude(), MILES )) {
  }

  Run::Run( float time, float speed ) : Run(Quantity(time, MINUTES),
      Quantity(speed, MPH)) {
  }

}

