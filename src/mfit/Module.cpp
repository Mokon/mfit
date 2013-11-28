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
        print( out, stat.getHeader( ), stat.getValue( cfg ) ) ;
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

}

