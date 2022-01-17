#pragma once
#include <map>

using namespace std;

class SimulationParams
{

   private:
      // HUMAN
      float            _resistanceInfectionValuesByAge[8];
      float            _maxResistanceInjectionValuesByAge[8];
      float            _minResistanceInjectionValuesByAge[8];

      //WORLD
      float            _tableTauxMortaliteByAgeBy10[8];
      int              _nbPlaceHospital;
      int              _nbPlaceReanimation;
      float            _r0;
      float            _tauxMortRea;
      int              _size;
      int              _nbMalade;
      int              _nbHumain;
      int              _nbIteration;
      int              _nbMultMortToHosp;
      int              _isVaccin;
      float            _histogrammeContamination[11];
      float            _pourcentAsymptomatique;
      float            _tauxDeChanceDeMourirHospitalFull;
      float            _tauxVaccination;
      float            _tauxContaDistanceDeux;

      map<string, int> _mapStringValues;

   public:
      SimulationParams(char *);
      float * getResistanceInfectionValuesByAge();
      float * getMaxResistanceInjectionValuesByAge();
      float * getMinResistanceInjectionValuesByAge();
      float * getTableTauxMortaliteByAgeBy10();
      float   getTauxVaccination();
      int     getNbPlaceHospital();
      int     getNbPlaceReanimation();
      int     getR0();
      float   getTauxMortRea();
      int     getSize();
      int     getNbMalade();
      int     getNbHumain();
      int     getNbIteration();
      int     getNbMultMortToHosp();
      int     getIsVaccin();
      float * getHistogrammeContamination();
      float   getPourcentAsymptomatique();
      float   getTauxDeChanceDeMourirHospitalFull();
      float   getTauxContaDistanceDeux();

};
