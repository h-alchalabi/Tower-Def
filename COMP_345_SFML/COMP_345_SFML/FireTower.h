#pragma once
#include "DecoratedTower.h"
class FireTower : public DecoratedTower{
public:
	FireTower(Tower* decoratedTower);
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