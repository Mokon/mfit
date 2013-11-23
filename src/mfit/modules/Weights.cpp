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

    WeightRepSet dumbbellChestPressFlat = Weights::getDumbbellChestPressFlat( cfg ) ;
    WeightRepSet dumbbellChestPressFlatBrzcki = dumbbellChestPressFlat.convert(1, Brzcki);
    WeightRepSet dumbbellChestPressFlatBaechle = dumbbellChestPressFlat.convert(1, Baechle);
    WeightRepSet dumbbellChestPressFlatDosRemedios = dumbbellChestPressFlat.convert(1, DosRemedios);

    out << "\tDumbbell Chest Press Flat " << dumbbellChestPressFlat << std::endl
      << "\tDumbbell Chest Press Flat 1 Rep Max Brzcki Model " 
      << dumbbellChestPressFlatBrzcki << std::endl
      << "\tDumbbell Chest Press Flat 1 Rep Max Baechle Model " 
      << dumbbellChestPressFlatBaechle << std::endl
      << "\tDumbbell Chest Press Flat 1 Rep Max DosRemedios Model " 
      << dumbbellChestPressFlatDosRemedios << std::endl ;
  }

  const std::string Weights::key = "mfit::Weights" ;

  WeightRepSet Weights::getDumbbellChestPressFlat(
      const pugi::xml_document& cfg ) {
    return WeightRepSet(
        Engine::getNodeAsQuantity( cfg,
          "/person/excercises/weights/flatchestpress[@type='dumbbell']/weight", LBS ),
        Engine::getNodeAsFloat( cfg,
          "/person/excercises/weights/flatchestpress[@type='dumbbell']/sets" ),
        Engine::getNodeAsFloat( cfg,
          "/person/excercises/weights/flatchestpress[@type='dumbbell']/reps"
          ) ) ;
  }

}

