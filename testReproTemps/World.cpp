#include "World.hpp"
#include <typeinfo>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

// -------------------------------------------------------------------- //
// World::World:  Constructeur de l'objet World                         //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inSimulationParams :                                              //
//       Permet de récupérer les données du fichier de config           //
//                                                                      //                          
//    inNomFichierLog :                                                 //
//       Détermine le nom du fichier de log dans lequel                 //
//       on va stocker les résultats                                    //
//                                                                      //
//    inLog :                                                           //
//       Booléen pour déterminer si oui ou non on stocke les résultats  //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
World::World(SimulationParams * inSimulationParams,
             char             * inNomFichierLog, 
             bool               inLog)
{
   int     size = 
                     inSimulationParams->getSize();
                     
   int     nbIteration = 
                     inSimulationParams->getNbIteration();
                     
   float * tableTauxHospitalisationByAge = 
                     inSimulationParams->getTableTauxHospitalisationByAge();
                     
   int   * tableTailleHopitaux = 
                     inSimulationParams->getTableTailleHopitaux();
            
   float   facteurTailleHopitaux =
                     inSimulationParams->getFacteurTailleHopitaux();
                     
   float   tauxMortRea = 
                     inSimulationParams->getTauxMortRea();
                     
   float   r0 = 
                     inSimulationParams->getR0();
                     
   int     nbPlaceHospital = 
                     inSimulationParams->getNbPlaceHospital();
                     
   int     nbPlaceReanimation = 
                     inSimulationParams->getNbPlaceReanimation();
                     
   float   pourcentAsymptomatique = 
                     inSimulationParams->getPourcentAsymptomatique();
/*                     
   float   tauxVaccination = 
                     inSimulationParams->getTauxVaccination();
*/ 
           _timelineVaccination =
                     inSimulationParams->getTimelineVaccination();
   
   float   tauxDeChanceDeMourirHospitalFull = 
                     inSimulationParams->getTauxDeChanceDeMourirHospitalFull();
                     
   float * histogrammeContamination = 
                     inSimulationParams->getHistogrammeContamination();
                     
   float   tauxContaDistanceDeux = 
                     inSimulationParams->getTauxContaDistanceDeux();
/*                     
   float   tauxVaccinationRappel =
                     inSimulationParams->getTauxVaccinationRappel();
*/ 
           _timelineVaccinationRappel =
                     inSimulationParams->getTimelineVaccinationRappel();

   int     isVaccin =
                     inSimulationParams->getIsVaccin();

   int     nbHumain =
                     inSimulationParams->getNbHumain();

   int     nbMalade =
                     inSimulationParams->getNbMalade();
                     
   int     nbHopitaux =
                     inSimulationParams->getNbHopitaux();
                     
   float   tauxAugmentationContaminationHopitaux =
                     inSimulationParams->getTauxAugmentationContaminationHopitaux();
            
   float   tauxContaminationHopitaux =
                     inSimulationParams->getTauxContaminationHopitaux();

                     
   int     nbSalleDeSport =
                     inSimulationParams->getNbSalleDeSport();
                     
   float   tauxAugmentationContaminationGym =
                     inSimulationParams->getTauxAugmentationContaminationGym();
            
   float   tauxContaminationGym =
                     inSimulationParams->getTauxContaminationGym();

                     
   int     nbBoiteDeNuit =
                     inSimulationParams->getNbBoiteDeNuit();
                     
                     
   float   tauxAugmentationContaminationClub =
                     inSimulationParams->getTauxAugmentationContaminationClub();
            
   float   tauxContaminationClub =
                     inSimulationParams->getTauxContaminationClub();
                     
   int     nbMagasin =
                     inSimulationParams->getNbMagasin();                     
                     
   float   tauxAugmentationContaminationShop =
                     inSimulationParams->getTauxAugmentationContaminationShop();
            
   float   tauxContaminationShop =
                     inSimulationParams->getTauxContaminationShop();
                     
   int     nbrestaurant =
                     inSimulationParams->getNbRestaurant();                                          
                     
   float   tauxAugmentationContaminationRestaurant =
                     inSimulationParams->getTauxAugmentationContaminationRestaurant();
            
   float   tauxContaminationRestaurant =
                     inSimulationParams->getTauxContaminationRestaurant();
                     
   int     isMedicament =
                     inSimulationParams->getIsMedicament();

   float   tauxProtectionReaMedicament =
                     inSimulationParams->getTauxProtectionReaMedicament();

   int     isMasqueTissu =
                     inSimulationParams->getIsMasqueTissu();

   float   tauxProtectionMasqueTissu =
                     inSimulationParams->getTauxProtectionMasqueTissu();
                     
   int     isMasqueChir =
                     inSimulationParams->getIsMasqueChir();

   float   tauxProtectionMasqueChir =
                     inSimulationParams->getTauxProtectionMasqueChir();
                     
   int     isMasqueFFP2 =
                     inSimulationParams->getIsMasqueFFP2();

   float   tauxProtectionMasqueFFP2 =
                     inSimulationParams->getTauxProtectionMasqueFFP2();

   int     isConfinement =
                     inSimulationParams->getIsConfinement();

   int     nbDeplacementReductionConfinement =
                     inSimulationParams->getNbDeplacementReductionConfinement();
                     
   int     nbLimiteDistanceMaxConfinement = 
                     inSimulationParams->getNbLimiteDistanceMaxConfinement();

   int     isDeplacementLimites =
                     inSimulationParams->getIsDeplacementLimites();

   int     nbDistanceMax =
                     inSimulationParams->getNbDistanceMax();

   int     isGelHydroalcolique =
                     inSimulationParams->getIsGelHydroalcolique();

   float   tauxProtectionTransmissionGelHydro =
                     inSimulationParams->getTauxProtectionTransmissionGelHydro();

   int     isTestCovid =
                     inSimulationParams->getIsTestCovid();

   float   tauxDeDivisionAsymptomatique =
                     inSimulationParams->getTauxDeDivisionAsymptomatique();

   int     isCouvreFeu =
                     inSimulationParams->getIsCouvreFeu();

   int     nbDeplacementReductionCouvreFeu =
                     inSimulationParams->getNbDeplacementReductionCouvreFeu();

   int     nbSuperContaminateur =
                     inSimulationParams->getNbSuperContaminateur();

   int     rayonSuperContaminateur =
                     inSimulationParams->getRayonSuperContaminateur();

   int     nbDeplacementJour =
                     inSimulationParams->getNbDeplacementJour();
                     
   int     nbVariants =
                     inSimulationParams->getNbVariants();
                     
   float * defaultVariantHistoConta =
                     inSimulationParams->getDefaultVariantHistoConta();
   
   float * variantsHistoConta =
                     inSimulationParams->getVariantsHistoConta();
               
   int   * dureeVariants =
                     inSimulationParams->getDureeVariants();
                     
   float * pourcentAsymptomatiqueVariants =
                     inSimulationParams->getPourcentAsymptomatiqueVariants();
                     
   float * tableTauxHospitalisationByAgeVariants =
                     inSimulationParams->getTableTauxHospitalisationByAgeVariants();
  
   _timelineMasqueTissu = 
                     inSimulationParams->getTimelineMasqueTissu();

   _timelineMasqueChir =
                     inSimulationParams->getTimelineMasqueChir();
                     
   _timelineMasqueFFP2 =
                     inSimulationParams->getTimelineMasqueFFP2();
                     
   _timelineGelHydroalcolique = 
                     inSimulationParams->getTimelineGelHydroalcolique();
                     
   _timelineConfinement =
                     inSimulationParams->getTimelineConfinement();
                     
   _timelineCouvreFeu =
                     inSimulationParams->getTimelineCouvreFeu();
                     
   _timelineMedicament =
                     inSimulationParams->getTimelineMedicament();
                     
   _timelineDeplacementLimites = 
                     inSimulationParams->getTimelineDeplacementLimites();
                     
   _tauxObesitePopulation =
                     inSimulationParams->getTauxObesitePopulation();
                     
   _tauxDiabetePopulation =
                     inSimulationParams->getTauxDiabetePopulation();
   

   _carte = (Human ***)malloc(size * sizeof(Human**));
   for(int i = 0; i < size; i++)
   {
      _carte[i] = (Human **)malloc(size * sizeof(Human*));
   }
   
   for(int i = 0; i<size ;i++)
   {
      for(int j = 0; j<size ; j++)
      {
         
         _carte[i][j] = nullptr;
      }
   }
   
   /*
    * La carte de lieu sera un tableau d'octet (char) pour gagner en performance.
    * 
    * 
    * 
    */
   
   
   _carteLieu = (char **) malloc(size * sizeof(char*));
   for(int i =0; i < size; i++)
   {
      _carteLieu[i] = (char *) malloc (size * sizeof(char));
   }
   
   for(int i = 0; i<size ;i++)
   {
      for(int j = 0; j<size ; j++)
      {
         
         _carteLieu[i][j] = 0;
      }
   }
   
   for(int i = 0; i < 256; i++)
   {
      _tabAugmentionContaminationParLieu[i] = 0;
   }
   
   _histogrammeContamination = (float*)malloc( 11 * sizeof(float));
   _histogrammeContamination = histogrammeContamination;
   
   _tableTauxHospitalisationByAge = (float*)malloc( 8 * sizeof(float));
   _tableTauxHospitalisationByAge = tableTauxHospitalisationByAge;
   
   
   
   _size = size;
   _nbIteration = nbIteration;
   _tauxMortRea = tauxMortRea;
   _r0 = r0;
   _nbPlaceHospital = nbPlaceHospital;
   _nbPlaceReanimation = nbPlaceReanimation;
   _pourcentAsymptomatique = pourcentAsymptomatique;
   //_tauxVaccination = tauxVaccination;
   _tauxDeChanceDeMourirHospitalFull = tauxDeChanceDeMourirHospitalFull;
   _tauxContaDistanceDeux = tauxContaDistanceDeux;
   _nbHumain = nbHumain;
   _nbMalade = nbMalade;
   _facteurTailleHopitaux = facteurTailleHopitaux;
   _nbHopitaux = nbHopitaux;
   _tableTailleHopitaux = (int *)malloc( _nbHopitaux * sizeof(int));
   _tableTailleHopitaux = tableTailleHopitaux;
   _tauxAugmentationContaminationHopitaux = tauxAugmentationContaminationHopitaux;
   _tabAugmentionContaminationParLieu['H'] = tauxAugmentationContaminationHopitaux;
   _tauxContaminationHopitaux = tauxContaminationHopitaux;
   _nbSalleDeSport = nbSalleDeSport;
   _tauxAugmentationContaminationGym = tauxAugmentationContaminationGym;
   _tabAugmentionContaminationParLieu['G'] = tauxAugmentationContaminationGym;
   _tauxContaminationGym = tauxContaminationGym;
   _nbBoiteDeNuit = nbBoiteDeNuit;
   _tauxAugmentationContaminationClub = tauxAugmentationContaminationClub;
   _tabAugmentionContaminationParLieu['C'] = tauxAugmentationContaminationClub;
   _tauxContaminationClub = tauxContaminationClub;
   _nbMagasin = nbMagasin;
   _tauxAugmentationContaminationShop = tauxAugmentationContaminationShop;
   _tabAugmentionContaminationParLieu['S'] = tauxAugmentationContaminationShop;
   _tauxContaminationShop = tauxContaminationShop;
   _nbRestaurant = nbrestaurant;
   _tauxAugmentationContaminationRestaurant = tauxAugmentationContaminationRestaurant;
   _tabAugmentionContaminationParLieu['R'] = tauxAugmentationContaminationRestaurant;
   _tauxContaminationRestaurant = tauxContaminationRestaurant;
   _isVaccin = isVaccin;
   //_tauxVaccinationRappel = tauxVaccinationRappel;
   _isMedicament = isMedicament;
   _tauxProtectionReaMedicament = tauxProtectionReaMedicament;
   _isMasqueTissu = isMasqueTissu;
   _tauxProtectionMasqueTissu = tauxProtectionMasqueTissu;
   _isMasqueChir = isMasqueChir;
   _tauxProtectionMasqueChir = tauxProtectionMasqueChir;
   _isMasqueFFP2 = isMasqueFFP2;
   _tauxProtectionMasqueFFP2 = tauxProtectionMasqueFFP2;
   _isConfinement = isConfinement;
   _nbDeplacementReductionConfinement = nbDeplacementReductionConfinement;
   _nbLimiteDistanceMaxConfinement = nbLimiteDistanceMaxConfinement;
   _isDeplacementLimites = isDeplacementLimites;
   _nbDistanceMax = nbDistanceMax;
   _isGelHydroalcolique = isGelHydroalcolique;
   _tauxProtectionTransmissionGelHydro = tauxProtectionTransmissionGelHydro;
   _isTestCovid = isTestCovid;
   _tauxDeDivisionAsymptomatique = tauxDeDivisionAsymptomatique;
   _isCouvreFeu = isCouvreFeu;
   _nbDeplacementReductionCouvreFeu = nbDeplacementReductionCouvreFeu;
   _nbSuperContaminateur = nbSuperContaminateur;
   _rayonSuperContaminateur = rayonSuperContaminateur;
   _nbDeplacementJour = nbDeplacementJour;
   _nbVariants = nbVariants;
   _defaultVariantHistoConta = defaultVariantHistoConta;
   _variantsHistoConta = variantsHistoConta;
   _dureeVariants = dureeVariants;
   _pourcentAsymptomatiqueVariants = pourcentAsymptomatiqueVariants;
   _tableTauxHospitalisationByAgeVariants = tableTauxHospitalisationByAgeVariants;
   _log = inLog;
   _stats["dead"] = 0;
   _stats["contamined"] = 0;
   _stats["recovered"] = 0;
   _stats["safe"] = 0;
   if(_log)
   {
      _logfile.open(inNomFichierLog,ios::out);
   }
   
   initTimeline();


}

