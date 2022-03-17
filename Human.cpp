#include "Human.hpp"
#include <ostream>
#include <iostream>

using namespace std;




// -------------------------------------------------------------------- //
// Human::Human:  Constructeur de Human                                 //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inSimulationParams :                                              //
//       Objet contenant les paramètres du fichier de configuration     //
//                                                                      //
//                                                                      //
//    inRow :                                                           //
//       La ligne de l'humain (Position X sur la carte)                 //
//                                                                      //
//    inColumn :                                                        //
//       La colonne de l'humain  (Position Y sur la carte)              //
//                                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Un objet humain                                                   //
// -------------------------------------------------------------------- //
Human::Human(SimulationParams * inSimulationParams,
             int                inRow, 
             int                inColumn
            )

{
   _pos          = Position(inRow,inColumn);
   _symbol       = Human::SYMBOL;
   float randAge = randmt->genrand_real1();
   
   _resistanceInfectionValuesByAge = 
      inSimulationParams->getResistanceInfectionValuesByAge();
   
   _maxResistanceInjectionValuesByAge =
      inSimulationParams->getMaxResistanceInjectionValuesByAge();
   
   _minResistanceInjectionValuesByAge = 
      inSimulationParams->getMinResistanceInjectionValuesByAge();
   
   _tauxDeProtectionHospVaccinByAge = 
      inSimulationParams->getTauxDeProtectionHospVaccinByAge();
   
   _tauxDeProtectionReaVaccinByAge = 
      inSimulationParams->getTauxDeProtectionReaVaccinByAge();
   
   _tauxDeProtectionHospVaccinRappelByAge = 
      inSimulationParams->getTauxDeProtectionHospVaccinRappelByAge();
   
   _tauxDeProtectionReaVaccinRappelByAge = 
      inSimulationParams->getTauxDeProtectionReaVaccinRappelByAge();
   
   _tauxDeProtectionHospInfectionByAge = 
      inSimulationParams->getTauxDeProtectionHospInfectionByAge();
   
   _tauxDeProtectionReaInfectionByAge = 
      inSimulationParams->getTauxDeProtectionReaInfectionByAge();
   
   _probasCumulativesTrancheAge = 
      inSimulationParams->getProbasCumulativesTrancheAge();
   
   
   // https://www.insee.fr/fr/statistiques/2381474#figure1_radio2
   // 8 Tranches : 0 - 15, 15 - 25 , 25 - 35 , 35 - 45 , 45 - 55, 55 - 65, 65 - 75, 75 +
   
   // Pour passer en paramètre, il me faut les probas cumulatives.
   /*
   if(randAge < 0.177)
   {
      _age = 0; // 0%
   }
   else if(randAge >= 0.177 && randAge < 0.296)
   {
      _age = 1; // 0.2%
   }
   else if(randAge >= 0.296 && randAge < 0.411)
   {
      _age = 2; // 0.2%
   }
   else if(randAge >= 0.411 && randAge < 0.535)
   {
      _age = 3; //0.4%
   }
   else if(randAge >= 0.535 && randAge < 0.667)
   {
      _age = 4; //1.3%
   }
   else if(randAge >= 0.667 && randAge < 0.793)
   {
      _age = 5; //3.6%
   }
   else if(randAge >= 0.793 && randAge < 0.905)
   {
      _age = 6; //8%
   }
   else if(randAge >= 0.905)
   {
      _age = 7; // 14.8%
   }
   */

   for(int i = 0;i<8;i++)
   {
      if(randAge <= _probasCumulativesTrancheAge[i])
      {
         _age = i;
         break;
      }
   }
   


   float randSexe = randmt->genrand_real1();
   // 50/50 homme et femme
   if(randSexe < 0.5)
   {
      _sexe = 0;
   }
}

// -------------------------------------------------------------------- //
// Human::Contamine  Contamine un humain et augmente sa resistance      //
//                   à la réinfection                                   //
// -------------------------------------------------------------------- //

void Human::contamine()
{
   _state = 1;
   _numberOfInfections++;
   if(_tauxDeProtectionInfection < _resistanceInfectionValuesByAge[_age])
   {
       _newTauxDeProtectionInfection = _resistanceInfectionValuesByAge[_age];
   }
   
   if(_tauxDeProtectionHospitalisation < _tauxDeProtectionHospInfectionByAge[_age])
   {
       _newTauxDeProtectionHospitalisation = _tauxDeProtectionHospInfectionByAge[_age];
   }
   
   if(_tauxDeProtectionReanimation < _tauxDeProtectionReaInfectionByAge[_age])
   {
       _newTauxDeProtectionReanimation = _tauxDeProtectionReaInfectionByAge[_age];
   }
   
   _daysSinceLastInfectionOrInjection = 0;
}



// -------------------------------------------------------------------- //
// Human::Vaccine  Vaccine un humain et augmente sa resistance          //
//                 à l'infection                                        //
// -------------------------------------------------------------------- //

