#pragma once
#include <map>

using namespace std;
class SimulationParams {

	private:
		// HUMAN
		float resistanceInfectionValuesByAge[8];// = {0.999,0.999,0.999,0.999,0.99,0.90, 0.80 ,0.70};
		float maxResistanceInjectionValuesByAge[8];// = {0.8,0.8,0.8,0.7,0.6,0.6,0.5,0.4};
		float minResistanceInjectionValuesByAge[8];// = {0.5,0.5,0.5,0.5,0.4,0.4,0.4,0.3};

		//WORLD
		float table_taux_mortalite_by_age_by_10[8];// = {0, 0.2, 0.2, 0.4, 1.3, 3.6, 8, 14.8};
		float taux_contamination_voisin;	
		int nbPlaceHospital;
		int nbPlaceReanimation;
		float r0;
		float tauxMortRea;
		
		int size;
		int nbMalade;
		int nbHumain;
		int nbIteration;
		int nbMultMortToHosp;
		int isVaccin;
		float histogrammeContamination[11];// = {0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.7, 0.6, 0.4, 0.2};
		float pourcentAsymptomatique;
		float tauxDeChanceDeMourirHospitalFull;
		float tauxVaccination;

		map<string, int> mapStringValues;

	public:
		SimulationParams(char *);
		float * getResistanceInfectionValuesByAge();
		float * getMaxResistanceInjectionValuesByAge();
		float * getMinResistanceInjectionValuesByAge();
		float * getTable_taux_mortalite_by_age_by_10();
		float getTaux_contamination_voisin();
		float getTauxVaccination();
		int getNbPlaceHospital();
		int getNbPlaceReanimation();
		int getR0();
		float getTauxMortRea();
		int getSize();
		int getNbMalade();
		int getNbHumain();
		int getNbIteration();
		int getNbMultMortToHosp();
		int getIsVaccin();
		float * getHistogrammeContamination();
		float getPourcentAsymptomatique();
		float getTauxDeChanceDeMourirHospitalFull();



};