// -------------------------------------------------------------------- //
// World::initTimeline  Initialise les valeurs clés du variant au cours //
//                      du temps.                                       //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//   Pas de sortie                                                      //
// -------------------------------------------------------------------- //
void World::initTimeline()
{
   int dureeVariantsCumulative[_nbVariants];
   
   dureeVariantsCumulative[0] = _dureeVariants[0];
   for(int i = 1; i<_nbVariants; i++)
   {
      dureeVariantsCumulative[i] = _dureeVariants[i] + dureeVariantsCumulative[i-1];
   }
   
   _timelineContamination = (float **) malloc(_nbIteration * sizeof(float*));
   for(int i =0; i < _nbIteration; i++)
   {
      _timelineContamination[i] = (float *) malloc (11 * sizeof(float));
   }
   
   int compteur = 0;
   for(int nb = 0; nb<_nbVariants; nb++)
   {
      for(compteur; compteur<dureeVariantsCumulative[nb] ;compteur++)
      {
         for(int j = 0; j<11 ; j++)
         {
            
            _timelineContamination[compteur][j] = _variantsHistoConta[j + 11*nb];
         }
      }
      
      //On remplit la timeline avec les variants, mais s'ils ne font pas toute la durée on complète avec des valeurs par défaut.
      for(compteur; compteur<_nbIteration ;compteur++)
      {
         for(int j = 0; j<11 ; j++)
         {
            
            _timelineContamination[compteur][j] = _defaultVariantHistoConta[j];
         }
      }
   }
   
   
   
   _timelineAsymptomatique = (float *) malloc(_nbIteration * sizeof(float));

   compteur = 0;
   for(int nb = 0; nb<_nbVariants; nb++)
   {
      for(compteur; compteur<dureeVariantsCumulative[nb] ;compteur++)
      { 
         _timelineAsymptomatique[compteur] = _pourcentAsymptomatiqueVariants[nb];
      }
      for(compteur; compteur<_nbIteration; compteur++)
      {
         _timelineAsymptomatique[compteur] = 0.2; //Default asymptomatique
      }
   }
   
   
   
   
   
   _timelineHospByAge = (float **) malloc(_nbIteration * sizeof(float*));
   for(int i =0; i < _nbIteration; i++)
   {
      _timelineHospByAge[i] = (float *) malloc (8 * sizeof(float));
   }
   
   compteur = 0;
   for(int nb = 0; nb<_nbVariants; nb++)
   {
      for(compteur; compteur<dureeVariantsCumulative[nb] ;compteur++)
      {
         for(int j = 0; j<8 ; j++)
         {
            
            _timelineHospByAge[compteur][j] = _tableTauxHospitalisationByAgeVariants[j + 8*nb];
         }
      }
      
      //On remplit la timeline avec les variants, mais s'ils ne font pas toute la durée on complète avec des valeurs par défaut.
      for(compteur; compteur<_nbIteration ;compteur++)
      {
         for(int j = 0; j<8 ; j++)
         {
            
            _timelineHospByAge[compteur][j] = _tableTauxHospitalisationByAgeVariants[j]; //On va dire que le defaut c'est le 1er variant.
         }
      }
   }
   


   
}

// -------------------------------------------------------------------- //
// World::~World:  Destructeur de l'objet World                         //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//   Pas de sortie                                                      //
// -------------------------------------------------------------------- //
World::~World()
{
    
   if(_log)
   {
      _logfile.close();
   }
}



// -------------------------------------------------------------------- //
// World::writeLog:  Permet d'écrire un message dans le fichier de log  //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inSimulationParams :                                              //
//       Permet de récupérer les données du fichier de config           //
//                                                                      //
//    inNomFichierLog :                                                 //
//       Détermine le nom du fichier de log dans lequel                 //
//       on va stocker les résultats                                    //
//                                                                      //
//    inLog :                                                           //
//       Booléen pour déterminer si oui ou non on stocke les résultats  //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void World::writeLog(string inMsg)
{
   _logfile << inMsg;
   _logfile << endl;
}


// -------------------------------------------------------------------- //
// World::pause:  Permet d'afficher un message de pause                 //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//   Pas de sortie                                                      //
// -------------------------------------------------------------------- //
void World::pause()
{
   cout << "Hit <Return to continue" << endl ;
}



