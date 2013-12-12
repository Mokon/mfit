/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include <functional>
#include <list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <pugixml.hpp>

#include "mcommon/Value.hpp"

namespace mfit {

  class Statistic {

    public:

      typedef std::function<std::shared_ptr<mcommon::Value> (
          const pugi::xml_document& cfg )> ValueGetter ;

      typedef std::function<void ( const pugi::xml_document& cfg,
          std::list<std::shared_ptr<mcommon::Value> >& values )>
          MultiValueGetter ;

      typedef std::function<void ( const pugi::xml_document& cfg,
          std::list<std::pair<std::shared_ptr<mcommon::Value>,
                              std::shared_ptr<mcommon::Value> > >& values )>
          MultiPairValueGetter ;

      typedef std::function<void ( const pugi::xml_document& cfg,
          std::list<std::list<std::shared_ptr<mcommon::Value> > >& values )>
          MultiListValueGetter ;

      typedef std::function<void ( const pugi::xml_document& cfg,
          std::list<std::list<std::pair<std::string, std::shared_ptr<mcommon::Value> > > >& values )>
          MultiListWHeadersValueGetter ;

      Statistic( std::string header, ValueGetter get ) ;

      Statistic( std::string header, MultiValueGetter get ) ;

      Statistic( std::string header, std::string header2,
          MultiPairValueGetter get ) ;

      Statistic( std::vector<std::string> headers, MultiListValueGetter get ) ;
      
      Statistic( MultiListWHeadersValueGetter get ) ;

      virtual ~Statistic( ) = default ;

      Statistic( const Statistic& ) = default ;

      Statistic& operator=( const Statistic& ) = default ;

      std::string getHeader( ) const ;

      std::string getHeader( int i ) const ;

      std::string getValue( const pugi::xml_document& cfg ) const ;

      void getValues( const pugi::xml_document& cfg,
        std::list<std::string>& values ) const ;

      void getValues( const pugi::xml_document& cfg,
        std::list<std::pair<std::string, std::string> >& values ) const ;

      void getValues( const pugi::xml_document& cfg,
        std::list<std::list<std::string> >& values ) const ;
      
      void getValues( const pugi::xml_document& cfg,
        std::list<std::list<std::pair<std::string, std::string> > >& values ) const ;

      bool isMulti( ) ;

      bool isMultiPair( ) ;

      bool isMultiList( ) ;

      bool isMultiListWHeaders( ) ;

    protected:

      std::vector<std::string> headers ;

      ValueGetter get ;

      MultiValueGetter multiGet ;

      MultiPairValueGetter multiPairGet ;

      MultiListValueGetter multiListGet ;
      
      MultiListWHeadersValueGetter multiListWHeadersGet ;

  } ;

}

