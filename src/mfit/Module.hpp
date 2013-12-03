/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include <list>
#include <string>

#include <pugixml.hpp>

#include "mfit/Statistic.hpp"

namespace mfit {

  class Engine ;

  class Module {

    public:

      Module( ) ;

      virtual ~Module( ) = default ;

      Module( const Module& ) = delete ;

      Module& operator=( const Module& ) = delete ;

      /* Sets the html flag on this module so that all output from this module
       * will now be in html rather than terminal output. */
      void setHTML( ) ;

      virtual std::string getKey( ) = 0 ;

      /* This function can be overridden for stats that can't be handled with
       * registered stats. */
      virtual void process( std::ostream& out,
          const pugi::xml_document& cfg ) const ;

      /* Adds a stat to be automatically printed during the processing stage
       * of the module. Most stats should be added in this manner rather
       * than my manually doing them in the process function as this function
       * will gracefully handle exceptions which indicate a missing stat.
       */
      void processRegisteredStats( std::ostream& out,
          const pugi::xml_document& cfg ) ;

      void add( Statistic stat ) ;

      void add( std::string header, Statistic::ValueGetter get ) ;

      void add( std::string header, Statistic::MultiValueGetter get ) ;

      void add( std::string header, std::string header2,
          Statistic::MultiPairValueGetter get ) ;

      void add( std::vector<std::string> headers,
          Statistic::MultiListValueGetter get ) ;

      /* Prints a stat in html or terminal output. */
      void print( std::ostream& out, std::string header,
          std::string value ) const ;

    private:

      bool html ;

      std::list<Statistic> stats ;

  } ;

}

