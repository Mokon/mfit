/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include "mfit/modules/ValueString.hpp"

using namespace mcommon ;

namespace mfit {

  ValueString::ValueString( std::string value ) : value(value) {
  }

  std::ostream& ValueString::out( std::ostream& o ) const {
    return o << value ;
  }

}

