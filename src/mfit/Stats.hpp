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

  template <typename T> T* getStat( const Stats& stats,
      const std::string statS ) {
    T* stat = static_cast<T*>( stats.find(statS)->second ) ;

    if(stat == NULL ) {
      throw StatMissingException( statS ) ;
    } else {
      return stat ;
    }
  }

}

