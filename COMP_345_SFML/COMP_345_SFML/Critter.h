#pragma once

#include "Entity.h"

class Critter : public Entity{
public:

	virtual int getSpeed() = 0;
	virtual int getHP() = 0;
	virtual int getReward() = 0;
	virtual void setHP(int HP) = 0;
	virtual void setReward(int reward) = 0;
	void move();
	int getStep();
	~Critter(){};
	Critter();

protected:
	int HP;
	int speed;
	int reward;
	int level;
	int step;
};