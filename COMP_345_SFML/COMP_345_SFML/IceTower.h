#include "Tower.h"
#pragma once
class IceTower : public Tower {
public:
	IceTower();
	IceTower(int x, int y, int level, int damage, int range, int fireRate, int basePrice, int sellPrice, int upgradedPrice);
	void slowCritter();
};