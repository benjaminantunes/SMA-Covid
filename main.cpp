#include "Human.hpp"
#include "Position.hpp"
#include "RandMT.hpp"
#include "World.hpp"
#include <iostream>
#include <fstream>
using namespace std;

RandMT * randmt;

int main(int argc, char ** argv)
{

   
   //argv[0] = le nom de la commande
   //argv[1] = le nom du fichier contenant le statut de MT à utiliser, le 1er statut ( ../101-StatutsMT-10p12/mtS10p12i-0001). Doit contenir un nombre. 0,1,2 128 par exemple.
   //argv[2] = le nom du fichier de configParams
   
   char milliers = '0';
   char centaines = '0';
   char dizaines = '0';
   char unites = '0';
   int j;

   char dizainesDpt = '0';
   char unitesDpt = '0';
   int k;

   for(int i = 0; i < 96; i++)
   {
      
      const char * cheminStatut = "../101-StatutsMT-10p12/mtS10p12i-";
      char buf[33];
      strcpy(buf, cheminStatut);
      
      // Le + 48 est pour la table ASCII
      j = i + atoi(argv[1]);
      int milliersNumber = j/1000;
      milliers = milliersNumber + 48;
      j = j - (1000*milliersNumber);
      
      int centaineNumber = j/100;
      centaines = centaineNumber + 48;
      j = j - (100*centaineNumber);
      
      int dizaineNumber = j/10;
      dizaines = dizaineNumber + 48;
      j = j - (10*dizaineNumber);
      
      int uniteNumber = j/1;
      unites = uniteNumber + 48;
      j = j - (1*uniteNumber);
      
      
      char valeur[5];
      valeur[0] = milliers;
      valeur[1] = centaines;
      valeur[2] = dizaines;
      valeur[3] = unites;
      valeur[4] = '\0';
      
      strcat(buf, valeur);
      printf("%s\n",buf);
      randmt =  new RandMT(buf);

      // Ici je vais instancier un objet SimulationParams, qui va aller récupérer tous les paramètres. Ensuite, je passe cet objet dans le constructeur de World au lieu de tous les params.
      
      const char * configDpt = "configDpt";
      k = i;
      dizaineNumber = k/10;
      dizainesDpt = dizaineNumber + 48;
      k = k - (10*dizaineNumber);
      
      uniteNumber = k/1;
      unitesDpt = uniteNumber + 48;
      k = k - (1*uniteNumber);
      
      char valeurDpt[3];
      valeur[0] = dizainesDpt;
      valeur[1] = unitesDpt;
      valeur[2] = '\0';
      strcat(configDpt,valeurDpt);

      SimulationParams * simulationParams = new SimulationParams(configDpt,argv[2]);
      
      char * logFilename = strcat(configDpt,valeur);

      World * world = new World(simulationParams, logFilename, true);
   

      world->initialize(simulationParams);


      world->startSimulation(simulationParams);
      
   }

   
   
}
