/* Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved */

#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include "mcommon/Log.hpp"

#include "mfit/modules/Cardio.hpp"
#include "mfit/modules/General.hpp"
#include "mfit/modules/Measurements.hpp"
#include "mfit/Engine.hpp"

using namespace mcommon ;

namespace mfit {

  Cardio::Cardio( ) {
    add( "You were on the treadmill for", getTreadmillTime ) ;
    add( "\tand you traveled", getTreadmillDistance ) ;
    add( "\tand your pace was", getTreadmillPace ) ;
    add( "\tand you spent", getTreadmillMETS ) ;
    add( "\tand you burnt", getTreadmillCals ) ;
    add( "Your average speed for your best run was", getAverageSpeed ) ;
    add( "Given this pace it would take you", "\tto travel", getTimeToTravel ) ;
    add( "Given this pace you would travel", "\tin", getDistanceTraveled ) ;
    add( { "This means that for your given age your run time percentile is",
        "\tgiven a run length of",
        "\tand given a run time of" },
        getAgeGrade ) ;
  }

  std::string Cardio::getKey( ) {
    return key ;
  }

  float Cardio::getGradient( const pugi::xml_document& cfg ) {
    return Engine::getAttributeAs<float>( cfg,
        "/person/excercises/cardio/runs[@type='treadmill']/@gradient" ) ;
  }

  const std::string Cardio::key = "mfit::Cardio" ;

  void Cardio::getRuns( const pugi::xml_document& cfg,
      const std::string xpath, std::vector<Run>& runs, Quantity& tTime,
      Quantity& tDis ) {
    tDis = Quantity( 0, MILES ) ;
    tTime = Quantity( 0, HOURS ) ;

    pugi::xpath_node_set xruns = cfg.select_nodes(xpath.c_str());

    for ( auto it : xruns ) {
      DLOG(INFO) << xpath << " " <<  it.node().name() << " "
        << it.node().child("speed").last_child().value() << std::endl ;

      float time = boost::lexical_cast<float>(
          it.node().child("time").last_child().value());
      float speed = boost::lexical_cast<float>(
          it.node().child("speed").last_child().value());
      runs.push_back( Run(time, speed) );
      tTime += runs.back().time;
      tDis += runs.back().distance ;
    }
  }

  std::shared_ptr<Quantity> Cardio::getTreadmillDistance(
      const pugi::xml_document& cfg ) {
    Quantity weight = *Measurements::getWeight( cfg ) ;
    std::vector<Run> treadmillRuns ;
    Quantity tDis ;
    Quantity tTime ;
    getRuns(cfg, "/person/excercises/cardio/runs[@type='treadmill']/run",
        treadmillRuns, tTime, tDis) ;

    return std::shared_ptr<Quantity>( new Quantity(tDis) ) ;
  }

  std::shared_ptr<Quantity> Cardio::getTreadmillTime(
      const pugi::xml_document& cfg ) {
    Quantity weight = *Measurements::getWeight( cfg ) ;
    std::vector<Run> treadmillRuns ;
    Quantity tDis ;
    Quantity tTime ;
    getRuns(cfg, "/person/excercises/cardio/runs[@type='treadmill']/run",
        treadmillRuns, tTime, tDis) ;

    return std::shared_ptr<Quantity>( new Quantity(tTime) ) ;
  }
  
  std::shared_ptr<Quantity> Cardio::getTreadmillPace(
      const pugi::xml_document& cfg ) {
    std::vector<Run> treadmillRuns ;
    Quantity tDis ;
    Quantity tTime ;
    getRuns(cfg, "/person/excercises/cardio/runs[@type='treadmill']/run",
        treadmillRuns, tTime, tDis) ;

    float dis = tDis.convert(MILES).magnitude( ) ;
    float t = tTime.convert(HOURS).magnitude( ) ;
    float sp = dis/t ;
    return std::shared_ptr<Quantity>( new Quantity(sp, MPH) ) ;
  }

  std::shared_ptr<Quantity> Cardio::getTreadmillMETS(
      const pugi::xml_document& cfg ) {
    float gradient = Cardio::getGradient( cfg ) ;
    Quantity weight = *Measurements::getWeight( cfg ) ;
    std::vector<Run> treadmillRuns ;
    Quantity tDis ;
    Quantity tTime ;
    getRuns(cfg, "/person/excercises/cardio/runs[@type='treadmill']/run",
        treadmillRuns, tTime, tDis) ;

    float dis = tDis.convert(KM).magnitude( ) ;
    float we = weight.convert(KG).magnitude( ) ;
    float t = tTime.convert(MINUTES).magnitude( ) ;
    float sp = dis/t*60.0; // KMH
    float gas =  sp + sp*gradient*9.0/200.0 ;
    float cal=(gas*1000.0/60.0+17.5)*t*we/1000.0 ;
    return std::shared_ptr<Quantity>( new Quantity(cal/we/t*60, METS) ) ;
  }

  std::shared_ptr<Quantity> Cardio::getTreadmillCals(
      const pugi::xml_document& cfg ) {
    float gradient = Cardio::getGradient( cfg ) ;
    Quantity weight = *Measurements::getWeight( cfg ) ;
    std::vector<Run> treadmillRuns ;
    Quantity tDis ;
    Quantity tTime ;
    getRuns(cfg, "/person/excercises/cardio/runs[@type='treadmill']/run",
        treadmillRuns, tTime, tDis) ;

    float dis = tDis.convert(KM).magnitude( ) ;
    float we = weight.convert(KG).magnitude( ) ;
    float t = tTime.convert(MINUTES).magnitude( ) ;
    float sp = dis/t*60.0; // KMH
    float gas =  sp + sp*gradient*9.0/200.0 ;
    return std::shared_ptr<Quantity>(
        new Quantity((gas*1000.0/60.0+17.5)*t*we/1000.0, CALORIES) ) ;
  }

