/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <cmath>

#include "mcommon/Log.hpp"

#include "mfit/Engine.hpp"
#include "mfit/modules/General.hpp"
#include "mfit/modules/Calories.hpp"
#include "mfit/modules/Measurements.hpp"
#include "mfit/modules/GreekIdeal.hpp"
#include "mfit/modules/Weights.hpp"
#include "mfit/modules/Cardio.hpp"
#include "mfit/modules/BodyFatPercentage.hpp"

using namespace mcommon ;

namespace mfit {

  Engine::Engine( bool html ) : html(html) {
    add(std::shared_ptr<General>( new General( ) ) ) ;
    add(std::shared_ptr<Calories>( new Calories( ) ) ) ;
    add(std::shared_ptr<Measurements>( new Measurements( ) ) ) ;
    add(std::shared_ptr<GreekIdeal>( new GreekIdeal( ) ) ) ;
    add(std::shared_ptr<Weights>( new Weights( ) ) ) ;
    add(std::shared_ptr<Cardio>( new Cardio( ) ) ) ;
    add(std::shared_ptr<BodyFatPercentage>( new BodyFatPercentage( ) ) ) ;
  }

  void Engine::add( std::shared_ptr<Module> module ) {
    if( html ) {
      module->setHTML( ) ;
    }
    modules[module->getKey()] = module ;
  }

  std::string Engine::getAttribute( const pugi::xml_document& cfg,
      const std::string xpath ) {
    const pugi::xpath_node xpnode = cfg.select_single_node(xpath.c_str()) ;

    DLOG(INFO) << xpath << " " <<  xpnode.attribute().name() << " "
      << xpnode.attribute().value() << std::endl ;

    std::string ret(xpnode.attribute().value());
    if( ret.size( ) == 0 ) {
      throw StatMissingException( "xpath [" + xpath + "] returns no value." ) ;
    }
    return ret ;
  }

  std::string Engine::getNode( const pugi::xml_document& cfg,
      const std::string xpath ) {
    const pugi::xpath_node xpnode = cfg.select_single_node(xpath.c_str()) ;

    DLOG(INFO) << xpath << " " <<  xpnode.node().name() << " "
      << xpnode.node().last_child().value() << std::endl ;

    std::string ret(xpnode.node().last_child().value());
    if( ret.size( ) == 0 ) {
      throw StatMissingException( "xpath [" + xpath + "] returns no value." ) ;
    }
    return ret ;
  }

  std::shared_ptr<Quantity> Engine::getNodeAsQuantity(
      const pugi::xml_document& cfg, const std::string xpath ) {
    return std::shared_ptr<Quantity>(
        new Quantity( getNodeAs<float>(cfg, xpath),
          getAttributeAs<Unit>( cfg, xpath + "/@unit" ) ) )  ;
  }

  void Engine::process( std::ostream& out,
      const std::vector<std::string>& files ) const {
    for( auto file : files ) {
      process( out, file ) ;
    }
  }

  void Engine::process( std::ostream& out, const std::string config ) const {
    pugi::xml_document cfg ;
    cfg.load_file( config.c_str( ) ) ;

    std::string name = getNode( cfg, "/person/name" ) ;

    if( html ) {
      out << "<html><body><h1>" ;
    }

    out << "mfit analytics engine stats for " << name ;

    if( html ) {
      out << "</h1>" ;
    } else {
      out << std::endl ;
    }

    for( auto mod : modules ) {
      if( html ) {
        out << "<h2>" ;
      }

      out << mod.first << " statistics" ;

      if( html ) {
        out << "</h2><ul>" ;
      } else {
        out << std::endl ;
      }

      try {
        mod.second->process( out, cfg ) ;
      } catch( const std::exception& ex ) {
        DLOG(INFO) << "Couldn't process a statistic with the given config: "
          << ex.what() << std::endl ;
      }
      mod.second->processRegisteredStats( out, cfg ) ;

      if( html ) {
        out << "</ul>" ;
      }
    }

    if( html ) {
      out << "</body></html>" ;
    }
  }

}

