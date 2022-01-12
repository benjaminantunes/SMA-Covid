#include "World.hpp"
#include <typeinfo>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;
World::World(SimulationParams * simulationParams, char * nomFichierLog, bool log){
	int size = simulationParams->getSize();
	float taux_contamination_voisin = simulationParams->getTaux_contamination_voisin();
	int multMortToHosp = simulationParams->getNbMultMortToHosp();
	float * table_taux_mortalite_by_age_by_10 = simulationParams->getTable_taux_mortalite_by_age_by_10();
	float tauxMortRea = simulationParams->getTauxMortRea();
	float r0 = simulationParams->getR0();
	int nbPlaceHospital = simulationParams->getNbPlaceHospital();
	int nbPlaceReanimation = simulationParams->getNbPlaceReanimation();
	float pourcentAsymptomatique = simulationParams->getPourcentAsymptomatique();
	float tauxVaccination = simulationParams->getTauxVaccination();
	float tauxDeChanceDeMourirHospitalFull = simulationParams->getTauxDeChanceDeMourirHospitalFull();
	float * histogrammeContamination = simulationParams->getHistogrammeContamination();
	float tauxContaDistanceDeux = simulationParams->getTauxContaDistanceDeux();

	// Agent *** carte; === Agent * carte[size][size];
	this->carte = (Human ***)malloc(size * sizeof(Human**));
	for(int i = 0; i < size; i++) this->carte[i] = (Human **)malloc(size * sizeof(Human*));
	
	
	for(int i = 0; i<size ;i++){
		for(int j = 0; j<size ; j++){
			
			this->carte[i][j] = nullptr;
		}
	}

	this->histogrammeContamination = (float*)malloc( 11 * sizeof(float));
	this->histogrammeContamination = histogrammeContamination;
	
	this->taux_contamination_voisin = taux_contamination_voisin;

	this->table_taux_mortalite_by_age_by_10 = (float*)malloc( 8 * sizeof(float));
	this->table_taux_mortalite_by_age_by_10 = table_taux_mortalite_by_age_by_10;
	for(int i = 0; i<8;i++){
		this->table_taux_hospitalisation_by_age_by_10[i] = this->table_taux_mortalite_by_age_by_10[i] * multMortToHosp;
	}

	this->size = size;
	this->tauxMortRea = tauxMortRea;
	this->r0 = r0;
	this->nbPlaceHospital = nbPlaceHospital;
	this->nbPlaceReanimation = nbPlaceReanimation;
	this->pourcentAsymptomatique = pourcentAsymptomatique;
	this->tauxVaccination = tauxVaccination;
	this->tauxDeChanceDeMourirHospitalFull = tauxDeChanceDeMourirHospitalFull;
	this->tauxContaDistanceDeux = tauxContaDistanceDeux;
	this->log = log;
	this->stats["dead"] = 0;
	this->stats["contamined"] = 0;
	this->stats["recovered"] = 0;
	this->stats["safe"] = 0;
	if(this->log){
		this->logfile.open(nomFichierLog,ios::out);
	}
	
	


}

World::~World(){
	if(this->log){
		this->logfile.close();
	}
}

void World::writeLog(string msg){
	this->logfile << msg;
	this->logfile << endl;
}


void World::pause(){
	cout << "Hit <Return to continue" << endl ;
}

void World::display(){
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "**********************************************************************";
	for(int row = 0; row<this->size; row++){
		cout << "   " << endl;
		for(int column = 0; column<this->size; column++ ){
			if(this->carte[row][column] == nullptr){// Null n'existe pas en C++. J'ai initialisé à NULL, donc j'imagine un tableau rempli de 0.
				cout << World::SYMBOL_EMPTY;
			}else{
				
				cout << this->carte[row][column]->to_string();
			}

		}
		cout << endl;
	}
}


void World::updateStats(string state, RandMT * rand){
	if(state == "recovered"){
		this->stats.at("contamined") -= 1;
		this->stats.at("recovered") += 1;	  
	}
	else if(state == "dead"){
		this->stats.at("contamined") -= 1;
		this->stats.at("dead") += 1;
	}
	else if(state == "contamined"){
		this->stats.at("safe") -= 1;
		this->stats.at("contamined") += 1;
	}
	else if(state == "safe"){
		this->stats.at("safe") += 1;
	}
}