  std::shared_ptr<Quantity> Cardio::getAverageSpeed(
      const pugi::xml_document& cfg ) {
    std::vector<Run> runs ;
    Quantity tDis ;
    Quantity tTime ;
    getRuns(cfg, "/person/excercises/cardio/runs[@type='best']/run",
        runs, tTime, tDis) ;

    return std::shared_ptr<Quantity>(
        new Quantity( tDis.convert(MILES).magnitude()/
          tTime.convert(HOURS).magnitude(), MPH ) ) ;
  }

  void Cardio::getDistanceTraveled( const pugi::xml_document& cfg,
      std::list<std::pair<std::shared_ptr<mcommon::Value>,
      std::shared_ptr<mcommon::Value> > >& values ) {
    std::list<std::shared_ptr<Quantity> > qvalues ;
    Engine::getNodesAsQuantity( cfg,
        "/person/excercises/cardio/compute/distanceTraveledIn/time", qvalues ) ;

    Quantity avgSpeed(*getAverageSpeed(cfg)) ;
//    Quantity avgSpeed(*getTreadmillPace(cfg)) ;

    for( auto time : qvalues ) {
      values.push_back( std::make_pair( std::shared_ptr<Quantity>(
              new Quantity( time->convert(HOURS).magnitude()*
                avgSpeed.convert(MPH).magnitude(), MILES ) ), time ) ) ;
    }
  }

  void Cardio::getTimeToTravel( const pugi::xml_document& cfg,
      std::list<std::pair<std::shared_ptr<mcommon::Value>,
      std::shared_ptr<mcommon::Value> > >& values ) {
    std::list<std::shared_ptr<Quantity> > qvalues ;
    Engine::getNodesAsQuantity( cfg,
        "/person/excercises/cardio/compute/timeToTravel/distance", qvalues ) ;

    Quantity avgSpeed(*getAverageSpeed(cfg)) ;
//    Quantity avgSpeed(*getTreadmillPace(cfg)) ;

    for( auto dis : qvalues ) {
      values.push_back( std::make_pair(
            std::shared_ptr<Quantity>(
              new Quantity( dis->convert(MILES).magnitude( )/
                avgSpeed.convert(MPH).magnitude( ), HOURS ) ),  dis ) ) ;
    }
  }

  void Cardio::getAgeGrade( const pugi::xml_document& cfg,
      std::list<std::list<std::shared_ptr<mcommon::Value> > >& values ) {
    Quantity age = General::getAge( cfg )->convert(YEARS) ;
    Gender gender = General::getGender( cfg ) ;
    Quantity avgSpeed(*getAverageSpeed(cfg)) ;
//    Quantity avgSpeed(*getTreadmillPace(cfg)) ;

    std::list<std::shared_ptr<Quantity> > distances ;
    Engine::getNodesAsQuantity( cfg,
        "/person/excercises/cardio/compute/ageGrade/distance", distances ) ;

    for( auto dis : distances ) {
      std::list<std::shared_ptr<Value> > avalues ;

      std::shared_ptr<Quantity> time(
          new Quantity( dis->convert(MILES).magnitude( )/
            avgSpeed.convert(MPH).magnitude( ), HOURS ) )  ;

      float ag = std[gender][getStdIndex(*dis)] /
        factors[gender][getFactorIndex(gender,*dis)][(int)std::round(age.magnitude()-5)] /
        time->convert(SECONDS).magnitude() * 100.0f ;
      avalues.push_back( std::shared_ptr<Quantity>(
            new Quantity( ag, PERCENTAGE ) ) ) ;
      avalues.push_back( dis ) ;
      avalues.push_back( time ) ;
      values.push_back( avalues ) ;
    }
  }

  const float Cardio::std[GENDER_MAX][33] = {
    { 774,940,1011,1272,1280,1611,1951,2469,2663,3358,3553,4259,5179,7495,9080,
      16080,21360,36300,39850,52800,205.8,222.6,283.2,440,474.6,598,730,757,919,
      1247,1255,1580 },
    { 888,1073,1154,1445,1452,1820,2200,2772,2981,3738,3950,4712,5696,8125,9820,
      17760,23591,39700,43500,57600,232.47,251.6,321.5,501.42,541.5,683,833,
      864.68,1051,1132,1425,1435,1801.09},
  } ;

