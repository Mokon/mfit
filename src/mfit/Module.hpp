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

      Module( ) = default ;

      virtual ~Module( ) = default ;

      Module( const Module& ) = delete ;

      Module& operator=( const Module& ) = delete ;

      virtual std::string getKey( ) = 0 ;

      virtual void process( std::ostream& out,
          const pugi::xml_document& cfg ) const ;
    
      void processRegisteredStats( std::ostream& out,
          const pugi::xml_document& cfg ) ;

      void add( Statistic stat ) ;
      
      void add( std::string header, Statistic::ValueGetter get ) ;

    private:

      std::list<Statistic> stats ;

  } ;

}

