#include "Critter.h"
#include "GameConstants.h"
#include <string>
#include <vector>

using namespace std;

Critter::Critter() : Entity(GameConstants::CRITTER_IMAGE_NAME){
	this->step = 0;
}

void Critter::move() {
	++step;
}
int Critter::getStep(){
	return step;
}

void Critter::tick() {
	if (critterClock.getElapsedTime().asMilliseconds() >= statusTime) {
		critterStatus = CritterStatus::NORMAL;
	}
}