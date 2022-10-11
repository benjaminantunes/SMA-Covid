#include "City.hpp"
#include <ostream>
#include <iostream>

City::City(int inTaille, int inNbHab, int inCoordX, int inCoordY)
{
   _coordX = inCoordX;
   _coordY = inCoordY;
   _taille = inTaille;
   _nbHab  = inNbHab;
}


int City::getCoordX()
{
   return _coordX;
}

int City::getCoordY()
{
   return _coordY;
}

int City::getTaille()
{
   return _taille;
}

int City::getNbHab()
{
   return _nbHab;
}

void City::toString()
{
    cout << "La ville a pour coord X : " << _coordX << " , coordY : " << _coordY << ", taille : " << _taille << " , nbHab : " << _nbHab << endl; 
}


