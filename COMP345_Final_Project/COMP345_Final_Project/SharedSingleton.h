#pragma once

#include "TowerController.h"
#include "ProjectileController.h"
#include "Wave.h"

class SharedSingleton{
public:
	int money;
	static TowerController *tc_ptr;
	static SharedSingleton* getInstance();
private:
	SharedSingleton();
	static SharedSingleton* ss_ptr;
};