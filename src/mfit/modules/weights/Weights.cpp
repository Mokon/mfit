/* Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved */

#include <memory>
#include <stdexcept>

#include "mcommon/Log.hpp"

#include "mfit/modules/weights/Weights.hpp"
#include "mfit/modules/Measurements.hpp"
#include "mfit/Engine.hpp"

using namespace mcommon ;

namespace mfit {

  /* TODO make this dynamically populated from a xml file. */
  const std::map<const std::string, Weight> Weights::weightTypes {
    /* name, key, type, equipment, varient, factor */
    /* Free Weights */
    { "Dead Lift", { "deadlift", "freeweights", "", "", 1.0, true } },
      { "Back Squat", { "squat", "freeweights", "", "back", 0.714, true } },
      { "Bench Press", { "benchpress", "freeweights", "barbell", "flat", 0.556, true } },
      { "Smith Machine Bench Press", { "smithmachinebenchpress", "freeweights", "smithmachine", "flat", 0.556*(1.0-0.16), true } },
      { "Pull Up", { "pullup", "freeweights", "", "", 0.556, false } },
      { "Front Squat", { "squat", "freeweights", "", "front", 0.5, false } },
      { "Close Grip Bench Press", { "benchpress", "freeweights", "barbell", "closegrip", 0.5, false } },
      { "Hang Clean", { "hangclean", "freeweights", "", "", 0.45, false } },
      { "Dumbbell Flat Chest Press", { "chestpress", "freeweights", "dumbbell", "flat", 0.43, true } },
      { "One Arm Row", { "onearmrow", "freeweights", "", "", 0.43, false } },
      { "Push Press", { "pushpress", "freeweights", "", "", 0.4, false } },
      { "Jerk", { "jerk", "freeweights", "", "", 0.4, false } },
      { "Dumbbell Incline Chest Press", { "chestpress", "freeweights", "dumbbell", "incline", 0.4, true } },
      { "Dumbbell Overhead Press", { "overheadpress", "freeweights", "dumbbell", "", 0.325, true } },
      { "Hammer Curl", { "curl", "freeweights", "dumbbell", "hammer", 0.315, false } },
      { "Dumbbel Curl", { "curl", "freeweights", "dumbbell", "standing", 0.3, true } },
      { "Barbell Curl", { "curl", "freeweights", "barbell", "", 0.3, true } },
      { "Dumbbell Overhead Ticep Extension", { "overheadticepextension", "freeweights", "dumbbell", "", 0.3, true } },
      { "Bulgarian Squat", { "squat", "freeweights", "", "bulgarian", 0.275, false } },
      { "Lunge", { "lunge", "freeweights", "", "", 0.25, false } },
      { "Split Squat", { "squat", "freeweights", "", "split", 0.25, false } },
      { "Press Down", { "pressdown", "freeweights", "", "", 0.25, false } },
      { "Ez Bar Skull Crusher", { "skullcrusher", "freeweights", "ezbar", "", 0.24, true } },
      { "Dumbbell Skull Crusher", { "skullcrusher", "freeweights", "dumbbell", "", 0.22, false } },
      { "Preacher Curl", { "curl", "freeweights", "", "preacher", 0.22, false } },
      { "Concentration Curl", { "curl", "freeweights", "dumbbell", "concentration", 0.22/2.0, true } },
      { "Seated Calf Raise", { "seatedcalfraise", "freeweights", "", "", 0.2, false } },
      { "Pec Fly", { "pecfly", "freeweights", "", "", 0.2, false } },
      { "Single Leg Romanian Deadlift", { "singlelegromaniandeadlift", "freeweights", "", "", 0.13, false } },
      { "Standing Calf Raise", { "standingcalfraise", "freeweights", "", "", 0.13, false } },
      { "Dumbbell Shrugs", { "shrugs", "freeweights", "dumbbell", "", 0.0, false } },
      /* Machines */
      { "Machine Fly", { "fly", "machine", "", "", 0.0, false } },
      { "Machine Bicep Curls", { "curl", "machine", "", "", 0.0, false } },
      { "Machine Ticep Press", { "triceppress", "machine", "", "", 0.0, false } },
      { "Machine Pulldown", { "pulldown", "machine", "", "", 0.0, false } },
      { "Machine Row", { "row", "machine", "", "", 0.0, false } },
      { "Machine Abdominal", { "/abdominal", "machine", "", "", 0.0, false } },
      { "Machine Seated Leg Press", { "seatedlegpress", "machine", "", "", 0.0, false } },
      { "Machine Back Extensions", { "backextensions", "machine", "", "", 0.0, false } },
      { "Machine Calf Extensions", { "calfextensions", "machine", "", "", 0.0, false } },
      { "Machine Shoulder Press", { "shoulderpress", "machine", "", "", 0.0, false } },
      { "Machine Incline Bench Press", { "benchpress", "machine", "", "incline", 0.0, false } },
  } ;

  Weights::Weights( ) {
    add( getWeights ) ;

    add( "Your maximum bench press possible might be ", getMaxBench ) ;
    add( "Your strength level is", getStrengthLevel ) ;
  }

