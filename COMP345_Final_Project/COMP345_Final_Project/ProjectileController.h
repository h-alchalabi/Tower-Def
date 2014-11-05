#ifndef PROJECTILECONTROLLER_H
#define PROJECTILECONTROLLER_H

#include "Projectile.h"
#include "Critter.h"
#include <vector>

class ProjectileController{
	ProjectileController();
	// create and a Projectile to the list.
	void addProjectile(int dmg, float startX, float startY, float speed, Critter* target);
	// remove a Projectile from the list, trim list to proper size.
	void removeProjectile(Projectile* Projectile);
	// return the pointer to the Projectile at the given index.
	Projectile* getProjectile(int i);
	// return the list of Projectiles.
	vector<Projectile> getProjectileList();
	// move each Projectile in the list.
	void moveProjectiles();
private:
	vector<Projectile> ProjectileList;
};

#endif // PROJECTILECONTROLLER_H