  const float Cardio::factors[GENDER_MAX][23][98] = { {
    { .6526,.6899,.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,.9999,.9991,.9975,.9952,.9922,.9885,.984,.9788,.9729,.9662,.9592,.9521,.9451,.938,.931,.924,.9169,.9099,.9028,.8958,.8888,.8817,.8747,.8676,.8606,.8536,.8465,.8395,.8324,.8254,.8184,.8113,.8043,.7972,.7902,.7832,.7761,.7691,.762,.755,.7479,.7402,.7319,.723,.7134,.7031,.6923,.6808,.6687,.6559,.6425,.6285,.6138,.5985,.5825,.566,.5488,.5309,.5124,.4933,.4735,.4531,.4321,.4104,.3881,.3652,.3416,.3174,.2926,.2671,.2409,.2142,.1868 },
      { .6526,.6899,.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,.9998,.9989,.9972,.9947,.9913,.9872,.9822,.9765,.9699,.9628,.9556,.9485,.9413,.9341,.927,.9198,.9126,.9055,.8983,.8911,.884,.8768,.8697,.8625,.8553,.8482,.841,.8338,.8267,.8195,.8123,.8052,.798,.7908,.7837,.7765,.7694,.7622,.755,.7479,.7404,.7322,.7235,.714,.7039,.6932,.6818,.6698,.6571,.6438,.6299,.6152,.6,.5841,.5675,.5503,.5324,.5139,.4948,.475,.4545,.4334,.4117,.3893,.3663,.3426,.3182,.2933,.2676,.2413,.2144,.1868 },
      { .651,.6884,.7236,.7566,.7874,.816,.8424,.8666,.8886,.9084,.926,.9414,.9546,.9667,.9788,.9892,.9961,.9996,1,1,1,1,1,1,1,.9999,.999,.9972,.9945,.9909,.9864,.981,.9746,.9674,.9601,.9528,.9455,.9382,.9309,.9235,.9162,.9089,.9016,.8943,.887,.8797,.8723,.865,.8577,.8504,.8431,.8358,.8284,.8211,.8138,.8065,.7992,.7919,.7845,.7772,.7699,.7626,.7553,.748,.7406,.7327,.7241,.7149,.705,.6944,.6832,.6713,.6588,.6456,.6317,.6172,.602,.5861,.5696,.5524,.5346,.5161,.4969,.4771,.4566,.4354,.4136,.3911,.368,.3442,.3197,.2946,.2688,.2424,.2153,.1875 },
      { .6495,.687,.7223,.7554,.7863,.815,.8415,.8658,.8879,.9078,.9255,.941,.9543,.9665,.9787,.9891,.9961,.9996,1,1,1,1,1,1,1,1,.9994,.9979,.9955,.9921,.9877,.9824,.9761,.969,.9616,.9542,.9469,.9395,.9321,.9248,.9174,.91,.9027,.8953,.888,.8806,.8732,.8659,.8585,.8511,.8438,.8364,.829,.8217,.8143,.807,.7996,.7922,.7849,.7775,.7701,.7628,.7554,.748,.7407,.7329,.7245,.7154,.7056,.6951,.684,.6722,.6597,.6466,.6328,.6183,.6032,.5874,.5709,.5537,.5359,.5174,.4982,.4783,.4578,.4366,.4148,.3922,.369,.3451,.3206,.2954,.2695,.2429,.2157,.1878 },
      { .64,.6781,.714,.7477,.7792,.8085,.8356,.8605,.8832,.9037,.922,.9381,.952,.9648,.9776,.9886,.9959,.9995,1,1,1,1,1,1,1,1,1,.9995,.998,.9953,.9915,.9867,.9808,.9738,.9663,.9588,.9512,.9437,.9362,.9287,.9212,.9137,.9062,.8987,.8912,.8836,.8761,.8686,.8611,.8536,.8461,.8386,.8311,.8235,.816,.8085,.801,.7935,.786,.7785,.771,.7634,.7559,.7484,.7409,.7333,.7252,.7164,.7069,.6967,.6858,.6742,.6619,.6489,.6353,.6209,.6059,.5901,.5737,.5566,.5388,.5203,.5011,.4812,.4606,.4393,.4174,.3947,.3714,.3474,.3226,.2972,.2711,.2443,.2168,.1886 },
      { .6369,.6752,.7113,.7452,.7769,.8064,.8337,.8588,.8817,.9024,.9209,.9372,.9513,.9643,.9773,.9884,.9958,.9995,1,1,1,1,1,1,1,1,1,.9998,.9984,.996,.9925,.9878,.982,.975,.9675,.9599,.9524,.9448,.9373,.9297,.9222,.9146,.9071,.8995,.892,.8844,.8769,.8693,.8618,.8542,.8467,.8392,.8316,.8241,.8165,.809,.8014,.7939,.7863,.7788,.7712,.7637,.7561,.7486,.741,.7334,.7253,.7166,.7071,.6969,.686,.6744,.6622,.6492,.6356,.6212,.6062,.5905,.574,.5569,.5391,.5206,.5014,.4815,.4609,.4396,.4177,.395,.3717,.3476,.3229,.2974,.2713,.2445,.2169,.1887 },
      { .629,.6678,.7044,.7388,.771,.801,.8288,.8544,.8778,.899,.918,.9348,.9494,.9629,.9764,.9879,.9957,.9995,1,1,1,1,1,1,1,1,1,1,.9996,.998,.9952,.991,.9856,.9789,.9713,.9636,.956,.9483,.9406,.933,.9253,.9177,.91,.9023,.8947,.887,.8793,.8717,.864,.8563,.8487,.841,.8333,.8257,.818,.8104,.8027,.795,.7874,.7797,.772,.7644,.7567,.749,.7414,.7337,.7257,.717,.7076,.6975,.6867,.6751,.6629,.65,.6364,.6221,.6071,.5914,.575,.5579,.5401,.5216,.5024,.4825,.4619,.4406,.4186,.3959,.3726,.3485,.3237,.2982,.272,.2451,.2175,.1892 },
      { .6243,.6634,.7003,.735,.7675,.7978,.8259,.8518,.8755,.897,.9163,.9334,.9483,.9621,.9759,.9877,.9956,.9995,1,1,1,1,1,1,1,1,1,1,1,.9995,.9976,.9943,.9895,.9832,.9756,.9678,.96,.9522,.9444,.9366,.9289,.9211,.9133,.9055,.8977,.8899,.8821,.8743,.8666,.8588,.851,.8432,.8354,.8276,.8198,.812,.8042,.7965,.7887,.7809,.7731,.7653,.7575,.7497,.7419,.7342,.7262,.7176,.7082,.6982,.6874,.676,.6638,.651,.6374,.6231,.6082,.5925,.5761,.559,.5412,.5227,.5035,.4836,.463,.4417,.4197,.3969,.3735,.3494,.3245,.299,.2727,.2458,.2181,.1898 },
      { .6211,.6604,.6975,.7324,.7651,.7956,.8239,.85,.8739,.8956,.9151,.9324,.9475,.9615,.9755,.9875,.9955,.9995,1,1,1,1,1,1,1,1,1,1,1,1,1,.999,.996,.991,.984,.9759,.9679,.9599,.9519,.9439,.9358,.9278,.9198,.9118,.9038,.8957,.8877,.8797,.8717,.8637,.8556,.8476,.8396,.8316,.8236,.8155,.8075,.7995,.7915,.7835,.7754,.7674,.7594,.7514,.7434,.7353,.7272,.7185,.7091,.699,.6882,.6766,.6644,.6515,.6379,.6236,.6085,.5928,.5764,.5593,.5415,.5229,.5037,.4838,.4632,.4419,.4198,.3971,.3737,.3496,.3248,.2992,.273,.2461,.2185,.1902 },
      { .6526,.6899,.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,.9999,.9991,.9975,.9952,.9922,.9885,.984,.9788,.9729,.9662,.9592,.9521,.9451,.938,.931,.924,.9169,.9099,.9028,.8958,.8888,.8817,.8747,.8676,.8606,.8536,.8465,.8395,.8324,.8254,.8184,.8113,.8043,.7972,.7902,.7832,.7761,.7691,.762,.755,.7479,.7402,.7319,.723,.7134,.7031,.6923,.6808,.6687,.6559,.6425,.6285,.6138,.5985,.5825,.566,.5488,.5309,.5124,.4933,.4735,.4531,.4321,.4104,.3881,.3652,.3416,.3174,.2926,.2671,.2409,.2142,.1868 },
  }, {
    {.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,1,1,1,.9997,.9989,.9976,.9957,.9934,.9904,.987,.983,.9785,.9734,.9678,.9617,.9551,.9479,.9402,.9319,.9232,.9139,.904,.8937,.8828,.8719,.861,.8501,.8392,.8283,.8174,.8065,.7956,.7847,.7738,.7629,.752,.7411,.7302,.7193,.7084,.6975,.6866,.6757,.6648,.6539,.643,.6321,.6212,.6103,.5994,.5885,.5776,.5667,.5552,.5425,.5286,.5135,.4972,.4797,.461,.4411,.42,.3977,.3742,.3495,.3236,.2965,.2682,.2387,.208,.1761,.143,.1087,.0732},
      {.7236,.7566,.7874,.816,.8424,.8666,.8886,.9084,.926,.9414,.9546,.9667,.9788,.9892,.9961,.9996,1,1,1,1,1,1,1,1,1,.9997,.9989,.9976,.9957,.9934,.9904,.987,.983,.9785,.9734,.9678,.9617,.9551,.9479,.9402,.9319,.9232,.9139,.904,.8937,.8828,.8719,.861,.8501,.8392,.8283,.8174,.8065,.7956,.7847,.7738,.7629,.752,.7411,.7302,.7193,.7084,.6975,.6866,.6757,.6648,.6539,.643,.6321,.6212,.6103,.5994,.5885,.5776,.5667,.5552,.5425,.5286,.5135,.4972,.4797,.461,.4411,.42,.3977,.3742,.3495,.3236,.2965,.2682,.2387,.208,.1761,.143,.1087,.0732},
      {.7181,.7515,.7827,.8117,.8385,.8631,.8855,.9057,.9237,.9395,.9531,.9656,.9781,.9888,.996,.9996,1,1,1,1,1,1,1,1,1,.9997,.9989,.9976,.9957,.9934,.9904,.987,.983,.9785,.9734,.9678,.9617,.9551,.9479,.9402,.9319,.9232,.9139,.904,.8937,.8828,.8719,.861,.8501,.8392,.8283,.8174,.8065,.7956,.7847,.7738,.7629,.752,.7411,.7302,.7193,.7084,.6975,.6866,.6757,.6648,.6539,.643,.6321,.6212,.6103,.5994,.5885,.5776,.5667,.5552,.5425,.5286,.5135,.4972,.4797,.461,.4411,.42,.3977,.3742,.3495,.3236,.2965,.2682,.2387,.208,.1761,.143,.1087,.0732},
      {.6975,.7324,.7651,.7956,.8239,.85,.8739,.8956,.9151,.9324,.9475,.9615,.9755,.9875,.9955,.9995,1,1,1,1,1,1,1,1,1,.9997,.9989,.9976,.9957,.9934,.9904,.987,.983,.9785,.9734,.9678,.9617,.9551,.9479,.9402,.9319,.9232,.9139,.904,.8937,.8828,.8719,.861,.8501,.8392,.8283,.8174,.8065,.7956,.7847,.7738,.7629,.752,.7411,.7302,.7193,.7084,.6975,.6866,.6757,.6648,.6539,.643,.6321,.6212,.6103,.5994,.5885,.5776,.5667,.5552,.5425,.5286,.5135,.4972,.4797,.461,.4411,.42,.3977,.3742,.3495,.3236,.2965,.2682,.2387,.208,.1761,.143,.1087,.0732},
      {.6838,.7197,.7534,.7849,.8142,.8413,.8662,.8889,.9094,.9277,.9438,.9588,.9738,.9866,.9952,.9995,1,1,1,1,1,1,1,1,1,.9997,.9989,.9976,.9957,.9934,.9904,.987,.983,.9785,.9734,.9678,.9617,.9551,.9479,.9402,.9319,.9232,.9139,.904,.8937,.8828,.8719,.861,.8501,.8392,.8283,.8174,.8065,.7956,.7847,.7738,.7629,.752,.7411,.7302,.7193,.7084,.6975,.6866,.6757,.6648,.6539,.643,.6321,.6212,.6103,.5994,.5885,.5776,.5667,.5552,.5425,.5286,.5135,.4972,.4797,.461,.4411,.42,.3977,.3742,.3495,.3236,.2965,.2682,.2387,.208,.1761,.143,.1087,.0732},
      {.6631,.7005,.7357,.7687,.7995,.8281,.8545,.8787,.9007,.9205,.9381,.9546,.9711,.9853,.9947,.9994,1,1,1,1,1,1,1,1,1,.9997,.9989,.9976,.9957,.9934,.9904,.987,.983,.9785,.9734,.9678,.9617,.9551,.9479,.9402,.9319,.9232,.9139,.904,.8937,.8828,.8719,.861,.8501,.8392,.8283,.8174,.8065,.7956,.7847,.7738,.7629,.752,.7411,.7302,.7193,.7084,.6975,.6866,.6757,.6648,.6539,.643,.6321,.6212,.6103,.5994,.5885,.5776,.5667,.5552,.5425,.5286,.5135,.4972,.4797,.461,.4411,.42,.3977,.3742,.3495,.3236,.2965,.2682,.2387,.208,.1761,.143,.1087,.0732},
      {.6563,.6942,.7299,.7634,.7947,.8238,.8507,.8754,.8979,.9182,.9363,.9533,.9703,.9848,.9945,.9994,1,1,1,1,1,1,1,1,1,.9997,.9989,.9976,.9957,.9934,.9904,.987,.983,.9785,.9734,.9678,.9617,.9551,.9479,.9402,.9319,.9232,.9139,.904,.8937,.8828,.8719,.861,.8501,.8392,.8283,.8174,.8065,.7956,.7847,.7738,.7629,.752,.7411,.7302,.7193,.7084,.6975,.6866,.6757,.6648,.6539,.643,.6321,.6212,.6103,.5994,.5885,.5776,.5667,.5552,.5425,.5286,.5135,.4972,.4797,.461,.4411,.42,.3977,.3742,.3495,.3236,.2965,.2682,.2387,.208,.1761,.143,.1087,.0732},
      {.6425,.6814,.7181,.7526,.7849,.815,.8429,.8686,.8921,.9134,.9325,.9505,.9685,.9839,.9942,.9994,1,1,1,1,1,1,1,1,1,.9997,.9988,.9974,.9953,.9927,.9895,.9857,.9813,.9763,.9708,.9647,.9579,.9506,.9428,.9343,.9252,.9156,.9054,.8946,.8837,.8728,.8619,.851,.8401,.8292,.8183,.8074,.7965,.7856,.7747,.7638,.7529,.742,.7311,.7202,.7093,.6984,.6875,.6766,.6657,.6548,.6439,.633,.6221,.6112,.6003,.5894,.5785,.5675,.5557,.5428,.5287,.5136,.4974,.4801,.4616,.4421,.4215,.3998,.377,.3531,.3281,.3019,.2747,.2464,.217,.1865,.1549,.1222,.0885,.0536},
      {.6288,.6687,.7064,.7419,.7752,.8063,.8352,.8619,.8864,.9087,.9288,.9478,.9668,.983,.9939,.9993,1,1,1,1,1,1,1,1,1,.9997,.9987,.9971,.9948,.9918,.9882,.984,.9791,.9736,.9673,.9605,.953,.9448,.936,.9265,.9164,.9057,.8948,.8839,.873,.8621,.8512,.8403,.8294,.8185,.8076,.7967,.7858,.7749,.764,.7531,.7422,.7313,.7204,.7095,.6986,.6877,.6768,.6659,.655,.6441,.6332,.6223,.6114,.6005,.5896,.5787,.5675,.5553,.5421,.528,.5128,.4967,.4796,.4615,.4425,.4224,.4014,.3793,.3563,.3323,.3073,.2813,.2544,.2264,.1975,.1676,.1367,.1048,.0719,.038},
      {.615,.6559,.6946,.7311,.7654,.7975,.8274,.8551,.8806,.9039,.925,.945,.965,.9821,.9936,.9993,1,1,1,1,1,1,1,1,1,.9996,.9983,.9962,.9933,.9895,.9849,.9795,.9732,.966,.9581,.9493,.9396,.9292,.9183,.9074,.8965,.8856,.8747,.8638,.8529,.842,.8311,.8202,.8093,.7984,.7875,.7766,.7657,.7548,.7439,.733,.7221,.7112,.7003,.6894,.6785,.6676,.6567,.6458,.6349,.624,.6131,.6022,.5913,.5803,.5686,.5561,.5429,.5289,.5141,.4985,.4821,.465,.4471,.4284,.4089,.3886,.3676,.3458,.3232,.2998,.2756,.2507,.225,.1985,.1712,.1431,.1143,.0847,.0543,.0231},
      {.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,1,1,.9998,.9989,.9971,.9946,.9913,.9871,.9822,.9765,.9701,.9628,.9547,.9459,.9362,.9258,.9151,.9044,.8937,.8831,.8724,.8617,.851,.8403,.8297,.819,.8083,.7976,.7869,.7763,.7656,.7549,.7442,.7335,.7229,.7122,.7015,.6908,.6801,.6695,.6588,.6481,.6374,.6267,.6161,.6054,.5947,.584,.5733,.5627,.552,.5413,.5306,.5199,.5087,.4962,.4825,.4676,.4515,.4343,.4158,.3961,.3752,.3531,.3299,.3054,.2797,.2528,.2247,.1955,.165,.1333,.1004,.0663},
      {.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,1,1,.9998,.9989,.9972,.9948,.9915,.9875,.9827,.9771,.9707,.9636,.9557,.9469,.9375,.9272,.9165,.9058,.8951,.8844,.8737,.863,.8523,.8416,.8309,.8202,.8095,.7988,.7881,.7774,.7667,.756,.7453,.7346,.7239,.7132,.7025,.6918,.6811,.6704,.6597,.649,.6383,.6276,.6169,.6062,.5955,.5848,.5741,.5634,.5527,.542,.5313,.5206,.5091,.4965,.4827,.4678,.4516,.4343,.4158,.3961,.3752,.3532,.3299,.3055,.2799,.2532,.2252,.1961,.1658,.1343,.1016,.0677},
      {.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,1,1,.9999,.9991,.9976,.9953,.9923,.9885,.984,.9787,.9727,.9659,.9584,.9501,.9411,.9313,.9208,.91,.8992,.8885,.8777,.867,.8562,.8454,.8347,.8239,.8132,.8024,.7916,.7809,.7701,.7594,.7486,.7378,.7271,.7163,.7056,.6948,.684,.6733,.6625,.6518,.641,.6302,.6195,.6087,.598,.5872,.5764,.5657,.5549,.5442,.5334,.5225,.5106,.4976,.4834,.4682,.4517,.4341,.4154,.3956,.3746,.3524,.3292,.3047,.2792,.2525,.2246,.1957,.1655,.1343,.1019,.0684},
      {.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,1,1,1,.9994,.9981,.9962,.9935,.9902,.9861,.9813,.9759,.9697,.9628,.9553,.947,.938,.9283,.918,.9071,.8962,.8854,.8745,.8636,.8527,.8419,.831,.8201,.8092,.7984,.7875,.7766,.7657,.7549,.744,.7331,.7222,.7114,.7005,.6896,.6787,.6678,.657,.6461,.6352,.6243,.6135,.6026,.5917,.5808,.57,.5591,.5482,.5373,.5257,.5131,.4993,.4845,.4686,.4517,.4336,.4145,.3942,.3729,.3506,.3271,.3026,.277,.2503,.2225,.1936,.1637,.1327,.1006,.0674},
      {.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,1,1,1,.9994,.9982,.9963,.9937,.9904,.9864,.9817,.9764,.9703,.9635,.9561,.9479,.9391,.9295,.9193,.9085,.8976,.8867,.8758,.8649,.854,.8431,.8322,.8213,.8104,.7995,.7886,.7777,.7668,.7559,.745,.7341,.7232,.7123,.7014,.6906,.6797,.6688,.6579,.647,.6361,.6252,.6143,.6034,.5925,.5816,.5707,.5598,.5489,.538,.5263,.5135,.4997,.4848,.4688,.4518,.4337,.4146,.3944,.3731,.3508,.3275,.303,.2775,.251,.2234,.1947,.165,.1342,.1023,.0694},
      {.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,1,1,1,.9996,.9985,.9967,.9943,.9912,.9874,.983,.9779,.9721,.9656,.9585,.9507,.9422,.9331,.9233,.9128,.9019,.8909,.88,.869,.8581,.8471,.8361,.8252,.8142,.8033,.7923,.7814,.7704,.7594,.7485,.7375,.7266,.7156,.7047,.6937,.6827,.6718,.6608,.6499,.6389,.628,.617,.606,.5951,.5841,.5732,.5622,.5513,.5401,.528,.5149,.5007,.4855,.4693,.4521,.4339,.4147,.3944,.3731,.3508,.3275,.3031,.2777,.2514,.2239,.1955,.1661,.1356,.1041,.0716},
      {.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,1,1,1,.9997,.9987,.997,.9947,.9918,.9882,.9839,.979,.9735,.9673,.9604,.9529,.9448,.936,.9265,.9164,.9056,.8946,.8836,.8726,.8616,.8506,.8396,.8286,.8176,.8066,.7955,.7845,.7735,.7625,.7515,.7405,.7295,.7185,.7075,.6965,.6854,.6744,.6634,.6524,.6414,.6304,.6194,.6084,.5974,.5864,.5753,.5643,.5533,.5419,.5294,.516,.5015,.4861,.4696,.4522,.4337,.4143,.3938,.3724,.3499,.3265,.302,.2766,.2501,.2227,.1942,.1648,.1343,.1029,.0704},
      {.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,1,1,1,.9997,.9987,.9971,.9948,.9919,.9883,.9841,.9793,.9737,.9676,.9608,.9533,.9452,.9365,.9271,.917,.9063,.8953,.8843,.8733,.8623,.8512,.8402,.8292,.8182,.8072,.7961,.7851,.7741,.7631,.7521,.741,.73,.719,.708,.697,.6859,.6749,.6639,.6529,.6419,.6308,.6198,.6088,.5978,.5868,.5757,.5647,.5537,.5422,.5297,.5161,.5016,.4861,.4696,.4521,.4335,.414,.3935,.372,.3495,.3259,.3014,.2759,.2494,.2219,.1933,.1638,.1333,.1018,.0692},
      {.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,1,1,1,.9997,.9988,.9972,.995,.9922,.9888,.9848,.9801,.9749,.969,.9624,.9553,.9475,.9391,.9301,.9205,.9103,.8994,.8883,.8771,.866,.8548,.8437,.8325,.8214,.8102,.7991,.7879,.7768,.7657,.7545,.7434,.7322,.7211,.7099,.6988,.6876,.6765,.6653,.6542,.643,.6319,.6208,.6096,.5985,.5873,.5762,.565,.5539,.5426,.5305,.5174,.5033,.4882,.472,.4549,.4368,.4177,.3976,.3765,.3543,.3312,.3071,.282,.2559,.2288,.2007,.1715,.1414,.1103,.0782},
      {.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,1,1,1,.9997,.9988,.9972,.9951,.9924,.989,.985,.9804,.9752,.9694,.963,.956,.9483,.9401,.9312,.9217,.9117,.901,.8898,.8786,.8674,.8562,.845,.8338,.8226,.8114,.8002,.789,.7778,.7666,.7554,.7443,.7331,.7219,.7107,.6995,.6883,.6771,.6659,.6547,.6435,.6323,.6211,.6099,.5987,.5875,.5763,.5651,.5539,.5427,.5309,.518,.5041,.4893,.4734,.4565,.4387,.4198,.3999,.3791,.3572,.3343,.3105,.2856,.2598,.2329,.205,.1762,.1463,.1154,.0836},
      {.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,1,1,1,.9997,.9988,.9974,.9953,.9927,.9895,.9857,.9813,.9764,.9708,.9647,.958,.9507,.9428,.9343,.9253,.9157,.9055,.8947,.8834,.872,.8607,.8493,.838,.8266,.8153,.804,.7926,.7813,.7699,.7586,.7472,.7359,.7245,.7132,.7019,.6905,.6792,.6678,.6565,.6451,.6338,.6224,.6111,.5997,.5884,.5771,.5657,.5544,.543,.5315,.519,.5055,.491,.4755,.459,.4416,.4231,.4036,.3831,.3616,.3391,.3157,.2912,.2657,.2392,.2117,.1832,.1537,.1233,.0918},
      {.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,1,1,1,.9997,.9988,.9974,.9953,.9927,.9895,.9857,.9813,.9764,.9709,.9647,.958,.9507,.9429,.9344,.9254,.9158,.9056,.8948,.8835,.8722,.8608,.8495,.8381,.8268,.8154,.8041,.7927,.7814,.77,.7587,.7473,.736,.7246,.7133,.7019,.6906,.6792,.6679,.6565,.6452,.6338,.6225,.6111,.5998,.5884,.5771,.5657,.5544,.543,.5315,.519,.5055,.491,.4756,.4591,.4416,.4231,.4037,.3832,.3617,.3392,.3157,.2913,.2658,.2393,.2118,.1833,.1539,.1234,.0919},
      {.725,.7579,.7886,.8171,.8434,.8675,.8894,.9091,.9266,.9419,.955,.967,.979,.9893,.9961,.9996,1,1,1,1,1,1,1,1,1,.9997,.9989,.9975,.9955,.993,.99,.9863,.9821,.9774,.9721,.9662,.9598,.9528,.9453,.9372,.9285,.9193,.9096,.8992,.8883,.877,.8655,.854,.8425,.831,.8195,.808,.7965,.785,.7735,.762,.7505,.739,.7275,.716,.7045,.693,.6815,.67,.6585,.647,.6355,.624,.6125,.601,.5895,.578,.5665,.555,.5435,.532,.52,.507,.493,.478,.462,.445,.427,.408,.388,.367,.345,.322,.298,.273,.247,.22,.192,.163,.133,.102},
  } } ;

#define MAR 42.195
#define HMAR (MAR/2.0)