// -------------------------------------------------------------------- //
// World::Display:                                                      //
//    Permet d'afficher l'état actuel de la carte et des Humains        //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//   Pas de sortie                                                      //
// -------------------------------------------------------------------- //
void World::display()
{
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << "*****************************************************************";
   for(int row = 0; row<_size; row++)
   {
      cout << "   " << endl;
      for(int column = 0; column<_size; column++ )
      {
         if(_carte[row][column] == nullptr)
         {
            // Null n'existe pas en C++. J'ai initialisé à NULL, 
            //donc j'imagine un tableau rempli de 0.
            cout << World::SYMBOL_EMPTY;
         }
         else
         {            
            cout << _carte[row][column]->to_string();
         }

      }
      cout << endl;
   }
}



// -------------------------------------------------------------------- //
// World::updateStats:                                                  //
//    Permet de mettre à jour les statistiques des Humains.             //
//    Les statistiques sont : Le nombre d'humain qui n'ont pas eu la    //
//    maladie, le nombre d'humain qui ont eu la maladie puis ce sont    //
//    retabli, le nombre d'humain actuellement contaminé, et enfin      //
//    le nombre d'humain qui sont morts.                                //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inState :                                                         //
//       String représentant le changement d'état de l'Humain           //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//   Pas de sortie                                                      //
// -------------------------------------------------------------------- //
void World::updateStats(string inState)
{
   if(inState == "recovered")
   {
      _stats.at("contamined") -= 1;
      _stats.at("recovered") += 1;     
   }
   else if(inState == "dead")
   {
      _stats.at("contamined") -= 1;
      _stats.at("dead") += 1;
   }
   else if(inState == "contamined")
   {
      _stats.at("safe") -= 1;
      _stats.at("contamined") += 1;
   }
   else if(inState == "safe")
   {
      _stats.at("safe") += 1;
   }
}


// -------------------------------------------------------------------- //
// World::displayStats:  Affiche les statistiques                       //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//   Pas de sortie                                                      //
// -------------------------------------------------------------------- //
void World::displayStats()
{
   cout << "***************STATISTICS******************" <<endl;
   cout <<"Safe : " << _stats.at("safe") << endl;
   cout <<"Contamined : " << _stats.at("contamined") << endl;
   cout <<"Recovered : " << _stats.at("recovered") << endl;
   cout <<"Dead : " << _stats.at("dead") << endl;
}


// -------------------------------------------------------------------- //
// World::isValid:  Teste si la position est valide (dans la carte)     //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inRow :                                                           //
//       Ligne de la position à tester                                  //
//    inColumn :                                                        //
//       Colonne de la position à tester                                //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Booléen :                                                         //
//       Oui ou non la position est valide                              //
// -------------------------------------------------------------------- //
bool World::isValid(int inRow, int inColumn)
{
   return inRow >= 0 && inColumn >= 0 && inRow < _size and inColumn < _size;
}



// -------------------------------------------------------------------- //
// World::isHuman:  Teste si la position est un humain                  //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inRow :                                                           //
//       Ligne de la position à tester                                  //
//    inColumn :                                                        //
//       Colonne de la position à tester                                //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Booléen :                                                         //
//       Oui ou non la position est un humain                           //
// -------------------------------------------------------------------- //
bool World::isHuman(int inRow, int inColumn)
{
   if(isValid(inRow,inColumn) && _carte[inRow][inColumn] != nullptr)
   {
      return
         isValid(inRow,inColumn) && 
         (
            _carte[inRow][inColumn]->to_string() == 'X' ||
            _carte[inRow][inColumn]->to_string() == 'O' ||
            _carte[inRow][inColumn]->to_string() == 'H' ||
            _carte[inRow][inColumn]->to_string() == 'R'
               
           );
   }
   return false;

}



// -------------------------------------------------------------------- //
// World::isEmpty:  Teste si la position est vide                       //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inRow :                                                           //
//       Ligne de la position à tester                                  //
//    inColumn :                                                        //
//       Colonne de la position à tester                                //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Booléen :                                                         //
//       Oui ou non la position est vide                                //
// -------------------------------------------------------------------- //
bool World::isEmpty(int inRow, int inColumn)
{
   return isValid(inRow,inColumn) && _carte[inRow][inColumn] == nullptr;
}


// -------------------------------------------------------------------- //
// World::addAgent:  Initialise la carte en ajoutant les Agents         //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inSimulationParams :                                              //
//       Les paramètres du fichier de configuration                     //
//                                                                      //
//    inWorldMax :                                                      //
//        Facteur déterminant le nombre maximal d'humain                //
//        (Param à supprimer ?)                                         //
//                                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//   Pas de sortie                                                      //
// -------------------------------------------------------------------- //
void World::addAgent(SimulationParams * inSimulationParams, 
                     float              inWorldMax 
                    )
{


   int maxAgents = pow(_size,2) * inWorldMax;
   

    /*
   if(_nbHumain > maxAgents)
   {
      cout << "trop d'agent" << endl;
      exit(1);
   }
    */
   if(_nbMalade > _nbHumain)
   {
      cout << "trop de malade" << endl;
      exit(1);
   }

   int tempCompt = _nbSuperContaminateur;
   
   for(int qtyAgent = 0; qtyAgent < _nbHumain-_nbMalade; qtyAgent++)
   {        
      bool  varEmpty = false;
      int   row;
      int   column;
        
      while(!varEmpty)
      {
            
         // On cherche une position libre sur la carte 
         row = randmt->genrand_int32()%_size ;
         column = randmt->genrand_int32()%_size ;
         varEmpty = isEmpty(row,column);
      }

         
      _carte[row][column] = new Human(inSimulationParams,row,column);
      
      //On va créer X super contaminateur parmis les humains.
      if(tempCompt > 0)
      {
         _carte[row][column]->setIsSuperContaminateur(true);
      }
      tempCompt--;
/*      
      if(_isVaccin == 1)
      {
         float randValue = randmt->genrand_real1();
         float randValueRappel = randmt->genrand_real1();
         if(randValue < _tauxVaccination)
         {
            _carte[row][column]->vaccine();
            if(randValueRappel < _tauxVaccinationRappel)
            {
                _carte[row][column]->vaccineRappel();
            }
            
         }
         
      }
      */
      
      float randValue = randmt->genrand_real1();
      if(randValue < _tauxObesitePopulation)
      {
         _carte[row][column]->setIsObese();
      }
      
      randValue = randmt->genrand_real1();
      if(randValue < _tauxDiabetePopulation)
      {
         _carte[row][column]->setIsDiabete();
      }
      
      
      
      updateStats("safe");
      _humanSafePositions.push_back(_carte[row][column]->getPosition());
      
   }
   


   for(int qtyAgents = 0; qtyAgents<_nbMalade;qtyAgents++)
   {
      
      bool varEmpty = false;
      int row;
      int column;
      while(!varEmpty)
      {
         row = randmt->genrand_int32()%_size ;
         column = randmt->genrand_int32()%_size ;
         varEmpty = isEmpty(row,column);
      }
      
      _carte[row][column] = new Human(inSimulationParams,row,column);
      updateStats("safe");
      _carte[row][column]->contamine();
      updateStats("contamined");
      _humanAsymptomatiquePositions.push_back(_carte[row][column]->getPosition());
      

   }
   

   
   for(int qtyShop = 0; qtyShop < _nbMagasin; qtyShop++)
   {
      int row;
      int column;
      
      row = randmt->genrand_int32()%_size ;
      column = randmt->genrand_int32()%_size ;
      
      int taille = 20; //Choix arbitraire, 400m² magasin.
      
      
      for(int i = row; i < row+taille; i++)
      {
         for(int j = column; j < column+taille; j++)
         {
            if(isValid(i,j))
            {
               _carteLieu[i][j] = 'S';
            }
            
         }
      }
      
   }
   
   
   for(int qtyRestaurant = 0; qtyRestaurant < _nbRestaurant; qtyRestaurant++)
   {
      int row;
      int column;
      
      row = randmt->genrand_int32()%_size ;
      column = randmt->genrand_int32()%_size ;
      
      int taille = 20; //Choix arbitraire, 400m² magasin.
      
      
      for(int i = row; i < row+taille; i++)
      {
         for(int j = column; j < column+taille; j++)
         {
            if(isValid(i,j))
            {
               _carteLieu[i][j] = 'R';
            }
            
         }
      }
      
   }
   
   for(int qtyGym = 0; qtyGym < _nbSalleDeSport; qtyGym++)
   {
      int row;
      int column;
      
      row = randmt->genrand_int32()%_size ;
      column = randmt->genrand_int32()%_size ;
      
      int taille = 20; //Choix arbitraire, 400m² salle de sport.
      
      
      for(int i = row; i < row+taille; i++)
      {
         for(int j = column; j < column+taille; j++)
         {
            if(isValid(i,j))
            {
               _carteLieu[i][j] = 'G';
            }
            
         }
      }
      
   }
   for(int qtyClub = 0; qtyClub < _nbBoiteDeNuit; qtyClub++)
   {
      int row;
      int column;
      
      row = randmt->genrand_int32()%_size ;
      column = randmt->genrand_int32()%_size ;
      
      int taille = 20; //Choix arbitraire, 400m² club.
      
      
      for(int i = row; i < row+taille; i++)
      {
         for(int j = column; j < column+taille; j++)
         {
            if(isValid(i,j))
            {
               _carteLieu[i][j] = 'C';
            }
         }
      }
      
   }
   
   for(int qtyHopitaux = 0; qtyHopitaux < _nbHopitaux; qtyHopitaux++)
   {
      int row;
      int column;
      
      row = randmt->genrand_int32()%_size ;
      column = randmt->genrand_int32()%_size ;
      
      int taille = sqrt(_tableTailleHopitaux[qtyHopitaux]);
      taille = taille * _facteurTailleHopitaux;
      
      for(int i = row; i < row+taille; i++)
      {
         for(int j = column; j < column+taille; j++)
         {
            if(isValid(i,j))
            {
               _carteLieu[i][j] = 'H';
            }
            
         }
      }
   }
   

   //Portion de test
   int compteCase = 0;
   for(int i = 0; i < _size; i++)
   {
      for(int j = 0; j < _size; j++)
      {
         if(_carteLieu[i][j] != 0)
         {
            compteCase++;
         }
         
      }

   }
   
   printf("Le pourcentage de carte recouverte par des lieu est de : %f %%\n",((double)compteCase/(double)(_size*_size))*100);
   
   

}


