#include "Tower.h"

Tower::Tower(){
	
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

	//Average Tower
	if (type == 0)
	{
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

	//Special Type of Tower
	if (type == 1)
	{
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

Tower::~Tower(){}

int Tower::getLvl(){
	return lvl;
}

int Tower::getType(){
	return type;
}

int Tower::getBuyCost(){
	return buyingCost;
}

int Tower::getResellVal(){
	return resellVal;
}

float Tower::getRange(){
	return range;
}

int Tower::getAtk(){
	return atk;
}

float Tower::getRate(){
	return fireRate;
}

int Tower::getUpgradeCost(){
	return upgradeCost;
}
int Tower::getstatusEffect(){
	return status;
}
string Tower::displayStatus(Effect status){
	char* statusEffect[] = { "NONE", "SLOW" };
	return statusEffect[status];

}
void Tower::setPostionY(int y){
	positionY = y;
}
void Tower::setPostionX(int x){
	positionX = x;
}
int Tower::getPositionX(){ 
	return positionX;
}
int Tower::getPositionY(){
	return positionY;
}

//void Tower::placeTower(){}


void Tower::setUpgradeStats()
{
	++lvl;
	resellVal += 15;
	++range;
	atk += 5;
	++fireRate;

}