/*******************************************************************************************************************/
//
/*******************************************************************************************************************/

#pragma once
#include <string>
#include <sstream>
#include "Entity.h"
#include "NormalCritter.h"
#include "Target.h"
#include "SFML/Graphics.hpp"
using namespace std;

class Tower : public Entity {
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
	string to_string();
	virtual void shoot(Critter* targettedCritter) = 0;
	void attack(std::vector<Critter*> critterList);
	void pause();
	void resume();
	bool isPaused();
	void setStrategy(Strategy* strategy);
	Strategy* getStrategy();

private:
	sf::Clock towerClock;
	sf::Time pausedTime, pauseStartTime, pauseEndTime;
	bool paused;
	Target targetStrategy;
};