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
   //argv[1] = le nom du fichier contenant le statut de MT à utiliser
   //argv[2] = le nom du fichier de config à utiliser
   //argv[3] = le nom du fichier de log à utiliser

   randmt =  new RandMT(argv[1]);

   // Ici je vais instancier un objet SimulationParams, qui va aller récupérer tous les paramètres. Ensuite, je passe cet objet dans le constructeur de World au lieu de tous les params.

   SimulationParams * simulationParams = new SimulationParams(argv[2]);
   World * world = new World(simulationParams, argv[3], true);

   world->initialize(simulationParams);

   
   world->startSimulation(simulationParams);
   
   
}
