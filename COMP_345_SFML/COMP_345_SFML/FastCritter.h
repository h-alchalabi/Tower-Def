#pragma once
#include "NormalCritter.h"
class FastCritter :  public NormalCritter
{
public:
	FastCritter(int level);
	~FastCritter();
	/*int getSpeed();
	void setSpeed(int speed);
	int getHP();
	void setHP(int HP);
	int getReward();
	void setReward(int reward);
	CritterStatus getCritterStatus();
	void setCritterStatus(CritterStatus critterStatus, float statusDuration);*/
};

