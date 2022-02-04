#include <string>
#include <map>
#include <fstream>
#include "RandMT.hpp"
#include <vector>
#include "Human.hpp"
#include "SimulationParams.hpp"
using namespace std;

class World{
   private:
      int              _size;
      Human ***        _carte;
      int              _nbPlaceHospital;
      int              _nbPlaceReanimation;
      int              _nbHumain;
      int              _nbMalade;
      int              _isVaccin;
      int              _isMedicament;
      float            _tauxProtectionReaMedicament;
      int              _isMasqueTissu;
      float            _tauxProtectionMasqueTissu;
      int              _isMasqueChir;
      float            _tauxProtectionMasqueChir;
      int              _isMasqueFFP2;
      float            _tauxProtectionMasqueFFP2;
      int              _isConfinement;
      int              _nbDeplacementReductionConfinement;
      int              _isDeplacementLimites;
      int              _nbDistanceMax;
      int              _isGelHydroalcolique;
      float            _tauxProtectionTransmissionGelHydro;
      int              _isTestCovid;
      float            _tauxDeDivisionAsymptomatique;
      int              _isCouvreFeu;
      int              _nbDeplacementReductionCouvreFeu;
      int              _isSuperContaminateur;
      int              _nbDeplacementSuperContaminateur;
   
      // On consid�re ici le taux de mortalit� r�el, en supposant qu'on a deux fois plus de chance d'avoir �t� en r�animation (50% des gens en r�a meurent) et deux fois plus de chance d'avoir �t� hospitalis� (50% de personnes hospitalis�s vont en r�a)
      // Ces chiffres sont purement arbitraires, � mettre en param
      //float table_taux_mortalite_by_age_by_10[8] = {0, 0.2, 0.2, 0.4, 1.3, 3.6, 8, 14.8};
        
      float          * _tableTauxMortaliteByAgeBy10;
      float            _tableTauxHospitalisationByAgeBy10[8];
      float            _pourcentAsymptomatique;
      float            _tauxVaccination;
      float            _tauxVaccinationRappel;
      float            _tauxDeChanceDeMourirHospitalFull;
      float            _tauxContaDistanceDeux;
      float          * _histogrammeContamination;
        
      vector<Position> _humanSafePositions;
      vector<Position> _humanAsymptomatiquePositions;
      vector<Position> _humanConfinedPositions;
      vector<Position> _humanHospitalPositions;
      vector<Position> _humanReanimationPositions;
      
      vector<Position> _newHumanSafePositions;
      vector<Position> _newCurrentHumanAsymptomatiquePositions;
      vector<Position> _newNextHumanAsymptomatiquePositions;
      vector<Position> _newHumanConfinedPositions;
      vector<Position> _newHumanHospitalPositions;
      vector<Position> _newHumanReanimationPositions;
   
      bool             _log = false;
      fstream          _logfile;
      int              _iteration = 0;
      float            _r0;
      map<string, int> _stats;

      static const char SYMBOL_EMPTY = '.';
      static constexpr float MAX_HUMANS = 0.8;
      
      vector<int>      _ageOfDeadHumansDaily;
      vector<int>      _ageOfSymptomaticDailyHuman;
      float            _tauxMortRea;
      int              _nbNouveauxCas = 0;
      int              _nbPersonneHospital = 0 ;
      int              _nbPersonneReanimation = 0;
      int              _nbNouveauxHospitalisation = 0;
      int              _nbNouveauxReanimation = 0;
      int              _nbMorts = 0;
      int              _nbCasCovidConnuTotal = 0;


      
      
