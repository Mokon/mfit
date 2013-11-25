/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include "mfit/Statistic.hpp"

namespace mfit {

  Statistic::Statistic( std::string header, ValueGetter get ) : header(header),
  get(get) {
  }

  void Statistic::process( std::ostream& out,
      const pugi::xml_document& cfg ) const {
    out << "\t" << header << " " << get(cfg) << std::endl ;
  }

}

