#include "Tower.h"
#pragma once

class FireTower : public Tower {
public:
	FireTower();
	FireTower(int damage, int range, int fireRate, int basePrice, int sellPrice, int upgradedPrice, int burnDamage);
	void shoot(NormalCritter targettedCritter);
private:
	int burnDamage;
};