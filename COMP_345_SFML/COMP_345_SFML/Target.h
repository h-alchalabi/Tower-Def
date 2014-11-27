#include "Strategy.h"

/*******************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//COMP345 - assignment 3
//November 20, 2014
//
//This is the target class that will be used by a tower to use one of the strategy objects.
//
/*******************************************************************************************************************/

#pragma once
class Target {
public:
	Target();
	Target(Strategy *initStrategy);
	Strategy* getStrategy();
	void setStrategy(Strategy *newStrategy);
	int executeStrategy(vector<Critter*> critters, int towerX, int towerY, int towerRange);
private:
	Strategy* strategy;
};