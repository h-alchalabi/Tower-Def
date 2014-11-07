#ifndef SHAREDSINGLETON_H
#define SHAREDSINGLETON_H

#include "TowerController.h"
#include "ProjectileController.h"
#include "Wave.h"

class SharedSingleton{
public:
	//TowerController* mainTowerController;
	int money;
	SharedSingleton();
	SharedSingleton(const SharedSingleton&  s);
	
	//const ProjectileController mainProjectileController();
	//const Wave mainWave();
	SharedSingleton* getInstance();
	~SharedSingleton();
};

#endif // SHAREDSINGLETON_H