  int Cardio::getStdIndex( Quantity distance ) {
    if( distance == Quantity( 5, KM ) ) {
      return 0 ;
    } else if ( distance == Quantity( 6, KM ) ) {
      return 1 ;
    } else if ( distance == Quantity( 4, MILES ) ) {
      return 2 ;
    } else if ( distance == Quantity( 8, KM ) ) {
      return 3 ;
    } else if ( distance == Quantity( 5, MILES ) ) {
      return 4 ;
    } else if ( distance == Quantity( 10, KM ) ) {
      return 5 ;
    } else if ( distance == Quantity( 12, KM ) ) {
      return 6 ;
    } else if ( distance == Quantity( 15, KM ) ) {
      return 7 ;
    } else if ( distance == Quantity( 10, MILES ) ) {
      return 8 ;
    } else if ( distance == Quantity( 20, KM ) ) {
      return 9 ;
    } else if ( distance == Quantity( HMAR, KM ) ) {
      return 10 ;
    } else if ( distance == Quantity( 25, KM ) ) {
      return 11 ;
    } else if ( distance == Quantity( 30, KM ) ) {
      return 12 ;
    } else if ( distance == Quantity( MAR, KM ) ) {
      return 13 ;
    } else if ( distance == Quantity( 50, KM ) ) {
      return 14 ;
    } else if ( distance == Quantity( 50, MILES ) ) {
      return 15 ;
    } else if ( distance == Quantity( 100, KM ) ) {
      return 16 ;
    } else if ( distance == Quantity( 150, KM ) ) {
      return 17 ;
    } else if ( distance == Quantity( 100, MILES ) ) {
      return 18 ;
    } else if ( distance == Quantity( 200, KM ) ) {
      return 19 ;
    } else if ( distance == Quantity( 1500, M ) ) {
      return 20 ;
    } else if ( distance == Quantity( 1, MILES ) ) {
      return 21 ;
    } else if ( distance == Quantity( 2000, M ) ) {
      return 22 ;
    } else if ( distance == Quantity( 3000, M ) ) {
      return 23 ;
    } else if ( distance == Quantity( 2, MILES ) ) {
      return 24 ;
    } else if ( distance == Quantity( 4000, M ) ){
      return 25 ;
    } else if (  distance == Quantity( 3, MILES ) ){
      return 26 ;
    } else if ( distance == Quantity( 5000, M ) ) {
      return 27 ;
    } else if ( distance == Quantity( 6000, M ) ) {
      return 28 ;
    } else if ( distance == Quantity( 8000, M ) ) {
      return 30 ;
    } else if ( distance == Quantity( 5, MILES ) ) {
      return 31 ;
    } else if ( distance == Quantity( 10000, M ) ) {
      return 32 ;
    } else {
      throw std::runtime_error("unknown distance for age grade" ) ;
    }
  }

