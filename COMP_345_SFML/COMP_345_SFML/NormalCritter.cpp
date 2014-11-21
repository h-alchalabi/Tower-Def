#include "NormalCritter.h"

NormalCritter::NormalCritter(int level){
	this->level = level;
	this->HP = 5*level;
	this->speed = 2;
	this->reward = 1*level;

}

NormalCritter::~NormalCritter(){

}

int NormalCritter::getHP(){
	return HP;
}
void NormalCritter::setHP(int HP){
	this->HP = HP;
}

int NormalCritter::getReward(){
	return reward;
}

void NormalCritter::setReward(int reward){
	this->reward = reward;
}

int NormalCritter::getSpeed(){
	return speed;
}

void NormalCritter::setSpeed(int speed) {
	this->speed = speed;
}

CritterStatus NormalCritter::getCritterStatus() {
	return critterStatus;
}

void NormalCritter::setCritterStatus(CritterStatus critterStatus, float statusDuration) {
	critterClock.restart();
	statusTime = statusDuration;
	this->critterStatus = critterStatus;

}