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
	Tower(int damage, int range, int fireRate, int basePrice, int sellPrice, int upgradedPrice, string towerImageName);
	int getX();
	int getY();
	int getLevel();
	int getDamage();
	int getRange(); // Radius
	int getFireRate();
	int getBasePrice();
	int getSellPrice();
	int getUpgradePrice();
	void setX(int x);
	void setY(int y);
	void setLevel(int level);
	void setDamage(int damage);
	void setRange(int range);
	void setFireRate(int fireRate);
	void setBasePrice(int basePrice);
	void setSellPrice(int sellPrice);
	void setUpgradedPrice(int upgradedPrice);
	string to_string();
	virtual void shoot(NormalCritter targettedCritter);
private:
	int x;
	int y;
	int level;
	int damage;
	int range;
	int fireRate;
	int basePrice;
	int sellPrice;
	int upgradedPrice;
};