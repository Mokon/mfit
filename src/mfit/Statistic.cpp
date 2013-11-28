/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <boost/lexical_cast.hpp>

#include "mfit/Statistic.hpp"

namespace mfit {

  Statistic::Statistic( std::string header, ValueGetter get ) : header(header),
  get(get) {
  }

  std::string Statistic::getHeader( ) const {
    return header ;
  }

  std::string Statistic::getValue( const pugi::xml_document& cfg ) const {
    return boost::lexical_cast<std::string>(*get(cfg)) ;
  }

}

