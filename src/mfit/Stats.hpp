/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include <string>
#include <stdexcept>
#include <map>

namespace mfit {

  typedef std::map<std::string, void*> Stats ;

  class StatMissingException : public std::runtime_error {
     public:
         StatMissingException( const std::string& err ) : runtime_error(err) {
    }
  } ;

}

