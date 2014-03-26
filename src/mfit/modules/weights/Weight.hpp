/* Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <string>

namespace mfit {

  class Weight {

    public:

      Weight( std::string weight, std::string type, std::string equipment,
          std::string varient, float factor, bool ismajor ) ;

      virtual ~Weight( ) = default ;

      Weight( const Weight& ) = default ;

      Weight& operator=( const Weight& ) = default ;

      std::string getXPath( ) const ;

      float getFactor( ) const ;

      bool isMajor( ) const ;

    private:

      std::string xpath ;

      float factor ;

      bool ismajor ; /* Can't name major since GNU populates the global ns... */

  } ;

}

