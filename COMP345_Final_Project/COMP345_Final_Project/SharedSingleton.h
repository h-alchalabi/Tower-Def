#ifndef SHAREDSINGLETON_H
#define SHAREDSINGLETON_H

#include "TowerController.h"
#include "ProjectileController.h"
#include "Wave.h"

class SharedSingleton{
public:
	int money;
	//TowerController* towerController;
	static SharedSingleton* getInstance();
private:
	SharedSingleton();
	static SharedSingleton* ss_ptr;
};

#endif // SHAREDSINGLETON_H