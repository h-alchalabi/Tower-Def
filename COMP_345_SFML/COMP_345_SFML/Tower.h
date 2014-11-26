#pragma once

/* Abstract Tower Class. Defines Functionality for classes
* implementing Tower.
*/

#include <string>
#include <sstream>
#include "Entity.h"
#include "NormalCritter.h"

using namespace std;

class Tower : public Entity{
public:
	Tower();
	//Tower(int damage, int range, int fireRate, int basePrice, int sellPrice, int upgradedPrice, string towerImageName);
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual int getLevel() = 0;
	virtual int getDamage() = 0;
	virtual int getRange() = 0; // Radius
	virtual int getFireRate() = 0;
	virtual int getBasePrice() = 0;
	virtual int getSellPrice() = 0;
	virtual int getUpgradePrice() = 0;
	/*void setX(int x);
	void setY(int y);
	void setLevel(int level);
	void setDamage(int damage);
	void setRange(int range);
	void setFireRate(int fireRate);
	void setBasePrice(int basePrice);
	void setSellPrice(int sellPrice);
	void setUpgradedPrice(int upgradedPrice);*/
	string to_string();
	virtual void shoot(Critter* targettedCritter) = 0;
private:
	/*int x;
	int y;
	int level;
	int damage;
	int range;
	int fireRate;
	int basePrice;
	int sellPrice;
	int upgradedPrice;*/
};