#pragma once
#include "Critter.h"
#include"SlowCritter.h"
#include "NormalCritter.h"
#include "FastCritter.h"
class CritterFactory
{
public:
	~CritterFactory(){};
	static Critter* createCritter(std::string type, int level){
		if (type == "normal") return new NormalCritter(level);
		if (type == "slow") return new SlowCritter(level);
		if (type == "fast") return new FastCritter(level);

		else
			return NULL;
	}
	
private:
	CritterFactory(){};
};