// -------------------------------------------------------------------- //
// World::initialize:  Initialise en appelant addAgent                  // 
//                     (Fonction inutile ?)                             //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inSimulationParams :                                              //
//       Les paramètres du fichier de configuration                     //
//                                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//   Pas de sortie                                                      //
// -------------------------------------------------------------------- //
void World::initialize(SimulationParams * inSimulationParams)
{
   addAgent(inSimulationParams,World::MAX_HUMANS);
}



// -------------------------------------------------------------------- //
// World::vision:  Détermine le contenu des cases voisines d'une cases  //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inLength :                                                        //
//       La distance à observer (voisinage de Moore)                    //
//                                                                      //
//    inRow :                                                           //
//       La ligne de départ (Position X)                                //
//                                                                      //
//    inColumn :                                                        //
//       La colonne de départ (Position Y)                              //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Un dictionnaire/map associant les cases vides à une liste de      //
//    positions et les cases occupées à une liste de positions.         // 
// -------------------------------------------------------------------- //
map<string,vector<Position>> World::vision(int inLength,
                                           int inRow, 
                                           int inColumn)
{


   Position                      maPositionTest;
   map<string, vector<Position>> neighborhood;

   neighborhood["empty"];
   neighborhood["human"];
    

   for(int elt_1 = 0-inLength; elt_1<inLength+1;elt_1++)
   {
      for(int elt_2 = 0-inLength; elt_2<inLength+1;elt_2++)
      {

         maPositionTest.setPosX(elt_1);
         maPositionTest.setPosY(elt_2);

         bool isInNeighborhood = false;

         for(Position  temp: neighborhood.at("empty") )
         {
            if(temp == maPositionTest)
            {
               isInNeighborhood = true;
            }
         }
         for(Position  temp: neighborhood.at("human") )
         {

            if(temp == maPositionTest)
            {
               isInNeighborhood = true;
            }
         }


         
         // Tous ça pour ça : and (elt_1, elt_2) not in neighborhood
         if((elt_1 != 0 || elt_2 !=0) && !isInNeighborhood )
         {
            
            
            if(isHuman(inRow+elt_1,inColumn+elt_2))
            {
               neighborhood["human"].push_back(_carte[inRow+elt_1][inColumn+elt_2]->getPosition());
            }
            if(isEmpty(inRow+elt_1,inColumn+elt_2))
            {
               Position pos;
               pos.setPosX(inRow+elt_1);
               pos.setPosY(inColumn+elt_2);
               neighborhood["empty"].push_back(pos);
            }
            
         }
      }
   }

   return neighborhood;
}





