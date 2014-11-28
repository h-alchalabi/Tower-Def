/*******************************************************************************************************************/
//
/*******************************************************************************************************************/

#include "Strategy.h"
#pragma once

class NearestCritterTowerStrategy : public Strategy {
public:
	int execute(vector<Critter*> critters, int towerX, int towerY, int towerRange);
};

