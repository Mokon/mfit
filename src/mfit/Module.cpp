/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <boost/concept_check.hpp>

#include "mcommon/Log.hpp"

#include "mfit/Module.hpp"

namespace mfit {

  void Module::process( std::ostream& out,
      const pugi::xml_document& cfg ) const {
    boost::ignore_unused_variable_warning( out ) ;
    boost::ignore_unused_variable_warning( cfg ) ;
  }

  void Module::processRegisteredStats( std::ostream& out,
      const pugi::xml_document& cfg ) {
    for( auto stat : stats) {
      try {
          stat.process( out, cfg ) ;
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