// -------------------------------------------------------------------- //
// World::Contamination:                                                // 
//    Un malade essaye de contaminer ses voisins sains                  //
//    lors d'un déplacement                                             //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inRow :                                                           //
//       La ligne de destination de l'humain malade                     //
//                                                                      //
//    inColumn :                                                        //
//       La colonne de destination de l'humain malade                   //
//                                                                      //
//                                                                      //
//    inCurrentRow :                                                    //
//       La ligne actuelle de l'humain malade                           //
//                                                                      //
//    inCurrentColumn :                                                 //
//       La colonne actuelle de l'humain malade                         //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void World::contamination(int inRow, int inColumn, int inCurrentRow, int inCurrentColumn)
{
   map<string, vector<Position>> target_v1;

   if(_carte[inCurrentRow][inCurrentColumn]->getIsSuperContaminateur())
   {
      target_v1 = vision(_rayonSuperContaminateur,inRow,inColumn);
   }
   else
   {
      target_v1 = vision(2,inRow,inColumn);
   }
   
   Position                      maPositionTest;

   
   for(Position  pos : target_v1["human"])
   {
   
      if(!_carte[pos.getPosX()][pos.getPosY()]->isSick())
      {
      
         float randomValue = randmt->genrand_real1();

         int distanceRow = abs(inRow - pos.getPosX());
         int distanceColumn = abs(inColumn - pos.getPosY());
         int distance;
         
         if(distanceRow > distanceColumn)
         {
            distance = distanceRow;
         }
         else
         {
            distance = distanceColumn;
         }

         if(distance == 1 || _carte[inCurrentRow][inCurrentColumn]->getIsSuperContaminateur())
         {   
            if(_isMasqueTissu)
            {
               if(_isGelHydroalcolique)
               {
                  if(randomValue 
                     < 
                     ((_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * (1 - _tauxProtectionMasqueTissu))
                      * (1 - _tauxProtectionTransmissionGelHydro)
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1){
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                   }
               }
               else
               {
                  if(randomValue 
                     < 
                     (_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * (1 - _tauxProtectionMasqueTissu)
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1){
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                   }
               
               }
 
            }
            else if(_isMasqueChir)
            {
               if(_isGelHydroalcolique)
               {
                  if(randomValue 
                     < 
                     ((_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * (1 - _tauxProtectionMasqueChir))
                      * (1 - _tauxProtectionTransmissionGelHydro)
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1){
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                   }
               }
               else
               {
                  if(randomValue 
                     < 
                     (_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * (1 - _tauxProtectionMasqueChir)
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1){
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                   }
               
               }
            }
            else if(_isMasqueFFP2)
            {
               if(_isGelHydroalcolique)
               {
                  if(randomValue 
                     < 
                     ((_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * (1 - _tauxProtectionMasqueFFP2))
                      * (1 - _tauxProtectionTransmissionGelHydro)
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1){
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                   }
               }
               else
               {
                  if(randomValue 
                     < 
                     (_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * (1 - _tauxProtectionMasqueFFP2)
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1)
                      {
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                  }
               
               }
            }
            else
            {
               if(_isGelHydroalcolique)
               {
                  if(randomValue 
                     < 
                     (_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * (1 - _tauxProtectionTransmissionGelHydro)
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1)
                      {
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                  }
               }
               else
               {
                  if(randomValue 
                     < 
                     _timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        )
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1)
                      {
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                  }
               }
            }
         }
         else if(distance == 2)
         {
            if(_isMasqueTissu)
            {
               if(_isGelHydroalcolique)
               {
                  if(randomValue 
                     < 
                     (((_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * (1 - _tauxProtectionMasqueTissu))
                      * (1 - _tauxProtectionTransmissionGelHydro))
                      * _tauxContaDistanceDeux
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1)
                      {
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                  }
               }
               else
               {
                  if(randomValue 
                     < 
                     ((_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * (1 - _tauxProtectionMasqueTissu))
                      * _tauxContaDistanceDeux
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1)
                      {
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                  }
               
               }
 
            }
            else if(_isMasqueChir)
            {
               if(_isGelHydroalcolique)
               {
                  if(randomValue 
                     < 
                     (((_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * (1 - _tauxProtectionMasqueChir))
                      * (1 - _tauxProtectionTransmissionGelHydro))
                      * _tauxContaDistanceDeux
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1)
                      {
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                  }
               }
               else
               {
                  if(randomValue 
                     < 
                     ((_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * (1 - _tauxProtectionMasqueChir))
                      * _tauxContaDistanceDeux
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1){
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()
                                                              ));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                  }
               
               }
            }
            else if(_isMasqueFFP2)
            {
               if(_isGelHydroalcolique)
               {
                  if(randomValue 
                     < 
                     (((_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * (1 - _tauxProtectionMasqueFFP2))
                      * (1 - _tauxProtectionTransmissionGelHydro))
                      * _tauxContaDistanceDeux
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1){
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                  }
               }
               else
               {
                  if(randomValue 
                     < 
                     ((_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * ( 1 - _tauxProtectionMasqueFFP2))
                      * _tauxContaDistanceDeux
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1){
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                  }
               }
            }
            else{
               if(_isGelHydroalcolique)
               {
                  if(randomValue 
                     < 
                     ((_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * ( 1 - _tauxProtectionTransmissionGelHydro))
                      * _tauxContaDistanceDeux
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1){
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                  }
               }
               else
               {
                  if(randomValue 
                     < 
                     (_timelineContamination[_iteration][
                            _carte[inCurrentRow][inCurrentColumn]
                               ->getState()-1
                                        ] 
                      * (1 - _carte[pos.getPosX()][pos.getPosY()]
                         ->getTauxDeProtectionInfection()
                        ))
                      * _tauxContaDistanceDeux
                      * (1 + _tabAugmentionContaminationParLieu[_carteLieu[pos.getPosX()][pos.getPosY()]])
                    )
                
                
                  {               
                      _carte[pos.getPosX()][pos.getPosY()]->contamine();
                      if(_carte[pos.getPosX()][pos.getPosY()]->getNumberOfInfections() > 1){
                         _nbHumainContaminePlusieursFois++;
                      }
                      _nbNouveauxCas++;
                      _newNextHumanAsymptomatiquePositions.push_back(
                                                      Position(pos.getPosX(),
                                                               pos.getPosY()));
               
               
                      maPositionTest.setPosX(pos.getPosX());
                      maPositionTest.setPosY(pos.getPosY());
                      int index = 0;
                      for(Position  temp: _newHumanSafePositions )
                      {
                         if(temp == maPositionTest)
                         {
                            _newHumanSafePositions.erase(
                                           _newHumanSafePositions.begin()+index
                                                       );
                         }
                         index++;
                      }

                      updateStats("contamined");
                  }
               }
            }
         }
      }
   }
}



// -------------------------------------------------------------------- //
// World::humanGoFromTo:                                                //
//    Déplace un humain sur la carte, et le tue s'il doit mourir        //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inFromRow :                                                       //
//       La ligne actuelle de l'humain                                  //
//                                                                      //
//    inFromColumn :                                                    //
//       La colonne actuelle de l'humain                                //
//                                                                      //
//    inToRow :                                                         //
//       La ligne de destination de l'humain                            //
//                                                                      //
//    inToColumn :                                                      //
//        La colonne de destination de l'humain                         //
//                                                                      //
//    inDie :                                                           //
//       Booléen pour définir si l'humain doit mourir                   //
//                                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void World::humanGoFromTo(int  inFromRow,
                          int  inFromColumn, 
                          int  inToRow, 
                          int  inToColumn, 
                          bool inDie)
{
    
   if(!inDie)
   {   
      _carte[inToRow][inToColumn] = _carte[inFromRow][inFromColumn];
      _carte[inToRow][inToColumn]->setPosition(inToRow,inToColumn);
      _carte[inFromRow][inFromColumn] = nullptr;

   }
   else
   {
      _carte[inFromRow][inFromColumn] = nullptr;
      updateStats("dead");
   }
}





// -------------------------------------------------------------------- //
// World::moveHumanSafe:  Réalise le comportement des humains sains     //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inRow :                                                           //
//       La ligne de l'humain sur la carte (Position X sur la carte)    //
//                                                                      //
//    inColumn :                                                        //
//       La colonne de l'humain sur la carte (Position Y sur la carte)  //
//                                                                      //
//                                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void World::moveHumanSafe(int inRow, int inColumn)
{

   _carte[inRow][inColumn]->updateHumanProtection();
   if(_carte[inRow][inColumn]->getTauxDeProtectionReanimation() > 0)
   {
      _carte[inRow][inColumn]->decreaseResistance();
   }
   
   int rowDeplacement;
   int columnDeplacement;
   if(_isDeplacementLimites)
   {
      //a + (b - a) * randNum0-1
      rowDeplacement = (inRow-_nbDistanceMax) 
                       +
                       ((inRow + _nbDistanceMax)
                       - 
                       (inRow - _nbDistanceMax))
                       * 
                       randmt->genrand_real1();
      columnDeplacement = 
                       (inColumn-_nbDistanceMax) 
                       +
                       ((inColumn + _nbDistanceMax)
                       - 
                       (inColumn - _nbDistanceMax))
                       * 
                       randmt->genrand_real1();
   }
   if(_isConfinement && (_nbLimiteDistanceMaxConfinement < _nbDistanceMax))
   {
      //a + (b - a) * randNum0-1
      rowDeplacement = (inRow-_nbLimiteDistanceMaxConfinement) 
                       +
                       ((inRow + _nbLimiteDistanceMaxConfinement)
                       - 
                       (inRow - _nbLimiteDistanceMaxConfinement))
                       * 
                       randmt->genrand_real1();
      columnDeplacement = 
                       (inColumn-_nbLimiteDistanceMaxConfinement) 
                       +
                       ((inColumn + _nbLimiteDistanceMaxConfinement)
                       - 
                       (inColumn - _nbLimiteDistanceMaxConfinement))
                       * 
                       randmt->genrand_real1();
   }
   else
   {
      // Il peut se déplacer de 0 à size
      rowDeplacement = randmt->genrand_int32()%_size; 
      columnDeplacement = randmt->genrand_int32()%_size; 
   }
   
 
   map<string, vector<Position>> target_v1 = vision(1,rowDeplacement,columnDeplacement);

   if(target_v1["empty"].size() != 0)
   {
      int taille = target_v1.at("empty").size();
      int randomValue = ((long)floor(randmt->genrand_int32()))%taille;
      humanGoFromTo(inRow,
                    inColumn, 
                    target_v1.at("empty").at(randomValue).getPosX(),
                    target_v1.at("empty").at(randomValue).getPosY()
                   );
      _newHumanSafePositions.push_back(target_v1.at("empty").at(randomValue));
   }
   else
   {
      _newHumanSafePositions.push_back(_carte[inRow][inColumn]->getPosition());
   }


}




// -------------------------------------------------------------------- //
// World::moveHumanAsymptomatique:                                      //
//    Réalise la comportement des humains asymptomatique                //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inRow :                                                           //
//       La ligne de l'humain sur la carte (Position X sur la carte)    //
//                                                                      //
//    inColumn :                                                        //
//       La colonne de l'humain sur la carte (Position Y sur la carte)  //
//                                                                      //
//                                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void World::moveHumanAsymptomatique(int inRow, int inColumn, int inRowDepart, int inColumnDepart)
{

   /*
   
   ATTENTION :
   INCREMENTSTATE() dans le code apellant, pas ici. 
   On peut faire plusieurs déplacement dans 1 seule journée (sans augmenter le state)
   
   */

   if(_carte[inRow][inColumn]->getState() > 10)
   {
      _carte[inRow][inColumn]->resetState();
      updateStats("recovered");
      _newHumanSafePositions.push_back(Position(inRow, inColumn)); 
      return;
          
   }
   
   if(_carte[inRow][inColumn]->getState() == 3)
   {
         // Proportion de asymptomatique varie de 15 à 30% selon les études. Param ?
         // https://www.inspq.qc.ca/sites/default/files/covid/2989-asymptomatiques-potentiel-transmission-covid19.pdf


         float randValue = randmt->genrand_real1();
         if(randValue < 1 - _timelineAsymptomatique[_iteration])
         {
            // entre 15% et 30% de chance qu'il soit asymptomatique et qu'il continue de se déplacer
            _nbCasCovidConnuTotal++;
            _ageOfSymptomaticDailyHuman.push_back(_carte[inRow][inColumn]->getAge());
            _carte[inRow][inColumn]->getConfined();
            _newHumanConfinedPositions.push_back(Position(inRow, inColumn));
            return;
         }       
   }
   
   /*
   L'individu ne contamine que si il se déplace. 
   Il y a 2 tour ou tous le monde est forcément asymptomatique (2jours de contamination potentielle)
   Ensuite, si on est malade, on se confine, si on est a l'hopital, on est confiné, et si on est en réanimation ou mort, on est confiné aussi.
   Si on est malade, on ne se déplace pas.
   De plus, on est contagieux que pendant 9 jours. (2 jours avant symptomes + 9 jours après)
   */
   
   if(_carte[inRow][inColumn]->getState() < 12)
   {
   

      int rowDeplacement;
      int columnDeplacement;
      if(_isDeplacementLimites)
      {
         //a + (b - a) * randNum0-1
         rowDeplacement = (inRowDepart-_nbDistanceMax) 
                          +
                          ((inRowDepart + _nbDistanceMax)
                          - 
                          (inRowDepart - _nbDistanceMax))
                          * 
                          randmt->genrand_real1();
         columnDeplacement = 
                          (inColumnDepart-_nbDistanceMax) 
                          +
                          ((inColumnDepart + _nbDistanceMax)
                          - 
                          (inColumnDepart - _nbDistanceMax))
                          * 
                          randmt->genrand_real1();
      }
      if(_isConfinement && (_nbLimiteDistanceMaxConfinement < _nbDistanceMax))
      {
         //a + (b - a) * randNum0-1
         rowDeplacement = (inRowDepart-_nbLimiteDistanceMaxConfinement) 
                          +
                          ((inRowDepart + _nbLimiteDistanceMaxConfinement)
                          - 
                          (inRowDepart - _nbLimiteDistanceMaxConfinement))
                          * 
                          randmt->genrand_real1();
         columnDeplacement = 
                          (inColumnDepart-_nbLimiteDistanceMaxConfinement) 
                          +
                          ((inColumnDepart + _nbLimiteDistanceMaxConfinement)
                          - 
                          (inColumnDepart - _nbLimiteDistanceMaxConfinement))
                          *  
                          randmt->genrand_real1();
      }
      else
      {
         // Il peut se déplacer de 0 à size
         rowDeplacement = randmt->genrand_int32()%_size; 
         columnDeplacement = randmt->genrand_int32()%_size; 
      }
      map<string, vector<Position>> target_v1 = vision(1,rowDeplacement,columnDeplacement);


      if(target_v1["empty"].size() != 0)
      {
     
         int taille = target_v1.at("empty").size();
         int randomValue = ((long)floor(randmt->genrand_int32()))%taille;

         contamination(target_v1.at("empty").at(randomValue).getPosX(),
                       target_v1.at("empty").at(randomValue).getPosY(),
                       inRow,
                       inColumn
                      );

         humanGoFromTo(inRow,
                       inColumn, 
                       target_v1.at("empty").at(randomValue).getPosX(),
                       target_v1.at("empty").at(randomValue).getPosY()
                      );


         _newCurrentHumanAsymptomatiquePositions.push_back(
                                          target_v1.at("empty").at(randomValue)
                                                          );
         
      }
      else
      {
         contamination(inRow,inColumn, inRow, inColumn);
         _newCurrentHumanAsymptomatiquePositions.push_back(
                                         _carte[inRow][inColumn]->getPosition()
                                                          );
      }
   
   }
}





// -------------------------------------------------------------------- //
// World::moveHumanConfined:                                            //
//    Réalise la comportement des humains confiné                       //
//    Les humains contaminés qui ne sont pas asymptomatique             //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inRow :                                                           //
//       La ligne de l'humain sur la carte (Position X sur la carte)    //
//                                                                      //
//    inColumn :                                                        //
//       La colonne de l'humain sur la carte (Position Y sur la carte)  //
//                                                                      //
//                                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void World::moveHumanConfined(int inRow, int inColumn)
{

   _carte[inRow][inColumn]->updateHumanProtection();
   if(_carte[inRow][inColumn]->getState() > 10)
   {   
      _carte[inRow][inColumn]->resetState();
      _newHumanSafePositions.push_back(_carte[inRow][inColumn]->getPosition());
      updateStats("recovered");
      return;
   
   }
   
   if(_carte[inRow][inColumn]->getState() == 4)
   {         
         //Si la personne est symtomatique, alors elle a des chances d'aller a l'hopital
         float randValue = randmt->genrand_real1();

         if(randValue 
            < 
            (_timelineHospByAge[_iteration][
                      _carte[inRow][inColumn]->getAge()
                                           ]
                                              /100)
             * ( 1 -_carte[inRow][inColumn]->getTauxDeProtectionHospitalisation())
             * (1 + _carte[inRow][inColumn]->getTauxComorbiditeHosp())
           )
             
         {
            if(_nbPersonneHospital < _nbPlaceHospital)
            {
               _carte[inRow][inColumn]->goToHospital();
               _newHumanHospitalPositions.push_back(
                                         _carte[inRow][inColumn]->getPosition()
                                                   );
               _nbNouveauxHospitalisation++;
               _nbPersonneHospital++;
            }
            else
            {
               // Si il n'y a plus de place a l'hopital et qu'on a besoin d'etre hospitalisé, 20% de chance de mourir

               
               if(randValue < _tauxDeChanceDeMourirHospitalFull)
               {
                  _ageOfDeadHumansDaily.push_back(
                                       _carte[inRow][inColumn]->getAge()
                                                 );
                  humanGoFromTo(inRow,inColumn, 0,0, true);
                  _nbMorts++;
                  return;
               }
            }
            
         }
         else
         {
            _newHumanConfinedPositions.push_back(
                                      _carte[inRow][inColumn]->getPosition()
                                                );
         }   
      }
      else
      {
         _newHumanConfinedPositions.push_back(
                                   _carte[inRow][inColumn]->getPosition()
                                             );
      }
   
   _carte[inRow][inColumn]->incrementState();

}




// -------------------------------------------------------------------- //
// World::moveHumanHospital:                                            //
//    Réalise le comportement des humains à l'hopital                   //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inRow :                                                           //
//       La ligne de l'humain sur la carte (Position X sur la carte)    //
//                                                                      //
//    inColumn :                                                        //
//       La colonne de l'humain sur la carte (Position Y sur la carte)  //
//                                                                      //
//                                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void World::moveHumanHospital(int inRow, int inColumn)
{

   _carte[inRow][inColumn]->updateHumanProtection();
   if(_carte[inRow][inColumn]->getState() > 10)
   { 
      _newHumanSafePositions.push_back(_carte[inRow][inColumn]->getPosition());
      _nbPersonneHospital--;
      _carte[inRow][inColumn]->resetState();
      updateStats("recovered");
      return;
   }
   
   if(_carte[inRow][inColumn]->getState() == 5)
   {
   
         float randValue = randmt->genrand_real1();
         float tauxReaIfHospByAge[8] = {0};
         float tauxReaIfHosp;
         
         // On utilise la timeline, qui possède 633 jours. Si la simu dure plus longtemps (prédictions), alors on part sur une base de 15%
         if(_iteration < 633)
         {
               tauxReaIfHosp = _ratioHospRea[_iteration];
         }
         else
         {
            tauxReaIfHosp = 0.15; // La moyenne est 0.1474089554531037
         }
         
         for(int i = 0; i<8; i++)
         {
             tauxReaIfHospByAge[i] = tauxReaIfHosp * ((i +1)/2);
         }
         if(_isMedicament)
         {
            if(randValue 
               < 
               (tauxReaIfHospByAge[_carte[inRow][inColumn]->getAge()] * _tauxProtectionReaMedicament)
               * (1 - _carte[inRow][inColumn]->getTauxDeProtectionReanimation())
               * (1 + _carte[inRow][inColumn]->getTauxComorbiditeRea())
               
              )
            {
            
               if(_nbPersonneReanimation < _nbPlaceReanimation)
               {
               
                  _nbPersonneHospital--;
                  _newHumanReanimationPositions.push_back(
                                            _carte[inRow][inColumn]->getPosition()
                                                         );
               
                  _carte[inRow][inColumn]->goToReanimation();
                  _nbNouveauxReanimation++;
                  _nbPersonneReanimation++;
               }
               else
               {
                  // Si la personne doit aller en réanimation mais qu'il n'y a plus de place, elle meurt.
                  _nbPersonneHospital--;
               
                  _ageOfDeadHumansDaily.push_back(_carte[inRow][inColumn]->getAge());
                  humanGoFromTo(inRow,inColumn, 0,0,true);
                  _nbMorts++;
                  return;
               }
            
            }
            else
            {
               _newHumanHospitalPositions.push_back(
                                      _carte[inRow][inColumn]->getPosition()
                                                   );
            } 
         
         }
         else
         {
            if(randValue 
               < 
               tauxReaIfHospByAge[_carte[inRow][inColumn]->getAge()] 
               * (1 - _carte[inRow][inColumn]->getTauxDeProtectionReanimation())
               * (1 + _carte[inRow][inColumn]->getTauxComorbiditeRea())
              )
            {
            
               if(_nbPersonneReanimation < _nbPlaceReanimation)
               {
               
                  _nbPersonneHospital--;
                  _newHumanReanimationPositions.push_back(
                                            _carte[inRow][inColumn]->getPosition()
                                                         );
               
                  _carte[inRow][inColumn]->goToReanimation();
                  _nbNouveauxReanimation++;
                  _nbPersonneReanimation++;
               }
               else
               {
                  // Si la personne doit aller en réanimation mais qu'il n'y a plus de place, elle meurt.
                  _nbPersonneHospital--;
               
                  _ageOfDeadHumansDaily.push_back(_carte[inRow][inColumn]->getAge());
                  humanGoFromTo(inRow,inColumn, 0,0,true);
                  _nbMorts++;
                  return;
               }
            
            }
            else
            {
               _newHumanHospitalPositions.push_back(
                                      _carte[inRow][inColumn]->getPosition()
                                                   );
            } 
         }
      }
      else
      {
         _newHumanHospitalPositions.push_back(
                                   _carte[inRow][inColumn]->getPosition()
                                             );
      }
      
   
   
      _carte[inRow][inColumn]->incrementState();

}




// -------------------------------------------------------------------- //
// World::moveHumanReanimation:                                         //
//    Réalise le comportement des humains en réanimation                //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inRow :                                                           //
//       La ligne de l'humain sur la carte (Position X sur la carte)    //
//                                                                      //
//    inColumn :                                                        //
//       La colonne de l'humain sur la carte (Position Y sur la carte)  //
//                                                                      //
//                                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void World::moveHumanReanimation(int inRow, int inColumn)
{
   /*
   Selon les données de l'AP-HP, la durée moyenne de séjour des patients Covid-19 en réanimation est passée de 19 jours avant le 1er juillet à 9,5 jours après le 1er juillet,
   a indiqué à APMnews Frédéric Adnet, chef de service du Samu de Seine-Saint-Denis et chef des urgences de l'hôpital Avicenne à Bobigny. 
   Entre les 2 périodes, l'âge médian est passé de 61 ans à 64 ans.
   
   Dans le service de réanimation du Pr Demoule, 
   "la durée de séjour en réanimation est de 5 jours pour les patients non intubés.
   S'ils sont intubés ils restent quand même 3 semaines (même si on manque encore de recul par rapport à la 2e vague)".
   
   https://www.apmnews.com/depeche/1/355843/covid-19-en-reanimation-une-prise-en-charge-amelioree%2C-des-patients-un-peu-moins-severes
   */
   
   
   // Ici ça ne va pas car appelé a chaque boucle => attribut durée réanimation propre a chaque humain fixé au départ?


   //double dureeReanimation = (rand->genrand_int32()%21) + 10; // Entre 5 jours et 21 jours de réanimation. (on a deja fait 5 jours de maladie)
 
   _carte[inRow][inColumn]->updateHumanProtection();
   if(_carte[inRow][inColumn]->getState() 
       >
       _carte[inRow][inColumn]->getDureeReanimation()
     )
   {
      _newHumanSafePositions.push_back(_carte[inRow][inColumn]->getPosition());
      _nbPersonneReanimation--;
      _carte[inRow][inColumn]->resetState();
      updateStats("recovered");
      return;
   }   
 

      
      
      
      
   if(_carte[inRow][inColumn]->getState() == 6)
   {
      
      float randValue = randmt->genrand_real1();
      // 50% de chances de mourir si on était en réa.
      // L'objectif serait de retrouver 14%, 8%, etc. Mais au niveau des probas c'est sur que ça ne va pas le faire :
      // Pour retrouver 14 % : sur 100% de contaminé -> 60% d'aller a l'hopital -> 15% d'aller en réa -> 50% de mourir.
      // En partant de contaminé, la chance de mourir : 0.6 * 0.15 * 0.5 = 0.045. Très très loin de 0.14.
      // Meme en prenant 100% de anciens a l'hopital, 0.15% *0.5 = 0.075. Il faudrait que les anciens aient quasi 100% de chances de mourir en réa
      
      if(randValue < _tauxMortRea)
      {

         _nbPersonneReanimation--;
         
         _ageOfDeadHumansDaily.push_back(_carte[inRow][inColumn]->getAge());
         humanGoFromTo(inRow,inColumn, 0,0, true);
         _nbMorts++;
         return;


      }
      else
      {
         _newHumanReanimationPositions.push_back(
                                      _carte[inRow][inColumn]->getPosition()
                                                );
      }
      
      
   }
   else
   {
      _newHumanReanimationPositions.push_back(_carte[inRow][inColumn]->getPosition());
   }
   _carte[inRow][inColumn]->incrementState();

}

void World::gestionVaccination()
{
   if(!_timelineVaccination.empty()){
      int dateVaccination = _timelineVaccination.front();
      if(_iteration == dateVaccination)
      {
         _timelineVaccination.pop_front();
         int proportionVaccination = _timelineVaccination.front();
         int nbVaccineTotal = _nbHumain * ((float)proportionVaccination /(float)100);
         int nbPersonneAVacciner = nbVaccineTotal - _totalPersonneVaccine;
         _timelineVaccination.pop_front();
         //_totalPersonneVaccine = nbVaccineTotal;
         int compteur = 0;
         for(Position  temp: _humanSafePositions)
         {
            if(compteur == nbPersonneAVacciner)
            {
               _totalPersonneVaccine = nbVaccineTotal;
               break;
            }
            if(_carte[temp.getPosX()][temp.getPosY()]->getNumberOfInjections() == 0)
            {
               _carte[temp.getPosX()][temp.getPosY()]->vaccine();
               compteur++;
            }
         }
         _totalPersonneVaccine += compteur;
         
         //Je ne peux vacciner que des personnes saines
         // Or, si je veux vacciner 50% de la population globale,
         // Mais que 80% des personnes sont malades, alors je ne peux pas.
         // Je ne vais donc vacciner que la partie vaccinable.
         // Et lorsque cela sera possible, je vaccinerai les personnes restantes pour coller aux params.
         
      }
   }
   
   
   if(!_timelineVaccinationRappel.empty())
   {
      int dateVaccinationRappel = _timelineVaccinationRappel.front();
      if(_iteration == dateVaccinationRappel)
      {
         _timelineVaccinationRappel.pop_front();
         int proportionVaccination = _timelineVaccinationRappel.front();
         int nbVaccineTotal = _nbHumain * ((float)proportionVaccination /(float)100);
         int nbPersonneAVacciner = nbVaccineTotal - _totalPersonneVaccineRappel;
         _timelineVaccinationRappel.pop_front();
         //_totalPersonneVaccineRappel = nbVaccineTotal;
         
         int compteur = 0;
         for(Position  temp: _humanSafePositions)
         {
            if(compteur == nbPersonneAVacciner)
            {
               _totalPersonneVaccineRappel = nbVaccineTotal;
               break;
            }
            if(_carte[temp.getPosX()][temp.getPosY()]->getNumberOfInjections() == 1)
            {
               _carte[temp.getPosX()][temp.getPosY()]->vaccineRappel();
               compteur++;
            }
         }
         
         _totalPersonneVaccineRappel += compteur;

         
      }
   }
   
    
   
   
}


void World::gestionMesuresBarrieres()
{
   if(!_timelineMasqueTissu.empty())
   {
      if(_iteration == _timelineMasqueTissu.front())
      {
         _timelineMasqueTissu.pop_front();
         if(_isMasqueTissu)
         {
            _isMasqueTissu = 0;
         }
         else
         {
            _isMasqueTissu = 1;
         }
      }
      
   }
   
   if(!_timelineMasqueChir.empty())
   {
      if(_iteration == _timelineMasqueChir.front())
      {
         _timelineMasqueChir.pop_front();
         if(_isMasqueChir)
         {
            _isMasqueChir = 0;
         }
         else
         {
            _isMasqueChir = 1;
         }
      }
   }
   
   if(!_timelineMasqueFFP2.empty())
   {
      if(_iteration == _timelineMasqueFFP2.front())
      {
         _timelineMasqueFFP2.pop_front();
         if(_isMasqueFFP2)
         {
            _isMasqueFFP2 = 0;
         }
         else
         {
            _isMasqueFFP2 = 1;
         }
      }
   }
   
   if(!_timelineGelHydroalcolique.empty())
   {
      if(_iteration == _timelineGelHydroalcolique.front())
      {
         _timelineGelHydroalcolique.pop_front();
         if(_isGelHydroalcolique)
         {
            _isGelHydroalcolique = 0;
         }
         else
         {
            _isGelHydroalcolique = 1;
         }
      }
   }
   
   if(!_timelineConfinement.empty())
   {
      if(_iteration == _timelineConfinement.front())
      {
         _timelineConfinement.pop_front();
         if(_isConfinement)
         {
            _isConfinement = 0;
         }
         else
         {
            _isConfinement = 1;
         }
      }
   }
   
   if(!_timelineCouvreFeu.empty())
   {
      if(_iteration == _timelineCouvreFeu.front())
      {
         _timelineCouvreFeu.pop_front();
         if(_isCouvreFeu)
         {
            _isCouvreFeu = 0;
         }
         else
         {
            _isCouvreFeu = 1;
         }
      }
   }
   
   if(!_timelineMedicament.empty())
   {
      if(_iteration == _timelineMedicament.front())
      {
         _timelineMedicament.pop_front();
         if(_isMedicament)
         {
            _isMedicament = 0;
         }
         else
         {
            _isMedicament = 1;
         }
      }
   }
   
   if(!_timelineDeplacementLimites.empty())
   {
      if(_iteration == _timelineDeplacementLimites.front())
      {
         _timelineDeplacementLimites.pop_front();
         if(_isDeplacementLimites)
         {
            _isDeplacementLimites = 0;
         }
         else
         {
            _isDeplacementLimites = 1;
         }
      }
   }
   
   
}


// -------------------------------------------------------------------- //
// World::nextIteration:                                                //
//    Effectue les changements necessaires et écrit les log             //
//    pour passer à l'itération suivante                                //
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void World::nextIteration()
{
   
   gestionVaccination();
   
   gestionMesuresBarrieres();
   
   writeLog(to_string(_iteration));
   writeLog(to_string(_nbNouveauxCas));
   writeLog(to_string(_nbPersonneHospital));
   writeLog(to_string(_nbPersonneReanimation));
   writeLog(to_string(_nbNouveauxHospitalisation));
   writeLog(to_string(_nbNouveauxReanimation));
   writeLog(to_string(_nbMorts));
   writeLog(to_string(_nbCasCovidConnuTotal));
    
   float totalMalade = (float)(_humanAsymptomatiquePositions.size() 
                                + _humanConfinedPositions.size() 
                                + _humanHospitalPositions.size() 
                                +_humanReanimationPositions.size()
                               );
   float reffectifJour = 0;
   
    
   if(totalMalade > 0)
   {
      reffectifJour = (float)_nbNouveauxCas / totalMalade;
   }


   writeLog(to_string(reffectifJour*11)); // 11 est le nb de jour où une personne est contaminante : 2 + 9.
   
   if(_nbNouveauxCasSemaine.size() > 6){
      _nbNouveauxCasSemaine.pop_front();
   }
   _nbNouveauxCasSemaine.push_back(_nbNouveauxCas);
   
   int jour = 0;
   int nbNouveauxCasSemaineSomme = 0;
   for(jour = 0; jour < _nbNouveauxCasSemaine.size(); jour++){
      nbNouveauxCasSemaineSomme = nbNouveauxCasSemaineSomme + _nbNouveauxCasSemaine[jour];
   }
   
   //Taux d'incidence sur 100 000 hab
   // Mettre dans write log et le traiter dans notebook
   double tauxIncidence = 100000.0 * (double)nbNouveauxCasSemaineSomme / (double)_nbHumain;
   writeLog(to_string(tauxIncidence));

   for (int age: _ageOfSymptomaticDailyHuman)
   {
      writeLog("AgeC:" + to_string(age));
   }
   for (int age: _ageOfDeadHumansDaily)
   {
      writeLog("AgeD:" + to_string(age));
   }

   
   writeLog("##########");
   _ageOfSymptomaticDailyHuman.clear();
   _ageOfDeadHumansDaily.clear();
   _nbNouveauxCas = 0;
   _nbNouveauxHospitalisation = 0;
   _nbNouveauxReanimation = 0;
   _nbMorts = 0;
   _iteration += 1;

   
   for(Position  temp: _humanSafePositions)
   {
      moveHumanSafe(temp.getPosX(),temp.getPosY());
   }


   
   /* Lors du couvre feu ou du confinement, un humain asymptomatique,
    * qui se déplace plusieurs fois, ne doit pas pouvoir aller 
    * au dela d'une certaine distance. Il faut donc fixer sa
    * position de depart de déplacement. On utilisera cette 
    * position lors de l'appel à moveHumanAsymptomatique()
    */
   for(Position  temp: _humanAsymptomatiquePositions)
   {
      _carte[temp.getPosX()][temp.getPosY()]->setPositionDebutTour(
                                                 temp.getPosX(),
                                                 temp.getPosY());
   }
   
//////////////////////////////////////////////////////////////////// 
   // Ce code est provisoire, afin de connaitre le nombre d'iteration à avoir sur Paris pour avoir un r0 de 3 sur les premiers jours de l'épidémie.
   //int nbBoucle = 0;
     //while(_nbNouveauxCas < _humanAsymptomatiquePositions.size() * _r0 ){
        //nbBoucle++;
////////////////////////////////////////////////////////////////////
   if(_isConfinement)
   {
      if(_isCouvreFeu)
      {
         for(int x = 0; x < _nbDeplacementJour - (_nbDeplacementReductionConfinement + _nbDeplacementReductionCouvreFeu); x++)
         {
            for(Position  temp: _humanAsymptomatiquePositions)
            {
               moveHumanAsymptomatique(temp.getPosX(),
                                       temp.getPosY(),
                                       _carte[temp.getPosX()][temp.getPosY()]->getPositionDebutTour().getPosX(),
                                       _carte[temp.getPosX()][temp.getPosY()]->getPositionDebutTour().getPosY()); 
            
            }
            _humanAsymptomatiquePositions = _newCurrentHumanAsymptomatiquePositions;
            _newCurrentHumanAsymptomatiquePositions.clear();
         }
         for(Position  temp: _humanAsymptomatiquePositions)
         {
            _carte[temp.getPosX()][temp.getPosY()]->incrementState();
            _carte[temp.getPosX()][temp.getPosY()]->updateHumanProtection();
         }
      }
      else
      {
         for(int x = 0; x < _nbDeplacementJour - _nbDeplacementReductionConfinement; x++)
         {
            for(Position  temp: _humanAsymptomatiquePositions)
            {
               
               moveHumanAsymptomatique(temp.getPosX(),
                                       temp.getPosY(),
                                       _carte[temp.getPosX()][temp.getPosY()]->getPositionDebutTour().getPosX(),
                                       _carte[temp.getPosX()][temp.getPosY()]->getPositionDebutTour().getPosY()); 
               
            }
            _humanAsymptomatiquePositions = _newCurrentHumanAsymptomatiquePositions;
            _newCurrentHumanAsymptomatiquePositions.clear();
         }
         for(Position  temp: _humanAsymptomatiquePositions)
         {
            _carte[temp.getPosX()][temp.getPosY()]->incrementState();
            _carte[temp.getPosX()][temp.getPosY()]->updateHumanProtection();
         }
      }
   }
   else if(_isCouvreFeu)
   {
      for(int x = 0; x < _nbDeplacementJour - _nbDeplacementReductionCouvreFeu; x++)
      {
         for(Position  temp: _humanAsymptomatiquePositions)
         {            
            moveHumanAsymptomatique(temp.getPosX(),
                                    temp.getPosY(),
                                    _carte[temp.getPosX()][temp.getPosY()]->getPositionDebutTour().getPosX(),
                                    _carte[temp.getPosX()][temp.getPosY()]->getPositionDebutTour().getPosY()); 
            
         }
         _humanAsymptomatiquePositions = _newCurrentHumanAsymptomatiquePositions;
         _newCurrentHumanAsymptomatiquePositions.clear();
      }
      for(Position  temp: _humanAsymptomatiquePositions)
      {
         _carte[temp.getPosX()][temp.getPosY()]->incrementState();
         _carte[temp.getPosX()][temp.getPosY()]->updateHumanProtection();
      }
   }
   else
   {
      for(int x = 0; x < _nbDeplacementJour; x++)
      {
         for(Position  temp: _humanAsymptomatiquePositions)
         {
            
            moveHumanAsymptomatique(temp.getPosX(),
                                    temp.getPosY(),
                                    _carte[temp.getPosX()][temp.getPosY()]->getPositionDebutTour().getPosX(),
                                    _carte[temp.getPosX()][temp.getPosY()]->getPositionDebutTour().getPosY()); 
            
         }
         _humanAsymptomatiquePositions = _newCurrentHumanAsymptomatiquePositions;
         _newCurrentHumanAsymptomatiquePositions.clear();
      }
      for(Position  temp: _humanAsymptomatiquePositions)
      {
         _carte[temp.getPosX()][temp.getPosY()]->incrementState();
         _carte[temp.getPosX()][temp.getPosY()]->updateHumanProtection();
      }
   }


   
   
//////////////////////////////////////////////////////////  

    
   for(Position  temp: _humanConfinedPositions)
   {
      moveHumanConfined(temp.getPosX(),temp.getPosY());

   }

////////////////////////////////////////////////////////////

   
   for(Position  temp: _humanHospitalPositions)
   {
      moveHumanHospital(temp.getPosX(),temp.getPosY());

   }

   
///////////////////////////////////////////////////////////////

   
   for(Position  temp: _humanReanimationPositions)
   {
      moveHumanReanimation(temp.getPosX(),temp.getPosY());
   }


   _humanSafePositions = _newHumanSafePositions;
   
    
   // Pour les asymptomatiques j'ai deux vecteurs, 
   //donc je dois les concatener pour les mettres dans le vecteur courant
   
   _humanAsymptomatiquePositions.insert(_humanAsymptomatiquePositions.end(), 
                                        _newNextHumanAsymptomatiquePositions.begin(), 
                                        _newNextHumanAsymptomatiquePositions.end());
   
   
   _humanConfinedPositions = _newHumanConfinedPositions;
   _humanHospitalPositions = _newHumanHospitalPositions;
   _humanReanimationPositions = _newHumanReanimationPositions;
   // Cette section ne va fonctionner que si le "=" fait une copie, 
   //car si le "=" passe le pointeur au début du vecteur, alors le clear() va également écraser le nouveau.
   
   _newHumanSafePositions.clear();
   _newCurrentHumanAsymptomatiquePositions.clear();
   _newNextHumanAsymptomatiquePositions.clear();
   _newHumanConfinedPositions.clear();
   _newHumanHospitalPositions.clear();
   _newHumanReanimationPositions.clear();
   
}




// -------------------------------------------------------------------- //
// World::startSimulation:  Démarre la simulation                       //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inSimulationParams :                                              //
//       Objet contenant les paramètres du fichier de configuration     //
//                                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void World::startSimulation(SimulationParams * inSimulationParams)
{


   for(int iteration = 0;
       iteration < inSimulationParams->getNbIteration();
       iteration++)
   {
      //displayStats();
      //display();
      
      //World::pause();
      nextIteration();
      /*
      if(_humansPosition.size() == 0){
         cout << "no more humans in the simulation" << endl;
         //self.writeLog('[STOP] No more human in the simulation !\n')
         break;
      }
      */
   }


   writeLog("CompteurRand:" + to_string(randmt->getCompteur()));
   writeLog("NbHumainSimuDepart:" + to_string(_nbHumain));
   //cout << "\033[2J" << endl;
   displayStats();
   
}


