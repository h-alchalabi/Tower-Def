#ifndef TOWER_H
#define TOWER_H

#include "Entity.h"
#include "Critter.h";

class Tower: public Entity{
public:
	/*Have this constructor generate a normal type tower at lvl 1*/
	Tower();
	/* This constructor should adjust create a tower of some type,
	and based on level, give it a fire rate, missle strength etc.*/
	Tower(int type);
	/*This function should check if the critter is in range, if yes, then fire a missle.
	Also if a missle is fired you must wait (fire rate) before firing another one.*/
	void handleCollision(Critter& e);
	virtual ~Tower();

	int getLvl();
	int getType();
	int getBuyCost();
	int getResellVal();
	float getRange();
	int getAtk();
	float getRate();
	int getUpgradeCost();
	enum Effect{ NONE, SLOW };

	void setUpgradeStats();

private:
	float range;
	float fireRate;
	int lvl;
	int type;
	int buyingCost;
	int resellVal;
	int atk;
	int upgradeCost;
	Effect status;
};

#endif // !TOWER_H
