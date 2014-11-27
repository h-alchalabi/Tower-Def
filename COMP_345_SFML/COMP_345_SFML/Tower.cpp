#include "Tower.h"
#include "GameConstants.h"
#include <string>
#include "NearestCritterTowerStrategy.h"

using namespace std;

Tower::Tower() : Entity(GameConstants::NORMAL_TOWER_IMAGE_NAME){
	targetStrategy = Target(new NearestCritterTowerStrategy());
}

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

	int towerX = this->getSprite().getPosition().x + this->getSprite().getLocalBounds().width / 2;
	int towerY = this->getSprite().getPosition().y + this->getSprite().getLocalBounds().height / 2;
	int targettedCritter = targetStrategy.executeStrategy(critterList, towerX, towerY, this->getRange());
	if (targettedCritter != -1){
		//std::cout << "pre- " << critterList[targettedCritter]->getHP();
		this->shoot(critterList[targettedCritter]);
		//std::cout << " post- " << critterList[targettedCritter]->getHP() << std::endl;
		//std::cout << "Hit critter: " << targettedCritter << "\nRange: " << this->getRange()<< std::endl;
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

Strategy* Tower::getStrategy() {
	return targetStrategy.getStrategy();
}

void Tower::setStrategy(Strategy* strategy) {
	targetStrategy.setStrategy(strategy);
}