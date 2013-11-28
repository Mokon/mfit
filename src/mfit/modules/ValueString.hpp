/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include <string>

#include "mcommon/Value.hpp"

namespace mfit {

  class ValueString : public mcommon::Value {

    public:

      ValueString( std::string value ) ;

      virtual ~ValueString( ) = default ;

      ValueString( const ValueString& ) = default ;

      ValueString& operator=( const ValueString& ) = default ;

      virtual std::ostream& out( std::ostream& o ) const ;

    private:

      std::string value ;

  } ;

}

