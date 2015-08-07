#include "Bicycle.h"

//Order of methods is not important

Bicycle::Bicycle(){
	speed = 10;
}

Bicycle::Bicycle(int startSpeed){
	speed = startSpeed;
}

Bicycle::~Bicycle(){
}

int Bicycle::getSpeed(){
	return speed;
}

void Bicycle::applyBrake(int decrement){
	speed -= decrement;
}

void Bicycle::speedUp(int increment){
	speed += increment;
}