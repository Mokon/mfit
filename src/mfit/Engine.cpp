/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <cmath>
#include <memory>

#include <boost/lexical_cast.hpp>

#include "mcommon/Log.hpp"
#include "mcommon/Quantity.hpp"

#include "mfit/Engine.hpp"
#include "mfit/modules/General.hpp"

using namespace mcommon ;

namespace mfit {

  void Engine::add( std::shared_ptr<Module> module ) {
    modules[module->getKey()] = module ;
  }

  float Engine::getNodeAsFloat( const pugi::xml_document& cfg,
          const std::string xpath ) {
    return boost::lexical_cast<float>(getNodeAsString(cfg, xpath));
  }

  float Engine::getAttributeAsFloat( const pugi::xml_document& cfg,
      const std::string xpath ) {
    const pugi::xpath_node xpnode = cfg.select_single_node(xpath.c_str()) ;

    DLOG(INFO) << xpath << " " <<  xpnode.attribute().name() << " "
      << xpnode.attribute().value() << std::endl ;

    std::string ret(xpnode.attribute().value());
    if( ret.size( ) == 0 ) {
      throw StatMissingException( "xpath [" + xpath + "] returns no value." ) ;
    }
    return boost::lexical_cast<float>(ret) ;
  }

  std::string Engine::getNodeAsString( const pugi::xml_document& cfg,
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

  Quantity Engine::getNodeAsQuantity( const pugi::xml_document& cfg,
      const std::string xpath, const Unit unit ) {
    /* TODO remove unit param and query from xml */
    float val = boost::lexical_cast<float>(getNodeAsString(cfg, xpath));
    return Quantity(val, unit);
  }
  
  std::shared_ptr<Quantity> Engine::getNodeAsQuantityPtr( const pugi::xml_document& cfg,
      const std::string xpath, const Unit unit ) {
    /* TODO remove unit param and query from xml */
    float val = boost::lexical_cast<float>(getNodeAsString(cfg, xpath));
    return std::shared_ptr<Quantity>( new Quantity(val, unit ) ) ;
  }

  Gender Engine::getNodeAsGender( const pugi::xml_document& cfg,
      const std::string xpath ) {
    return toGender(getNodeAsString( cfg, xpath));
  }

  void Engine::process( std::ostream& out, const std::string config ) const {
    pugi::xml_document cfg ;
    cfg.load_file( config.c_str( ) ) ;

    std::string name = getNodeAsString( cfg, "/person/name" ) ;

    out << "The mfit analytics engine is processing stats for " << name
      << "." << std::endl ;

    for( auto mod : modules ) {
      out << mod.first << " statistics" << std::endl ;
      mod.second->process( out, cfg ) ;
      mod.second->processRegisteredStats( out, cfg ) ;
    }
  }

}

