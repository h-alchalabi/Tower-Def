#include "StrongestCritterStrategy.h"
#include <limits>

int StrongestCritterStrategy::execute(vector<Critter*> critters, int towerX, int towerY, int towerRange) {
	int biggestHealth = 0;          //The biggest health that will determine the strongest critter
	int strongestCritterIndex = -1;  //The index of the strongest critter

	//Determining the strongest critter in the tower's range
	for (int i = 0; i < critters.size(); i++) {
		int critterX = critters[i]->getSprite().getPosition().x + critters[i]->getSprite().getLocalBounds().width / 2;
		int critterY = critters[i]->getSprite().getPosition().y + critters[i]->getSprite().getLocalBounds().height / 2;

		float distanceFromTower = sqrt((pow(critterX - towerX, 2) + pow(critterY - towerY, 2)));
		if (distanceFromTower <= towerRange) {
			//The critter is in the tower's range
			if (biggestHealth < critters[i]->getHP()) {
				//Updating the strongest critter in the tower's range
				biggestHealth = critters[i]->getHP();
				strongestCritterIndex = i;
			}
		}
	}

	return strongestCritterIndex;
}