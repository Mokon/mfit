/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include <functional>
#include <memory>
#include <ostream>
#include <string>

#include <pugixml.hpp>

#include "mcommon/Value.hpp"

namespace mfit {

  class Statistic {

    public:

      typedef std::function<mcommon::Value (
          const pugi::xml_document& cfg )> ValueGetter ;

      Statistic( std::string header, ValueGetter get ) ;

      virtual ~Statistic( ) = default ;

      Statistic( const Statistic& ) = default ;

      Statistic& operator=( const Statistic& ) = default ;

      void process( std::ostream& out,
          const pugi::xml_document& cfg ) const ;

    protected:

      std::string header ;

      ValueGetter get ;

  } ;

}

