#pragma once
#include "Critter.h"
class FastCritter :  public Critter
{
public:
	FastCritter(int level);
	~FastCritter();
	int getSpeed();
	int getHP();
	void setHP(int HP);
	int getReward();
	void setReward(int reward);
	



};

