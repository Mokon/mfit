/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

namespace mfit {

  class Stats ;

  class Engine {

    public:

      Engine( const Stats& stats ) ;

      void process( ) ;

    private:

      const Stats& stats ;

  } ;

}

