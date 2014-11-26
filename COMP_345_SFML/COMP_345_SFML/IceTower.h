#pragma once
#include "DecoratedTower.h"
class IceTower : public DecoratedTower{
public:
	IceTower(Tower* decoratedTower);
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
private:
	int burnDamage;
};