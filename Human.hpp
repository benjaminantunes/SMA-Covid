#pragma once

#include <string>

#include "Position.hpp"
#include "RandMT.hpp"
#include "SimulationParams.hpp"

extern RandMT * randmt;

class Human 
{
   private:
      
      static const char SYMBOL = 'X';
      static const char SYMBOL_SICK = 'O';
      static const char SYMBOL_SICK_CONFINED = 'C';
      static const char SYMBOL_SICK_HOSPITAL = 'H';
      static const char SYMBOL_SICK_REANIMATION = 'R';
      
      int               _state = 0;
      char              _symbol;
      int               _age;
      int               _sexe; //0 homme et 1 femme
      bool              _isConfined = false;
      bool              _isHospital = false;
      bool              _isReanimation = false;
      float             _tauxDeProtectionInfection = 0;
      float             _tauxDeProtectionHospitalisation = 0;
      float             _tauxDeProtectionReanimation = 0;
      float             _newTauxDeProtectionInfection = 0;
      float             _newTauxDeProtectionHospitalisation = 0;
      float             _newTauxDeProtectionReanimation = 0;
      float           * _resistanceInfectionValuesByAge;
      float           * _maxResistanceInjectionValuesByAge;
      float           * _minResistanceInjectionValuesByAge;
      int               _dureeReanimation = 0;
      int               _daysSinceLastInfectionOrInjection = 0;
      float           * _tauxDeProtectionHospVaccinByAge;
      float           * _tauxDeProtectionReaVaccinByAge;
      float           * _tauxDeProtectionHospVaccinRappelByAge;
      float           * _tauxDeProtectionReaVaccinRappelByAge;
      float           * _tauxDeProtectionHospInfectionByAge;
      float           * _tauxDeProtectionReaInfectionByAge;
      float           * _probasCumulativesTrancheAge;
      int               _numberOfInfections = 0;

      Position          _pos;

   public:
 
      Human(SimulationParams*,int,int);
      
      void      contamine();
      void      vaccine();
      void      vaccineRappel();
      bool      isSick();
      int       getState();
      int       getAge();
      float     getTauxDeProtectionInfection();
      void      decreaseResistance();
      void      resetState();
      void      incrementState();
      char      to_string();
      void      getConfined();
      void      goToHospital();
      void      goToReanimation();
      void      setPosition(int,int);
      bool      getIsConfined();
      bool      getIsHospital();
      bool      getIsReanimation();
      int       getDureeReanimation();
      Position  getPosition();
      float     getTauxDeProtectionHospitalisation();
      float     getTauxDeProtectionReanimation();
      int       getNumberOfInfections();
      void      updateHumanProtection();

};
