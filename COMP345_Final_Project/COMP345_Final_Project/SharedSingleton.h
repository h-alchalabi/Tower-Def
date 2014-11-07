#ifndef SHAREDSINGLETON_H
#define SHAREDSINGLETON_H

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

#endif // SHAREDSINGLETON_H