void World::displayStats(){
	cout << "***************STATISTICS******************" <<endl;
	cout <<"Safe : " << this->stats.at("safe") << endl;
	cout <<"Contamined : " << this->stats.at("contamined") << endl;
	cout <<"Recovered : " << this->stats.at("recovered") << endl;
	cout <<"Dead : " << this->stats.at("dead") << endl;
}

bool World::isValid(int row, int column){
	return row >= 0 && column >= 0 && row < this->size and column < this->size;
}


bool World::isHuman(int row, int column){
	if(this->isValid(row,column) && this->carte[row][column] != nullptr){
		return this->isValid(row,column) && (this->carte[row][column]->to_string() == 'X' ||this->carte[row][column]->to_string() == 'O' ||this->carte[row][column]->to_string() == 'H' || this->carte[row][column]->to_string() == 'R');
	}
	return false;

}

bool World::isEmpty(int row, int column){
	return this->isValid(row,column) && this->carte[row][column] == nullptr;

}


void World::addAgent(string agent_name,SimulationParams * simulationParams, int agents, float world_max, RandMT * rand,  int isVaccin ,int sicks){


	int max_agents = pow(this->size,2) * world_max;
	


	if(agents > max_agents){
		cout << "trop d'agent" << endl;
		exit(1);
	}

	if(sicks > agents){
		cout << "trop de malade" << endl;
		exit(1);
	}

	for(int qty_agent = 0; qty_agent < agents-sicks; qty_agent++){
		bool varEmpty = false;
		int row;
		int column;
		while(!varEmpty){
				
			// On cherche une position libre sur la carte 
			row = rand->genrand_int32()%this->size ;
			column = rand->genrand_int32()%this->size ;
			varEmpty = this->isEmpty(row,column);
		}

			
		this->carte[row][column] = new Human(simulationParams,rand,row,column);
		if(isVaccin == 1){
			float randValue = rand->genrand_real1();
			if(randValue < this->tauxVaccination){
				this->carte[row][column]->vaccine(rand);
			}
			
		}
		this->updateStats("safe", rand);
		this->humanSafePositions.push_back(this->carte[row][column]->getPosition());
		//this->writeLog("Human cree sur xxxxx");
		
	}
	

	for(int qty_agents = 0; qty_agents<sicks;qty_agents++){
		
		bool varEmpty = false;
		int row;
		int column;
		while(!varEmpty){
			//row, column= randint(0, self._size - 1), randint(0, self._size - 1)
			row = rand->genrand_int32()%this->size ;
			column = rand->genrand_int32()%this->size ;
			varEmpty = this->isEmpty(row,column);
		}
		
		this->carte[row][column] = new Human(simulationParams,rand,row,column);
		this->updateStats("safe",rand);
		this->carte[row][column]->contamine();
		this->updateStats("contamined",rand);
		this->humanAsymptomatiquePositions.push_back(this->carte[row][column]->getPosition());
		//this->writeLog("Humain crée sur xxxx");
		

	}
   

}

void World::initialize(SimulationParams * simulationParams, RandMT * rand){

	//this->writeLog("******Initialization******");
	this->addAgent("Human",simulationParams, simulationParams->getNbHumain(), World::MAX_HUMANS, rand, simulationParams->getIsVaccin(), simulationParams->getNbMalade());

}


