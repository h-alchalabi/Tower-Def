#pragma once
#include "Critter.h"
class FastCritter :  public Critter
{
public:
	FastCritter(int level);
	~FastCritter();
	int getSpeed();
	void setSpeed(int speed);
	int getHP();
	void setHP(int HP);
	int getMaxHP() const;
	int getReward();
	void setReward(int reward);
	CritterStatus getCritterStatus();
	void setCritterStatus(CritterStatus critterStatus, float statusDuration);
};

