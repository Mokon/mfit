/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <stdexcept>

#include "mfit/modules/Weights.hpp"
#include "mfit/Engine.hpp"

using namespace mcommon ;

namespace mfit {

  std::string Weights::getKey( ) {
    return key ;
  }

  void Weights::process( std::ostream& out,
      const pugi::xml_document& cfg ) const {
    out << "Weight Lifting" << std::endl ;

      processWeightLift (out, cfg, "Dumbbell Chest Press Flat",
          &Weights::getDumbbellChestPressFlat ) ;
      processWeightLift (out, cfg, "Machine Incline Chest Press Flat",
          &Weights::getMachineInclineChestPress ) ;
      processWeightLift (out, cfg, "Dumbbell Bicep Curls",
          &Weights::getDumbbellBicepCurls ) ;
      processWeightLift (out, cfg, "Machine Fly",
          &Weights::getMachineFly ) ;
      processWeightLift (out, cfg, "Machine Bicep Curls",
          &Weights::getMachineBicepCurls ) ;
      processWeightLift (out, cfg, "Machine Ticep Press",
          &Weights::getMachineTricepPress ) ;
      processWeightLift (out, cfg, "Machine Pulldown",
          &Weights::getMachinePulldown ) ;
      processWeightLift (out, cfg, "Machine Row",
          &Weights::getMachineRow ) ;
      processWeightLift (out, cfg, "Machine Abdominal",
          &Weights::getMachineAbdominal ) ;
      processWeightLift (out, cfg, "Machine Seated Leg Press",
          &Weights::getMachineSeatedLegPress ) ;
      processWeightLift (out, cfg, "Machine Back Extensions",
          &Weights::getMachineBackExtensions ) ;
      processWeightLift (out, cfg, "Machine Calf Extensions",
          &Weights::getMachineCalfExtensions ) ;
  }

  void Weights::processWeightLift( std::ostream& out,
      const pugi::xml_document& cfg, const std::string weightLiftName,
      WeightRepSet (*getWeightLift)( const pugi::xml_document& cfg ) ) {
    WeightRepSet weightLift = getWeightLift( cfg ) ;
    WeightRepSet weightLiftBrzcki = weightLift.convert(1, Brzcki) ;
    WeightRepSet weightLiftBaechle = weightLift.convert(1, Baechle) ;
    WeightRepSet weightLiftDosRemedios = weightLift.convert(1, DosRemedios) ;
#define CLREOL $'\x1B[K'
#define THDR "[38;5;203m"
#define TRESET "[0m"
#define TVALUE "[0;37;44m"
    out << "\t" << THDR<< weightLiftName << " " << TVALUE << weightLift << TRESET 
      << "\t\t" << " 1 Rep Max Brzcki Model " 
      << weightLiftBrzcki << std::endl
      << "\t\t" << " 1 Rep Max Baechle Model " 
      << weightLiftBaechle << std::endl
      << "\t\t" << " 1 Rep Max DosRemedios Model " 
      << weightLiftDosRemedios << std::endl ;
  }

  const std::string Weights::key = "mfit::Weights" ;
  
  WeightRepSet Weights::getNodeAsWeightRepSet(
      const pugi::xml_document& cfg, const std::string xpath ) {
    return WeightRepSet(
        Engine::getNodeAsQuantity( cfg, xpath + "/weight", LBS ),
        Engine::getNodeAsFloat( cfg, xpath + "/sets" ),
        Engine::getNodeAsFloat( cfg, xpath + "/reps" ) ) ;
  }

  WeightRepSet Weights::getDumbbellChestPressFlat(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg, 
        "/person/excercises/weights/flatchestpress[@type='dumbbell']" ) ;
  }

  WeightRepSet Weights::getMachineFly(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg, 
        "/person/excercises/weights/fly[@type='machine']" ) ;
  }

  WeightRepSet Weights::getMachineInclineChestPress(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg, 
        "/person/excercises/weights/inclinechestpress[@type='machine']" ) ;
  }

  WeightRepSet Weights::getDumbbellBicepCurls(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg, 
        "/person/excercises/weights/bicepcurls[@type='dumbbell']" ) ;
  }

  WeightRepSet Weights::getMachineBicepCurls(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg, 
        "/person/excercises/weights/bicepcurls[@type='machine']" ) ;
  }

  WeightRepSet Weights::getMachineTricepPress(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg, 
        "/person/excercises/weights/triceppress[@type='machine']" ) ;
  }

  WeightRepSet Weights::getMachinePulldown(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg, 
        "/person/excercises/weights/pulldown[@type='machine']" ) ;
  }

  WeightRepSet Weights::getMachineRow(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg, 
        "/person/excercises/weights/row[@type='machine']" ) ;
  }

  WeightRepSet Weights::getMachineAbdominal(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg, 
        "/person/excercises/weights/abdominal[@type='machine']" ) ;
  }

  WeightRepSet Weights::getMachineSeatedLegPress(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg, 
        "/person/excercises/weights/seatedlegpress[@type='machine']" ) ;
  }

  WeightRepSet Weights::getMachineBackExtensions(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg, 
        "/person/excercises/weights/backextensions[@type='machine']" ) ;
  }

  WeightRepSet Weights::getMachineCalfExtensions(
      const pugi::xml_document& cfg ) {
    return getNodeAsWeightRepSet( cfg, 
        "/person/excercises/weights/calfextensions[@type='machine']" ) ;
  }

}

