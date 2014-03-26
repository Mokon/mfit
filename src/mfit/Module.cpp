/* Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved */

#include <boost/concept_check.hpp>

#include "mcommon/Log.hpp"

#include "mfit/Engine.hpp"
#include "mfit/Module.hpp"

namespace mfit {

  Module::Module( ) : engine(NULL) {
  }

  void Module::set( Engine* engine ) {
    this->engine = engine ;
  }

  void Module::process( std::ostream& out,
      const pugi::xml_document& cfg ) const {
    /* By default do nothing. This allow concrete classes to implement this
     * at their discrection. */
    boost::ignore_unused_variable_warning( out ) ;
    boost::ignore_unused_variable_warning( cfg ) ;
  }

  void Module::processRegisteredStats( std::ostream& out,
      const pugi::xml_document& cfg ) {
    for( auto stat : stats) {
      try {
        if( stat.isMultiListWHeaders( ) ) {
          std::list<std::list<std::pair<std::string, std::string> > > values ;
          stat.getValues( cfg, values ) ;
          for( auto v : values ) {
            int i = 0 ;
            for( auto av : v ) {
              engine->print( out, av.first, av.second, i++ != 0 ) ;
            }
          }
        } else if( stat.isMultiList( ) ) {
          std::list<std::list<std::string> > values ;
          stat.getValues( cfg, values ) ;
          for( auto v : values ) {
            int i = 0 ;
            for( auto av : v ) {
              engine->print( out, stat.getHeader( i ), av, i != 0 ) ;
              i++ ;
            }
          }
        } else if( stat.isMultiPair( ) ) {
          std::list<std::pair<std::string, std::string> > values ;
          stat.getValues( cfg, values ) ;
          for( auto v : values ) {
            engine->print( out, stat.getHeader( 0 ), v.first, false ) ;
            engine->print( out, stat.getHeader( 1 ), v.second, false ) ;
          }
        } else if( stat.isMulti( ) ) {
          std::list<std::string> values ;
          stat.getValues( cfg, values ) ;
          for( auto v : values ) {
            engine->print( out, stat.getHeader( ), v, false ) ;
          }
        } else {
          engine->print( out, stat.getHeader( ), stat.getValue( cfg ), false ) ;
        }
      } catch( const std::exception& ex ) {
        DLOG(INFO) << "Couldn't process a statistic with the given config: "
          << ex.what() << std::endl ;
      }
    }
  }

  void Module::add( Statistic stat ) {
    stats.push_back( stat ) ;
  }

  void Module::add( std::string header, Statistic::ValueGetter get ) {
    DLOG(INFO) << "Adding registered stat for module " << getKey()
      << " with header " << header << " and function " << (void*)&get
      << std::endl ;

    add( Statistic( header, get ) ) ;
  }

  void Module::add( std::string header, Statistic::MultiValueGetter get ) {
    DLOG(INFO) << "Adding registered stat for module " << getKey()
      << " with header " << header << " and function " << (void*)&get
      << std::endl ;

    add( Statistic( header, get ) ) ;
  }

  void Module::add( std::string header, std::string header2,
      Statistic::MultiPairValueGetter get ) {
    DLOG(INFO) << "Adding registered stat for module " << getKey()
      << " with header " << header << " and function " << (void*)&get
      << std::endl ;

    add( Statistic( header, header2, get ) ) ;
  }

  void Module::add( std::vector<std::string> headers,
      Statistic::MultiListValueGetter get ) {
    DLOG(INFO) << "Adding registered stat for module " << getKey()
      << " with header " << headers.front( ) << " and function " << (void*)&get
      << std::endl ;

    add( Statistic( headers, get ) ) ;
  }

  void Module::add( Statistic::MultiListWHeadersValueGetter get ) {
    DLOG(INFO) << "Adding registered stat for module " << getKey()
      << " with dynamic headers and function " << (void*)&get
      << std::endl ;

    add( Statistic( get ) ) ;
  }

}

