#include "FastCritter.h"

FastCritter::FastCritter(int level) : NormalCritter(level) {
	//this->level = level;
	this->HP = 3*level;
	this->reward = 1 * level;
	this->speed = 3;
}

FastCritter::~FastCritter(){

}

/*int FastCritter::getHP(){
	return HP;
}
void FastCritter::setHP(int HP){
	this->HP = HP;
}

int FastCritter::getReward(){
	return reward;
}

void FastCritter::setReward(int reward){
	this->reward = reward;
}

int FastCritter::getSpeed(){
	return speed;
}

void FastCritter::setSpeed(int speed) {
	this->speed = speed;
}

void FastCritter::setCritterStatus(CritterStatus critterStatus, float statusDuration) {
	critterClock.restart();
	statusTime = statusDuration;
	this->critterStatus = critterStatus;

}

CritterStatus FastCritter::getCritterStatus() {
	return critterStatus;
}*/