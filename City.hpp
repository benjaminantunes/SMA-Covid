#pragma once

using namespace std;

class City
{

   private:
      int _coordX;
      int _coordY;
      int _taille;
      int _nbHab;

   public:
      
      City(int taille = -1,int nbHab = -1,int coordX = -1,int coordY = -1);
      
      int  getCoordX();
      int  getCoordY();
      int  getTaille();
      int  getNbHab();
      void toString();
      
};
