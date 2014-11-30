/*******************************************************************************************************************/
//Strongest critter targetting strategy (strategy patern)
/*******************************************************************************************************************/

#pragma once
#include "Strategy.h"

class StrongestCritterStrategy : public Strategy {
public:
	int execute(vector<Critter*> critters, int towerX, int towerY, int towerRange);
};