/* Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved */

#include <memory>
#include <stdexcept>

#include "mcommon/Log.hpp"

#include "mfit/modules/weights/Weights.hpp"
#include "mfit/Engine.hpp"

using namespace mcommon ;

namespace mfit {

  const std::map<const std::string, Weight> Weights::weightTypes {
    /* name, key, type, equipment, varient, factor */
    { "Dead Lift", { "deadlift", "freeweights", "", "", 1.0 } },
      { "Back Squat", { "squat", "freeweights", "", "back", 0.714 } },
      { "Bench Press", { "benchpress", "freeweights", "barbell", "", 0.556 } },
      { "Pull Up", { "pullup", "freeweights", "", "", 0.556 } },
      { "Front Squat", { "squat", "freeweights", "", "front", 0.5 } },
      { "Close Grip Bench Press", { "benchpress", "freeweights", "barbell", "closegrip", 0.5 } },
      { "Hang Clean", { "hangclean", "freeweights", "", "", 0.45 } },
      { "Dumbbell Flat Chest Press", { "chestpress", "freeweights", "dumbbell", "flat", 0.43 } },
      { "One Arm Row", { "onearmrow", "freeweights", "", "", 0.43 } },
      { "Push Press", { "pushpress", "freeweights", "", "", 0.4 } },
      { "Jerk", { "jerk", "freeweights", "", "", 0.4 } },
      { "Dumbbell Incline Bench Press", { "benchpress", "freeweights", "dumbbell", "incline", 0.4 } },
      { "Dumbbell Overhead Press", { "overheadpress", "freeweights", "dumbbell", "", 0.325 } },
      { "Hammer Curl", { "curl", "freeweights", "dumbbell", "hammer", 0.315 } },
      { "Dumbbel Curl", { "curl", "freeweights", "dumbbell", "", 0.3 } },
      { "Barbell Curl", { "curl", "freeweights", "barbell", "", 0.3 } },
      { "Dumbbell Overhead Ticep Extension", { "overheadticepextension", "freeweights", "dumbbell", "", 0.3 } },
      { "Bulgarian Squat", { "squat", "freeweights", "", "bulgarian", 0.275 } },
      { "Lunge", { "lunge", "freeweights", "", "", 0.25 } },
      { "Split Squat", { "squat", "freeweights", "", "split", 0.25 } },
      { "Press Down", { "pressdown", "freeweights", "", "", 0.25 } },
      { "Ez Bar Skull Crusher", { "skullcrusher", "freeweights", "ezbar", "", 0.24 } },
      { "Dumbbell Skull Crusher", { "skullcrusher", "freeweights", "dumbbell", "", 0.22 } },
      { "Preacher Curl", { "curl", "freeweights", "", "preacher", 0.22 } },
      { "Concentration Curl", { "curl", "freeweights", "dumbbell", "concentration", 0.22/2.0 } },
      { "Seated Calf Raise", { "seatedcalfraise", "freeweights", "", "", 0.2 } },
      { "Pec Fly", { "pecfly", "freeweights", "", "", 0.2 } },
      { "Single Leg Romanian Deadlift", { "singlelegromaniandeadlift", "freeweights", "", "", 0.13 } },
      { "Standing Calf Raise", { "standingcalfraise", "freeweights", "", "", 0.13 } },
      { "Dumbbell Shrugs", { "shrugs", "freeweights", "dumbbell", "", 0.0 } },

      { "Machine Fly", { "fly", "machine", "", "", 0.0 } },
      { "Machine Bicep Curls", { "curl", "machine", "", "", 0.0 } },
      { "Machine Ticep Press", { "triceppress", "machine", "", "", 0.0 } },
      { "Machine Pulldown", { "pulldown", "machine", "", "", 0.0 } },
      { "Machine Row", { "row", "machine", "", "", 0.0 } },
      { "Machine Abdominal", { "/abdominal", "machine", "", "", 0.0 } },
      { "Machine Seated Leg Press", { "seatedlegpress", "machine", "", "", 0.0 } },
      { "Machine Back Extensions", { "backextensions", "machine", "", "", 0.0 } },
      { "Machine Calf Extensions", { "calfextensions", "machine", "", "", 0.0 } },
      { "Machine Shoulder Press", { "shoulderpress", "machine", "", "", 0.0 } },
      { "Machine Incline Bench Press", { "benchpress", "machine", "", "incline", 0.4 } },
  } ;

  Weights::Weights( ) {
    add( getWeights ) ;
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

  std::shared_ptr<WeightRepSet> Weights::getNodeAsWeightRepSet(
      const pugi::xml_document& cfg, const std::string xpath ) {
    return std::shared_ptr<WeightRepSet>( new WeightRepSet (
          *Engine::getNodeAsQuantity( cfg, xpath + "/weight" ),
          Engine::getNodeAs<float>( cfg, xpath + "/sets" ),
          Engine::getNodeAs<float>( cfg, xpath + "/reps" ) ) ) ;
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

        handle( Brzcki ) ;
        handle( Baechle ) ;
        handle( DosRemedios ) ;

        values.push_back( avalues ) ;
      } catch( const std::exception& ex ) {
        DLOG(INFO) << "Couldn't process a statistic with the given config: "
          << ex.what() << std::endl ;
      }
    }
  }

}

