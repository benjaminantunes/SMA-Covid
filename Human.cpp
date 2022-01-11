
#include "Human.hpp"
#include <ostream>
#include <iostream>

using namespace std;
Human::Human(SimulationParams * simulationParams, RandMT* rand, int row, int column){
	this->pos = Position(row,column);
	this->symbol = Human::SYMBOL;
	float randAge = rand->genrand_real1();
	this->resistanceInfectionValuesByAge = simulationParams->getResistanceInfectionValuesByAge();
	this->maxResistanceInjectionValuesByAge = simulationParams->getMaxResistanceInjectionValuesByAge();
	this->minResistanceInjectionValuesByAge = simulationParams->getMinResistanceInjectionValuesByAge();
	// https://www.insee.fr/fr/statistiques/2381474#figure1_radio2
	// 8 Tranches : 0 - 15, 15 - 25 , 25 - 35 , 35 - 45 , 45 - 55, 55 - 65, 65 - 75, 75 +
	if(randAge < 0.177){
		this->age = 0; // 0%
	}else if(randAge >= 0.177 && randAge < 0.296){
		this->age = 1; // 0.2%
	}else if(randAge >= 0.296 && randAge < 0.411){
		this->age = 2; // 0.2%
	}else if(randAge >= 0.411 && randAge < 0.535){
		this->age = 3; //0.4%
	}else if(randAge >= 0.535 && randAge < 0.667){
		this->age = 4; //1.3%
	}else if(randAge >= 0.667 && randAge < 0.793){
		this->age = 5; //3.6%
	}else if(randAge >= 0.793 && randAge < 0.905){
		this->age = 6; //8%
	}else if(randAge >= 0.905){
		this->age = 7; // 14.8%
	}
	
	
	
	float randSexe = rand->genrand_real1();
	// 50/50 homme et femme
	if(randSexe < 0.5){
		this->sexe = 0;
	}
}

void Human::contamine(){
	this->state = 1;
	this->resistanceVirus = this->resistanceInfectionValuesByAge[this->age];
	this->daysSinceLastInfectionOrInjection = 0;
}

void Human::vaccine(RandMT* rand){
	double randomValue = this->minResistanceInjectionValuesByAge[this->age]
						 + (
							this->maxResistanceInjectionValuesByAge[this->age]
							-
							this->minResistanceInjectionValuesByAge[this->age]
						   )
						 * rand->genrand_real1();
	
	if(this->resistanceVirus < randomValue){
		this->resistanceVirus = randomValue;
		this->daysSinceLastInfectionOrInjection = 0;
	}
	
}

bool Human::isSick(){
	return this->state != 0;
}

int Human::getState(){
	return this->state;
}

void Human::incrementState(){
	this->state += 1;
}

char Human::to_string(){
	
	if(this->isConfined){
		return Human::SYMBOL_SICK_CONFINED;
	}
	if(this->isHospital){
		return Human::SYMBOL_SICK_HOSPITAL;
	}
	if(this->isReanimation){
		return Human::SYMBOL_SICK_REANIMATION;
	}
	if (this->isSick()){
		return Human::SYMBOL_SICK;
	}else{
		return this->symbol;
	}
}

int Human::getPositionRow(){
	return this->pos.getPosX();
};

int Human::getPositionColumn(){
	return this->pos.getPosY();
};

void Human::setPosition(int posX,int posY){
	this->pos.setPosX(posX);
	this->pos.setPosY(posY);
};


Position  Human::getPosition(){
	return this->pos;
}

void Human::resetState(){
	this->state = 0;
	this->isConfined = false;
	this->isHospital = false;
	this->isReanimation = false;
}
void Human::getConfined(){
	this->isConfined = true;
	this->isHospital = false;
	this->isReanimation = false;
}

void Human::goToHospital(){
	this->isConfined = false;
	this->isHospital = true;
	this->isReanimation = false;
}
void Human::goToReanimation(RandMT * rand){
	this->isConfined = false;
	this->isHospital = false;
	this->isReanimation = true;
	this->dureeReanimation = (rand->genrand_int32()%26) + 10; // Entre 10 et 25 jours de rea, sachant qu'on a deja 5 jours de maladie (State)
	// Ca fait donc entre 5 et 20 jours de rea.
}

bool Human::getIsConfined(){
	return this->isConfined;
}
bool Human::getIsHospital(){
	return this->isHospital;
}
bool Human::getIsReanimation(){
	return this->isReanimation;
}
int Human::getAge(){
	return this->age;
}

float Human::getResistanceVirus(){
	return this->resistanceVirus;
}

int Human::getDureeReanimation(){
	return this->dureeReanimation;
}


void Human::decreaseResistance(){
	if(this->daysSinceLastInfectionOrInjection < 90){
		return;
	}else if(this->daysSinceLastInfectionOrInjection >= 90 && this->resistanceVirus > 0){
		this->resistanceVirus = this->resistanceVirus - 0.001;
	}
	
}



