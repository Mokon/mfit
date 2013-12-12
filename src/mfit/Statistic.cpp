/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <boost/lexical_cast.hpp>

#include "mfit/Statistic.hpp"

namespace mfit {

  Statistic::Statistic( std::string header, ValueGetter get ) : get(get) {
    headers.push_back(header) ;
  }

  Statistic::Statistic( std::string header, MultiValueGetter get ) : multiGet(get) {
    headers.push_back(header) ;
  }

  Statistic::Statistic( std::string header, std::string header2,
      MultiPairValueGetter get ) : multiPairGet(get) {
    headers.push_back(header) ;
    headers.push_back(header2) ;
  }

  Statistic::Statistic( std::vector<std::string> headers,
      MultiListValueGetter get ) : headers(headers), multiListGet(get) {
  }

  Statistic::Statistic( MultiListWHeadersValueGetter get ) :
    multiListWHeadersGet(get) {
  }

  std::string Statistic::getHeader( ) const {
    return headers.front( ) ;
  }

  std::string Statistic::getHeader( int i ) const {
    return headers.at(i) ;
  }

  bool Statistic::isMulti( ) {
    return (bool)multiGet ;
  }

  bool Statistic::isMultiPair( ) {
    return (bool)multiPairGet ;
  }

  bool Statistic::isMultiList( ) {
    return (bool)multiListGet ;
  }

  bool Statistic::isMultiListWHeaders( ) {
    return (bool)multiListWHeadersGet ;
  }

  std::string Statistic::getValue( const pugi::xml_document& cfg ) const {
    return boost::lexical_cast<std::string>(*get(cfg)) ;
  }

  void Statistic::getValues( const pugi::xml_document& cfg,
      std::list<std::string>& values ) const {
    std::list<std::shared_ptr<mcommon::Value> > vs ;
    multiGet(cfg, vs) ;
    for( auto v : vs ) {
      values.push_back( boost::lexical_cast<std::string>(*v)) ;
    }
  }

  void Statistic::getValues( const pugi::xml_document& cfg,
      std::list<std::pair<std::string, std::string> >& values ) const {
    std::list<std::pair<std::shared_ptr<mcommon::Value>,
    std::shared_ptr<mcommon::Value> > > vs ;
    multiPairGet(cfg, vs) ;
    for( auto v : vs ) {
      values.push_back( std::make_pair(
            boost::lexical_cast<std::string>(*v.first),
            boost::lexical_cast<std::string>(*v.second) ) ) ;
    }
  }
  
  void Statistic::getValues( const pugi::xml_document& cfg,
      std::list<std::list<std::string> >& values ) const {
    std::list<std::list<std::shared_ptr<mcommon::Value> > > vs ;
    multiListGet(cfg, vs) ;
    for( auto v : vs ) {
      std::list<std::string> avs ;
      for( auto av : v ) {
        avs.push_back( boost::lexical_cast<std::string>(*av) ) ;
      }
      values.push_back( avs ) ;
    }
  }

  void Statistic::getValues( const pugi::xml_document& cfg,
      std::list<std::list<std::pair<std::string, std::string> > >& values ) const {
    std::list<std::list<std::pair< std::string, std::shared_ptr<mcommon::Value> > > > vs ;
    multiListWHeadersGet(cfg, vs) ;
    for( auto v : vs ) {
      std::list<std::pair<std::string, std::string> > avs ;
      for( auto av : v ) {
        avs.push_back( std::make_pair(
              av.first, boost::lexical_cast<std::string>(*(av.second)) ) ) ;
      }
      values.push_back( avs ) ;
    }
  }

}

