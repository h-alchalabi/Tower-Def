#pragma once
#include "Critter.h"
class NormalCritter :  public Critter{
public:
	NormalCritter(int level);
	~NormalCritter();
	int getSpeed();
	void setSpeed(int speed);
	int getHP();
	void setHP(int newHP);
	int getReward();
	void setReward(int reward);
	CritterStatus getCritterStatus();
	void setCritterStatus(CritterStatus critterStatus, float statusDuration);
};

