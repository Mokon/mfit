/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include "config.h"

#include <boost/concept_check.hpp>

#include "mcommon/Log.hpp"

#include "mfit/Stats.hpp"
#include "mfit/Engine.hpp"

int main( int argc, char* argv[] ) {
  boost::ignore_unused_variable_warning( argc ) ; 

  int rv = EXIT_SUCCESS ;

  try {
    google::InitGoogleLogging( argv[0] ) ;
    google::InstallFailureSignalHandler( ) ;
    google::SetStderrLogging( google::INFO ) ;

    CONSOLE( ) << PACKAGE_NAME << " " << PACKAGE_COPYRIGHT << std::endl ;

    mfit::Stats stats ;
    mfit::Engine e(stats);
    e.process( ) ;
  } catch( const std::exception& ex ) {
    LOG(WARNING) << ex.what() << std::endl ;
    rv = EXIT_FAILURE ;
  } catch ( ... ) {
    LOG(WARNING) << "Exception Caught" << std::endl ;
    rv = EXIT_FAILURE ;
  } 

  CONSOLE( ) << PACKAGE_NAME << " Good Bye!" << std::endl ;

  return rv ;
}

