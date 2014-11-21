#pragma once

/* Abstract Tower Class. Defines Functionality for classes
* implementing Tower.
*/

#include <string>
#include <sstream>
#include "Entity.h"

class Tower: public Entity{
public:
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual int getLevel() = 0;
	virtual int getDamage() = 0;
	virtual int getRange() = 0;
	virtual int getFireRate() = 0;
	virtual int getBasePrice() = 0;
	virtual int getSellPrice() = 0;
	virtual int getUpgradePrice() = 0;
	std::string to_string(){
		std::stringstream ss;
		ss << "Tower:\n---------------------------------------" << std::endl;
		ss << "Level:\t\t\t" << getLevel() << std::endl;
		ss << "Base Price:\t\t" << getBasePrice() << std::endl;
		ss << "Sell Price:\t\t" << getSellPrice() << std::endl;
		ss << "Upgrade Price:\t\t" << getUpgradePrice() << std::endl;
		ss << "Damage:\t\t\t" << getDamage() << std::endl;
		ss << "Range:\t\t\t" << getRange() << std::endl;
		ss << "Fire Rate:\t\t" << getFireRate() << std::endl;
		std::string str = ss.str();
		return str;
	}
};