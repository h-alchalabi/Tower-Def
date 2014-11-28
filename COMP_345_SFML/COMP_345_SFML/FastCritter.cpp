#include "FastCritter.h"
#include "GameConstants.h"

FastCritter::~FastCritter() {}

FastCritter::FastCritter(int level) : Critter(GameConstants::FAST_CRITTER_IMAGE_NAME) {
	this->level = level;
	this->maxHP= this->HP = 30*level;
	this->reward = 5 * level;
	this->speed = 3;
}

int FastCritter::getHP() {
	return HP;
}

int FastCritter::getMaxHP() const {
	return this->maxHP;
}

void FastCritter::setHP(int HP) {
	this->HP = HP;
}

int FastCritter::getReward() {
	return reward;
}

void FastCritter::setReward(int reward) {
	this->reward = reward;
}

int FastCritter::getSpeed() {
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
}