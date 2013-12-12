/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include <list>
#include <memory>
#include <ostream>
#include <vector>
#include <string>

#include <boost/lexical_cast.hpp>

#include <pugixml.hpp>

#include "mcommon/Exception.hpp"
#include "mcommon/Quantity.hpp"

namespace mfit {

  class Module ;

  DEFINE_EXCEPTION_CLASS( ModuleMissingException ) ;
  DEFINE_EXCEPTION_CLASS( StatMissingException ) ;

  class Engine {

    public:

      Engine( bool html ) ;

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

      /* Process all files */
      void process( std::ostream& out,
          const std::vector<std::string>& files ) const ;

      static std::string getAttribute( const pugi::xml_document& cfg,
          const std::string xpath ) ;

      template<typename T> static T getAttributeAs(
          const pugi::xml_document& cfg, const std::string xpath ) {
        return boost::lexical_cast<T>(getAttribute( cfg, xpath ) ) ;
      }

      static void getAttributes( const pugi::xml_document& cfg,
          const std::string xpath, std::list<std::string>& attrs ) ;

      template<typename T> static void getAttributesAs(
          const pugi::xml_document& cfg, const std::string xpath,
          std::list<T>& attrs ) {
        std::list<std::string> sattrs ;
        getAttributes( cfg, xpath, sattrs ) ;
        for( auto a : sattrs ) {
          attrs.push_back( boost::lexical_cast<T>( a ) ) ;
        }
      }

      static std::string getNode( const pugi::xml_document& cfg,
          const std::string xpath ) ;

      template<typename T> static T getNodeAs(
          const pugi::xml_document& cfg, const std::string xpath ) {
        return boost::lexical_cast<T>(getNode(cfg, xpath));
      }

      static std::shared_ptr<mcommon::Quantity> getNodeAsQuantity(
          const pugi::xml_document& cfg, const std::string xpath ) ;

      static void getNodes( const pugi::xml_document& cfg,
          const std::string xpath, std::list<std::string>& nodes ) ;

      template<typename T> static void getNodesAs(
          const pugi::xml_document& cfg, const std::string xpath,
          std::list<T>& nodes ) {
        std::list<std::string> snodes ;
        getNodes( cfg, xpath, snodes ) ;
        for( auto n : snodes ) {
          nodes.push_back( boost::lexical_cast<T>( n ) ) ;
        }
      }

      static void getNodesAsQuantity(
          const pugi::xml_document& cfg, const std::string xpath,
          std::list<std::shared_ptr<mcommon::Quantity> >& nodes ) ;

      /* Prints a stat in html or terminal output. */
      void print( std::ostream& out, std::string header,
          std::string value, bool indent ) const ;

      void print( std::ostream& out, std::string text ) const ;

    private:

      /* A boolean on whether to output html versus console text. */
      bool html ;

      std::list<std::shared_ptr<Module>> modules ;

  } ;

}

