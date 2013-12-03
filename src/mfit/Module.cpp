/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <boost/concept_check.hpp>

#include "mcommon/Log.hpp"

#include "mfit/Module.hpp"

namespace mfit {

  static const std::string THDR = "[38;5;203m" ;

  static const std::string TRESET = "[0m" ;

  static const std::string TVALUE = "[0;37;48m" ;

  Module::Module( ) : html(false) {
  }

  void Module::setHTML( ) {
    html = true ;
  }

  void Module::process( std::ostream& out,
      const pugi::xml_document& cfg ) const {
    /* By default do nothing. This allow concrete classes to implement this
     * at their descretion. */
    boost::ignore_unused_variable_warning( out ) ;
    boost::ignore_unused_variable_warning( cfg ) ;
  }

  void Module::print( std::ostream& out, std::string header,
      std::string value ) const {
    if( html ) {
      out << "<li><span class='header'>" << header << " " << "</span>" <<
        "<span class='value'>" << value << "</span></li>" ;
    } else {
      out << "\t" << THDR << header << TRESET << " "
        << TVALUE << value << TRESET << std::endl ;
    }
  }

  void Module::processRegisteredStats( std::ostream& out,
      const pugi::xml_document& cfg ) {
    for( auto stat : stats) {
      try {
        if( stat.isMultiList( ) ) {
          std::list<std::list<std::string> > values ;
          stat.getValues( cfg, values ) ;
          for( auto v : values ) {
            int i = 0 ;
            for( auto av : v ) {
              print( out, stat.getHeader( i++ ), av ) ;
            }
          }
        } else if( stat.isMultiPair( ) ) {
          std::list<std::pair<std::string, std::string> > values ;
          stat.getValues( cfg, values ) ;
          for( auto v : values ) {
            print( out, stat.getHeader( 0 ), v.first ) ;
            print( out, stat.getHeader( 1 ), v.second ) ;
          }
        } else if( stat.isMulti( ) ) {
          std::list<std::string> values ;
          stat.getValues( cfg, values ) ;
          for( auto v : values ) {
            print( out, stat.getHeader( ), v ) ;
          }
        } else {
          print( out, stat.getHeader( ), stat.getValue( cfg ) ) ;
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


}

