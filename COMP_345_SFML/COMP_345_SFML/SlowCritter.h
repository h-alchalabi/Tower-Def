#pragma once
#include "Critter.h"
class SlowCritter :  public Critter{
public:
	SlowCritter();
	SlowCritter(int level);
	~SlowCritter();
	int getSpeed();
	int getHP();
	void setHP(int newHP);
	int getReward();
	void setReward(int reward);



	

};

