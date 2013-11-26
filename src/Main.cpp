/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include "config.h"

#include "mcommon/Log.hpp"

#include "mfit/Engine.hpp"
#include "mfit/modules/General.hpp"
#include "mfit/modules/Measurements.hpp"
#include "mfit/modules/GreekIdeal.hpp"
#include "mfit/modules/Weights.hpp"
#include "mfit/modules/Cardio.hpp"
#include "mfit/modules/BodyFatPercentage.hpp"

int main( int argc, char* argv[] ) {
  int rv = EXIT_SUCCESS ;

  try {
    google::InitGoogleLogging( argv[0] ) ;
    google::InstallFailureSignalHandler( ) ;
    google::SetStderrLogging( google::INFO ) ;

    CONSOLE( ) << PACKAGE_NAME << " " << PACKAGE_COPYRIGHT << std::endl ;

    if( argc < 2 ) {
      CONSOLE( ) << "Usage: mfit <config file> ..." << std::endl ;
      return EXIT_FAILURE ;
    }
    
    mfit::Engine e ;

    /* TODO move to factory design pattern */
    e.add(std::shared_ptr<mfit::General>( new mfit::General( ) ) ) ;
    e.add(std::shared_ptr<mfit::Measurements>( new mfit::Measurements( ) ) ) ;
    e.add(std::shared_ptr<mfit::GreekIdeal>( new mfit::GreekIdeal( ) ) ) ;
    e.add(std::shared_ptr<mfit::Weights>( new mfit::Weights( ) ) ) ;
    e.add(std::shared_ptr<mfit::Cardio>( new mfit::Cardio( ) ) ) ;
    e.add(std::shared_ptr<mfit::BodyFatPercentage>( new mfit::BodyFatPercentage( ) ) ) ;

    for( int i = 1 ; i < argc ; i++ ) {
      e.process( std::cout, argv[i] ) ;
    }
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

