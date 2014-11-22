#pragma once
#include "Critter.h"
#include "CritterFactory.h"
#include <vector>
#include "Map.h"
#include "SFML\Graphics.hpp"

class Wave
{
	
public:
	Wave();
	~Wave();
	void createWave(int wave);
	void deploy(Map* map);
	void move(Map* map);
	void pauseWave();
	void resumeWave();
	bool doneWave();
	bool isPaused();

private:
	int critterDeployed;
	bool paused;
	bool launchCritter;
	sf::Int32 deploy_delay;
	sf::Clock* deployClock;
	sf::Time pausedTime;
	sf::Time pauseStartTime;
	sf::Time pauseEndTime;
	int numOfCritters;
	std::vector <Critter*> critVec;
	Critter* critter;
	int level;
	

};

