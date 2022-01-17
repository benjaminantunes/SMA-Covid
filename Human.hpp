#pragma once
#include <string>
#include "Position.hpp"
#include "RandMT.hpp"
#include "SimulationParams.hpp"

class Human 
{

   private:
      int               _state = 0;
      char              _symbol;
      static const char SYMBOL = 'X';
      static const char SYMBOL_SICK = 'O';
      static const char SYMBOL_SICK_CONFINED = 'C';
      static const char SYMBOL_SICK_HOSPITAL = 'H';
      static const char SYMBOL_SICK_REANIMATION = 'R';
      
      int               _age;
      int               _sexe; //0 homme et 1 femme
      Position          _pos;
      bool              _isConfined = false;
      bool              _isHospital = false;
      bool              _isReanimation = false;
      float             _resistanceVirus = 0;
      float           * _resistanceInfectionValuesByAge;
      float           * _maxResistanceInjectionValuesByAge;
      float           * _minResistanceInjectionValuesByAge;
      int               _dureeReanimation = 0;
      int               _daysSinceLastInfectionOrInjection = 0;


   public:
      Human(SimulationParams*,RandMT*,int,int);
      void      contamine();
      void      vaccine(RandMT*);
      bool      isSick();
      int       getState();
      int       getAge();
      float     getResistanceVirus();
      void      decreaseResistance();
      void      resetState();
      void      incrementState();
      char      to_string();
      void      getConfined();
      void      goToHospital();
      void      goToReanimation(RandMT*);
      void      setPosition(int,int);
      bool      getIsConfined();
      bool      getIsHospital();
      bool      getIsReanimation();
      int       getDureeReanimation();
      Position  getPosition();

};
