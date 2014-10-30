#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "Entity.h"
#include <vector>

class CollisionHandler{
public:
	CollisionHandler();
	void addCollision(std::vector<Entity> target, std::vector<Entity> interacting);
	void checkCollisions();
private:
	std::vector<std::vector<Entity>> targetList;
	std::vector<std::vector<Entity>> interactingList;
};

#endif // COLLISION_HANDLER_H