map<string,vector<Position>> World::vision(int length, int row, int column){


	map<string, vector<Position>> neighborhood;

    neighborhood["empty"];
    neighborhood["human"];


    
    
    
    
	Position maPositionTest;
	for(int elt_1 = 0-length; elt_1<length+1;elt_1++){
		for(int elt_2 = 0-length; elt_2<length+1;elt_2++){

			maPositionTest.setPosX(elt_1);
			maPositionTest.setPosY(elt_2);

			bool isInNeighborhood = false;

			for(Position  temp: neighborhood.at("empty") ){
				if(temp == maPositionTest){
					isInNeighborhood = true;
				}
			}
			for(Position  temp: neighborhood.at("human") ){

				if(temp == maPositionTest){
					isInNeighborhood = true;
				}
			}

			
			// Tous ça pour ça : and (elt_1, elt_2) not in neighborhood
			if((elt_1 != 0 || elt_2 !=0) && !isInNeighborhood ){
				
				
				if(this->isHuman(row+elt_1,column+elt_2)){
					neighborhood["human"].push_back(this->carte[row+elt_1][column+elt_2]->getPosition());
				}
				if(this->isEmpty(row+elt_1,column+elt_2)){
					//Comment me débarasser de cette position qui va faire de la fuite mémoire
					//Position * pos = new Position(row+elt_1,column+elt_2);
                    Position pos;
                    pos.setPosX(row+elt_1);
                    pos.setPosY(column+elt_2);
					neighborhood["empty"].push_back(pos);
				}
				//delete pos;
			}
			

		}
	}
	//delete maPositionTest;
	return neighborhood;
}

void World::contamination(int row, int column, RandMT * rand, int currentRow, int currentColumn){

	//float histogrammeContamination[11] = {0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.7, 0.6, 0.4, 0.2};
	map<string, vector<Position>> target_v1 = this->vision(2,row,column);
	Position maPositionTest;

	for(Position  pos : target_v1["human"]){
	
		if(!this->carte[pos.getPosX()][pos.getPosY()]->isSick()){
		
			float randomValue = rand->genrand_real1();

			int distanceRow = abs(row - pos.getPosX());
			int distanceColumn = abs(column - pos.getPosY());
			int distance;
			
			if(distanceRow > distanceColumn){
				distance = distanceRow;
			}else{
				distance = distanceColumn;
			}

			if(distance == 1){	
				
				if(randomValue < this->histogrammeContamination[this->carte[currentRow][currentColumn]->getState()-1] * (1 - this->carte[pos.getPosX()][pos.getPosY()]->getResistanceVirus())){ 
					
					this->carte[pos.getPosX()][pos.getPosY()]->contamine();
					this->nbNouveauxCas++;
					this->newNextHumanAsymptomatiquePositions.push_back(Position(pos.getPosX(), pos.getPosY()));
					
					maPositionTest.setPosX(pos.getPosX());
					maPositionTest.setPosY(pos.getPosY());
					int index = 0;
					for(Position  temp: this->newHumanSafePositions ){
						if(temp == maPositionTest){
							this->newHumanSafePositions.erase(this->newHumanSafePositions.begin()+index);
						}
						index++;
					}

					this->updateStats("contamined", rand);
				}
			
			}else if(distance == 2){

				if(randomValue < (this->histogrammeContamination[this->carte[currentRow][currentColumn]->getState()-1] * (1 - this->carte[pos.getPosX()][pos.getPosY()]->getResistanceVirus()))*this->tauxContaDistanceDeux){  // On divise par deux la chance de contamination car 2 cases de distance.
					
					this->carte[pos.getPosX()][pos.getPosY()]->contamine();
					this->nbNouveauxCas++;
					this->newNextHumanAsymptomatiquePositions.push_back(Position(pos.getPosX(), pos.getPosY()));
					maPositionTest.setPosX(pos.getPosX());
					maPositionTest.setPosY(pos.getPosY());
					int index = 0;
					for(Position  temp: this->newHumanSafePositions ){
						if(temp == maPositionTest){
							this->newHumanSafePositions.erase(this->newHumanSafePositions.begin()+index);
						}
						index++;
					}
					this->updateStats("contamined", rand);
				}
			
			}
	
		}
	}
	
	
}


void World::humanGoFromTo(int fromRow, int fromColumn, int toRow, int toColumn,RandMT * rand, bool die){
	if(!die){
	
		this->carte[toRow][toColumn] = this->carte[fromRow][fromColumn];
		this->carte[toRow][toColumn]->setPosition(toRow,toColumn);
		this->carte[fromRow][fromColumn] = nullptr;
		// Interet de rajouter cette ligne ? Bizarre
		this->carte[toRow][toColumn]->setPosition(toRow,toColumn);

		//self.writeLog(f"Human ({fromRow},{fromColumn}) go to ({toRow},{toColumn})\n")

	}else{
		this->carte[fromRow][fromColumn] = nullptr;
		//self.writeLog(f"Human ({fromRow},{fromColumn}) go to ({toRow},{toColumn} and die)\n")
		this->updateStats("dead",rand);

	}
}

