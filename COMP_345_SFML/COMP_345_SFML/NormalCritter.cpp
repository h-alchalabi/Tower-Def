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