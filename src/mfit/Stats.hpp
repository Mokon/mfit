/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once 

#include <map>
#include <stdexcept>
#include <string>

namespace mfit {

  class StatMissingException : public std::runtime_error {
    public:
      StatMissingException( const std::string& err ) : runtime_error(err) {
      }
  } ;

  class Stats : public std::map<std::string, void*> {

    public:

      Stats( ) ;

      template <typename T> T* get( const std::string statS ) const {
        T* stat = static_cast<T*>( find(statS)->second ) ;

        if(stat == NULL ) {
          throw StatMissingException( statS ) ;
        } else {
          return stat ;
        }
      }

  } ;

}

