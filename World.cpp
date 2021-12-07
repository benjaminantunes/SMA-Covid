#include "World.hpp"
#include <typeinfo>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;
World::World(int size, float taux_contamination_voisin,int nbPlaceHospital, int nbPlaceReanimation, int multMortToHosp, float tauxMortRea, bool log){

    // Agent *** carte; === Agent * carte[size][size];
    this->carte = (Human ***)malloc(size * sizeof(Human**));
	for(int i = 0; i < size; i++) this->carte[i] = (Human **)malloc(size * sizeof(Human*));
	
	
    for(int i = 0; i<size ;i++){
    	for(int j = 0; j<size ; j++){
    		
    		this->carte[i][j] = nullptr;
    	}
    }
    
    this->taux_contamination_voisin = taux_contamination_voisin;
    for(int i = 0; i<8;i++){
    	this->table_taux_hospitalisation_by_age_by_10[i] = this->table_taux_mortalite_by_age_by_10[i] * multMortToHosp;
    }
    this->size = size;
    this->tauxMortRea = tauxMortRea;
    this->nbPlaceHospital = nbPlaceHospital;
    this->nbPlaceReanimation = nbPlaceReanimation;
    this->log = log;
    this->stats["dead"] = 0;
    this->stats["contamined"] = 0;
    this->stats["recovered"] = 0;
    this->stats["safe"] = 0;

    if(this->log){
        this->logfile.open("log.txt",ios::out);
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


void World::addAgent(string agent_name, int agents, float world_max, RandMT * rand, int sicks){


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

        	
		this->carte[row][column] = new Human(rand);
		this->updateStats("safe", rand);
		this->humansPosition.push_back(new Position(row,column));
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
        
        this->carte[row][column] = new Human(rand);
        this->updateStats("safe",rand);
        this->carte[row][column]->contamine();
        this->updateStats("contamined",rand);
        this->humansPosition.push_back(new Position(row,column));
        //this->writeLog("Humain crée sur xxxx");
        

    }
   

}

void World::initialize(int humans, RandMT * rand, int sicks){

    //this->writeLog("******Initialization******");
    this->addAgent("Human", humans, World::MAX_HUMANS, rand, sicks);

}


map<string,vector<Position*>> World::vision(int length, int row, int column){

    map<string, vector<Position*>> neighborhood;
    neighborhood["empty"];
    neighborhood["human"];
    
    for(int elt_1 = 0-length; elt_1<length+1;elt_1++){
        for(int elt_2 = 0-length; elt_2<length+1;elt_2++){

            Position * test = new Position(elt_1,elt_2);
            bool isInNeighborhood = false;

            for(Position * temp: neighborhood.at("empty") ){
                if(*temp == *test){
                    isInNeighborhood = true;
                }
            }
            for(Position * temp: neighborhood.at("human") ){

                if(*temp == *test){
                    isInNeighborhood = true;
                }
            }

            delete test;
            // Tous ça pour ça : and (elt_1, elt_2) not in neighborhood
            if((elt_1 != 0 || elt_2 !=0) && !isInNeighborhood ){
                Position * pos = new Position(row+elt_1,column+elt_2);
                
                if(this->isHuman(pos->getPosX(),pos->getPosY())){
                    neighborhood["human"].push_back(pos);
                }
                if(this->isEmpty(pos->getPosX(),pos->getPosY())){
                    neighborhood["empty"].push_back(pos);
                }
				//delete pos;
            }
            

        }
    }
    return neighborhood;
}

void World::contamination(int row, int column, RandMT * rand, int currentRow, int currentColumn){

	float histogrammeContamination[11] = {0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.7, 0.6, 0.4, 0.2};

    map<string, vector<Position*>> target_v1 = this->vision(2,row,column);
    for(Position * pos : target_v1["human"]){
    
        if(!this->carte[pos->getPosX()][pos->getPosY()]->isSick()){
        
        	float randomValue = rand->genrand_real1();

			int distanceRow = abs(row - pos->getPosX());
			int distanceColumn = abs(column - pos->getPosY());
			int distance;
			
			if(distanceRow > distanceColumn){
				distance = distanceRow;
			}else{
				distance = distanceColumn;
			}

			if(distance == 1){
			
				if(randomValue < histogrammeContamination[this->carte[currentRow][currentColumn]->getState()-1] * (1 - (float)this->carte[pos->getPosX()][pos->getPosY()]->getResistanceVirus())){        
					this->carte[pos->getPosX()][pos->getPosY()]->contamine();
					// Hmmmmm, les nouveaux cas, on peut peut etre les considérer que si ils sont symptomatiques ?
					this->nbNouveauxCas++;
			    	//self.writeLog(f"Human ({position[0]}, {position[1]} is contamined\n")
				
			    	this->updateStats("contamined", rand);
				}
			
			}else if(distance == 2){
				if(randomValue < (histogrammeContamination[this->carte[currentRow][currentColumn]->getState()] * (this->carte[pos->getPosX()][pos->getPosY()]->getResistanceVirus()))/2){  // On divise par deux la chance de contamination car 2 cases de distance.      
					this->carte[pos->getPosX()][pos->getPosY()]->contamine();
					// Hmmmmm, les nouveaux cas, on peut peut etre les considérer que si ils sont symptomatiques ?
					this->nbNouveauxCas++;
			    	//self.writeLog(f"Human ({position[0]}, {position[1]} is contamined\n")
				
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

Position * World::moveHuman(int row, int column, RandMT * rand){

    
    // Chaque state est un jour
    if(this->carte[row][column]->getState() > 11 && !this->carte[row][column]->getIsReanimation()){
    
    	if(this->carte[row][column]->getIsHospital()){
    		this->nbPersonneHospital--;
    	}
    	
    	this->carte[row][column]->resetState();
    	this->updateStats("recovered",rand);
    	
    	
    	
    }
    
    if(this->carte[row][column]->getIsReanimation()){
    
    	/*
    	Selon les données de l'AP-HP, la durée moyenne de séjour des patients Covid-19 en réanimation est passée de 19 jours avant le 1er juillet à 9,5 jours après le 1er juillet, a indiqué à APMnews Frédéric Adnet, chef de service du Samu de Seine-Saint-Denis et chef des urgences de l'hôpital Avicenne à Bobigny. Entre les 2 périodes, l'âge médian est passé de 61 ans à 64 ans.
    	
    	Dans le service de réanimation du Pr Demoule, "la durée de séjour en réanimation est de 5 jours pour les patients non intubés. S'ils sont intubés ils restent quand même 3 semaines (même si on manque encore de recul par rapport à la 2e vague)".
    	
    	https://www.apmnews.com/depeche/1/355843/covid-19-en-reanimation-une-prise-en-charge-amelioree%2C-des-patients-un-peu-moins-severes
    	*/
    	double dureeReanimation = (rand->genrand_int32()%16) + 5; // Entre 5 jours et 21 jours de réanimation.
    	
    	if(this->carte[row][column]->getState() > dureeReanimation){
    		this->nbPersonneReanimation--;
    		this->carte[row][column]->resetState();
    		this->updateStats("recovered",rand);
    	}	
    }

    if(this->carte[row][column]->getResistanceVirus() > 0 ){
    	this->carte[row][column]->decreaseResistance();
    }
    

    
    if(this->carte[row][column]->isSick()){
    	
        this->carte[row][column]->incrementState();
        if(this->carte[row][column]->getState() == 3){
        	// Proportion de asymptomatique varie de 15 à 30% selon les études. Param ?
        	// https://www.inspq.qc.ca/sites/default/files/covid/2989-asymptomatiques-potentiel-transmission-covid19.pdf
        	float pourcentAsymptomatique = (( rand->genrand_int32() % 15) + 15.0)/100;
    		float randValue = rand->genrand_real1();
	    	if(randValue < 1 - pourcentAsymptomatique){
	    		// entre 15% et 30% de chance qu'il soit asymptomatique et qu'il continue de se déplacer
	    		this->nbCasCovidConnuTotal++;
	    		this->ageOfSymptomaticDailyHuman.push_back(this->carte[row][column]->getAge());
	    		this->carte[row][column]->getConfined();
	    	}
        	
        	
        }
        
        if(this->carte[row][column]->getState() == 4){
			if(this->carte[row][column]->getIsConfined()){
				//Si la personne est symtomatique, alors elle a des chances d'aller a l'hopital
				float randValue = rand->genrand_real1();

				if(randValue < this->table_taux_hospitalisation_by_age_by_10[this->carte[row][column]->getAge()]/100){
					if(this->nbPersonneHospital < this->nbPlaceHospital){
						this->carte[row][column]->goToHospital();
						this->nbNouveauxHospitalisation++;
						this->nbPersonneHospital++;
					}else{
						// Si il n'y a plus de place a l'hopital et qu'on a besoin d'etre hospitalisé, 20% de chance de mourir
						if(randValue < 0.2){
							this->ageOfDeadHumansDaily.push_back(this->carte[row][column]->getAge());
							this->updateStats("dead",rand);
							this->humanGoFromTo(row,column, 0,0,rand,  true);
							
							this->nbMorts++;
						    ////delete newPosition;
						    return nullptr;
						}
					}
					
				}
        	}
        	
        }
        if(this->carte[row][column]->getState() == 5){
			if(this->carte[row][column]->getIsHospital()){
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
						if(this->carte[row][column]->getIsHospital()){
							this->nbPersonneHospital--;
						}
						this->carte[row][column]->goToReanimation();
						this->nbNouveauxReanimation++;
						this->nbPersonneReanimation++;
					}else{
						// Si la personne doit aller en réanimation mais qu'il n'y a plus de place, elle meurt.
						if(this->carte[row][column]->getIsHospital()){
							this->nbPersonneHospital--;
						}
						this->ageOfDeadHumansDaily.push_back(this->carte[row][column]->getAge());
						this->updateStats("dead",rand);
						this->humanGoFromTo(row,column, 0,0,rand,  true);
						this->nbMorts++;
						
						////delete newPosition;
						return nullptr;
					}
					
				}
        	}
        	
        }
        
        if(this->carte[row][column]->getState() == 6){
			if(this->carte[row][column]->getIsReanimation()){
				float randValue = rand->genrand_real1();
				// 50% de chances de mourir si on était en réa.
				// L'objectif serait de retrouver 14%, 8%, etc. Mais au niveau des probas c'est sur que ça ne va pas le faire :
				// Pour retrouver 14 % : sur 100% de contaminé -> 60% d'aller a l'hopital -> 15% d'aller en réa -> 50% de mourir.
				// En partant de contaminé, la chance de mourir : 0.6 * 0.15 * 0.5 = 0.045. Très très loin de 0.14.
				// Meme en prenant 100% de anciens a l'hopital, 0.15% *0.5 = 0.075. Il faudrait que les anciens aient quasi 100% de chances de mourir en réa
				
				if(randValue < this->tauxMortRea){
					/*
					this->carte[row][column] = nullptr;
					//self.writeLog(f"Human ({fromRow},{fromColumn}) go to ({toRow},{toColumn} and die)\n")
					
					*/
					if(this->carte[row][column]->getIsHospital()){
						this->nbPersonneHospital--;
					}
					if(this->carte[row][column]->getIsReanimation()){
						this->nbPersonneReanimation--;
					}
					this->ageOfDeadHumansDaily.push_back(this->carte[row][column]->getAge());
					this->updateStats("dead",rand);
					this->updateStats("dead",rand);
					this->humanGoFromTo(row,column, 0,0,rand,  true);
					this->nbMorts++;
					
					////delete newPosition;
					return nullptr;
				}
        	}
        	
        }

		/*
		L'individu ne contamine que si il se déplace. 
		Il y a 2 tour ou tous le monde est forcément asymptomatique (2jours de contamination potentielle)
		Ensuite, si on est malade, on se confine, si on est a l'hopital, on est confiné, et si on est en réanimation ou mort, on est confiné aussi.
		Si on est malade, on ne se déplace pas.
		De plus, on est contagieux que pendant 9 jours. (2 jours avant symptomes + 9 jours après)
		*/
        if(!this->carte[row][column]->getIsConfined() && !this->carte[row][column]->getIsHospital() && !this->carte[row][column]->getIsReanimation() && this->carte[row][column]->getState() < 13){
        
        	int rowDeplacement = rand->genrand_int32()%this->size; // Il peut se déplacer de 0 à size
        	int columnDeplacement = rand->genrand_int32()%this->size; // Il peut se déplacer de 0 à size
        	map<string, vector<Position*>> target_v1 = this->vision(1,rowDeplacement,columnDeplacement);
		    if(target_v1["empty"].size() != 0){
		  
		    	int taille = target_v1.at("empty").size();
		    	int randomValue = ((long)floor(rand->genrand_int32()))%taille;

		        Position * newPosition = target_v1.at("empty").at(randomValue);
		        this->contamination(newPosition->getPosX(),newPosition->getPosY(), rand, row, column);

		        
		        this->humanGoFromTo(row,column, newPosition->getPosX(),newPosition->getPosY(),rand);
		        return newPosition;
		        
		    }else{
		    	this->contamination(row,column, rand, row, column);
		        //self.writeLog (f"Human ({row}, {column}) stay at the same position\n")
		        return new Position(row,column);
		    }
        
		}else{
			return new Position(row,column);
		}
        
    }else{
    	//Si il n'est pas malade
    	int rowDeplacement = rand->genrand_int32()%this->size; // Il peut se déplacer de 0 à size
        int columnDeplacement = rand->genrand_int32()%this->size; // Il peut se déplacer de 0 à size
        map<string, vector<Position*>> target_v1 = this->vision(1,rowDeplacement,columnDeplacement);
        if(target_v1["empty"].size() != 0){
            // Demander a Bruno bachelet si dans un cas comme ça, pour le return, on privilégie pointeur ou valeur.
            int taille = target_v1.at("empty").size();
            int randomValue = ((long)floor(rand->genrand_int32()))%taille;
            Position * newPosition = target_v1.at("empty").at(randomValue);
            this->humanGoFromTo(row,column, newPosition->getPosX(),newPosition->getPosY(),rand);
            return newPosition;
        }else{
            //self.writeLog (f"Human ({row}, {column}) stay at the same position\n")
            return new Position(row, column);
        }

    }

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
	//this->writeLog("XX");
	for (int age: this->ageOfSymptomaticDailyHuman) {
        this->writeLog("AgeC:" + to_string(age));
    }
	for (int age: this->ageOfDeadHumansDaily) {
        this->writeLog("AgeD:" + to_string(age));
    }
	//this->writeLog("XX");
	
	this->writeLog("##########");
	this->ageOfSymptomaticDailyHuman.clear();
	this->ageOfDeadHumansDaily.clear();
	this->nbNouveauxCas = 0;
    this->nbNouveauxHospitalisation = 0;
    this->nbNouveauxReanimation = 0;
    this->nbMorts = 0;
    this->iteration += 1;
    vector<Position*> newHumansPosition;
    //self.writeLog (f'\n\n**** Iteration #{self._iteration} ****\n')
    for(Position * temp: this->humansPosition){

        Position * newPosition = this->moveHuman(temp->getPosX(),temp->getPosY(), rand);

        if(newPosition != nullptr){
            //self.writeLog(f' [DEBUG] -  Adding {newPosition}\n')
            newHumansPosition.push_back(newPosition);
            //delete newPosition;
        }
    }
    this->humansPosition = newHumansPosition;
}

void World::startSimulation(int maxIterations, RandMT * rand){
    for(int iteration = 0;iteration<maxIterations;iteration++){
    	//this->displayStats();
        this->display();
        
        World::pause();
        this->nextIteration(rand);
        if(this->humansPosition.size() == 0){
        	cout << "no more humans in the simulation" << endl;
            //self.writeLog('[STOP] No more human in the simulation !\n')
            break;
        }
    }
    
    
    //self.writeLog(f' [STOP] Maximum number of iterations reached ({maxIterations}) end of the simulation!\n')
    //cout << "\033[2J" << endl;
    this->displayStats();
    
}


