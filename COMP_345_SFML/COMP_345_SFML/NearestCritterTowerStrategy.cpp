#include "NearestCritterTowerStrategy.h"
#include <limits>
#include <math.h>

/*******************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//COMP345 - assignment 3
//November 20, 2014
//
//This is the "nearest critter to a tower" strategy object.
//
/*******************************************************************************************************************/

void NearestCritterTowerStrategy::execute(vector<Critter*> critters, Tower* tower) {
	int closestDistTower = numeric_limits<int>::max();  //The closest distance to the tower
	int closestCritterTowerIndex = 0;                   //The index of the critter that is the closest to the tower

	//Determining the closest critter to the tower in the tower's range
	int towerX = tower->getSprite().getPosition().x + tower->getSprite().getLocalBounds().width / 2;
	int towerY = tower->getSprite().getPosition().y + tower->getSprite().getLocalBounds().height / 2;
	for (int i = 0; i < critters.size(); i++) {
		int critterX = critters[i]->getSprite().getPosition().x + critters[i]->getSprite().getLocalBounds().width / 2;
		int critterY = critters[i]->getSprite().getPosition().y + critters[i]->getSprite().getLocalBounds().height / 2;

		float distanceFromTower = sqrt((pow(critterX - towerX, 2) + (critterY - towerY, 2)));
		if (distanceFromTower <= tower->getRange()) {

			if (closestDistTower > distanceFromTower) {
				//Updating the closest critter to the tower in the tower's range
				closestDistTower = distanceFromTower;
				closestCritterTowerIndex = i;
			}
		}

	}

	//Displaying which critter that tower has targeted
	if (closestDistTower == numeric_limits<int>::max())
		cout << "no critter\n";
	else
		cout << "critter #" << (closestCritterTowerIndex + 1) << "\n";
}