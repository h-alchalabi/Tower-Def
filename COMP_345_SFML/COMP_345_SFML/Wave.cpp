/*******************************************************************************************************************/
//
/*******************************************************************************************************************/

#include "Wave.h"
#include "GameConstants.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Wave::~Wave(){}

Wave::Wave() {
	this->level = 1;
	this->numOfCritters = 4;
	this->deployClock = new sf::Clock();
	this->paused = false;
	this->critterDeployed = 0;
	this->launchCritter = true;
}

void Wave::createWave(int wave) {
	wave = wave % 3;
	critterDeployed = 0;
	switch (wave) {
		case 0:
			deploy_delay = GameConstants::FAST_CRITTER_DEPLOY_TIME;
			for (int i = 0; i < numOfCritters*level; ++i) {
				critVec.push_back(CritterFactory::createCritter("fast", level));
			}
			++level;
			break;
		case 1:
			deploy_delay = GameConstants::NORMAL_CRITTER_DEPLOY_TIME;
			for (int i = 0; i < numOfCritters*level; ++i){
				critVec.push_back(CritterFactory::createCritter("normal", level));
			}
			break;
		case 2:
			deploy_delay = GameConstants::SLOW_CRITTER_DEPLOY_TIME;
			for (int i = 0; i < numOfCritters*level; ++i){
				critVec.push_back(CritterFactory::createCritter("slow", level));
			}
			break;
	}
}

//To deploy the critters and to move them.
bool Wave::deploy(Map* map) {
	sf::Time currTime = this->deployClock->getElapsedTime();

	//if we have already deployed all the critters then simply move them
	if (!paused && (deployClock->getElapsedTime().asMilliseconds() - pausedTime.asMilliseconds()) >= 1000) {
		deployClock->restart();
		pausedTime = sf::Time::Zero;

		//if they haven't all been deployed than increment the counter
		if (critterDeployed < numOfCritters*level && launchCritter) {
			++critterDeployed;
		}
		launchCritter = !launchCritter;
		if (!move(map)) {
			// move all the appearing critters.
			return false;
		}
	}
	for (int i = 0; i < critVec.size(); ++i) {
		critVec[i]->tick(pausedTime);
	}

	return true;
}

bool Wave::move(Map* map) {
	//moving all critters
	for (int i = 0; i < critterDeployed && i < critVec.size(); ++i) {
		if (critVec[i]->getHP() <= 0) {
			GameConstants::collectMoney(critVec.at(i)->getReward());
			map->removeEntity(critVec.at(i));
			critVec.erase(critVec.begin() + i);
			--i;
			--critterDeployed;
			continue;
		}
		int currStep = critVec.at(i)->getStep();
		if (currStep > 0) {
			map->removeEntity(critVec.at(i));
		}		
		if (currStep < map->getPathSteps()) {
			map->addEntity(map->getPath().at(currStep * 2), map->getPath().at(currStep * 2 + 1), critVec.at(i));
			critVec.at(i)->move();
		} else {
			// Remove Money/HP from player.
			critVec.erase(critVec.begin() + i);
			critVec.shrink_to_fit();
			--critterDeployed;
			--i;
			GameConstants::decrementHP();
			if (GameConstants::getHp() == 0) {
				return false;
			}
		}
	}

	return true;
} 

void Wave::pauseWave() {
	this->paused = true;
	this->pauseStartTime = deployClock->getElapsedTime();
}

void Wave::resumeWave() {
	this->paused = false;
	this->pauseEndTime = deployClock->getElapsedTime();
	this->pausedTime += pauseEndTime - pauseStartTime;
}

bool Wave::doneWave() {
	return critVec.size() == 0;
}

bool Wave::isPaused() {
	return paused;
}

std::vector<Critter*> Wave::getCritterVector() {
	return this->critVec;
}