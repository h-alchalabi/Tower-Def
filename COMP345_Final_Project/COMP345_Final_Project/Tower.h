#ifndef TOWER_H
#define TOWER_H

#include "Entity.h"
#include "Critter.h";

class Tower: public Entity{
public:
	/*Have this constructor generate a normal type tower at lvl 1*/
	Tower();
	/* This constructor should adjust create a tower of some type,
	and based on level, give it a fire rate, missle strenght etc.*/
	Tower(int type, int level);
	/*This function should check if the critter is in range, if yes, then fire a missle.
	Also if a missle is fired you must wait (fire rate) before firing another one.*/
	void handleCollision(Critter& e);
	/*Function to upgrade. should increase range, fire rate, and lvl(obviously)*/
	void upgrade();
private:
	float range;
	float fireRate;
	int lvl;
	int type;
};

#endif // !TOWER_H
