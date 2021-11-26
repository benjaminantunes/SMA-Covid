
#include "Human.hpp"
#include <ostream>
#include <iostream>

using namespace std;
Human::Human(RandMT* rand){
	this->pos = new Position();
    this->symbol = Human::SYMBOL;
    float randAge = rand->genrand_real1();
    // En proportion, la population française est assez équitablement réparti
    // On considère ici : 10% moins de 10 ans, 30 % entre 10 et 20 ans, 10% entre 20 et 30 ans , ..... 15% >= 80 ans
    // pour l'instant je reste la dessus, mais je vais prendre des vrais chiffres.
    // 0 = [0;10] 1 = 10;20  2 = 20;30  3 = 30;40  4 = 40;50  5 = 50;60  6 = 60;70  7 = 70;80  8 = 80 ++ 
    if(randAge < 0.1){
    	this->age = 0; // 0%
    }else if(randAge >= 0.1 && randAge < 0.2){
    	this->age = 1; // 0.2%
    }else if(randAge >= 0.2 && randAge < 0.3){
    	this->age = 2; // 0.2%
    }else if(randAge >= 0.3 && randAge < 0.4){
    	this->age = 3; //0.2%
    }else if(randAge >= 0.4 && randAge < 0.5){
    	this->age = 4; //0.4%
    }else if(randAge >= 0.5 && randAge < 0.6){
    	this->age = 5; //1.3%
    }else if(randAge >= 0.6 && randAge < 0.7){
    	this->age = 6; //3.6%
    }else if(randAge >= 0.7 && randAge < 0.8){
    	this->age = 7; // 8%
    }else if(randAge >= 0.8 && randAge < 0.85){
    	this->age = 8; // 14.8%
    }else if(randAge >= 0.85){
    	this->age = 1; // Pour avoir 25% dans la tranche 10 à 20 ans, donc un total de 35% de 20 ans et moins.
    }
    
    
    
    float randSexe = rand->genrand_real1();
    // 50/50 homme et femme
    if(randSexe < 0.5){
    	this->sexe = 0;
    }
}

void Human::contamine(){
    this->state = 1;
    this->resistanceVirus = 180; //6mois, 180 jours/itérations
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
    return this->pos->getPosX();
};

int Human::getPositionColumn(){
    return this->pos->getPosY();
};

void Human::setPosition(int posX,int posY){
    this->pos->setPosX(posX);
    this->pos->setPosY(posY);
};


Position * Human::getPosition(){
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
void Human::goToReanimation(){
	this->isConfined = false;
	this->isHospital = false;
	this->isReanimation = true;
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

int Human::getResistanceVirus(){
	return this->resistanceVirus;
}

int Human::getVaccin(){
	return this->vaccin;
}
/*
void Human::setResistanceVirus(int res){
	this->resistanceVirus = res;
}
*/
void Human::decreaseResistance(){
	this->resistanceVirus = this->resistanceVirus - 1;
}
void Human::decreaseVaccin(){
	this->vaccin = this->vaccin - 1;
}
void Human::setVaccin(int res){
	this->vaccin = res;
}

