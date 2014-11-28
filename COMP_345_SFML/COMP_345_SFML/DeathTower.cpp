/*******************************************************************************************************************/
//
/*******************************************************************************************************************/

#include "DeathTower.h"
#include "GameConstants.h"
#include <iostream>
#include <cstdlib>

DeathTower::DeathTower(Tower* decoratedTower) : DecoratedTower(decoratedTower) {
	this->setImageName(GameConstants::DEATH_TOWER_IMAGE_NAME);
}

int DeathTower::getX() {
	return DecoratedTower::getX();
}

int DeathTower::getY() {
	return DecoratedTower::getY();
}

int DeathTower::getLevel() {
	return DecoratedTower::getLevel();
}

int DeathTower::getDamage() {
	return DecoratedTower::getDamage();
}

int DeathTower::getRange() {
	return DecoratedTower::getRange();
}

int DeathTower::getFireRate() {
	return DecoratedTower::getFireRate();
}

int DeathTower::getBasePrice() {
	return DecoratedTower::getBasePrice() + 25;
}

int DeathTower::getSellPrice() {
	return DecoratedTower::getSellPrice() + 25;
}

int DeathTower::getUpgradePrice() {
	return DecoratedTower::getUpgradePrice() + 25;
}

void DeathTower::shoot(Critter* targettedCritter) {
	int critterDeathChance = rand() % 5;
	if (critterDeathChance == 0) {
		cout << "Critter dead\n";
		targettedCritter->setHP(0);
	} else 
	cout << "not dead\n";
}