/*******************************************************************************************************************/
//
/*******************************************************************************************************************/

#include "Critter.h"
#include "GameConstants.h"
#include <string>
#include <vector>
using namespace std;

Critter::Critter(string imageName) : Entity(imageName){}

Critter::Critter() : Entity(GameConstants::CRITTER_IMAGE_NAME) {
	this->step = 0;
}

void Critter::move() {
	++step;
}

int Critter::getStep() {
	return step;
}

void Critter::tick(sf::Time pausedTime) {
	long elapsedTime = critterClock.getElapsedTime().asMilliseconds() - pausedTime.asMilliseconds();
	if (elapsedTime >= statusTime) {
		critterStatus = CritterStatus::NORMAL;
	} else if (critterStatus != CritterStatus::NORMAL && elapsedTime % 500 == 0) {
		//Critter is burned
		setHP(HP - 5);
	}
}