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
      float            _tauxDeProtectionHospVaccinByAge[8];
      float            _tauxDeProtectionReaVaccinByAge[8];
      float            _tauxDeProtectionHospVaccinRappelByAge[8];
      float            _tauxDeProtectionReaVaccinRappelByAge[8];
      float            _tauxDeProtectionHospInfectionByAge[8];
      float            _tauxDeProtectionReaInfectionByAge[8];
      float            _probasCumulativesTrancheAge[8];

      //WORLD
      float            _tableTauxHospitalisationByAge[8];
      int              _nbPlaceHospital;
      int              _nbPlaceReanimation;
      float            _r0;
      float            _tauxMortRea;
      int              _size;
      int              _nbMalade;
      int              _nbHumain;
      int              _nbIteration;
      int              _isVaccin;
      float            _tauxVaccination;
      float            _tauxVaccinationRappel;
      float            _histogrammeContamination[11];
      float            _pourcentAsymptomatique;
      float            _tauxDeChanceDeMourirHospitalFull;
      float            _tauxContaDistanceDeux;
      int              _nbDeplacementJour;
      
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
      int              _nbLimiteDistanceMaxConfinement;
      
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


      map<string, int> _mapStringValues;

   public:
      SimulationParams(char *, char *);
      float * getResistanceInfectionValuesByAge();
      float * getMaxResistanceInjectionValuesByAge();
      float * getMinResistanceInjectionValuesByAge();
      float * getTableTauxHospitalisationByAge();
      float   getTauxVaccination();
      int     getNbPlaceHospital();
      int     getNbPlaceReanimation();
      int     getR0();
      float   getTauxMortRea();
      int     getSize();
      int     getNbMalade();
      int     getNbHumain();
      int     getNbIteration();
      int     getIsVaccin();
      float * getHistogrammeContamination();
      float   getPourcentAsymptomatique();
      float   getTauxDeChanceDeMourirHospitalFull();
      float   getTauxContaDistanceDeux();
      float   getTauxVaccinationRappel();
      float * getTauxDeProtectionHospVaccinByAge();
      float * getTauxDeProtectionReaVaccinByAge();
      float * getTauxDeProtectionHospVaccinRappelByAge();
      float * getTauxDeProtectionReaVaccinRappelByAge();
      float * getTauxDeProtectionHospInfectionByAge();
      float * getTauxDeProtectionReaInfectionByAge();
      int     getIsMedicament();
      float   getTauxProtectionReaMedicament();
      int     getIsMasqueTissu();
      float   getTauxProtectionMasqueTissu();
      int     getIsMasqueChir();
      float   getTauxProtectionMasqueChir();
      int     getIsMasqueFFP2();
      float   getTauxProtectionMasqueFFP2();
      int     getIsConfinement();
      int     getNbDeplacementReductionConfinement();
      int     getNbLimiteDistanceMaxConfinement();
      int     getIsDeplacementLimites();
      int     getNbDistanceMax();
      int     getIsGelHydroalcolique();
      float   getTauxProtectionTransmissionGelHydro();
      int     getIsTestCovid();
      float   getTauxDeDivisionAsymptomatique();
      int     getIsCouvreFeu();
      int     getNbDeplacementReductionCouvreFeu();
      int     getIsSuperContaminateur();
      int     getNbDeplacementSuperContaminateur();
      float * getProbasCumulativesTrancheAge();
      int     getNbDeplacementJour();

};
