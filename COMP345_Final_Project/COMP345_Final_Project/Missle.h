#ifndef MISSLE_H
#define MISSLE_H

#include "Critter.h"

class Missle{
public:
	Missle();
	Missle(int dmg, float startX, float startY, float speed, Critter* target);
	~Missle();
	void move();
	float getX();
	float getY();
private:
	int damage;
	float x, y, speed;
	Critter* targetCritter;
};

#endif // !MISSLE_H
