/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include "config.h"

#include <limits>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "mcommon/Log.hpp"

#include "mfit/Engine.hpp"

static const std::string pager = "less" ;

static const std::string pager_opts = "-R" ;

/* Command line options parsing */
int parse( int argc, char* argv[], std::vector<std::string>& files, bool& page,
    bool& html, std::string& out ) {
  if( argc < 1 ) {
    return EXIT_FAILURE ;
  }

  std::string app = boost::filesystem::basename( argv[0] ) ;

  std::string pn(PACKAGE_NAME) ;
  boost::program_options::options_description desc( pn + " Program Options" ) ;
  desc.add_options()
    ("help", "program usage")
    ("page", boost::program_options::value<bool>(&page)->implicit_value(true), "page the output")
    ("html", boost::program_options::value<bool>(&html)->implicit_value(true), "use html output")
    ("out", boost::program_options::value<std::string>(&out), "output filename")
    ("files", boost::program_options::value<
     std::vector<std::string> >(&files)->required(), "xml config files") ;

  boost::program_options::positional_options_description po ;
  po.add( "files", std::numeric_limits<unsigned>::max() )  ;

  boost::program_options::variables_map vm ;
  try {
    boost::program_options::store(
        boost::program_options::command_line_parser(argc, argv).options(desc)
        .positional(po).run(), vm ) ;

    if ( vm.count("help")  ) {
      CONSOLE( ) << PACKAGE_NAME << std::endl << desc << std::endl ;
      return EXIT_SUCCESS;
    }

    boost::program_options::notify( vm ) ;
  } catch( boost::program_options::required_option& e ) {
    LOG(ERROR) << "Error: " << e.what() << std::endl << std::endl
      << PACKAGE_NAME << std::endl << desc << std::endl ;
    return EXIT_FAILURE ;
  } catch( boost::program_options::error& e ) {
    LOG(ERROR) << "Error: " << e.what() << std::endl << std::endl
      << PACKAGE_NAME << std::endl << desc << std::endl ;
    return EXIT_FAILURE ;
  }

  return EXIT_SUCCESS ;
}

/* Pagination: These are static globals which isn't nice but simplifies this
 * a lot. */
static pid_t pid ;

static int pipeFd[2] ;

int page_start( ) {
  if( pipe( pipeFd ) < 0 ) {
    perror( "pipe" ) ;
    return EXIT_FAILURE ;
  }

  pid = fork ( ) ;
  if( pid < 0 ) {
    perror( "fork" ) ;
    return EXIT_FAILURE ;
  }

  if( pid == 0 ) { /* In Child */
    if( close( pipeFd[1] ) != 0 ) {
      perror( "close" ) ;
      return EXIT_FAILURE ;
    }

    if( dup2( pipeFd[0], STDIN_FILENO ) < 0 ) {
      perror( "dup2" ) ;
      return EXIT_FAILURE ;
    }

    execlp( pager.c_str( ), pager.c_str( ), pager_opts.c_str( ), NULL ) ;

    perror( "execlp" ) ;
    return EXIT_FAILURE ;
  } else { /* In Parent */
    if( close( pipeFd[0] ) != 0 ) {
      perror( "close" ) ;
      return EXIT_FAILURE ;
    }

    if( dup2( pipeFd[1], STDOUT_FILENO ) < 0 ) {
      perror( "dup2" ) ;
      return EXIT_FAILURE ;
    }

    if( dup2( pipeFd[1], STDIN_FILENO ) < 0 ) {
      perror( "dup2" ) ;
      return EXIT_FAILURE ;
    }
  }

  return EXIT_SUCCESS ;
}

int page_end( ) {
  int status ;
  pid = waitpid( pid, &status, 0 ) ;
  if( pid < 0 ) {
    perror ( "waitpid" ) ;
    return EXIT_FAILURE ;
  }

  if( close( pipeFd[1] ) != 0 ) {
    perror( "close" ) ;
    return EXIT_FAILURE ;
  }

  return EXIT_SUCCESS ;
}

/* main program */
int main( int argc, char* argv[] ) {
  try {
    google::InitGoogleLogging( argv[0] ) ;
    google::InstallFailureSignalHandler( ) ;
    google::SetStderrLogging( google::INFO ) ;

    /* Options to be set. */
    std::vector<std::string> files ;
    bool html = false ;
    bool page = false ;
    std::string out ;

    /* Parse the command line arguments */
    if( parse( argc, argv, files, page, html, out ) != EXIT_SUCCESS ) {
      return EXIT_FAILURE ;
    }

    if( !html ) {
      CONSOLE( ) << PACKAGE_NAME << " " << PACKAGE_COPYRIGHT << std::endl ;
    }

    if( page && page_start( ) != EXIT_SUCCESS ) {
      return EXIT_FAILURE ;
    } else if( out.size( ) != 0 ) {
      /* Redirect stdout to file */
      if( freopen( out.c_str( ), "w", stdout ) == NULL ) {
        perror( "freopen" ) ;
        return EXIT_FAILURE ;
      }
    }

    mfit::Engine e(html) ;
    e.process( CONSOLE( ), files ) ;

    if( page && page_end( ) != EXIT_SUCCESS ) {
      return EXIT_FAILURE ;
    }

    if( !html ) {
      CONSOLE( ) << PACKAGE_NAME << " Good Bye!" << std::endl ;
    }

    return EXIT_SUCCESS ;
  } catch( const std::exception& ex ) {
    LOG(WARNING) << ex.what() << std::endl ;
    return EXIT_FAILURE ;
  } catch ( ... ) {
    LOG(WARNING) << "Exception Caught" << std::endl ;
    return EXIT_FAILURE ;
  }
}

