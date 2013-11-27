/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"

#include "mfit/Module.hpp"
#include "mfit/Statistic.hpp"
#include "mfit/modules/WeightRepSet.hpp"

namespace mfit {

  class Weights : public Module {

    public:

      Weights( ) ;

      virtual ~Weights( ) = default ;

      Weights( const Weights& ) = delete ;

      Weights& operator=( const Weights& ) = delete ;

      virtual std::string getKey( ) ;

      static const std::string key ;
  
      void addWeight( std::string hdr, Statistic::ValueGetter get ) ;

      static Statistic::ValueGetter getModelFunc( Statistic::ValueGetter get,
          OneRepMaxModel model ) ;

      static std::shared_ptr<WeightRepSet> getModel( Statistic::ValueGetter get,
          const pugi::xml_document& cfg, OneRepMaxModel model  ) ;

      static std::shared_ptr<WeightRepSet> getNodeAsWeightRepSet(
          const pugi::xml_document& cfg, const std::string xpath ) ;

      static std::shared_ptr<WeightRepSet> getDumbbellChestPressFlat(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<WeightRepSet> getMachineFly(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<WeightRepSet> getMachineInclineChestPress(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<WeightRepSet> getDumbbellBicepCurls(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<WeightRepSet> getMachineBicepCurls(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<WeightRepSet> getMachineTricepPress(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<WeightRepSet> getMachinePulldown(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<WeightRepSet> getMachineRow(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<WeightRepSet> getMachineAbdominal(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<WeightRepSet> getMachineSeatedLegPress(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<WeightRepSet> getMachineBackExtensions(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<WeightRepSet> getMachineCalfExtensions(
          const pugi::xml_document& cfg ) ;

  } ;

}

