#include "IceTower.h"
#include "GameConstants.h"

IceTower::IceTower() : Tower(5, 100, 1, 150, 100, 150, GameConstants::ICE_TOWER_IMAGE_NAME){

}
IceTower::IceTower(int damage, int range, int fireRate, int basePrice, int sellPrice,
	int upgradedPrice) : Tower(damage, range, fireRate, basePrice, sellPrice, upgradedPrice, GameConstants::ICE_TOWER_IMAGE_NAME) {}

void IceTower::shoot(NormalCritter targettedCritter) {
	targettedCritter.setHP(targettedCritter.getHP() - getDamage());
	targettedCritter.setCritterStatus(CritterStatus::FREEZE, 3000);
}