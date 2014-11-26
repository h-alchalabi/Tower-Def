#include "IceTower.h"
#include "GameConstants.h"
#include <iostream>

IceTower::IceTower(Tower* decoratedTower) : DecoratedTower(decoratedTower){
	this->setImageName(GameConstants::ICE_TOWER_IMAGE_NAME);
}
int IceTower::getX(){
	return DecoratedTower::getX();
}
int IceTower::getY(){
	return DecoratedTower::getY();
}
int IceTower::getLevel(){
	return DecoratedTower::getLevel();
}
int IceTower::getDamage(){
	return DecoratedTower::getDamage();
	std::cout << "Ice getDamage() = " << getDamage() <<std::endl;
}
int IceTower::getRange(){
	return DecoratedTower::getRange();
}
int IceTower::getFireRate(){
	return DecoratedTower::getFireRate();
}
int IceTower::getBasePrice(){
	return DecoratedTower::getBasePrice() + 25;
}
int IceTower::getSellPrice(){
	return DecoratedTower::getSellPrice() + 25;
}
int IceTower::getUpgradePrice(){
	return DecoratedTower::getUpgradePrice() + 25;
}
void IceTower::shoot(Critter* targettedCritter) {
	targettedCritter->setCritterStatus(CritterStatus::FREEZE, 3000);
	DecoratedTower::shoot(targettedCritter);
}