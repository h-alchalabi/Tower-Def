#include "FireTower.h"

FireTower::FireTower(int x, int y, int level, int damage, int range, int fireRate, int basePrice, int sellPrice,
	int upgradedPrice, int burnDamage) :  
	Tower(x, y, level, damage, range, fireRate, basePrice, sellPrice, upgradedPrice) {
	this->burnDamage = burnDamage;
}

void FireTower::shoot(NormalCritter targettedCritter) {
	targettedCritter.setHP(targettedCritter.getHP() - getDamage());
	targettedCritter.setCritterStatus(CritterStatus::BURN, 3000);
}