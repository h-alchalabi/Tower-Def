#ifndef SHAREDSINGLETON_H
#define SHAREDSINGLETON_H

#include "TowerController.h"
#include "ProjectileController.h"
#include "Wave.h"

class SharedSingleton{
public:
	const TowerController mainTowerController();
	const ProjectileController mainProjectileController();
	const Wave mainWave();
	SharedSingleton* getInstance();
	~SharedSingleton();
private:
	SharedSingleton();
	SharedSingleton(const SharedSingleton&  s);
};

#endif // SHAREDSINGLETON_H