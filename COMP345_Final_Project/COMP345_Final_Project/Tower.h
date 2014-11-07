#ifndef TOWER_H
#define TOWER_H

#include "Entity.h"
#include "Critter.h"
#include <string>

class Tower: public Entity{
public:
	/*Have this constructor generate a normal type tower at lvl 1*/
	Tower();
	/* This constructor should adjust create a tower of some type,
	and based on level, give it a fire rate, missle strength etc.*/
	Tower(int type);
	/*This function should check if the critter is in range, if yes, then fire a missle.
	Also if a missle is fired you must wait (fire rate) before firing another one.*/
	
	/*we'll handle collision right after the other things are completely done because the grading sheet 
	doesnt mention anything about attacking*/
	void handleCollision(Entity& e);
	virtual ~Tower();

	
	int getLvl() const;
	int getType() const;
	int getBuyCost() const;
	int getResellVal() const;
	float getRange() const;
	int getAtk() const;
	float getRate() const;
	int getUpgradeCost() const;
	enum Effect{ NONE, SLOW };
	void setPostionX(int x);
	void setPostionY(int y);
	int getPositionX() const;
	int getPositionY() const;
	void placeTower();
	string displayStatus(Effect status) const;
	int getstatusEffect() const;
	void setUpgradeStats();
	static std::string towerPreview(int type){
		std::string preview = "";
		switch (type){
		case 1:{
				   preview += "Type: Slowing Tower\n";
				   preview += "Level: 1\n";
				   preview += "Attack: 10\n";
				   preview += "Range: 6\n";
				   preview += "Status Effect: Slow\n";
				   preview += "Fire Rate: 1\n";
				   preview += "Cost: 175\n";
				   preview += "Sell Value: 125\n";
				   preview += "Upgrade Cost: 55\n";
		}break;
		default:{
					preview += "Type: Normal Tower\n";
					preview += "Level: 1\n";
					preview += "Cost: 150\n";
					preview += "Sell Value: 100\n";
					preview += "Attack: 30\n";
					preview += "Range: 3\n";
					preview += "Status Effect: None\n";
					preview += "Fire Rate: 2\n";
					preview += "Upgrade Cost: 45\n";
		}break;
		}
		return preview;
	}
	void printTowerStats() const;
	

private:
	int positionX;
	int positionY;
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
