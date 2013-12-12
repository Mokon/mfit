/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include <string>

namespace mfit {

  class Weight {

    public:

      Weight( std::string xpath, float factor ) ;

      Weight( std::string weight, std::string type, std::string equipment,
          std::string varient, float factor ) ;

      virtual ~Weight( ) = default ;

      Weight( const Weight& ) = default ;

      Weight& operator=( const Weight& ) = default ;

      std::string getXPath( ) const ;

      float getFactor( ) const ;

    private:

      std::string xpath ;

      float factor ;

  } ;

}