      //Utilisation des valeurs CSV de Our World In Data.
      double _ratioHospRea[633] =  {0.0,0.25,0.4,0.3333333333333333,0.3333333333333333,0.16666666666666666,0.16666666666666666,0.16666666666666666,0.16666666666666666,0.09090909090909091,0.09090909090909091,0.09090909090909091,0.09090909090909091,0.09090909090909091,0.125,0.08333333333333333,0.10465116279069768,0.07758620689655173,0.2710352849941838,0.25942126514131897,0.24601031180947705,0.24818216609261384,0.24627118644067797,0.24072476272648835,0.2398247434567047,0.24628554560661223,0.2431245858184228,0.24144390806254054,0.2393478122412585,0.24095563139931742,0.23779193205944799,0.24138260288360547,0.2424135497529993,0.24202420242024203,0.2412842983429643,0.2401289282836422,0.24008141984787343,0.23859881031064112,0.2349758192701816,0.23447490877439658,0.23228646126352714,0.22664009409304756,0.221004243281471,0.21669501588626078,0.21203221222169588,0.2093765648472709,0.2053779838784974,0.20020238434051166,0.19693956114461697,0.19065709410514795,0.18787481566442732,0.1851341599422686,0.183310353883527,0.1778948772678762,0.1730516083302393,0.1706110672208292,0.16757722210548434,0.1650485436893204,0.16354841004481752,0.16190885025398868,0.15909008584779222,0.15439856373429084,0.15069486866218693,0.14797163780076716,0.14640208147256417,0.1461595244570496,0.1428627512562814,0.13663414436662483,0.12943292070926732,0.12580491810363456,0.12446484530167277,0.12258837095844237,0.12123366811838948,0.11998739817273504,0.11593125870877845,0.11352277595316293,0.11058281456791334,0.10918640472703399,0.10793929382614083,0.10605118640555383,0.10329183372019414,0.10071160845238741,0.09808746225254446,0.0974496491127974,0.09603508974432966,0.09508235019273449,0.09445968824800047,0.09389559192450125,0.09371336911592325,0.09387598387406412,0.09204882876938304,0.09069179812879874,0.09023658315304627,0.09018288837502628,0.08920418627519842,0.08735155243954786,0.08756034162643891,0.08679332005515551,0.0841897233201581,0.0828440440762487,0.08248086991542489,0.0810987040508599,0.07771716323961393,0.07771664374140302,0.0766199649737303,0.07681198664139363,0.07759572901325479,0.07761166482096715,0.07639861772672084,0.07550047664442326,0.07278419096067305,0.07182539682539682,0.07042821158690177,0.0701593137254902,0.07025976682348128,0.06975538971807628,0.06923565530383231,0.0680786686838124,0.06849164467897977,0.06854428232100442,0.06815834767641997,0.06806462701959436,0.06837903505727178,0.06760098928276999,0.06681944276926788,0.06725903986177958,0.06707777498112258,0.06575098562889482,0.06625969731654585,0.06674353061747373,0.06768211920529801,0.06934105321202096,0.06812447434819176,0.06709401709401709,0.06719085060757685,0.06765841796595623,0.0672813715602939,0.06732300564644564,0.06649207042048597,0.0675155463429079,0.06801083358411074,0.0680374962201391,0.06805407868752848,0.06751183748281656,0.06677018633540373,0.06641366223908918,0.0694843617920541,0.06780556533990842,0.0653177138800142,0.0650709219858156,0.06661916636978982,0.06551724137931035,0.06581623220558329,0.06692913385826772,0.06600722845729504,0.06644774966196638,0.06649961449498844,0.06980802792321117,0.07107986721343487,0.0704914822792246,0.07292289300657502,0.0722334004024145,0.07347922103995182,0.07371794871794872,0.07434052757793765,0.07382820358076846,0.0731958762886598,0.07276119402985075,0.07184628237259816,0.0732821258044426,0.07323651452282158,0.07389969293756397,0.07463934768973447,0.07571637732691905,0.07791657844590302,0.07775423728813559,0.07854855923159018,0.07922272047832586,0.08297598627787307,0.08759283529925732,0.08224917309812568,0.08301970334292672,0.08434801859641355,0.08732269503546099,0.08766880673013062,0.0882997370727432,0.09114696903619712,0.0953619419159081,0.09902702702702702,0.10036535568450462,0.10199271480608528,0.10219288907813498,0.10861116792800164,0.11493322541481182,0.1189568706118355,0.1197557612763443,0.12227414330218069,0.12654559505409582,0.12662586074980872,0.1286731155320314,0.13286219081272085,0.13724137931034483,0.136137339055794,0.1413793103448276,0.1505552521390861,0.15571321882001493,0.16294443451849205,0.16340661242859617,0.1682732961271774,0.17315369261477045,0.17872340425531916,0.17955801104972377,0.17834803528468324,0.18102235422854462,0.18481950015427337,0.18746195982958003,0.189779921615918,0.1884272997032641,0.19124629080118694,0.19170017231476164,0.19365035733919736,0.19208350277890743,0.18711738088900717,0.18650532684466659,0.18347571082493944,0.18254764292878636,0.18017251852751792,0.17748817898742936,0.18290770609318996,0.18140194047748828,0.18165692821368948,0.17872467817583076,0.17963265698624867,0.1779388822611728,0.179553264604811,0.17434660233212707,0.17011092539127792,0.1648939967163966,0.16229562896229563,0.15930165632794013,0.15649690044973866,0.15545295872980125,0.1534687417567924,0.15041617122473247,0.14872400756143667,0.15203358461607908,0.14961108938426107,0.14865878040653116,0.14812898089171975,0.1474354088865178,0.14830431463778126,0.1486110622117382,0.14923156622345018,0.15002041094026397,0.14981632855677268,0.1503955238278989,0.15045906534930267,0.15004072936900809,0.14956819991425246,0.14955930958501654,0.14953184674140693,0.14765506807866868,0.1465069025279388,0.14599112827785993,0.1450428210051507,0.14349817416599617,0.14324705882352942,0.1432488442531484,0.14247192437028108,0.14111736462208654,0.13979865333071845,0.1381244990649212,0.13680759510962365,0.13525506638714185,0.13380006396815808,0.13237165888841748,0.1324524425236459,0.13016551374452212,0.1288816423330616,0.1280224929709466,0.12490963740821064,0.12365591397849462,0.12222983778843957,0.1210648236053621,0.11892434896839503,0.11874167515474418,0.11702845351005993,0.11522270777372409,0.11427769761103095,0.11350021819335898,0.11379621989076191,0.11389693339151823,0.11233288505656198,0.11125690882341246,0.11080376829023852,0.10951287320198236,0.10997155562677777,0.10860680131740803,0.10905663404460132,0.1086834057621117,0.10740846100703053,0.10739357116466193,0.10800196367206677,0.10763606823720552,0.10931223371880706,0.10774764579881178,0.10798045602605863,0.10755111238579096,0.10752998392614269,0.10761305094447625,0.10754640839386602,0.10644179152311513,0.10518274295364079,0.10551238465274405,0.1050718719372754,0.10690404889855191,0.10726072607260725,0.1068254097692245,0.10744800902788973,0.10840788568190099,0.10919749343036184,0.10871392546931914,0.10916070214722699,0.10930558335001,0.10960966911036259,0.10956066291432145,0.11080213065956447,0.11079922027290448,0.11152184909918673,0.11216759431045145,0.11158366841942469,0.11211442880449217,0.1127268670038679,0.11371968154045548,0.11414986546754635,0.11430993807136539,0.11441144114411442,0.11390499963291975,0.11416965872411416,0.11544808782377843,0.11666488279995718,0.1168747540514435,0.1166894763379673,0.11732917452488031,0.11764921140264208,0.11796615073050774,0.11977138774781211,0.12057610190345226,0.12069154174417332,0.12339131402292029,0.12481077808053286,0.12574438845625285,0.12495738797772811,0.12731324118135812,0.12742889864477955,0.12881329785182613,0.13158611035501808,0.1325178389398573,0.13332541849697258,0.1332076657241596,0.13189578413534125,0.13386593920498832,0.13414538924025923,0.1354820871351266,0.13708714683645046,0.1381807995518028,0.13813291139240505,0.13936295713723948,0.14194672050033647,0.1448369240571861,0.14595636977220683,0.14859681001413286,0.14980710659898477,0.1508179547102909,0.15276840642984718,0.15547002103091148,0.15691457407184908,0.16059216348861532,0.1629560790334963,0.1649710186048397,0.16515266717355637,0.16565236169460915,0.16628746273340655,0.16666666666666666,0.16723778014100596,0.16918584000947157,0.1704585503387242,0.16994522872791792,0.1717003926306252,0.17319479742861416,0.17305402589671082,0.17417517384228437,0.17495044416709493,0.17575846509409737,0.17580831408775982,0.17562319045265165,0.17790249035426167,0.17752872149808524,0.178755117035793,0.18288140902920394,0.18254517759468256,0.18193895626107098,0.18166315578292708,0.18362218088057705,0.18538053326430234,0.18671248568155785,0.1898371034755655,0.19078642767378795,0.1903426689706889,0.18923933209647495,0.19061038877858194,0.19120124400673838,0.19316551454284597,0.19407981097400892,0.19377493488080716,0.1913995258046705,0.1912603319023515,0.19249823071479122,0.19251146863087162,0.19524058235946987,0.1958735790787831,0.19794019933554818,0.19737841318057253,0.19613674990194796,0.19626168224299065,0.1965497643007589,0.19683250245871062,0.1961631524369167,0.19511939307065693,0.19380248455826218,0.19447322970639033,0.19361874274457383,0.19511666546268872,0.1938484343153604,0.19391591660020507,0.1939922480620155,0.19269682521223397,0.18974518818670616,0.18950775131852327,0.18895852230559906,0.1877747717281028,0.18593523028283346,0.18610021786492376,0.18529808822888996,0.18400808826761617,0.1820201287514734,0.1809153511031995,0.18163855421686748,0.17967242317779208,0.17930685555274475,0.17824543610547666,0.17745292117151415,0.17740607308286155,0.1790996611628032,0.17869683964104566,0.17971283001389532,0.17973526443877247,0.17842026825633384,0.1774523981682333,0.17559671805072102,0.17610947691520654,0.1751619446443761,0.17370447942706574,0.17375447288742085,0.17397590361445783,0.17258954129721427,0.17119565217391305,0.17196510424367883,0.1715049656226127,0.17015418502202642,0.16885403329065302,0.16875,0.1671246161305964,0.1641025641025641,0.16260092021876899,0.16186791434227102,0.16204134848202645,0.1617130376982243,0.16191291119984788,0.15934912382052763,0.1552856858451125,0.15443659809640772,0.15321550255536626,0.15114254624591947,0.14949024822695037,0.14967727576229692,0.14741125932624916,0.14489393763764924,0.1424683469411904,0.141156462585034,0.13960716061660866,0.13928210313447928,0.13951725009478075,0.1379707916986933,0.1351315961765091,0.13224565592253615,0.1315005417118093,0.13099656357388317,0.13183906445774746,0.13183906445774746,0.1340899537620849,0.13185415488976823,0.13211295586774513,0.1295718741139779,0.12896284607660308,0.12857555619763075,0.12846020761245674,0.12810680301093594,0.1267361111111111,0.12505459309943223,0.12704918032786885,0.12819758894442812,0.1293649624281715,0.12947537629694578,0.13448227150727504,0.13703236654056325,0.13762486126526083,0.14027086788280818,0.14559282900991444,0.14833310838169794,0.14998021369212505,0.15714285714285714,0.16691748181590169,0.16855175805261863,0.17295980511571254,0.17423518164435947,0.17922848664688426,0.17915947035118018,0.18477056085125249,0.1870424997268655,0.18899599263511319,0.19091389329107236,0.19180808715692438,0.1904021558872305,0.1890181669728516,0.18796177716481136,0.19111459046873472,0.19872291021671826,0.19717090069284066,0.19885877318116976,0.2012807034311383,0.19979344662473006,0.20123557735986192,0.20070486173865895,0.20042968400322264,0.20362031700288186,0.20336857194051244,0.20439739413680783,0.20519293184276957,0.20364606491774123,0.20611510791366908,0.20631351740264411,0.20806658130601793,0.20885724852071005,0.20865402665665478,0.20828635851183766,0.20907316166217346,0.21219237272214916,0.21306763747844415,0.21263198682553522,0.21265447355412753,0.2127171092034338,0.21264482620854974,0.2105948327658722,0.20535989321285553,0.20502354788069074,0.20996020221576853,0.20848952590959205,0.2061265709156194,0.20614380555868123,0.20407009609949123,0.2029322783337212,0.19681483242215356,0.1953381085346607,0.195633403231775,0.1968671679197995,0.19727295471603704,0.1968671679197995,0.19535956928598897,0.18974889981879367,0.18691341705221415,0.18286099865047234,0.1816561557444475,0.18144499178981938,0.1819427318810796,0.1802423900789177,0.17647058823529413,0.1738374619730552,0.1710506980161646,0.16805845511482254,0.1680273118598783,0.17015901322633378,0.1675969226127621,0.16527798818360853,0.16480147171546836,0.1624420401854714,0.1629641137175703,0.163151364764268,0.1621830550401979,0.16134505630109516,0.15870069605568446,0.15636138230280489,0.1578125,0.1586326402016383,0.1596361925670378,0.15971896955503512,0.16276183087664856,0.15996301433194637,0.15853844977832135,0.15824915824915825,0.15925812385039853,0.1591600730371272,0.161018225636391,0.1633233532934132,0.16203429923122412,0.1635903542721048,0.16169265033407573,0.1648417579121044,0.16410791474139216,0.16620538965768392,0.16639906582980588,0.16710107153200116,0.16470080552359034,0.16775475447062163,0.17049645390070922,0.17015890873294895,0.17076484173346013,0.1694757796947578,0.16964635260341904,0.17118274046487736,0.1704030226700252,0.1671682969651367,0.1665837272953471};


   public:
      World(SimulationParams*,char *, bool);
      ~World();
      void                         writeLog(string);
      static void                  pause();
      void                         display();
      void                         updateStats(string);
      void                         displayStats();
      bool                         isValid(int,int);
      bool                         isHuman(int,int);
      bool                         isEmpty(int,int);
      void                         addAgent(SimulationParams*,float, RandMT*);
      void                         initialize(SimulationParams*, RandMT*);
      map<string,vector<Position>> vision (int,int,int);
      void                         contamination(int,int,RandMT*, int, int);
      void                         humanGoFromTo(int,int,int,int, bool die = false);
      
      // Si on avait eu plusieurs classes h�ritant de human pour asymp, hops, etc, on aurait pu utiliser le polymorphisme sur une seule fonction.
      void                         moveHumanSafe(int,int, RandMT*);
      void                         moveHumanAsymptomatique(int,int, RandMT*);
      void                         moveHumanConfined(int,int, RandMT*);
      void                         moveHumanHospital(int,int, RandMT*);
      void                         moveHumanReanimation(int,int, RandMT*);
      
      void                         nextIteration(RandMT*);
      void                         startSimulation(SimulationParams*, RandMT*);

};
