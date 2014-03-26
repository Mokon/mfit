/* Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"
#include "mcommon/Gender.hpp"

#include "mfit/Module.hpp"

namespace mfit {

  class General : public Module {

    public:

      General( ) ;

      virtual ~General( ) = default ;

      General( const General& ) = delete ;

      General& operator=( const General& ) = delete ;

      virtual std::string getKey( ) ;

      virtual void process( std::ostream& out,
          const pugi::xml_document& cfg ) const ;

      static const std::string key ;

      static mcommon::Gender getGender( const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> avg(
          std::shared_ptr<mcommon::Quantity> a,
          std::shared_ptr<mcommon::Quantity> b ) ;

      static std::shared_ptr<mcommon::Quantity> getIdealBodyWeightBrocaIndex(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getIdealBodyWeightDevine(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getIdealBodyWeightRobinson(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getIdealBodyWeightMiller(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getAge(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBMI(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getBMITrefethen(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getLBPMPotentialBuiltLean(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getShreadedWeightLeanGains(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<mcommon::Quantity> getLBPMPotentialFrameSizeModel(
          const pugi::xml_document& cfg ) ;

  } ;

}

