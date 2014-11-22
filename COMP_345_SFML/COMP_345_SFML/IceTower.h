#include "Tower.h"
#pragma once
class IceTower : public Tower {
public:
	IceTower();
	IceTower(int damage, int range, int fireRate, int basePrice, int sellPrice, int upgradedPrice);
	void shoot(NormalCritter targettedCritter);
};