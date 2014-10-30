#include "CollisionHandler.h"
#include <vector>
#include "Entity.h"

CollisionHandler::CollisionHandler(){

}
void CollisionHandler::addCollision(std::vector<Entity> target, std::vector<Entity> interacting){
	this->targetList.resize(this->targetList.size() + 1);
	this->interactingList.resize(this->interactingList.size() + 1);
	this->targetList[this->targetList.size() - 1] = target;
	this->targetList[this->interactingList.size() - 1] = interacting;
}
void CollisionHandler::checkCollisions(){
	for (int k = 0; k < targetList.size(); ++k){
		std::vector<Entity> target = targetList[k];
		std::vector<Entity> interacting = interactingList[k];

		for (int i = 0; i < target.size(); ++i){
			Entity currTarget = target[i];
			for (int j = 0; j < target.size(); ++j){
				Entity currInteracting = interacting[j];
				currTarget.handleCollision(currInteracting);

			}
		}
	}
}
