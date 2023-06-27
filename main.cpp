#include "Human.hpp"
#include "Position.hpp"
#include "RandMT.hpp"
#include "World.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

RandMT * randmt;

int main(int argc, char ** argv)
{

   
   //argv[0] = le nom de la commande
   //argv[1] = le nom du fichier contenant le statut de MT à utiliser
   //argv[2] = le nom du fichier de configParams
   
   //In bash script, we have : # ./replicationSimulation statusNB numRepli configVaccin configDpt
   printf("Nom de la commande :%s\n",argv[0]);
   printf("Nom du fichier MT a utiliser :%s\n",argv[1]);
   printf("Numéro de la replication :%s\n",argv[2]);
   printf("config épidémie :%s\n",argv[3]);
   printf("config géographique :%s\n",argv[4]);

   string cheminStatut = "./mts-0000-0999/";
   cheminStatut = cheminStatut + argv[1];

   randmt =  new RandMT(cheminStatut);

   SimulationParams * simulationParams = new SimulationParams(argv[4],argv[3]);

   string logFilename = "log-";
   string mt = "-MT-";
   string extension = ".txt";

   logFilename += string(argv[3]);
   logFilename += "-";
   logFilename += string(argv[4]);
   logFilename += mt;
   logFilename += string(argv[1]);
   logFilename += "NumRepli" + string(argv[2]);
   logFilename += extension;


   cout << "log file name : " << logFilename << endl;

   World * world = new World(simulationParams, (char *)logFilename.c_str(), true);


   world->initialize(simulationParams);


   world->startSimulation(simulationParams);

   delete world;
   delete simulationParams;
      

   
   
}
