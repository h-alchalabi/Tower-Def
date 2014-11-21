#pragma once
#include "Critter.h"
class NormalCritter :  public Critter{
public:
	NormalCritter(int level);
	~NormalCritter();
	int getSpeed();
	int getHP();
	void setHP(int newHP);
	int getReward();
	void setReward(int reward);


};

