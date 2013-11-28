/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <cmath>

#include "mcommon/Gender.hpp"

#include "mfit/modules/Calories.hpp"
#include "mfit/modules/General.hpp"
#include "mfit/modules/Measurements.hpp"
#include "mfit/Engine.hpp"
#include "mfit/Statistic.hpp"

using namespace mcommon ;

namespace mfit {

  const std::string Calories::key = "mfit::Calories" ;

  Calories::Calories( ) {
    addBMR( "Your Harris Benedict BMR is", getBMRHarrisBenedict ) ;
    addBMR( "Your Roza Shizgal BMR is", getBMRRozaShizgal ) ;
  }

  std::string Calories::getKey( ) {
    return key ;
  }

  const float Calories::bmrMultipliers[ACTIVITY_LEVEL_MAX]
    = { 1.2, 1.375, 1.55, 1.725, 1.9 } ;

  void Calories::addBMR( std::string hdr, Statistic::ValueGetter get ) {
    add( hdr, get ) ;
    add( "\tThis means your maintenance caloric intake if you are sedentary (little or no exercise) is",
        getModelFunc( get, Sedentary ) ) ;
    add( "\tAnd if you are lightly active (light exercise/sports 1-3 days/week) is",
        getModelFunc( get, LightlyActive ) ) ;
    add( "\tAnd if you are moderatetely active (moderate exercise/sports 3-5 days/week) is",
        getModelFunc( get, ModeratelyActive ) ) ;
    add( "\tAnd if you are very active (hard exercise/sports 6-7 days a week) is",
        getModelFunc( get, VeryActive ) ) ;
    add( "\tAnd if you are extra active (very hard exercise/sports & physical job or 2x training) is",
        getModelFunc( get,  ExtraActive ) ) ;
  }

  Statistic::ValueGetter Calories::getModelFunc( Statistic::ValueGetter get,
      ActivityLevel model ) {
    return [get, model]( const pugi::xml_document& cfg )
      -> std::shared_ptr<mcommon::Value> {
        return getModel( get, cfg, model ) ;
      } ;
  }

  std::shared_ptr<Quantity> Calories::getModel( Statistic::ValueGetter get,
      const pugi::xml_document& cfg, ActivityLevel model ) {
    return std::shared_ptr<Quantity>(
        new Quantity( *std::dynamic_pointer_cast<Quantity>(
            get( cfg ) ) * bmrMultipliers[model] ) ) ;
  }

  std::shared_ptr<Quantity> Calories::getBMRRozaShizgal(
      const pugi::xml_document& cfg ) {
    Quantity weight = Measurements::getWeight( cfg )->convert(KG) ;
    Quantity height = Measurements::getHeight( cfg )->convert(CM) ;
    Quantity age = General::getAge( cfg )->convert(YEARS) ;
    Gender gender = General::getGender( cfg ) ;

    float cals ;
    switch ( gender ) {
      case Male:
        cals = (weight.magnitude()*13.397)+(height.magnitude()*4.799)
          - (age.magnitude()*5.677) + 88.362;
        break ;
      default:
        cals = (weight.magnitude()*9.247) + (height.magnitude()*4.799)
          - (age.magnitude()*4.330) + 447.593;
        break ;
    }

    return std::shared_ptr<Quantity>( new Quantity( cals, CALORIES ) ) ;
  }

  std::shared_ptr<Quantity> Calories::getBMRHarrisBenedict(
      const pugi::xml_document& cfg ) {
    Quantity weight = Measurements::getWeight( cfg )->convert(KG) ;
    Quantity height = Measurements::getHeight( cfg )->convert(CM) ;
    Quantity age = General::getAge( cfg )->convert(YEARS) ;
    Gender gender = General::getGender( cfg ) ;

    float cals ;
    switch ( gender ) {
      case Male:
        cals = (weight.magnitude()*13.7516)+(height.magnitude()*5.0033)
          - (age.magnitude()*6.755) + 66.4730;
        break ;
      default:
        cals = (weight.magnitude()*9.5634) + (height.magnitude()*1.8496)
          - (age.magnitude()*4.6756) + 655.0955;
        break ;
    }

    return std::shared_ptr<Quantity>( new Quantity( cals, CALORIES ) ) ;
  }

  std::shared_ptr<Quantity> Calories::metsToCalories(
      std::shared_ptr<Quantity> mets, std::shared_ptr<Quantity> time,
      const pugi::xml_document& cfg ) {
    Quantity weight = Measurements::getWeight( cfg )->convert(KG) ;
    Quantity ret = Quantity( mets->magnitude()*weight.magnitude()*
        time->convert(SECONDS).magnitude(), CALORIES ) ;
    return std::shared_ptr<Quantity>( new Quantity(ret) ) ;
  }

}

