
#include "SimulationParams.hpp"
#include <fstream>
#include <ostream>
#include <iostream>

using namespace std;


SimulationParams::SimulationParams(char * inFilenameCity, char * inFilenameConfigParams){


   _mapStringValues["resistanceInfectionValuesByAge"] = 0;
   _mapStringValues["maxResistanceInjectionValuesByAge"] = 1;
   _mapStringValues["minResistanceInjectionValuesByAge"] = 2;
   _mapStringValues["tableTauxHospitalisationByAge"] = 3;
   _mapStringValues["nbPlaceHospital"] = 5;
   _mapStringValues["nbPlaceReanimation"] = 6;
   _mapStringValues["r0"] = 7;
   _mapStringValues["tauxMortRea"] = 8;
   _mapStringValues["size"] = 9;
   _mapStringValues["nbMalade"] = 10;
   _mapStringValues["nbHumain"] = 11;
   _mapStringValues["nbIteration"] = 12;
   //_mapStringValues["nbMultMortToHosp"] = 13;
   _mapStringValues["isVaccin"] = 14;
   _mapStringValues["histogrammeContamination"] = 15;
   _mapStringValues["pourcentAsymptomatique"] = 16;
   _mapStringValues["tauxDeChanceDeMourirHospitalFull"] = 17;
   _mapStringValues["tauxVaccination"] = 18;
   _mapStringValues["tauxContaDistanceDeux"] = 19;
   _mapStringValues["tauxVaccinationRappel"] = 20;
   _mapStringValues["tauxDeProtectionHospVaccinByAge"] = 21;
   _mapStringValues["tauxDeProtectionReaVaccinByAge"] = 22;
   _mapStringValues["tauxDeProtectionHospVaccinRappelByAge"] = 23;
   _mapStringValues["tauxDeProtectionReaVaccinRappelByAge"] = 24;
   _mapStringValues["tauxDeProtectionHospInfectionByAge"] = 25;
   _mapStringValues["tauxDeProtectionReaInfectionByAge"] = 26;
   _mapStringValues["isMedicament"] = 27;
   _mapStringValues["tauxProtectionReaMedicament"] = 28;
   _mapStringValues["isMasqueTissu"] = 29;
   _mapStringValues["tauxProctectionMasqueTissu"] = 30;
   _mapStringValues["isMasqueChir"] = 31;
   _mapStringValues["tauxProtectionMasqueChir"] = 32;
   _mapStringValues["isMasqueFFP2"] = 33;
   _mapStringValues["tauxProtectionMasqueFFP2"] = 34;
   _mapStringValues["isConfinement"] = 35;
   _mapStringValues["nbDeplacementReductionConfinement"] = 36;
   _mapStringValues["isDeplacementLimites"] = 37;
   _mapStringValues["nbDistanceMax"] = 38;
   _mapStringValues["isGelHydroalcolique"] = 39;
   _mapStringValues["tauxProtectionTransmissionGelHydro"] = 40;
   _mapStringValues["isTestCovid"] = 41;
   _mapStringValues["tauxDeDivisionAsymptomatique"] = 42;
   _mapStringValues["isCouvreFeu"] = 43;
   _mapStringValues["nbDeplacementReductionCouvreFeu"] = 44;
   _mapStringValues["isSuperContaminateur"] = 45;
   _mapStringValues["nbDeplacementSuperContaminateur"] = 46;
   _mapStringValues["probasCumulativesTrancheAge"] = 47;
   _mapStringValues["nbLimiteDistanceMaxConfinement"] = 48;
   _mapStringValues["nbDeplacementJour"] = 49;



   string   line;
   ifstream readFile(inFilenameConfigParams);
   size_t   pos = 0;
   

   string   delimiterName = "||";
   string   delimiterValues = ",";
   
   
   while (getline(readFile, line))
   {
      if(line.find("#") == string::npos)
      {
         string paramName = line.substr(0, line.find(delimiterName));
         string paramValues = line.erase(0,
                                         line.find(delimiterName) 
                                         + 
                                         delimiterName.length()
                                        );
         string value;
         int j = 0;
         
         switch (_mapStringValues[paramName])
         {
            
             case 0:
               while ((pos = paramValues.find(delimiterValues)) != string::npos)
               {
                  value = paramValues.substr(0, pos);
                  _resistanceInfectionValuesByAge[j] = stof(value);
                  j++;
                  paramValues.erase(0, pos + delimiterValues.length());
               }
               value = paramValues.substr(0, pos);
               _resistanceInfectionValuesByAge[j] = stof(value);
               break;
               
             case 1:
               while ((pos = paramValues.find(delimiterValues)) != string::npos)
               {
                  value = paramValues.substr(0, pos);
                  _maxResistanceInjectionValuesByAge[j] = stof(value);
                  j++;
                  paramValues.erase(0, pos + delimiterValues.length());
               }
               value = paramValues.substr(0, pos);
               _maxResistanceInjectionValuesByAge[j] = stof(value);
               break;
               
             case 2:
               while ((pos = paramValues.find(delimiterValues)) != string::npos)
               {
                  value = paramValues.substr(0, pos);
                  _minResistanceInjectionValuesByAge[j] = stof(value);
                  j++;
                  paramValues.erase(0, pos + delimiterValues.length());
               }
               value = paramValues.substr(0, pos);
               _minResistanceInjectionValuesByAge[j] = stof(value);
               break;
               
             case 3:
               while ((pos = paramValues.find(delimiterValues)) != string::npos)
               {
                  value = paramValues.substr(0, pos);
                  _tableTauxHospitalisationByAge[j] = stof(value);
                  j++;
                  paramValues.erase(0, pos + delimiterValues.length());
               }
               value = paramValues.substr(0, pos);
               _tableTauxHospitalisationByAge[j] = stof(value);
               break;
               

            case 7:
               _r0 = stof(paramValues);
               break;
               
            case 8:
               _tauxMortRea = stof(paramValues);
               break;
               

            case 14:
               _isVaccin = stoi(paramValues);
               break;
               
            case 15:
               while ((pos = paramValues.find(delimiterValues)) != string::npos)
               {
                  value = paramValues.substr(0, pos);
                  _histogrammeContamination[j] = stof(value);
                  j++;
                  paramValues.erase(0, pos + delimiterValues.length());
               }
               value = paramValues.substr(0, pos);
               _histogrammeContamination[j] = stof(value);
               break;
               
            case 16:
               _pourcentAsymptomatique = stof(paramValues);
               break;
               
            case 17:
               _tauxDeChanceDeMourirHospitalFull = stof(paramValues);
               break;
               
            case 18:
               _tauxVaccination = stof(paramValues);
               break;
               
            case 19:
               _tauxContaDistanceDeux = stof(paramValues);
               break;
               
            case 20:
               _tauxVaccinationRappel = stof(paramValues);
               break;
               
            case 21:
               while ((pos = paramValues.find(delimiterValues)) != string::npos)
               {
                  value = paramValues.substr(0, pos);
                  _tauxDeProtectionHospVaccinByAge[j] = stof(value);
                  j++;
                  paramValues.erase(0, pos + delimiterValues.length());
               }
               value = paramValues.substr(0, pos);
               _tauxDeProtectionHospVaccinByAge[j] = stof(value);
               break;
               
            case 22:
               while ((pos = paramValues.find(delimiterValues)) != string::npos)
               {
                  value = paramValues.substr(0, pos);
                  _tauxDeProtectionReaVaccinByAge[j] = stof(value);
                  j++;
                  paramValues.erase(0, pos + delimiterValues.length());
               }
               value = paramValues.substr(0, pos);
               _tauxDeProtectionReaVaccinByAge[j] = stof(value);
               break;
               
            case 23:
               while ((pos = paramValues.find(delimiterValues)) != string::npos)
               {
                  value = paramValues.substr(0, pos);
                  _tauxDeProtectionHospVaccinRappelByAge[j] = stof(value);
                  j++;
                  paramValues.erase(0, pos + delimiterValues.length());
               }
               value = paramValues.substr(0, pos);
               _tauxDeProtectionHospVaccinRappelByAge[j] = stof(value);
               break;
               
            case 24:
               while ((pos = paramValues.find(delimiterValues)) != string::npos)
               {
                  value = paramValues.substr(0, pos);
                  _tauxDeProtectionReaVaccinRappelByAge[j] = stof(value);
                  j++;
                  paramValues.erase(0, pos + delimiterValues.length());
               }
               value = paramValues.substr(0, pos);
               _tauxDeProtectionReaVaccinRappelByAge[j] = stof(value);
               break;
               
            case 25:
               while ((pos = paramValues.find(delimiterValues)) != string::npos)
               {
                  value = paramValues.substr(0, pos);
                  _tauxDeProtectionHospInfectionByAge[j] = stof(value);
                  j++;
                  paramValues.erase(0, pos + delimiterValues.length());
               }
               value = paramValues.substr(0, pos);
               _tauxDeProtectionHospInfectionByAge[j] = stof(value);
               break;
               
            case 26:
               while ((pos = paramValues.find(delimiterValues)) != string::npos)
               {
                  value = paramValues.substr(0, pos);
                  _tauxDeProtectionReaInfectionByAge[j] = stof(value);
                  j++;
                  paramValues.erase(0, pos + delimiterValues.length());
               }
               value = paramValues.substr(0, pos);
               _tauxDeProtectionReaInfectionByAge[j] = stof(value);
               break;
            
               
            case 27:
               _isMedicament = stoi(paramValues);
               break;
               
            case 28:
               _tauxProtectionReaMedicament = stof(paramValues);
               break;
               
            case 29:
               _isMasqueTissu = stoi(paramValues);
               break;
               
            case 30:
               _tauxProtectionMasqueTissu = stof(paramValues);
               break;
               
            case 31:
               _isMasqueChir = stoi(paramValues);
               break;
               
            case 32:
               _tauxProtectionMasqueChir = stof(paramValues);
               break;
               
            case 33:
               _isMasqueFFP2 = stoi(paramValues);
               break;
               
            case 34:
               _tauxProtectionMasqueFFP2 = stof(paramValues);
               break;
               
            case 35:
               _isConfinement = stoi(paramValues);
               break;
               
            case 36:
               _nbDeplacementReductionConfinement = stof(paramValues);
               break;
               
            case 37:
               _isDeplacementLimites = stoi(paramValues);
               break;
               
            case 38:
               _nbDistanceMax = stoi(paramValues);
               break;
               
            case 39:
               _isGelHydroalcolique = stoi(paramValues);
               break;
               
            case 40:
               _tauxProtectionTransmissionGelHydro = stof(paramValues);
               break;
               
            case 41:
               _isTestCovid = stoi(paramValues);
               break;
               
            case 42:
               _tauxDeDivisionAsymptomatique = stof(paramValues);
               break;
               
            case 43:
               _isCouvreFeu = stoi(paramValues);
               break;
               
            case 44:
               _nbDeplacementReductionCouvreFeu = stoi(paramValues);
               break;
               
            case 45:
               _isSuperContaminateur = stoi(paramValues);
               break;
               
            case 46:
               _nbDeplacementSuperContaminateur = stoi(paramValues);
               break;
               
               
               
            case 48:
               _nbLimiteDistanceMaxConfinement = stoi(paramValues);
               break;
               
               

         }
      }
      
      
      
   }

   readFile.close();
   
   
   ifstream readFileCity(inFilenameCity);
   string   lineCity;
   
   pos = 0;
   
   while (getline(readFileCity, lineCity))
   {
      if(lineCity.find("#") == string::npos)
      {
         string paramName = lineCity.substr(0, lineCity.find(delimiterName));
         string paramValues = lineCity.erase(0,
                                         lineCity.find(delimiterName) 
                                         + 
                                         delimiterName.length()
                                        );
         string value;
         int j = 0;
         
         switch (_mapStringValues[paramName])
         {
            
             
               
            case 5:
               _nbPlaceHospital = stoi(paramValues);
               break;
               
            case 6:
               _nbPlaceReanimation = stoi(paramValues);
               break;
               
            case 9:
               _size = stoi(paramValues);
               break;
               
            case 10:
               _nbMalade = stoi(paramValues);
               break;
               
            case 11:
               _nbHumain = stoi(paramValues);
               break;
               
            case 12:
               _nbIteration = stoi(paramValues);
               break;
         
            case 49:
               _nbDeplacementJour = stoi(paramValues);
               break;
               
            case 47:
               while ((pos = paramValues.find(delimiterValues)) != string::npos)
               {
                  value = paramValues.substr(0, pos);
                  _probasCumulativesTrancheAge[j] = stof(value);
                  j++;
                  paramValues.erase(0, pos + delimiterValues.length());
               }
               value = paramValues.substr(0, pos);
               _probasCumulativesTrancheAge[j] = stof(value);
               break;
         }
      }
      
      
      
   }

   readFileCity.close();

}

