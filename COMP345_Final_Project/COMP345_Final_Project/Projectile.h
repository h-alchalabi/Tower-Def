#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Critter.h"

class Projectile{
public:
	Projectile();
	Projectile(int dmg, float startX, float startY, float speed, Critter* target);
	~Projectile();
	void move();
	float getX();
	float getY();
private:
	int damage;
	float x, y, speed;
	Critter* targetCritter;
};

#endif // !PROJECTILE_H
