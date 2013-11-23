/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include <map>
#include <memory>
#include <ostream>
#include <string>

#include <pugixml.hpp>

#include "mcommon/Exception.hpp"
#include "mcommon/Quantity.hpp"
#include "mcommon/Gender.hpp"

namespace mfit {

  class Module ;

  DEFINE_EXCEPTION_CLASS( ModuleMissingException ) ;

  class Engine {

    public:

      Engine( ) = default ;

      virtual ~Engine( ) = default ;

      Engine( const Engine& ) = delete ;

      Engine& operator=( const Engine& ) = delete ;

      /* Adds a module to the list of modules used for anaysis during the
       * processing phase. */
      void add( std::shared_ptr<Module> module ) ;

      /* Processes the given config file outputing the anayltics results to
       * the given ostream.
       */
      void process( std::ostream& out, const std::string config ) const ;

      /* TODO convert to templates */
      static float getNodeAsFloat( const pugi::xml_document& cfg,
          const std::string xpath ) ;

      static float getAttributeAsFloat( const pugi::xml_document& cfg,
          const std::string xpath ) ;

      static std::string getNodeAsString( const pugi::xml_document& cfg,
          const std::string xpath ) ;

      static mcommon::Quantity getNodeAsQuantity( const pugi::xml_document& cfg,
          const std::string xpath, const mcommon::Unit unit ) ;

      static mcommon::Gender getNodeAsGender(
          const pugi::xml_document& cfg, const std::string xpath ) ;

    private:

      std::map<const std::string, std::shared_ptr<Module>> modules ;

  } ;

}

