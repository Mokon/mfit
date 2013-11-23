/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"

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

      static mcommon::Quantity avg( mcommon::Quantity a, mcommon::Quantity b ) ;

      static mcommon::Gender getGender( const pugi::xml_document& cfg ) ;
      
      static mcommon::Quantity getAge( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getWeight( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getHeight( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getNeck( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getWaist( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getHips( const pugi::xml_document& cfg ) ;
      
      static mcommon::Quantity getThigh( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getThighLeft( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getThighRight( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getForearm( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getForearmLeft( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getForearmRight( const pugi::xml_document& cfg ) ;
      
      static mcommon::Quantity getWrist( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getWristLeft( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getWristRight( const pugi::xml_document& cfg ) ;
      
      static mcommon::Quantity getCalf( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getCalfLeft( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getCalfRight( const pugi::xml_document& cfg ) ;
      
      static mcommon::Quantity getBicepFlexedRight( const pugi::xml_document& cfg ) ;
      
      static mcommon::Quantity getBicepFlexedLeft( const pugi::xml_document& cfg ) ;

    private:

      static mcommon::Quantity bmrHarrisBenedict(
          const pugi::xml_document& cfg ) ;

      static mcommon::Quantity bmrRozaShizgal( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity metsToCalories( const mcommon::Quantity mets,
          const mcommon::Quantity time, const pugi::xml_document& cfg ) ;

      static float bmi( const pugi::xml_document& cfg ) ;

  } ;

}

