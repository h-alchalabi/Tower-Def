#include "Critter.h"
#include "GameConstants.h"
#include <string>
#include <vector>

using namespace std;

Critter::Critter() : Entity(GameConstants::CRITTER_IMAGE_NAME){
	this->step = 0;
}

Critter::Critter(string imageName): Entity(imageName){}

void Critter::move() {
	++step;
}
int Critter::getStep(){
	return step;
}

void Critter::tick(sf::Time pausedTime) {
	long elapsedTime = critterClock.getElapsedTime().asMilliseconds() - pausedTime.asMilliseconds();
	if (elapsedTime >= statusTime) {
		critterStatus = CritterStatus::NORMAL;
	}
	else if (critterStatus != CritterStatus::NORMAL && elapsedTime % 500 == 0){
		switch (critterStatus) {
			case CritterStatus::BURN:
				setHP(HP - 5);
				break;
			case CritterStatus::FREEZE:
				setSpeed(speed - 1);
				break;
		}
	}
}