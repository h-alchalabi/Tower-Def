#pragma once

/* Abstract Tower Class. Defines Functionality for classes
* implementing Tower.
*/

#include <string>
#include <sstream>
#include "Entity.h"

using namespace std;

class Tower: public Entity{
public:
	Tower();
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual int getLevel() = 0;
	virtual int getDamage() = 0;
	virtual int getRange() = 0;
	virtual int getFireRate() = 0;
	virtual int getBasePrice() = 0;
	virtual int getSellPrice() = 0;
	virtual int getUpgradePrice() = 0;
	virtual void setX(int x) = 0;
	virtual void setY(int y) = 0;
	virtual void setLevel(int level) = 0;
	virtual void setDamage(int damage) = 0;
	virtual void setRange(int range) = 0;
	virtual void setFireRate(int fireRate) = 0;
	virtual void setBasePrice(int basePrice) = 0;
	virtual void setSellPrice(int sellPrice) = 0;
	virtual void setUpgradedPrice(int upgradedPrice) = 0;
	string to_string();
};