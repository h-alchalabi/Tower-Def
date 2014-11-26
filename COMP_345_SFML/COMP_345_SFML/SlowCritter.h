#pragma once
#include "Critter.h"
class SlowCritter :  public Critter{
public:
	SlowCritter();
	SlowCritter(int level);
	~SlowCritter();
	int getSpeed();
	void setSpeed(int speed);
	int getMaxHP() const;
	int getHP();
	void setHP(int newHP);
	int getReward();
	void setReward(int reward);
	CritterStatus getCritterStatus();
	void setCritterStatus(CritterStatus critterStatus, float statusDuration);
};

