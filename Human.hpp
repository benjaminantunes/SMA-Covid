#pragma once
#include <string>
#include "Position.hpp"
#include "RandMT.hpp"
#include "SimulationParams.hpp"

class Human {

	private:
		int state = 0;
		char symbol;
		static const char SYMBOL = 'X';
		static const char SYMBOL_SICK = 'O';
		static const char SYMBOL_SICK_CONFINED = 'C';
		static const char SYMBOL_SICK_HOSPITAL = 'H';
		static const char SYMBOL_SICK_REANIMATION = 'R';
		
		int age;
		int sexe; //0 homme et 1 femme
		Position  pos;
		bool isConfined = false;
		bool isHospital = false;
		bool isReanimation = false;
		float resistanceVirus = 0;
		//float resistanceInfectionValuesByAge[8] = {0.999,0.999,0.999,0.999,0.99,0.90, 0.80 ,0.70};
		float * resistanceInfectionValuesByAge;
		//float maxResistanceInjectionValuesByAge[8] = {0.8,0.8,0.8,0.7,0.6,0.6,0.5,0.4};
		float * maxResistanceInjectionValuesByAge;
		//float minResistanceInjectionValuesByAge[8] = {0.5,0.5,0.5,0.5,0.4,0.4,0.4,0.3};
		float * minResistanceInjectionValuesByAge;
		int dureeReanimation = 0;
		int daysSinceLastInfectionOrInjection = 0;


	public:
		Human(SimulationParams* , RandMT*,int,int);
		void contamine();
		void vaccine(RandMT*);
		bool isSick();
		int getState();
		int getAge();
		float getResistanceVirus();
		void decreaseResistance();
		void resetState();
		void incrementState();
		char to_string();
		void getConfined();
		void goToHospital();
		void goToReanimation(RandMT*);
		int getPositionRow();
		int getPositionColumn();
		void setPosition(int,int);
		bool getIsConfined();
		bool getIsHospital();
		bool getIsReanimation();
		int getDureeReanimation();
		Position  getPosition();

};