float * SimulationParams::getResistanceInfectionValuesByAge()
{
   return _resistanceInfectionValuesByAge;
}

float * SimulationParams::getMaxResistanceInjectionValuesByAge()
{
   return _maxResistanceInjectionValuesByAge;
}


float * SimulationParams::getMinResistanceInjectionValuesByAge()
{
   return _minResistanceInjectionValuesByAge;
}


float * SimulationParams::getTableTauxHospitalisationByAge()
{
   return _tableTauxHospitalisationByAge;
}


int SimulationParams::getNbPlaceHospital()
{
   return _nbPlaceHospital;
}


int SimulationParams::getNbPlaceReanimation()
{
   return _nbPlaceReanimation;
}


int SimulationParams::getR0()
{
   return _r0;
}

float SimulationParams::getTauxMortRea()
{
   return _tauxMortRea;
}


int SimulationParams::getSize()
{
   return _size;
}


int SimulationParams::getNbMalade()
{
   return _nbMalade;
}

int SimulationParams::getNbHumain()
{
   return _nbHumain;
}


int SimulationParams::getNbIteration()
{
   return _nbIteration;
}


int SimulationParams::getIsVaccin()
{
   return _isVaccin;
}

float SimulationParams::getTauxVaccination()
{
   return _tauxVaccination;
}


