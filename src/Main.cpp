/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include "config.h"

#include <iostream>
#include <cmath>
#include <map>

#include "mcommon/Log.hpp"

#include <boost/concept_check.hpp>
#include <glog/raw_logging.h>
#include <boost/asio.hpp>

#include "mcommon/Quantity.hpp"
#include "mfit/Run.hpp"
#include "mfit/Stats.hpp"
#include "mfit/Engine.hpp"
#include "Config.hpp"

using namespace mfit ;
using namespace mcommon ;

/* Signal Handler */
static void exitApp( const boost::system::error_code& ec, int sig ) {
  boost::ignore_unused_variable_warning( ec ) ; 

  RAW_LOG(INFO, "%s Shutting Down on signal %d.\n", PACKAGE_NAME, sig ) ;
}

/* Cleanup function. */
static void cleanup( ) {
  exit(EXIT_SUCCESS) ;
}

/* Test Harness */
int main( int argc, char* argv[] ) {
  boost::ignore_unused_variable_warning( argc ) ; 

  int rv = EXIT_FAILURE ;

  try {
    /* Using Google Logging, Init */
    google::InitGoogleLogging( argv[0] ) ;
    google::InstallFailureSignalHandler( ) ;
    google::SetStderrLogging( google::INFO ) ;

    /* Banner */
    CONSOLE( ) << PACKAGE_NAME << " " << PACKAGE_COPYRIGHT << std::endl ;

    Stats stats ;
    initStats( stats ) ;

    Engine e(stats);
    e.process( ) ;
    
    /* Register for signals. */
    (void)exitApp ;
    //Timer::addSignalHandler(&exitApp);

  } catch( const std::exception& ex ) {
    LOG(WARNING) << ex.what() << std::endl ;
  } catch ( ... ) {
    LOG(WARNING) << "Exception Caught" << std::endl ;
  } 

  cleanup( ) ;

  CONSOLE( ) << PACKAGE_NAME << " Good Bye!" << std::endl ;

  return rv ;
}


