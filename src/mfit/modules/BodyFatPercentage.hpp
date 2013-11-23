/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include <pugixml.hpp>

#include "mcommon/Quantity.hpp"

#include "mfit/Module.hpp"

namespace mfit {

  class BodyFatPercentage : public Module {

    public:

      BodyFatPercentage( ) = default ;

      virtual ~BodyFatPercentage( ) = default ;

      BodyFatPercentage( const BodyFatPercentage& ) = delete ;

      BodyFatPercentage& operator=( const BodyFatPercentage& ) = delete ;

      virtual std::string getKey( ) ;

      virtual void process( std::ostream& out,
          const pugi::xml_document& cfg ) const ;

      static const std::string key ;

      static mcommon::Quantity getTicepsSkinfold( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getChestSkinfold( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getMidaxillarySkinfold( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getSubscapularSkinfold( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getSuprailiacSkinfold( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getAbdominalSkinfold( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getThighSkinfold( const pugi::xml_document& cfg ) ;

      static mcommon::Quantity getSuprailumSkinfold( const pugi::xml_document& cfg ) ;

    private:

      static std::string bfpToClassification( const float bfp,
          const pugi::xml_document& cfg ) ;

      static float bfp3Site( const pugi::xml_document& cfg ) ;
      
      static float bfp7Site( const pugi::xml_document& cfg ) ;

      static float bfpHeritageBMI( const pugi::xml_document& cfg ) ;

      static float bfpConvertBailey( const pugi::xml_document& cfg ) ;

      static float bfpHodgdonBeckett( const pugi::xml_document& cfg ) ;

      static float bfpUSNavy( const pugi::xml_document& cfg ) ;

      static float bfpUSMarines( const pugi::xml_document& cfg ) ;

      static float bfpYMCA( const pugi::xml_document& cfg ) ;

      static float bfpYMCAModified( const pugi::xml_document& cfg ) ;

  } ;

}