float * SimulationParams::getHistogrammeContamination()
{
   return _histogrammeContamination;
}


float SimulationParams::getPourcentAsymptomatique()
{
   return _pourcentAsymptomatique;
}


float SimulationParams::getTauxDeChanceDeMourirHospitalFull()
{
   return _tauxDeChanceDeMourirHospitalFull;
}

float SimulationParams::getTauxContaDistanceDeux()
{
   return _tauxContaDistanceDeux;
}

float SimulationParams::getTauxVaccinationRappel()
{
   return _tauxVaccinationRappel;
}

float *  SimulationParams::getTauxDeProtectionHospVaccinByAge()
{
   return _tauxDeProtectionHospVaccinByAge;
}

float * SimulationParams::getTauxDeProtectionReaVaccinByAge()
{
   return _tauxDeProtectionReaVaccinByAge;
}

float * SimulationParams::getTauxDeProtectionHospVaccinRappelByAge()
{
   return _tauxDeProtectionHospVaccinRappelByAge;
}

float * SimulationParams::getTauxDeProtectionReaVaccinRappelByAge()
{
   return _tauxDeProtectionReaVaccinRappelByAge;
}

float * SimulationParams::getTauxDeProtectionHospInfectionByAge()
{
   return _tauxDeProtectionHospInfectionByAge;
}

