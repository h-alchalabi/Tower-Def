#include "SlowCritter.h"
#include "GameConstants.h"
SlowCritter::SlowCritter(int level) : Critter(GameConstants::SLOW_CRITTER_IMAGE_NAME){
	//this->level = level;
	this->maxHP = this->HP = 70 * level;
	this->speed = 1;
	this->reward = 1 * level;
}

SlowCritter::~SlowCritter(){

}

int SlowCritter::getHP(){
	return HP;
}
void SlowCritter::setHP(int HP){
	this->HP = HP;
}

int SlowCritter::getMaxHP() const{
	return this->maxHP;
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
}