void World::moveHumanSafe(int row, int column, RandMT * rand){

	if(this->carte[row][column]->getResistanceVirus() > 0 ){
		this->carte[row][column]->decreaseResistance();
	}
	
	int rowDeplacement = rand->genrand_int32()%this->size; // Il peut se déplacer de 0 à size
	int columnDeplacement = rand->genrand_int32()%this->size; // Il peut se déplacer de 0 à size
	map<string, vector<Position>> target_v1 = this->vision(1,rowDeplacement,columnDeplacement);

	if(target_v1["empty"].size() != 0){
		// Demander a Bruno bachelet si dans un cas comme ça, pour le return, on privilégie pointeur ou valeur.
		int taille = target_v1.at("empty").size();
		int randomValue = ((long)floor(rand->genrand_int32()))%taille;
		//Position * newPosition = target_v1.at("empty").at(randomValue);
		this->humanGoFromTo(row,column, target_v1.at("empty").at(randomValue).getPosX(),target_v1.at("empty").at(randomValue).getPosY(),rand);
		this->newHumanSafePositions.push_back(target_v1.at("empty").at(randomValue));
	}else{
		this->newHumanSafePositions.push_back(this->carte[row][column]->getPosition());
	}


}


void World::moveHumanAsymptomatique(int row, int column, RandMT * rand){

	/*
	
	ATTENTION :
	INCREMENTSTATE() dans le code apellant. On peut faire plusieurs déplacement dans 1 seule journée (sans augmenter le state)
	
	*/

	if(this->carte[row][column]->getState() > 10){
	   	this->carte[row][column]->resetState();
		this->updateStats("recovered",rand);
		this->newHumanSafePositions.push_back(Position(row, column)); 
		return;
		 	
	}
	
	if(this->carte[row][column]->getState() == 3){
			// Proportion de asymptomatique varie de 15 à 30% selon les études. Param ?
			// https://www.inspq.qc.ca/sites/default/files/covid/2989-asymptomatiques-potentiel-transmission-covid19.pdf

			//float pourcentAsymptomatique = (( rand->genrand_int32() % 15) + 16.0)/100;
			float randValue = rand->genrand_real1();
			if(randValue < 1 - this->pourcentAsymptomatique){
				// entre 15% et 30% de chance qu'il soit asymptomatique et qu'il continue de se déplacer
				this->nbCasCovidConnuTotal++;
				this->ageOfSymptomaticDailyHuman.push_back(this->carte[row][column]->getAge());
				this->carte[row][column]->getConfined();
				this->newHumanConfinedPositions.push_back(Position(row, column));
				return;
			}	 	
	}
	
	/*
	L'individu ne contamine que si il se déplace. 
	Il y a 2 tour ou tous le monde est forcément asymptomatique (2jours de contamination potentielle)
	Ensuite, si on est malade, on se confine, si on est a l'hopital, on est confiné, et si on est en réanimation ou mort, on est confiné aussi.
	Si on est malade, on ne se déplace pas.
	De plus, on est contagieux que pendant 9 jours. (2 jours avant symptomes + 9 jours après)
	*/
	
	if(this->carte[row][column]->getState() < 12){
	

		int rowDeplacement = rand->genrand_int32()%this->size; // Il peut se déplacer de 0 à size
		int columnDeplacement = rand->genrand_int32()%this->size; // Il peut se déplacer de 0 à size
		map<string, vector<Position>> target_v1 = this->vision(1,rowDeplacement,columnDeplacement);


		if(target_v1["empty"].size() != 0){
	  
			int taille = target_v1.at("empty").size();
			int randomValue = ((long)floor(rand->genrand_int32()))%taille;

			//Position * newPosition = target_v1.at("empty").at(randomValue);
			this->contamination(target_v1.at("empty").at(randomValue).getPosX(),target_v1.at("empty").at(randomValue).getPosY(), rand, row, column);

			
			this->humanGoFromTo(row,column, target_v1.at("empty").at(randomValue).getPosX(),target_v1.at("empty").at(randomValue).getPosY(),rand);


			this->newCurrentHumanAsymptomatiquePositions.push_back(target_v1.at("empty").at(randomValue));
			
		}else{
			this->contamination(row,column, rand, row, column);
			this->newCurrentHumanAsymptomatiquePositions.push_back(this->carte[row][column]->getPosition());
		}
	
	}
}

