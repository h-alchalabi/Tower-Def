#include "Strategy.h"

/*******************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//COMP345 - assignment 3
//November 20, 2014
//
//This is the "nearest critter to a tower" strategy object.
//
/*******************************************************************************************************************/

class NearestCritterTowerStrategy : public Strategy {
public:
	void execute(vector<Critter*> critters, Tower* tower);
};