float * SimulationParams::getTauxDeProtectionReaInfectionByAge()
{
   return _tauxDeProtectionReaInfectionByAge;
}

int SimulationParams::getIsMedicament()
{
   return _isMedicament;
}

float SimulationParams::getTauxProtectionReaMedicament()
{
   return _tauxProtectionReaMedicament;
}

int SimulationParams::getIsMasqueTissu()
{
   return _isMasqueTissu;
}

float SimulationParams::getTauxProtectionMasqueTissu()
{
   return _tauxProtectionMasqueTissu;
}

int SimulationParams::getIsMasqueChir()
{
   return _isMasqueChir;
}

float SimulationParams::getTauxProtectionMasqueChir()
{
   return _tauxProtectionMasqueChir;
}

int SimulationParams::getIsMasqueFFP2()
{
   return _isMasqueFFP2;
}

float SimulationParams::getTauxProtectionMasqueFFP2()
{
   return _tauxProtectionMasqueFFP2;
}

int SimulationParams::getIsConfinement()
{
   return _isConfinement;
}

int SimulationParams::getNbDeplacementReductionConfinement()
{
   return _nbDeplacementReductionConfinement;
}

int SimulationParams::getNbLimiteDistanceMaxConfinement()
{
   return _nbLimiteDistanceMaxConfinement;
}

int SimulationParams::getIsDeplacementLimites()
{
   return _isDeplacementLimites;
}

int SimulationParams::getNbDistanceMax()
{
   return _nbDistanceMax;
}

int SimulationParams::getIsGelHydroalcolique()
{
   return _isGelHydroalcolique;
}

float SimulationParams::getTauxProtectionTransmissionGelHydro()
{
   return _tauxProtectionTransmissionGelHydro;    
}

int SimulationParams::getIsTestCovid()
{
   return _isTestCovid;
}

float SimulationParams::getTauxDeDivisionAsymptomatique()
{
   return _tauxDeDivisionAsymptomatique;
}

int SimulationParams::getIsCouvreFeu()
{
   return _isCouvreFeu;
}

int SimulationParams::getNbDeplacementReductionCouvreFeu()
{
   return _nbDeplacementReductionCouvreFeu;
}

int SimulationParams::getIsSuperContaminateur()
{
   return _isSuperContaminateur;
}

int SimulationParams::getNbDeplacementSuperContaminateur()
{
   return _nbDeplacementSuperContaminateur;
}

float * SimulationParams::getProbasCumulativesTrancheAge()
{
   return _probasCumulativesTrancheAge;
}

int SimulationParams::getNbDeplacementJour()
{
   return _nbDeplacementJour;
}
