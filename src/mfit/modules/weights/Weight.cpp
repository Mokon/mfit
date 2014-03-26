/* Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved */

#include "mfit/modules/weights/Weight.hpp"

namespace mfit {

  Weight::Weight( std::string weight, std::string type, std::string equipment,
      std::string varient, float factor, bool ismajor )
    : xpath(""), factor(factor), ismajor(ismajor) {
    xpath.append( "/person/excercises/weights/") ;
    xpath.append( weight ) ;

    bool started = false ;

    if( type.size( ) ) {
      xpath.append( "[ @type='" ) ;
      xpath.append( type ) ;
      xpath.append( "'" ) ;
      started = true ;
    }

    if( equipment.size( ) ) {
      if( !started ) {
        xpath.append( "[" ) ;
      } else {
        xpath.append( " and " ) ;
      started = true ;
      }
      xpath.append( "@equipment='" ) ;
      xpath.append( equipment ) ;
      xpath.append( "'" ) ;
    }
    
    if( varient.size( ) ) {
      if( !started ) {
        xpath.append( "[" ) ;
      } else {
        xpath.append( " and " ) ;
      started = true ;
      }
      xpath.append( "@varient='" ) ;
      xpath.append( varient ) ;
      xpath.append( "'" ) ;
    }

    if( started ) {
      xpath.append( "]" ) ;
    }
  }

  std::string Weight::getXPath( ) const {
    return xpath ;
  }

  float Weight::getFactor( ) const {
    return factor ;
  }

  bool Weight::isMajor( ) const {
    return ismajor ;
  }

}

