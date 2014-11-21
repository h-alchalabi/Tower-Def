#include "Wave.h"
#include "GameConstants.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Wave::Wave(){
	this->level = 1;
	this->numOfCritters = 10;
	this->deployClock = new sf::Clock();
	this->paused = false;
	this->critterDeployed = 0;
	this->launchCritter = true;
}

Wave::~Wave(){

}


void Wave::createWave(int wave){
	wave = wave % 3;
	critterDeployed = 0;
	switch (wave){
	case 1:{
		deploy_delay = GameConstants::NORMAL_CRITTER_DEPLOY_TIME;
		for (int i = 0; i < numOfCritters; ++i){
			critVec.push_back(CritterFactory::createCritter("normal", level));
		}
	}
		break;
	case 2:{
		deploy_delay = GameConstants::SLOW_CRITTER_DEPLOY_TIME;
		for (int i = 0; i < numOfCritters; ++i){
			critVec.push_back(CritterFactory::createCritter("slow", level));
		}
	}
		break;
	case 0:{
		deploy_delay = GameConstants::FAST_CRITTER_DEPLOY_TIME;
		for (int i = 0; i < numOfCritters; ++i){
			critVec.push_back(CritterFactory::createCritter("fast", level));
		}
	}
		break;
	}
}

void Wave::deploy(Map* map){//To deploy the critters and to move them.
	sf::Time currTime = this->deployClock->getElapsedTime();
	if (!paused && (deployClock->getElapsedTime().asMilliseconds() - pausedTime.asMilliseconds()) >= 250){//if we have already deployed all the critters than simply move them
		deployClock->restart();
		pausedTime = sf::Time::Zero;
		if (critterDeployed < numOfCritters*level && launchCritter){//if they haven't all been deployed than increment the counter
			++critterDeployed;
		}
		launchCritter = !launchCritter;
		move(map); // move all the appearing critters.
	}
	
}

void Wave::move(Map* map){//moving all critters
	for (int i = 0; i < critterDeployed && i < critVec.size(); ++i){
		int currStep = critVec.at(i)->getStep();
		if (currStep > 0){
			map->removeEntity(critVec.at(i));
		}		
		if (currStep < map->getPathSteps()){
			map->addEntity(map->getPath().at(currStep * 2), map->getPath().at(currStep * 2 + 1), critVec.at(i));
			critVec.at(i)->move();
		}
		else{
			critVec.erase(critVec.begin() + i);
			critVec.shrink_to_fit();
			--i;
		}
		
	}
} 
void Wave::pauseWave(){
	this->paused = true;
	this->pauseStartTime = deployClock->getElapsedTime();
}
void Wave::resumeWave(){
	this->paused = false;
	this->pauseEndTime = deployClock->getElapsedTime();
	this->pausedTime += pauseEndTime - pauseStartTime;
}
bool Wave::doneWave(){
	return critVec.size() == 0;
}
bool Wave::isPaused(){
	return paused;
}