  void Weights::process( std::ostream& out,
      const pugi::xml_document& cfg ) const {
    boost::ignore_unused_variable_warning( cfg ) ;

    engine->print( out, "Here are some stats based on your weight lifting. "
        "This includes 1 rep max predictions and balance body lifting "
        "predictions." ) ;
  }

  std::string Weights::getKey( ) {
    return key ;
  }

  const std::string Weights::key = "mfit::Weights" ;
  
  std::shared_ptr<Quantity> Weights::getStrengthLevel(
      const pugi::xml_document& cfg ) {
    Quantity weight = Measurements::getWeight( cfg )->convert( LBS ) ;

    return std::shared_ptr<Quantity>( new Quantity(weight) ) ;
  }

  std::shared_ptr<WeightRepSet> Weights::getNodeAsWeightRepSet(
      const pugi::xml_document& cfg, const std::string xpath ) {
    return std::shared_ptr<WeightRepSet>( new WeightRepSet (
          *Engine::getNodeAsQuantity( cfg, xpath + "/weight" ),
          Engine::getNodeAs<float>( cfg, xpath + "/sets" ),
          Engine::getNodeAs<float>( cfg, xpath + "/reps" ) ) ) ;
  }
  
  std::shared_ptr<Quantity> Weights::getMaxBench(
      const pugi::xml_document& cfg ) {
    float weight = Measurements::getWeight( cfg )->convert(LBS).magnitude() ;

    float ret = 2.6536e-5*pow(weight,3) - 0.02590*pow(weight,2) + 8.7356*weight - 439.90 ;

    return std::shared_ptr<Quantity>( new Quantity( ret, LBS ) ) ;
  }

  void Weights::getWeights( const pugi::xml_document& cfg,
      std::list<std::list<std::pair<std::string, std::shared_ptr<mcommon::Value> > > >& values ) {
    (void) cfg ;
    std::vector<std::string> headers ;
    for( auto w : weightTypes ) {
      try {
        std::list<std::pair<std::string, std::shared_ptr<Value> > > avalues ;

        std::shared_ptr<WeightRepSet> n( getNodeAsWeightRepSet( cfg,
              w.second.getXPath( ) ) ) ;
        avalues.push_back( std::make_pair(
              "For your " +  w.first + " you can lift: ", n ) ) ;

        std::function<void ( OneRepMaxModel model )> handle =
          [&cfg, &w, &n, &avalues]( OneRepMaxModel model ) -> void {
            std::string ms = WeightRepSet::oneRepMaxModelString[model] ;
            avalues.push_back( std::make_pair(
                  "therefore according to the " + ms + " model your 1 rep max is ",
                  std::shared_ptr<mcommon::Value>( new WeightRepSet (
                      n->convert(1, model ) ) ) ) ) ;
            if( w.second.getFactor( ) != 0 ) {
              for( auto cw : weightTypes ) {
                try {
                  if( cw.second.getFactor( ) == 0 ) {
                    continue ;
                  }
                  float cFactor = w.second.getFactor( ) / cw.second.getFactor( ) ;

                  if( cw.second.isMajor( ) ) {
                    std::shared_ptr<mcommon::Value> m1rm( new WeightRepSet (
                          n->convert(1, model )*(1/cFactor) ) ) ;

                    avalues.push_back( std::make_pair(
                          "according to this and the " + ms +
                          " model your " + cw.first + " 1 rep max lift should be around",
                          m1rm ) ) ;

                    std::shared_ptr<mcommon::Value> mnrm( new WeightRepSet (
                          n->convert(n->getReps( ), model )*(1/cFactor) ) ) ;

                    avalues.push_back( std::make_pair(
                          "according to this and the " + ms +
                          " model your " + cw.first + " N rep max lift should be around",
                          mnrm ) ) ;
                  }

                  if( cFactor == 1 ) {
                    continue ;
                  }

                  std::shared_ptr<WeightRepSet> cn( getNodeAsWeightRepSet( cfg,
                        cw.second.getXPath( ) ) ) ;

                  std::shared_ptr<mcommon::Value> c1rm( new WeightRepSet (
                        cn->convert(1, model )*cFactor ) ) ;

                  avalues.push_back( std::make_pair(
                        "according to your " + cw.first + " and the " +
                        ms + " model your 1 rep max lift should be around",
                        c1rm ) ) ;

                  std::shared_ptr<mcommon::Value> cnrm( new WeightRepSet (
                        cn->convert(n->getReps( ), model )*cFactor ) ) ;

                  avalues.push_back( std::make_pair(
                        "according to your " + cw.first + " and the " +
                        ms + " model your N rep max lift should be around",
                        cnrm ) ) ;
                } catch( const std::exception& ex ) {
                  DLOG(INFO) << "Couldn't process a statistic with the given config: "
                    << ex.what() << std::endl ;
                }
              }
            }
          } ;

        handle( Average ) ;
        //handle( Brzcki ) ;
        //handle( Baechle ) ;
        //handle( DosRemedios ) ;

        values.push_back( avalues ) ;
      } catch( const std::exception& ex ) {
          DLOG(INFO) << "Couldn't process a statistic with the given config: "
          << ex.what() << std::endl ;
      }
    }
  }

}

