#include "IceTower.h"

IceTower::IceTower(int x, int y, int level, int damage, int range, int fireRate, int basePrice, int sellPrice,
	int upgradedPrice) : Tower(x, y, level, damage, range, fireRate, basePrice, sellPrice, upgradedPrice) {}

void IceTower::shoot(NormalCritter targettedCritter) {
	targettedCritter.setHP(targettedCritter.getHP() - getDamage());
	targettedCritter.setCritterStatus(CritterStatus::FREEZE, 3000);
}