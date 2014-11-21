#include "FastCritter.h"

FastCritter::FastCritter(int level) {
	this->level = level;
	this->HP = 3*level;
	this->reward = 1 * level;
	this->speed = 3;

}

FastCritter::~FastCritter(){

}

int FastCritter::getHP(){
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