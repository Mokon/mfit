/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"

#include "mfit/Module.hpp"
#include "mfit/modules/WeightRepSet.hpp"

namespace mfit {

  class Weights : public Module {

    public:

      Weights( ) = default ;

      virtual ~Weights( ) = default ;

      Weights( const Weights& ) = delete ;

      Weights& operator=( const Weights& ) = delete ;

      virtual std::string getKey( ) ;

      virtual void process( std::ostream& out,
          const pugi::xml_document& cfg ) const ;

      static const std::string key ;

      static WeightRepSet getDumbbellChestPressFlat(
          const pugi::xml_document& cfg ) ;

  } ;

}

