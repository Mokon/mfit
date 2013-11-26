/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <boost/lexical_cast.hpp>

#include "mfit/Statistic.hpp"

namespace mfit {

  Statistic::Statistic( std::string header, ValueGetter get ) : header(header),
  get(get) {
  }

  void Statistic::process( std::ostream& out,
      const pugi::xml_document& cfg ) const {
    print( out, header, boost::lexical_cast<std::string>(*get(cfg)) ) ;
  }

  void Statistic::print( std::ostream& out, std::string header,
      std::string value ) {
#define THDR "[38;5;203m"
#define TRESET "[0m"
#define TVALUE "[0;37;48m"
    out << "\t" << THDR << header << TRESET << " "
      << TVALUE << value << TRESET << std::endl ;
  }

}

