#include "SlowCritter.h"
SlowCritter::SlowCritter(int level){
	this->level = level;
	this->HP = 7 * level;
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

int SlowCritter::getReward(){
	return reward;
}

void SlowCritter::setReward(int reward){
	this->reward = reward;
}
int SlowCritter::getSpeed(){
	return speed;
}