void Human::vaccine()
{
   double randomValue = _minResistanceInjectionValuesByAge[_age]
                   + (
                     _maxResistanceInjectionValuesByAge[_age]
                     -
                     _minResistanceInjectionValuesByAge[_age]
                     )
                   * randmt->genrand_real1();
   
   if(_tauxDeProtectionInfection < randomValue)
   {
      _tauxDeProtectionInfection = randomValue;
   }
   
   if(_tauxDeProtectionHospitalisation < _tauxDeProtectionHospVaccinByAge[_age])
   {
       _tauxDeProtectionHospitalisation = _tauxDeProtectionHospVaccinByAge[_age];
       
   }
   
   if(_tauxDeProtectionReanimation < _tauxDeProtectionReaVaccinByAge[_age])
   {
       _tauxDeProtectionReanimation = _tauxDeProtectionReaVaccinByAge[_age];
   }
   _daysSinceLastInfectionOrInjection = 0;
   
}

// -------------------------------------------------------------------- //
// Human::Vaccine  Vaccine un humain avec un rappel(booster)            //
// -------------------------------------------------------------------- //

void Human::vaccineRappel()
{
   double randomValue = _minResistanceInjectionValuesByAge[_age]
                   + (
                     _maxResistanceInjectionValuesByAge[_age]
                     -
                     _minResistanceInjectionValuesByAge[_age]
                     )
                   * randmt->genrand_real1();
   
   if(_tauxDeProtectionInfection < randomValue)
   {
      _newTauxDeProtectionInfection = randomValue;
   }
   
   if(_tauxDeProtectionHospitalisation < _tauxDeProtectionHospVaccinRappelByAge[_age])
   {
       _newTauxDeProtectionHospitalisation = _tauxDeProtectionHospVaccinRappelByAge[_age];
   }
   
   if(_tauxDeProtectionReanimation < _tauxDeProtectionReaVaccinRappelByAge[_age])
   {
       _newTauxDeProtectionReanimation = _tauxDeProtectionReaVaccinRappelByAge[_age];
   } 
   _daysSinceLastInfectionOrInjection = 0;
}

// -------------------------------------------------------------------- //
// Human::isSick  Renvoi si un humain est malade                        //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Booléen : Malade ou non                                           //
// -------------------------------------------------------------------- //

bool Human::isSick()
{
   return _state != 0;
}

// -------------------------------------------------------------------- //
// Human::getState  Retourne l'état de l'humain (les jours de maladie)  //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Integer : L'état                                                  //
// -------------------------------------------------------------------- //

int Human::getState()
{
   return _state;
}

// -------------------------------------------------------------------- //
// Human::incrementState                                                //
//    Augmente l'état de l'humain, un jour de plus de maladie           //
// -------------------------------------------------------------------- //

void Human::incrementState()
{
   _state += 1;
}

// -------------------------------------------------------------------- //
// Human::to_string  Renvoi une représentation graphique de l'humain    //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Char : Signe pour représenter l'état de l'humain                  //
// -------------------------------------------------------------------- //

char Human::to_string()
{
   
   if(_isConfined)
   {
      return Human::SYMBOL_SICK_CONFINED;
   }
   if(_isHospital)
   {
      return Human::SYMBOL_SICK_HOSPITAL;
   }
   if(_isReanimation)
   {
      return Human::SYMBOL_SICK_REANIMATION;
   }
   if (isSick())
   {
      return Human::SYMBOL_SICK;
   }
   else
   {
      return _symbol;
   }
}

// -------------------------------------------------------------------- //
// Human::setPosition  Modifie la position de l'humain                  //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inPosX :                                                          //
//       Position de la ligne                                           //
//                                                                      //
//     inPosY :                                                         //
//        Position de la colonne                                        // 
// -------------------------------------------------------------------- //

void Human::setPosition(int inPosX,int inPosY)
{
   _pos.setPosX(inPosX);
   _pos.setPosY(inPosY);
};

// -------------------------------------------------------------------- //
// Human::getPosition  Retourne la position de l'humain                 //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Position : La position de l'humain                                //
// -------------------------------------------------------------------- //

Position  Human::getPosition()
{
   return _pos;
}

// -------------------------------------------------------------------- //
// Human::resetState  Remet l'état à 0, l'humain n'est plus malade      //
// -------------------------------------------------------------------- //

void Human::resetState()
{
   _state = 0;
   _isConfined = false;
   _isHospital = false;
   _isReanimation = false;
}

// -------------------------------------------------------------------- //
// Human::getConfined  Confine l'humain                                 //
// -------------------------------------------------------------------- //

void Human::getConfined()
{
   _isConfined = true;
   _isHospital = false;
   _isReanimation = false;
}

// -------------------------------------------------------------------- //
// Human::goToHospital  Met l'humain à l'hopital                        //
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void Human::goToHospital()
{
   _isConfined = false;
   _isHospital = true;
   _isReanimation = false;
}




// -------------------------------------------------------------------- //
// Human::goToReanimation  Met l'humain en réanimation                  //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void Human::goToReanimation()
{
   _isConfined = false;
   _isHospital = false;
   _isReanimation = true;
   _dureeReanimation = (randmt->genrand_int32()%26) + 10; // Entre 10 et 25 jours de rea, sachant qu'on a deja 5 jours de maladie (State)
   // Ca fait donc entre 5 et 20 jours de rea.
}







