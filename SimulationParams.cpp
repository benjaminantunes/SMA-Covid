
#include "SimulationParams.hpp"
#include <fstream>
#include <ostream>
#include <iostream>

using namespace std;


SimulationParams::SimulationParams(char * inFilename){


   _mapStringValues["resistanceInfectionValuesByAge"] = 0;
   _mapStringValues["maxResistanceInjectionValuesByAge"] = 1;
   _mapStringValues["minResistanceInjectionValuesByAge"] = 2;
   _mapStringValues["tableTauxMortaliteByAgeBy10"] = 3;
   _mapStringValues["nbPlaceHospital"] = 5;
   _mapStringValues["nbPlaceReanimation"] = 6;
   _mapStringValues["r0"] = 7;
   _mapStringValues["tauxMortRea"] = 8;
   _mapStringValues["size"] = 9;
   _mapStringValues["nbMalade"] = 10;
   _mapStringValues["nbHumain"] = 11;
   _mapStringValues["nbIteration"] = 12;
   _mapStringValues["nbMultMortToHosp"] = 13;
   _mapStringValues["isVaccin"] = 14;
   _mapStringValues["histogrammeContamination"] = 15;
   _mapStringValues["pourcentAsymptomatique"] = 16;
   _mapStringValues["tauxDeChanceDeMourirHospitalFull"] = 17;
   _mapStringValues["tauxVaccination"] = 18;
   _mapStringValues["tauxContaDistanceDeux"] = 19;


   string   line;
   ifstream readFile(inFilename);
   size_t   pos = 0;
   

   string   delimiterName = "||";
   string   delimiterValues = ",";
   
   
   while (getline(readFile, line))
   {
      if(line.find("#") == string::npos)
      {
         string paramName = line.substr(0, line.find(delimiterName));
         string paramValues = line.erase(0,line.find(delimiterName) + delimiterName.length());
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
               _minResistanceInjectionValuesByAge[j] = stof(value);
               break;
               
             case 3:
               while ((pos = paramValues.find(delimiterValues)) != string::npos)
               {
                  value = paramValues.substr(0, pos);
                  _tableTauxMortaliteByAgeBy10[j] = stof(value);
                  j++;
                  paramValues.erase(0, pos + delimiterValues.length());
               }
               _tableTauxMortaliteByAgeBy10[j] = stof(value);
               break;
               
            case 5:
               _nbPlaceHospital = stoi(paramValues);
               break;
               
            case 6:
               _nbPlaceReanimation = stoi(paramValues);
               break;
               
            case 7:
               _r0 = stof(paramValues);
               break;
               
            case 8:
               _tauxMortRea = stof(paramValues);
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
               
            case 13:
               _nbMultMortToHosp = stoi(paramValues);
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
               

         }
      }
      
      
      
   }

   readFile.close();

}

float * SimulationParams::getResistanceInfectionValuesByAge(){
   return _resistanceInfectionValuesByAge;
}

float * SimulationParams::getMaxResistanceInjectionValuesByAge(){
   return _maxResistanceInjectionValuesByAge;
}


float * SimulationParams::getMinResistanceInjectionValuesByAge(){
   return _minResistanceInjectionValuesByAge;
}


float * SimulationParams::getTableTauxMortaliteByAgeBy10(){
   return _tableTauxMortaliteByAgeBy10;
}


int SimulationParams::getNbPlaceHospital(){
   return _nbPlaceHospital;
}


int SimulationParams::getNbPlaceReanimation(){
   return _nbPlaceReanimation;
}


int SimulationParams::getR0(){
   return _r0;
}

float SimulationParams::getTauxMortRea(){
   return _tauxMortRea;
}


int SimulationParams::getSize(){
   return _size;
}


int SimulationParams::getNbMalade(){
   return _nbMalade;
}

int SimulationParams::getNbHumain(){
   return _nbHumain;
}


int SimulationParams::getNbIteration(){
   return _nbIteration;
}

int SimulationParams::getNbMultMortToHosp(){
   return _nbMultMortToHosp;
}

int SimulationParams::getIsVaccin(){
   return _isVaccin;
}
float SimulationParams::getTauxVaccination(){
   return _tauxVaccination;
}


float * SimulationParams::getHistogrammeContamination(){
   return _histogrammeContamination;
}


float SimulationParams::getPourcentAsymptomatique(){
   return _pourcentAsymptomatique;
}


float SimulationParams::getTauxDeChanceDeMourirHospitalFull(){
   return _tauxDeChanceDeMourirHospitalFull;
}

float SimulationParams::getTauxContaDistanceDeux(){
   return _tauxContaDistanceDeux;
}
