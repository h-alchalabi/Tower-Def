#include "IceTower.h"

IceTower::IceTower(int x, int y, int level, int damage, int range, int fireRate, int basePrice, int sellPrice,
	int upgradedPrice) : Tower(x, y, level, damage, range, fireRate, basePrice, sellPrice, upgradedPrice) {}

void IceTower::slowCritter() {}