void World::moveHumanConfined(int row, int column, RandMT * rand){

	if(this->carte[row][column]->getState() > 10){   	
		this->carte[row][column]->resetState();
		this->newHumanSafePositions.push_back(this->carte[row][column]->getPosition());
		this->updateStats("recovered",rand);
		return;
	
	}
	
	if(this->carte[row][column]->getState() == 4){
			
			//Si la personne est symtomatique, alors elle a des chances d'aller a l'hopital
			float randValue = rand->genrand_real1();

			if(randValue < this->table_taux_hospitalisation_by_age_by_10[this->carte[row][column]->getAge()]/100){
				if(this->nbPersonneHospital < this->nbPlaceHospital){
					this->carte[row][column]->goToHospital();
					this->newHumanHospitalPositions.push_back(this->carte[row][column]->getPosition());
					this->nbNouveauxHospitalisation++;
					this->nbPersonneHospital++;
				}else{
					// Si il n'y a plus de place a l'hopital et qu'on a besoin d'etre hospitalisé, 20% de chance de mourir

					//### tauxDeChanceDeMourirHospitalFull
					if(randValue < this->tauxDeChanceDeMourirHospitalFull){
						this->ageOfDeadHumansDaily.push_back(this->carte[row][column]->getAge());
						//this->updateStats("dead",rand);
						this->humanGoFromTo(row,column, 0,0,rand,  true);
						
						this->nbMorts++;
						////delete newPosition;
						return;
					}
				}
				
			}else{
				this->newHumanConfinedPositions.push_back(this->carte[row][column]->getPosition());
				
			}	
		}else{
			this->newHumanConfinedPositions.push_back(this->carte[row][column]->getPosition());
		}
	
	this->carte[row][column]->incrementState();

}

void World::moveHumanHospital(int row, int column, RandMT * rand){

	if(this->carte[row][column]->getState() > 10){ 
	  	this->newHumanSafePositions.push_back(this->carte[row][column]->getPosition());
		this->nbPersonneHospital--;
		this->carte[row][column]->resetState();
		this->updateStats("recovered",rand);
		return;
	}
	
	if(this->carte[row][column]->getState() == 5){
	
			float randValue = rand->genrand_real1();
			float tauxReaIfHosp;
			
			// On utilise la timeline, qui possède 633 jours. Si la simu dure plus longtemps (prédictions), alors on part sur une base de 15%
			if(this->iteration < 633){
					tauxReaIfHosp = ratioHospRea[this->iteration];
				
				
			}else{
			
				tauxReaIfHosp = 0.15; // La moyenne est 0.1474089554531037
			}
			if(randValue < tauxReaIfHosp){
				
				if(this->nbPersonneReanimation < this->nbPlaceReanimation){
					
					this->nbPersonneHospital--;
					this->newHumanReanimationPositions.push_back(this->carte[row][column]->getPosition());
					this->carte[row][column]->goToReanimation(rand);
					this->nbNouveauxReanimation++;
					this->nbPersonneReanimation++;
				}else{
					// Si la personne doit aller en réanimation mais qu'il n'y a plus de place, elle meurt.
					this->nbPersonneHospital--;
					
					this->ageOfDeadHumansDaily.push_back(this->carte[row][column]->getAge());
					//this->updateStats("dead",rand);
					this->humanGoFromTo(row,column, 0,0,rand,  true);
					this->nbMorts++;
					return;
				}
				
			}else{
				this->newHumanHospitalPositions.push_back(this->carte[row][column]->getPosition());
			}
			
			
		}else{
			this->newHumanHospitalPositions.push_back(this->carte[row][column]->getPosition());
		}
		
	
	
   	this->carte[row][column]->incrementState();

}

