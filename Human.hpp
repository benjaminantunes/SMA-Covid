#pragma once
#include <string>
#include "Position.hpp"
#include "RandMT.hpp"

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
        Position * pos;
        bool isConfined = false;
        bool isHospital = false;
        bool isReanimation = false;
        int resistanceVirus = 0;
        //float resistanceInfectionValuesByAge[8] = {0.999,0.999,0.999,0.999,0.99,0.90, 0.80 ,0.70};
		float resistanceInfectionValuesByAge[8];
		//float maxResistanceInjectionValuesByAge[8] = {0.8,0.8,0.8,0.7,0.6,0.6,0.5,0.4};
		float maxResistanceInjectionValuesByAge[8];
		//float minResistanceInjectionValuesByAge[8] = {0.5,0.5,0.5,0.5,0.4,0.4,0.4,0.3};
		float minResistanceInjectionValuesByAge[8];
		int dureeReanimation = 0;
        int daysSinceLastInfectionOrInjection = 0;


    public:
        Human(RandMT*);
        void contamine();
        void vaccine(RandMT*);
        bool isSick();
        int getState();
        int getAge();
        int getResistanceVirus();
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
        Position * getPosition();

};
