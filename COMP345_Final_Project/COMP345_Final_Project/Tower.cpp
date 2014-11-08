#include "Tower.h"

//Constructor for a tower. Currently set to the Average Tower
Tower::Tower(){
	type = 0;
	lvl = 1;
	buyingCost = 150;
	resellVal = 100;
	range = 3;
	atk = 30;
	status = NONE;
	fireRate = 2;
	upgradeCost = 45;
	positionY = 0;
	positionX = 0;
	}

Tower::Tower(int type){

	//Constructor for Average Tower
	if (type == 0)
	{
		this->type = type;
		lvl = 1;
		buyingCost = 150;
		resellVal = 100;
		range = 3;
		atk = 30;
		status = NONE;
		fireRate = 2;
		upgradeCost = 45;
		positionY = 0;
		positionX = 0;
	}

	//Constructor for Special Type of Tower
	if (type == 1)
	{
		this->type = type;
		lvl = 1;
		buyingCost = 175;
		resellVal = 125;
		range = 6;
		atk = 10;
		status = SLOW;
		fireRate = 1;
		upgradeCost = 55;
		positionY = 0;
		positionX = 0;
	}
}

void Tower::handleCollision(Entity& e){
	// check if a critter is in range (use critter's center coordinates and radius)
	// if yes, handle the collision by creating a missle via MissleController and st it's target to the given Critter.
	// All this should occur once per <fireRate>
	// Use timers.
}

Tower::~Tower(){}

int Tower::getLvl() const{
	return lvl;
}
int Tower::getType() const{
	return type;
}
int Tower::getBuyCost() const{
	return buyingCost;
}
int Tower::getResellVal()const{
	return resellVal;
}
float Tower::getRange() const{
	return range;
}
int Tower::getAtk() const{
	return atk;
}
float Tower::getRate() const{
	return fireRate;
}
int Tower::getUpgradeCost() const{
	return upgradeCost;
}
int Tower::getstatusEffect() const{
	return status;
}
//Shows the status effects for the tower 
string Tower::displayStatus(Effect status) const{
	char* statusEffect[] = { "NONE", "SLOW" };
	return statusEffect[status];
}

void Tower::setPostionY(int y){
	positionY = y;
}
void Tower::setPostionX(int x){
	positionX = x;
}
int Tower::getPositionX() const{ 
	return positionX;
}
int Tower::getPositionY() const{
	return positionY;
}

//void Tower::placeTower(){}

//Update values for tower when calling upgrade
void Tower::setUpgradeStats()
{
	++lvl;
	resellVal += 15;
	++range;
	atk += 5;
	++fireRate;
}

// Display all tower stats
void Tower::printTowerStats() const{
	cout << "\n Tower Stats" <<
		"\n========================" <<
		"\nType: " << this->getType() <<
		"\nLevel: " << this->getLvl() <<
		"\nBuying Cost: " << this->getBuyCost() <<
		"\nResell Value: " << this->getResellVal() <<
		"\nStatus Effect: " << this->displayStatus(status) <<
		"\nAttack: " << this->getAtk() <<
		"\nRange: " << this->getRange() <<
		"\nFire Rate: " << this->getRate() <<
		"\nUpgrade Cost: " << this->getUpgradeCost() << endl;
}