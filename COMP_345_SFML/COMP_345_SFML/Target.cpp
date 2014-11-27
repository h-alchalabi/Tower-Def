#include "Target.h"

/*******************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//COMP345 - assignment 3
//November 20, 2014
//
//This is the target class that will be used by a tower to use one of the strategy objects.
//
/*******************************************************************************************************************/

Target::Target() {}

Target::Target(Strategy *initStrategy) {
	this->strategy = initStrategy;
}

void Target::setStrategy(Strategy *newStrategy) {
	this->strategy = newStrategy;
}

int Target::executeStrategy(vector<Critter*> critters, int towerX, int towerY, int towerRange) {
	return this->strategy->execute(critters, towerX, towerY, towerRange);
}
