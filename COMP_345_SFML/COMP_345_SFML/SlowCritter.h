#pragma once
#include "NormalCritter.h"
class SlowCritter :  public NormalCritter{
public:
	SlowCritter();
	SlowCritter(int level);
	~SlowCritter();
	/*int getSpeed();
	void setSpeed(int speed);
	int getHP();
	void setHP(int newHP);
	int getReward();
	void setReward(int reward);
	CritterStatus getCritterStatus();
	void setCritterStatus(CritterStatus critterStatus, float statusDuration);*/
};

