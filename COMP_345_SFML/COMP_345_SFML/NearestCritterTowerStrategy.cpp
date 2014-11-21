#include "NearestCritterTowerStrategy.h"
#include <limits>

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
	for (int i = 0; i < critters.size(); i++) {
		if (critters[i]->getPosition() >= tower->getRangeLeft() && critters[i]->getPosition() <= tower->getRangeRight()) {
			//The critter is in the tower's range

			//Calculating distance between a critter and the tower
			int distCritterTower;
			distCritterTower = critters[i]->getPosition() > tower->getPosition() ?
				critters[i]->getPosition() - tower->getPosition() :
				tower->getPosition() - critters[i]->getPosition();

			if (closestDistTower > distCritterTower) {
				//Updating the closest critter to the tower in the tower's range
				closestDistTower = distCritterTower;
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