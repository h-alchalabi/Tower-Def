/*******************************************************************************************************************/
//
/*******************************************************************************************************************/

#pragma once
#include "DecoratedTower.h"

class DeathTower : public DecoratedTower {
public:
	DeathTower(Tower* decoratedTower);
	int getX();
	int getY();
	int getLevel();
	int getDamage();
	int getRange(); // Radius
	int getFireRate();
	int getBasePrice();
	int getSellPrice();
	int getUpgradePrice();
	void shoot(Critter* targettedCritter);
};