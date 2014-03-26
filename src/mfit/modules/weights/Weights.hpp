/* Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include "mcommon/Quantity.hpp"

#include "mfit/Module.hpp"
#include "mfit/Statistic.hpp"
#include "mfit/modules/weights/Weight.hpp"
#include "mfit/modules/weights/WeightRepSet.hpp"

namespace mfit {

  class Weights : public Module {

    public:

      Weights( ) ;

      virtual ~Weights( ) = default ;

      Weights( const Weights& ) = delete ;

      Weights& operator=( const Weights& ) = delete ;

      virtual std::string getKey( ) ;

      static const std::string key ;
  
      void process( std::ostream& out, const pugi::xml_document& cfg ) const ;
  
      static std::shared_ptr<mcommon::Quantity> getMaxBench(
          const pugi::xml_document& cfg ) ;

      static std::shared_ptr<WeightRepSet> getNodeAsWeightRepSet(
          const pugi::xml_document& cfg, const std::string xpath ) ;
  
      static std::shared_ptr<mcommon::Quantity> getStrengthLevel(
        const pugi::xml_document& cfg ) ;

      static void getWeights( const pugi::xml_document& cfg,
          std::list<std::list<std::pair<std::string, std::shared_ptr<mcommon::Value> > > >& values ) ;

    private:

      const static std::map<const std::string, Weight> weightTypes ;

  } ;

}