// -------------------------------------------------------------------- //
// Human::getIsConfined  Récupère si l'humain est confiné               //
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Booléen : Oui ou non l'humain est confiné                         //
// -------------------------------------------------------------------- //
bool Human::getIsConfined()
{
   return _isConfined;
}






// -------------------------------------------------------------------- //
// Human::getIsHospital  Récupère si l'humain est hospitalisé           //
//                                                                      //
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Booléen : Oui ou non l'humain est hospitalisé                     //
// -------------------------------------------------------------------- //
bool Human::getIsHospital()
{
   return _isHospital;
}





// -------------------------------------------------------------------- //
// Human::getIsReanimation  Récupère si l'humain est en réanimation     //
//                                                                      //
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Booléen : Oui ou non l'humain est en réanimation                  //
// -------------------------------------------------------------------- //
bool Human::getIsReanimation()
{
   return _isReanimation;
}





// -------------------------------------------------------------------- //
// Human::getAge  Récupère la classe d'age de l'humain                  //
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Integer : Retourne le int de la classe d'age de l'humain          //
// -------------------------------------------------------------------- //
int Human::getAge()
{
   return _age;
}






// -------------------------------------------------------------------- //
// Human::getTauxDeProtectionInfection                                  //
//    Récupère la taux de resistance au virus                           //
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Float : Le taux de resistance au virus de l'humain                //
// -------------------------------------------------------------------- //
float Human::getTauxDeProtectionInfection()
{
   return _tauxDeProtectionInfection;
}

// -------------------------------------------------------------------- //
// Human::getTauxDeProtectionHospitalisation                            //
//    Récupère le taux de resistance à l'hospitalisation                //
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Float : Le taux de resistance à l'hospitalisation                 //
// -------------------------------------------------------------------- //
float Human::getTauxDeProtectionHospitalisation()
{
   return _tauxDeProtectionHospitalisation;
}

// -------------------------------------------------------------------- //
// Human::getTauxDeProtectionReanimation                                //
//    Récupère la taux de resistance à l'entrée en reanimation          //
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Float : Le taux de resistance à l'entrée en réanimation           //
// -------------------------------------------------------------------- //
float Human::getTauxDeProtectionReanimation()
{
   return _tauxDeProtectionReanimation;
}





// -------------------------------------------------------------------- //
// Human::getDureeReanimation                                           //
//    Récupère la durée que doit passer l'humain en réanimation         //
//    Cette durée est aléatoire selon l'humain                          //
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Integer : Le nb de jour que doit passer l'humain en réanimation   //
// -------------------------------------------------------------------- //
int Human::getDureeReanimation()
{
   return _dureeReanimation;
}







// -------------------------------------------------------------------- //
// Human::decreaseResistance  Diminue la resistance a la ré-infection   //
//    à l'hospitalisation et à la réanimation                           //
//    On reste protégé 90 jours en plus des 90 premiers jours contre    //
//    l'infection avec un taux de 40% par exemple.                      //
//    On reste protégé deux fois plus longtemps contre l'hospitalisation//
//    et quatre fois plus longtemps contre la réanimation               //
//                                                                      //
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void Human::decreaseResistance()
{
   if(_daysSinceLastInfectionOrInjection < 90)
   {
      return;
   }
   if(_daysSinceLastInfectionOrInjection >= 90 && _tauxDeProtectionInfection > 0)
   {
      _tauxDeProtectionInfection = _tauxDeProtectionInfection - 0.004;
   }
   if(_daysSinceLastInfectionOrInjection >= 90 && _tauxDeProtectionHospitalisation > 0)
   {
      _tauxDeProtectionHospitalisation = _tauxDeProtectionHospitalisation - 0.002;
   }
   if(_daysSinceLastInfectionOrInjection >= 90 && _tauxDeProtectionReanimation > 0)
   {
      _tauxDeProtectionReanimation = _tauxDeProtectionReanimation - 0.001;
   }
   
}


int Human::getNumberOfInfections()
{
   return _numberOfInfections;
}

void Human::updateHumanProtection()
{
   _daysSinceLastInfectionOrInjection++;
   
   if(_daysSinceLastInfectionOrInjection > 10)
   {
      if(_newTauxDeProtectionInfection > 0)
      {
         _tauxDeProtectionInfection = _newTauxDeProtectionInfection;
         _newTauxDeProtectionInfection = 0;
      }
      if(_newTauxDeProtectionHospitalisation > 0)
      {
         _tauxDeProtectionHospitalisation = _newTauxDeProtectionHospitalisation;
         _newTauxDeProtectionHospitalisation = 0;
      }
      if(_newTauxDeProtectionReanimation > 0)
      {
         _tauxDeProtectionReanimation = _newTauxDeProtectionReanimation;
         _newTauxDeProtectionReanimation = 0;
      }
      
   } 
}
