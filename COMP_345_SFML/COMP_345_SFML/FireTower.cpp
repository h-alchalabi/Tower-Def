#include "FireTower.h"
#include "GameConstants.h"

FireTower::FireTower() : Tower(10, 100, 1, 200, 150, 200, GameConstants::FIRE_TOWER_IMAGE_NAME){
	this->burnDamage = 2;
}

FireTower::FireTower(int damage, int range, int fireRate, int basePrice, int sellPrice,
	int upgradedPrice, int burnDamage) :  
	Tower(damage, range, fireRate, basePrice, sellPrice, upgradedPrice, GameConstants::FIRE_TOWER_IMAGE_NAME) {
	this->burnDamage = burnDamage;
}

void FireTower::shoot(NormalCritter targettedCritter) {
	targettedCritter.setHP(targettedCritter.getHP() - getDamage());
	targettedCritter.setCritterStatus(CritterStatus::BURN, 3000);
}