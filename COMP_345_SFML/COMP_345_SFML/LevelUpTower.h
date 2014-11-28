/*******************************************************************************************************************/
//
/*******************************************************************************************************************/

#pragma once
#include "DecoratedTower.h"

class LevelUpTower : public DecoratedTower {
public:
	LevelUpTower(Tower* decoratedTower);
	int getX();
	int getY();
	int getLevel();
	int getDamage();
	int getRange();
	int getFireRate();
	int getBasePrice();
	int getSellPrice();
	int getUpgradePrice();
};