void World::moveHumanReanimation(int row, int column, RandMT * rand){
   

	
	/*
	Selon les données de l'AP-HP, la durée moyenne de séjour des patients Covid-19 en réanimation est passée de 19 jours avant le 1er juillet à 9,5 jours après le 1er juillet, a indiqué à APMnews Frédéric Adnet, chef de service du Samu de Seine-Saint-Denis et chef des urgences de l'hôpital Avicenne à Bobigny. Entre les 2 périodes, l'âge médian est passé de 61 ans à 64 ans.
	
	Dans le service de réanimation du Pr Demoule, "la durée de séjour en réanimation est de 5 jours pour les patients non intubés. S'ils sont intubés ils restent quand même 3 semaines (même si on manque encore de recul par rapport à la 2e vague)".
	
	https://www.apmnews.com/depeche/1/355843/covid-19-en-reanimation-une-prise-en-charge-amelioree%2C-des-patients-un-peu-moins-severes
	*/
	
	
	// Ici ça ne va pas car appelé a chaque boucle => attribut durée réanimation propre a chaque humain fixé au départ?


	//double dureeReanimation = (rand->genrand_int32()%21) + 10; // Entre 5 jours et 21 jours de réanimation. (on a deja fait 5 jours de maladie)
	
	if(this->carte[row][column]->getState() > this->carte[row][column]->getDureeReanimation()){
		this->newHumanSafePositions.push_back(this->carte[row][column]->getPosition());
		this->nbPersonneReanimation--;
		this->carte[row][column]->resetState();
		this->updateStats("recovered",rand);
		return;
	}	
 

		
		
		
		
	if(this->carte[row][column]->getState() == 6){
		
		float randValue = rand->genrand_real1();
		// 50% de chances de mourir si on était en réa.
		// L'objectif serait de retrouver 14%, 8%, etc. Mais au niveau des probas c'est sur que ça ne va pas le faire :
		// Pour retrouver 14 % : sur 100% de contaminé -> 60% d'aller a l'hopital -> 15% d'aller en réa -> 50% de mourir.
		// En partant de contaminé, la chance de mourir : 0.6 * 0.15 * 0.5 = 0.045. Très très loin de 0.14.
		// Meme en prenant 100% de anciens a l'hopital, 0.15% *0.5 = 0.075. Il faudrait que les anciens aient quasi 100% de chances de mourir en réa
		
		if(randValue < this->tauxMortRea){

			this->nbPersonneReanimation--;
			
			this->ageOfDeadHumansDaily.push_back(this->carte[row][column]->getAge());
			//this->updateStats("dead",rand);
			this->humanGoFromTo(row,column, 0,0,rand,  true);
			this->nbMorts++;
			return;


		}else{
			this->newHumanReanimationPositions.push_back(this->carte[row][column]->getPosition());
		}
		
		
	}else{
		this->newHumanReanimationPositions.push_back(this->carte[row][column]->getPosition());
	}
	this->carte[row][column]->incrementState();

}


