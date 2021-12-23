
#include "SimulationParams.hpp"
#include <fstream>
#include <ostream>
#include <iostream>

using namespace std;


SimulationParams::SimulationParams(char * filename){


	this->mapStringValues["resistanceInfectionValuesByAge"] = 0;
	this->mapStringValues["maxResistanceInjectionValuesByAge"] = 1;
	this->mapStringValues["minResistanceInjectionValuesByAge"] = 2;
	this->mapStringValues["table_taux_mortalite_by_age_by_10"] = 3;
	this->mapStringValues["taux_contamination_voisin"] = 4;
	this->mapStringValues["nbPlaceHospital"] = 5;
	this->mapStringValues["nbPlaceReanimation"] = 6;
	this->mapStringValues["r0"] = 7;
	this->mapStringValues["tauxMortRea"] = 8;
	this->mapStringValues["size"] = 9;
	this->mapStringValues["nbMalade"] = 10;
	this->mapStringValues["nbHumain"] = 11;
	this->mapStringValues["nbIteration"] = 12;
	this->mapStringValues["nbMultMortToHosp"] = 13;
	this->mapStringValues["isVaccin"] = 14;
	this->mapStringValues["histogrammeContamination"] = 15;
	this->mapStringValues["pourcentAsymptomatique"] = 16;
	this->mapStringValues["tauxDeChanceDeMourirHospitalFull"] = 17;
	this->mapStringValues["tauxVaccination"] = 18;


	string line;
	ifstream readFile(filename);
	size_t pos = 0;
	

	string delimiterName = "||";
	string delimiterValues = ",";
	
	
	while (getline(readFile, line)) {
		if(line.find("#") == string::npos){
			string paramName = line.substr(0, line.find(delimiterName));
			string paramValues = line.erase(0,line.find(delimiterName) + delimiterName.length());
			string value;
			int j = 0;
			switch (this->mapStringValues[paramName]) {
				
				 case 0:
					while ((pos = paramValues.find(delimiterValues)) != string::npos) {
						value = paramValues.substr(0, pos);
						this->resistanceInfectionValuesByAge[j] = stof(value);
						j++;
						paramValues.erase(0, pos + delimiterValues.length());
					}
					this->resistanceInfectionValuesByAge[j] = stof(value);
					break;
				 case 1:
					while ((pos = paramValues.find(delimiterValues)) != string::npos) {
						value = paramValues.substr(0, pos);
						this->maxResistanceInjectionValuesByAge[j] = stof(value);
						j++;
						paramValues.erase(0, pos + delimiterValues.length());
					}
					this->maxResistanceInjectionValuesByAge[j] = stof(value);
					break;
				 case 2:
					while ((pos = paramValues.find(delimiterValues)) != string::npos) {
						value = paramValues.substr(0, pos);
						this->minResistanceInjectionValuesByAge[j] = stof(value);
						j++;
						paramValues.erase(0, pos + delimiterValues.length());
					}
					this->minResistanceInjectionValuesByAge[j] = stof(value);
					break;
				 case 3:
					while ((pos = paramValues.find(delimiterValues)) != string::npos) {
						value = paramValues.substr(0, pos);
						this->table_taux_mortalite_by_age_by_10[j] = stof(value);
						j++;
						paramValues.erase(0, pos + delimiterValues.length());
					}
					this->table_taux_mortalite_by_age_by_10[j] = stof(value);
					break;
			  	case 4:
					this->taux_contamination_voisin = stof(paramValues);
					break;
				case 5:
					this->nbPlaceHospital = stoi(paramValues);
					break;
				case 6:
					this->nbPlaceReanimation = stoi(paramValues);
					break;
				case 7:
					this->r0 = stof(paramValues);
					break;
				case 8:
					this->tauxMortRea = stof(paramValues);
					break;
				case 9:
					this->size = stoi(paramValues);
					break;
				case 10:
					this->nbMalade = stoi(paramValues);
					break;
				case 11:
					this->nbHumain = stoi(paramValues);
					break;
				case 12:
					this->nbIteration = stoi(paramValues);
					break;
				case 13:
					this->nbMultMortToHosp = stoi(paramValues);
					break;
				case 14:
					this->isVaccin = stoi(paramValues);
					break;
				case 15:
					while ((pos = paramValues.find(delimiterValues)) != string::npos) {
						value = paramValues.substr(0, pos);
						this->histogrammeContamination[j] = stof(value);
						j++;
						paramValues.erase(0, pos + delimiterValues.length());
					}
					this->histogrammeContamination[j] = stof(value);
					break;
				case 16:
					this->pourcentAsymptomatique = stof(paramValues);
					break;
				case 17:
					this->tauxDeChanceDeMourirHospitalFull = stof(paramValues);
					break;
				case 18:
					this->tauxVaccination = stof(paramValues);
					break;
				

			}
		}
		
		
		
	}

	readFile.close();

}

float * SimulationParams::getResistanceInfectionValuesByAge(){
	return this->resistanceInfectionValuesByAge;
}

float * SimulationParams::getMaxResistanceInjectionValuesByAge(){
	return this->maxResistanceInjectionValuesByAge;
}


float * SimulationParams::getMinResistanceInjectionValuesByAge(){
	return this->minResistanceInjectionValuesByAge;
}


float * SimulationParams::getTable_taux_mortalite_by_age_by_10(){
	return this->table_taux_mortalite_by_age_by_10;
}


float SimulationParams::getTaux_contamination_voisin(){
	return this->taux_contamination_voisin;
}


int SimulationParams::getNbPlaceHospital(){
	return this->nbPlaceHospital;
}


int SimulationParams::getNbPlaceReanimation(){
	return this->nbPlaceReanimation;
}


int SimulationParams::getR0(){
	return this->r0;
}

float SimulationParams::getTauxMortRea(){
	return this->tauxMortRea;
}


int SimulationParams::getSize(){
	return this->size;
}


int SimulationParams::getNbMalade(){
	return this->nbMalade;
}

int SimulationParams::getNbHumain(){
	return this->nbHumain;
}


int SimulationParams::getNbIteration(){
	return this->nbIteration;
}

int SimulationParams::getNbMultMortToHosp(){
	return this->nbMultMortToHosp;
}

int SimulationParams::getIsVaccin(){
	return this->isVaccin;
}
float SimulationParams::getTauxVaccination(){
	return this->tauxVaccination;
}


float * SimulationParams::getHistogrammeContamination(){
	return this->histogrammeContamination;
}


float SimulationParams::getPourcentAsymptomatique(){
	return this->pourcentAsymptomatique;
}


float SimulationParams::getTauxDeChanceDeMourirHospitalFull(){
	return this->tauxDeChanceDeMourirHospitalFull;
}
