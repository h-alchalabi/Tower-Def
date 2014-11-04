#ifndef MISSLECONTROLLER_H
#define MISSLECONTROLLER_H

#include "Missle.h"
#include "Critter.h"
#include <vector>

class MissleController{
	MissleController();
	// create and a missle to the list.
	void addMissle(int dmg, float startX, float startY, float speed, Critter* target);
	// remove a missle from the list, trim list to proper size.
	void removeMissle(Missle* missle);
	// return the pointer to the missle at the given index.
	Missle* getMissle(int i);
	// return the list of missles.
	vector<Missle> getMissleList();
	// move each missle in the list.
	void moveMissles();
private:
	vector<Missle> missleList;
};

#endif // !MISSLECONTROLLER_H
