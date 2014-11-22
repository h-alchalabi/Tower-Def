#pragma once

#include "Entity.h"

enum CritterStatus { NORMAL, BURN, FREEZE };

class Critter : public Entity {
public:

	virtual int getSpeed() = 0;
	virtual int getHP() = 0;
	virtual int getReward() = 0;
	virtual CritterStatus getCritterStatus() = 0;
	virtual void setHP(int HP) = 0;
	virtual void setReward(int reward) = 0;
	virtual void setSpeed(int speed) = 0;
	virtual void setCritterStatus(CritterStatus critterStatus, float statusDuration) = 0;
	void move();
	int getStep();
	void tick();
	~Critter(){};
	Critter();

protected:
	int HP;
	int speed;
	int reward;
	int level;
	int step;
	CritterStatus critterStatus;
	sf::Clock critterClock;
	float statusTime;
};