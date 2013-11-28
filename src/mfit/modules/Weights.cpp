/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <memory>
#include <stdexcept>

#include "mfit/modules/Weights.hpp"
#include "mfit/Engine.hpp"

using namespace mcommon ;

namespace mfit {

  Weights::Weights( ) {
    addWeight( "Dumbbell Chest Press Flat", getDumbbellChestPressFlat ) ;
    addWeight( "Machine Incline Chest Press Flat", getMachineInclineChestPress ) ;
    addWeight( "Dumbbell Bicep Curls", getDumbbellBicepCurls ) ;
    addWeight( "Machine Fly", getMachineFly ) ;
    addWeight( "Machine Bicep Curls", getMachineBicepCurls ) ;
    addWeight( "Machine Ticep Press", getMachineTricepPress ) ;
    addWeight( "Machine Pulldown", getMachinePulldown ) ;
    addWeight( "Machine Row", getMachineRow ) ;
    addWeight( "Machine Abdominal", getMachineAbdominal ) ;
    addWeight( "Machine Seated Leg Press", getMachineSeatedLegPress ) ;
    addWeight( "Machine Back Extensions", getMachineBackExtensions ) ;
    addWeight( "Machine Calf Extensions", getMachineCalfExtensions ) ;
    addWeight( "Machine Shoulder Press", getMachineShoulderPress ) ;
    addWeight( "Dumbbell Shrugs", getDumbbellShrugs ) ;
  }

  std::string Weights::getKey( ) {
    return key ;
  }

  const std::string Weights::key = "mfit::Weights" ;

  void Weights::addWeight( std::string hdr, Statistic::ValueGetter get ) {
    /* TODO create the concept of a sub stat so we can get html correct */
    add( hdr, get ) ;
    add( "\t1 Rep Max Brzcki Model",  getModelFunc( get, Brzcki ) ) ;
    add( "\t1 Rep Max Baechle Model",  getModelFunc( get, Baechle ) ) ;
    add( "\t1 Rep Max DosRemedios Model",  getModelFunc( get, DosRemedios ) ) ;
  }

  Statistic::ValueGetter Weights::getModelFunc( Statistic::ValueGetter get,
      OneRepMaxModel model ) {
    return [get, model]( const pugi::xml_document& cfg )
      -> std::shared_ptr<mcommon::Value> {
        return getModel( get, cfg, model ) ;
      } ;
  }

  std::shared_ptr<WeightRepSet> Weights::getModel( Statistic::ValueGetter get,
      const pugi::xml_document& cfg, OneRepMaxModel model  ) {
    return std::shared_ptr<WeightRepSet>(
        new WeightRepSet( std::dynamic_pointer_cast<WeightRepSet>(
            get( cfg ) )->convert(1, model) ) ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getNodeAsWeightRepSet(
      const pugi::xml_document& cfg, const std::string xpath ) {
    return std::shared_ptr<WeightRepSet>( new WeightRepSet (
          *Engine::getNodeAsQuantity( cfg, xpath + "/weight" ),
          Engine::getNodeAs<float>( cfg, xpath + "/sets" ),
          Engine::getNodeAs<float>( cfg, xpath + "/reps" ) ) ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getDumbbellChestPressFlat(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg,
        "/person/excercises/weights/flatchestpress[@type='dumbbell']" ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getMachineFly(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg,
        "/person/excercises/weights/fly[@type='machine']" ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getMachineInclineChestPress(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg,
        "/person/excercises/weights/inclinechestpress[@type='machine']" ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getDumbbellBicepCurls(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg,
        "/person/excercises/weights/bicepcurls[@type='dumbbell']" ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getMachineBicepCurls(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg,
        "/person/excercises/weights/bicepcurls[@type='machine']" ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getMachineTricepPress(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg,
        "/person/excercises/weights/triceppress[@type='machine']" ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getMachinePulldown(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg,
        "/person/excercises/weights/pulldown[@type='machine']" ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getMachineRow(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg,
        "/person/excercises/weights/row[@type='machine']" ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getMachineAbdominal(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg,
        "/person/excercises/weights/abdominal[@type='machine']" ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getMachineSeatedLegPress(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg,
        "/person/excercises/weights/seatedlegpress[@type='machine']" ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getMachineBackExtensions(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg,
        "/person/excercises/weights/backextensions[@type='machine']" ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getMachineCalfExtensions(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg,
        "/person/excercises/weights/calfextensions[@type='machine']" ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getDumbbellShrugs(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg,
        "/person/excercises/weights/shrugs[@type='dumbbell']" ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getMachineShoulderPress(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg,
        "/person/excercises/weights/shoulderpress[@type='machine']" ) ;
  }


}

