#pragma once
#include <string>
using namespace std;

class Position{

    private:
        int posX;
        int posY;

    public:

        // I don't know what i'm doing with friend, mais il faut definir operator == en dehors de la classe.
	friend bool operator==(Position const& a, Position const& b)
	{
	    //Redefinition du equals pour les positions
	    if (a.posX == b.posX && a.posY == b.posY)
		return true;
	    else
		return false;
	}
        int getPosX();
        int getPosY();
        void setPosX(int);
        void setPosY(int);
        Position(int posX = 0, int posY = 0);
};
