#include "Human.hpp"
#include "Position.hpp"
#include "RandMT.hpp"
#include "World.hpp"
#include <iostream>
#include <fstream>
using namespace std;
int main(void){
    // Initialisation par défaut comme Matsumoto
    RandMT * rand = new RandMT();

    float params[7]; 
	string valueParam;
	ifstream readFile("config.txt");
	int i = 0;
	
	

	string delimiter = ";";
	
	
	
	while (getline (readFile, valueParam)) {
	
		string token = valueParam.substr(0, valueParam.find(delimiter));
		if(i == 1){
			params[i] = stof(token);
			i++;
		}else{
			params[i] = stoi(token);
			i++;
		}
		
	}

	readFile.close();
	
	//Param [0] = size : int
	//Param [1] = taux_contamination_voisin : float
	//Param [2] = nombre d'humain : int
	//Param [3] = nombre de malade : int
	//Param [4] = nombre d'itération : int
	//Param [5] = nbPlaceHospital : int
	//Param [6] = nbPlaceReanimation : int

    World * world = new World((int)params[0],params[1], (int)params[5], (int)params[6],true);

    world->initialize((int)params[2],rand,(int)params[3]);

    world->startSimulation((int)params[4],rand);
}
