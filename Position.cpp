#include "Position.hpp"

Position::Position(int posX, int posY){
	this->posX = posX;
	this->posY = posY;
}


int Position::getPosX(){
	return posX;
}

int Position::getPosY(){
	return posY;
}

void Position::setPosX(int posX){
	this->posX = posX;
}

void Position::setPosY(int posY){
	this->posY = posY;
}


