#include "Tower.h"
#include "GameConstants.h"
#include <string>
#include <iostream>

using namespace std;

Tower::Tower() : Entity(GameConstants::NORMAL_TOWER_IMAGE_NAME){}

string Tower::to_string() {
	stringstream ss;
	ss << "Tower:\n---------------------------------------" << endl;
	ss << "Level:\t\t\t" << getLevel() << endl;
	ss << "Base Price:\t\t" << getBasePrice() << endl;
	ss << "Sell Price:\t\t" << getSellPrice() << endl;
	ss << "Upgrade Price:\t\t" << getUpgradePrice() << endl;
	ss << "Damage:\t\t\t" << getDamage() << endl;
	ss << "Range:\t\t\t" << getRange() << endl;
	ss << "Fire Rate:\t\t" << getFireRate() << endl;
	string str = ss.str();
	return str;
}

void Tower::attack(std::vector<Critter*> critterList){
	if (towerClock.getElapsedTime().asMilliseconds() - pausedTime.asMilliseconds() > 2000 && !paused){
		towerClock.restart();
		pausedTime = sf::Time::Zero;
	}
	else{
		return;
	}
	int closestDistTower = numeric_limits<int>::max();  //The closest distance to the tower
	int closestCritterTowerIndex = -1;
	int towerX = this->getSprite().getPosition().x + this->getSprite().getLocalBounds().width / 2;
	int towerY = this->getSprite().getPosition().y + this->getSprite().getLocalBounds().height / 2;
	for (int i = 0; i < critterList.size(); i++) {
		int critterX = critterList[i]->getSprite().getPosition().x + critterList[i]->getSprite().getLocalBounds().width / 2;
		int critterY = critterList[i]->getSprite().getPosition().y + critterList[i]->getSprite().getLocalBounds().height / 2;

		float distanceFromTower = sqrt((pow(critterX - towerX, 2) + pow(critterY - towerY, 2)));
		if (distanceFromTower <= this->getRange()) {

			if (closestDistTower > distanceFromTower) {
				//Updating the closest critter to the tower in the tower's range
				closestDistTower = distanceFromTower;
				closestCritterTowerIndex = i;
			}
		}

	}
	if (closestCritterTowerIndex != -1){
		std::cout << "pre- " << critterList[closestCritterTowerIndex]->getHP();
		this->shoot(critterList[closestCritterTowerIndex]);
		std::cout << " post- " << critterList[closestCritterTowerIndex]->getHP() << std::endl;
		std::cout << "Hit critter: " << closestCritterTowerIndex << "\nRange: " << this->getRange()<< std::endl;
	}
}
void Tower::pause(){
	this->paused = true;
	this->pauseStartTime = towerClock.getElapsedTime();
}
void Tower::resume(){
	this->paused = false;
	this->pauseEndTime = towerClock.getElapsedTime();
	this->pausedTime += pauseEndTime - pauseStartTime;
}
bool Tower::isPaused(){
	return paused;
}