  int Cardio::getFactorIndex( Gender g, Quantity distance ) {
    switch( g ) {
      case Male:
        if( distance == Quantity( 5, KM ) || 
            distance == Quantity( 6, KM ) ||
            distance == Quantity( 4, MILES ) ||
            distance == Quantity( 8, KM ) ||
            distance == Quantity( 5, MILES ) ||
            distance == Quantity( 10, KM ) ) {
          return 0 ;
        } else if ( distance == Quantity( 12, KM ) ) {
          return 1 ;
        } else if ( distance == Quantity( 15, KM ) ) {
          return 2 ;
        } else if ( distance == Quantity( 10, MILES ) ) {
          return 3 ;
        } else if ( distance == Quantity( 20, KM ) ) {
          return 4 ;
        } else if ( distance == Quantity( HMAR, KM ) ) {
          return 5 ;
        } else if ( distance == Quantity( 25, KM ) ) {
          return 6 ;
        } else if ( distance == Quantity( 30, KM ) ) {
          return 7 ;
        } else if ( distance == Quantity( MAR, KM ) ||
            distance == Quantity( 50, KM ) ||
            distance == Quantity( 50, MILES ) ||
            distance == Quantity( 100, KM ) ||
            distance == Quantity( 150, KM ) ||
            distance == Quantity( 100, MILES ) ||
            distance == Quantity( 200, KM ) ) {
          return 8 ;
        } else if ( distance == Quantity( 1500, M ) ||
            distance == Quantity( 1, MILES ) ||
            distance == Quantity( 2000, M ) ||
            distance == Quantity( 3000, M ) ||
            distance == Quantity( 2, MILES ) ||
            distance == Quantity( 4000, M ) ||
            distance == Quantity( 3, MILES ) ||
            distance == Quantity( 5000, M ) ||
            distance == Quantity( 6000, M ) ||
            distance == Quantity( 8000, M ) ||
            distance == Quantity( 5, MILES ) ||
            distance == Quantity( 10000, M ) ) {
          return 9 ;
        } else {
          throw std::runtime_error("unknown distance for age grade" ) ;
        }
      default:
        if( distance == Quantity( 5, KM ) || 
            distance == Quantity( 6, KM ) ||
            distance == Quantity( 4, MILES ) ||
            distance == Quantity( 8, KM ) ||
            distance == Quantity( 5, MILES ) ) {
          return 0 ;
        } else if( distance == Quantity( 10, KM ) ) {
          return 1 ;
        } else if ( distance == Quantity( 12, KM ) ) {
          return 2 ;
        } else if ( distance == Quantity( 15, KM ) ) {
          return 3 ;
        } else if ( distance == Quantity( 10, MILES ) ) {
          return 4 ;
        } else if ( distance == Quantity( 20, KM ) ) {
          return 5 ;
        } else if ( distance == Quantity( HMAR, KM ) ) {
          return 6 ;
        } else if ( distance == Quantity( 25, KM ) ) {
          return 7 ;
        } else if ( distance == Quantity( 30, KM ) ) {
          return 8 ;
        } else if ( distance == Quantity( MAR, KM ) ||
            distance == Quantity( 50, KM ) ||
            distance == Quantity( 50, MILES ) ||
            distance == Quantity( 100, KM ) ||
            distance == Quantity( 150, KM ) ||
            distance == Quantity( 100, MILES ) ||
            distance == Quantity( 200, KM ) ) {
          return 9 ;
        } else if ( distance == Quantity( 1500, M ) ||
            distance == Quantity( 1, MILES ) ||
            distance == Quantity( 2000, M ) ||
            distance == Quantity( 3000, M ) ||
            distance == Quantity( 2, MILES ) ||
            distance == Quantity( 4000, M ) ||
            distance == Quantity( 3, MILES ) ||
            distance == Quantity( 5000, M ) ||
            distance == Quantity( 6000, M ) ||
            distance == Quantity( 8000, M ) ||
            distance == Quantity( 5, MILES ) ||
            distance == Quantity( 10000, M ) ) {
          return 9 ;
        } else {
          throw std::runtime_error("unknown distance for age grade" ) ;
        }
    }
  }
}
