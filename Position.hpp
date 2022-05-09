#pragma once
#include <string>
using namespace std;

class Position
{

   private:
      int _posX;
      int _posY;

   public:

      // I don't know what i'm doing with friend, mais il faut definir operator == en dehors de la classe.
      friend bool operator==(Position const& inA, Position const& inB)
      {
         //Redefinition du equals pour les positions
         if (inA._posX == inB._posX && inA._posY == inB._posY)
            return true;
         else
            return false;
      }
      
      Position(int posX = 0, int posY = 0);
      
      int   getPosX();
      int   getPosY();
      void  setPosX(int);
      void  setPosY(int);
      
};
