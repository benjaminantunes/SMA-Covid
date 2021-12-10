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
        //int vaccin = 0;
        float resistanceValuesByAge[8] = {0.95,0.90,0.90,0.90,0.85,0.85, 0.80 ,0.80};
        int daysSinceLastInfectionOrInjection = 0;


    public:
        Human(RandMT*);
        void contamine();
        void vaccine();
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
        void goToReanimation();
        int getPositionRow();
        int getPositionColumn();
        void setPosition(int,int);
        bool getIsConfined();
        bool getIsHospital();
        bool getIsReanimation();
        Position * getPosition();

};
