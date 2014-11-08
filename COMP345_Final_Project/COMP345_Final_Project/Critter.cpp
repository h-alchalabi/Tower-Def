#include "Critter.h"
#include <fstream>

Critter::Critter(){

}

// this constructor mofifies the critter depending on Wave
Critter::Critter(int waveNumber, CritterType type, string critterMapPath){

	hitPoints = 5 * waveNumber;
	speed = speed*waveNumber;
	level = 1;
	reward = 1 * level;
	positionX = 0;
	positionY = 0;
	deploymentTime = 3.0f;
	mapPath = critterMapPath;
	steps = 0;
}


Critter::~Critter()
{
	
}

float Critter::getDeploymentTime(){
	return deploymentTime;
}
int Critter::getLevel(){
	return level;
}
void Critter::setLevel(int level){
	this->level = level;
}

int Critter::getHitPoints(){
	return hitPoints;
}

void Critter::setHitPoints(int hitPoints){
	this->hitPoints = hitPoints;
}

int Critter::getSpeed(){
	return speed;
}

void Critter::setSpeed(int speed){
	this->speed = speed;
}

int Critter::getReward(){
	return reward;
}

void Critter::setReward(int reward){
	this->reward = reward;
}

int Critter::getPositionX(){
	return positionX;
}

int Critter::getPositionY(){
	return positionY;
}

void Critter::setPositionX(int positionX){
	this->positionX = positionX;
}

void Critter::setPositionY(int positionY){
	this->positionY = positionY;
}

int Critter::getSteps(){
	return steps;
}

void Critter::setSteps(int steps){
	this->steps = steps;
}

void Critter::move(vector<int> coordinates){
	if (steps + 1 > coordinates.size()){//this if is to make sure that the critter does not attempt to go out of bounds.
		return;
	}
	else{//if it isn't out of bounds, it aquires the next step.
		positionX = coordinates.at(steps);
		positionY = coordinates.at(++steps);
		++steps;
	}

}

int* Critter::previousPos(vector <int> coordinates){//Getting the previous position of the critter to revert
	int* previousPos = new int[2];//the reason it is 4 and 3 rather than 2 and 1, is because the increment occurs before the next step.
	previousPos[0] = coordinates.at(steps - 4);//i.e., when a critter moves initially the step has become 2 after it moved twice is the first time it can revert
	previousPos[1] = coordinates.at(steps - 3);//therefore we find the inital position.
	return previousPos;
}





void Critter::handleCollision(Entity& e){
	// check if missle has hit (via hitboxes)
	// if yes, handle the collision by dealing damage and destroying missle.
	// missle should be destroyed via the Missle Controller.
}

