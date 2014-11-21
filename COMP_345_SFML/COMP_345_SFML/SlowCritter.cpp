#include "SlowCritter.h"
SlowCritter::SlowCritter(int level) : NormalCritter(level){
	//this->level = level;
	this->HP = 7 * level;
	this->speed = 1;
	this->reward = 1 * level;
}

SlowCritter::~SlowCritter(){

}

/*int SlowCritter::getHP(){
	return HP;
}
void SlowCritter::setHP(int HP){
	this->HP = HP;
}

int SlowCritter::getReward(){
	return reward;
}

void SlowCritter::setReward(int reward){
	this->reward = reward;
}
int SlowCritter::getSpeed(){
	return speed;
}

void SlowCritter::setSpeed(int speed) {
	this->speed = speed;
}

void SlowCritter::setCritterStatus(CritterStatus critterStatus, float statusDuration) {
	critterClock.restart();
	statusTime = statusDuration;
	this->critterStatus = critterStatus;

}

CritterStatus SlowCritter::getCritterStatus() {
	return critterStatus;
}*/