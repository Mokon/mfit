/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include "mcommon/Log.hpp"
#include "mcommon/Quantity.hpp"
#include "mfit/Stats.hpp"
#include "mfit/Run.hpp"

namespace mfit {

  class Engine {

    public:

      Engine( const Stats& stats ) : stats(stats) { } ;

      void process( ) { 
        using namespace mcommon ;

        Quantity as( Run::averageSpeed( stats ) ) ;

        Quantity dis( 1, MILES ) ;
        Quantity time( 12, MINUTES ) ;

        Quantity dti( Run::distanceTraveledIn( stats, time ) ) ;
        Quantity tttd( Run::timeToTravelDistance( stats, dis ) ) ;

        Quantity tttds( std::round(std::fmod(
                tttd.convert(SECONDS).magnitude(), 60)), SECONDS) ;
        Quantity tttdm( std::trunc(tttd.convert(MINUTES).magnitude()), MINUTES ) ;

        CONSOLE( ) << "Average Speed: " << as << std::endl
          << "Distance in " << time << ": " << dti << std::endl
          << "Time for " << dis << ": " << tttdm << " and " << tttds << std::endl ;
      } ;

    private:

      const Stats& stats ;

  } ;

}

