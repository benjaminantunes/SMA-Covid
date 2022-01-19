#include "Position.hpp"

Position::Position(int inPosX, int inPosY)
{
   _posX = inPosX;
   _posY = inPosY;
}


int Position::getPosX()
{
   return _posX;
}

int Position::getPosY()
{
   return _posY;
}

void Position::setPosX(int inPosX)
{
   _posX = inPosX;
}

void Position::setPosY(int inPosY)
{
   _posY = inPosY;
}


