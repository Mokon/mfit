/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"
#include "mcommon/Gender.hpp"

#include "mfit/Module.hpp"

namespace mfit {

  class General : public Module {

    public:

      General( ) = default ;

      virtual ~General( ) = default ;

      General( const General& ) = delete ;

      General& operator=( const General& ) = delete ;

      virtual std::string getKey( ) ;

      virtual void process( std::ostream& out,
          const pugi::xml_document& cfg ) const ;

      static const std::string key ;
  
      static void greekIdeal( std::ostream& out, const pugi::xml_document& cfg ) ;

      static mcommon::Quantity idealBodyWeightBrocaIndex( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity idealBodyWeightDevine( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity idealBodyWeightRobinson( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity idealBodyWeightMiller( const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> avg(
          std::shared_ptr<mcommon::Quantity> a, std::shared_ptr<mcommon::Quantity> b ) ;

      static mcommon::Gender getGender( const pugi::xml_document& cfg ) ;
      
      static mcommon::Quantity getAge( const pugi::xml_document& cfg ) ;

    private:

      static mcommon::Quantity bmrHarrisBenedict(
          const pugi::xml_document& cfg ) ;

      static mcommon::Quantity bmrRozaShizgal( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity metsToCalories( const mcommon::Quantity mets,
          const mcommon::Quantity time, const pugi::xml_document& cfg ) ;

      static float bmi( const pugi::xml_document& cfg ) ;

  } ;

}

