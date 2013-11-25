/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"

#include "mfit/Module.hpp"
#include "mfit/modules/WeightRepSet.hpp"

namespace mfit {

  class Weights : public Module {

    public:

      Weights( ) = default ;

      virtual ~Weights( ) = default ;

      Weights( const Weights& ) = delete ;

      Weights& operator=( const Weights& ) = delete ;

      virtual std::string getKey( ) ;

      virtual void process( std::ostream& out,
          const pugi::xml_document& cfg ) const ;

      static const std::string key ;

      static WeightRepSet getDumbbellChestPressFlat(
          const pugi::xml_document& cfg ) ;

      static WeightRepSet getMachineFly( const pugi::xml_document& cfg ) ;

      static WeightRepSet getMachineInclineChestPress(
          const pugi::xml_document& cfg ) ;

      static WeightRepSet getDumbbellBicepCurls( const pugi::xml_document& cfg ) ;

      static WeightRepSet getNodeAsWeightRepSet( const pugi::xml_document& cfg, const std::string xpath ) ;

      static WeightRepSet getMachineBicepCurls( const pugi::xml_document& cfg ) ;

      static WeightRepSet getMachineTricepPress( const pugi::xml_document& cfg ) ;

      static WeightRepSet getMachinePulldown( const pugi::xml_document& cfg ) ;

      static WeightRepSet getMachineRow( const pugi::xml_document& cfg ) ;

      static WeightRepSet getMachineAbdominal( const pugi::xml_document& cfg ) ;

      static WeightRepSet getMachineSeatedLegPress( const pugi::xml_document& cfg ) ;

      static WeightRepSet getMachineBackExtensions( const pugi::xml_document& cfg ) ;

      static WeightRepSet getMachineCalfExtensions( const pugi::xml_document& cfg ) ;

    private:

      static void processWeightLift( std::ostream& out,
          const pugi::xml_document& cfg, const std::string weightLiftName,
          WeightRepSet (*getWeightLift)( const pugi::xml_document& cfg ) ) ;

  } ;

}

