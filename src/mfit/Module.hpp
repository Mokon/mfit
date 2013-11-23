/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include <ostream>
#include <string>

#include <pugixml.hpp>

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
          const pugi::xml_document& cfg ) const = 0 ;

  } ;

}