void World::nextIteration(RandMT * rand){
	this->writeLog(to_string(this->iteration));
	this->writeLog(to_string(this->nbNouveauxCas));
	this->writeLog(to_string(this->nbPersonneHospital));
	this->writeLog(to_string(this->nbPersonneReanimation));
	this->writeLog(to_string(this->nbNouveauxHospitalisation));
	this->writeLog(to_string(this->nbNouveauxReanimation));
	this->writeLog(to_string(this->nbMorts));
	this->writeLog(to_string(this->nbCasCovidConnuTotal));
    
    float totalMalade = (float)(this->humanAsymptomatiquePositions.size() + this->humanConfinedPositions.size() + this->humanHospitalPositions.size() +this->humanReanimationPositions.size());
    float reffectifJour = 0;
    if(totalMalade > 0){
        reffectifJour = (float)this->nbNouveauxCas / totalMalade;
    }


	this->writeLog(to_string(reffectifJour*11)); // 10 est le nb de jour où la personne est contaminante : 2 + 9.

	for (int age: this->ageOfSymptomaticDailyHuman) {
		this->writeLog("AgeC:" + to_string(age));
	}
	for (int age: this->ageOfDeadHumansDaily) {
		this->writeLog("AgeD:" + to_string(age));
	}

	
	this->writeLog("##########");
	this->ageOfSymptomaticDailyHuman.clear();
	this->ageOfDeadHumansDaily.clear();
	this->nbNouveauxCas = 0;
	this->nbNouveauxHospitalisation = 0;
	this->nbNouveauxReanimation = 0;
	this->nbMorts = 0;
	this->iteration += 1;

	
	for(Position  temp: this->humanSafePositions){

		this->moveHumanSafe(temp.getPosX(),temp.getPosY(), rand);
	}

//////////////////////////////////////////////////////////////////// 
	// Ce code est provisoire, afin de connaitre le nombre d'iteration à avoir sur Paris pour avoir un r0 de 3 sur les premiers jours de l'épidémie.
	//int nbBoucle = 0;
  	//while(this->nbNouveauxCas < this->humanAsymptomatiquePositions.size() * this->r0 ){
  		//nbBoucle++;

	
  	for(int x = 0; x < 12; x++){
  		for(Position  temp: this->humanAsymptomatiquePositions){

			this->moveHumanAsymptomatique(temp.getPosX(),temp.getPosY(), rand);
		}
		this->humanAsymptomatiquePositions = this->newCurrentHumanAsymptomatiquePositions;
		this->newCurrentHumanAsymptomatiquePositions.clear();
  	}
	for(Position  temp: this->humanAsymptomatiquePositions){

		this->carte[temp.getPosX()][temp.getPosY()]->incrementState();
	}

	
	
//////////////////////////////////////////////////////////  

	 
	for(Position  temp: this->humanConfinedPositions){

		this->moveHumanConfined(temp.getPosX(),temp.getPosY(), rand);

	}

////////////////////////////////////////////////////////////

	
	for(Position  temp: this->humanHospitalPositions){

		this->moveHumanHospital(temp.getPosX(),temp.getPosY(), rand);

	}

	
///////////////////////////////////////////////////////////////

	
	for(Position  temp: this->humanReanimationPositions){

		this->moveHumanReanimation(temp.getPosX(),temp.getPosY(), rand);


	}


	this->humanSafePositions = this->newHumanSafePositions;
	//this->humanAsymptomatiquePositions = this->newHumanAsymptomatiquePositions;
	// Pour les asymptomatiques j'ai deux vecteurs, donc je dois les concatener pour les mettres dans le vecteur courant
	
	
	
	this->humanAsymptomatiquePositions.insert(this->humanAsymptomatiquePositions.end(), this->newNextHumanAsymptomatiquePositions.begin(), this->newNextHumanAsymptomatiquePositions.end());
	
	
	this->humanConfinedPositions = this->newHumanConfinedPositions;
	this->humanHospitalPositions = this->newHumanHospitalPositions;
	this->humanReanimationPositions = this->newHumanReanimationPositions;
	// Cette section ne va fonctionner que si le "=" fait une copie, car si le "=" passe le pointeur au début du vecteur, alors le clear() va également écraser le nouveau.
	
	this->newHumanSafePositions.clear();
	this->newCurrentHumanAsymptomatiquePositions.clear();
	this->newNextHumanAsymptomatiquePositions.clear();
	this->newHumanConfinedPositions.clear();
	this->newHumanHospitalPositions.clear();
	this->newHumanReanimationPositions.clear();
	
}





void World::startSimulation(SimulationParams * simulationParams, RandMT * rand){


	for(int iteration = 0;iteration < simulationParams->getNbIteration();iteration++){
		//this->displayStats();
		//this->display();
		
		//World::pause();
		this->nextIteration(rand);
		/*
		if(this->humansPosition.size() == 0){
			cout << "no more humans in the simulation" << endl;
			//self.writeLog('[STOP] No more human in the simulation !\n')
			break;
		}
		*/
	}
	
	fstream compteurLogFile;

	compteurLogFile.open("compteur.txt",ios::out);
	compteurLogFile << rand->getCompteur();
	compteurLogFile << endl;
	//self.writeLog(f' [STOP] Maximum number of iterations reached ({maxIterations}) end of the simulation!\n')
	//cout << "\033[2J" << endl;
	this->displayStats();
	
}


