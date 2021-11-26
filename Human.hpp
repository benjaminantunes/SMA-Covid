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
        int vaccin = 0;

    public:
        Human(RandMT*);
        void contamine();
        bool isSick();
        int getState();
        int getAge();
        int getResistanceVirus();
        int getVaccin();
        //void setResistanceVirus(int);
        void decreaseResistance();
        void decreaseVaccin();
        void setVaccin(int);
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
