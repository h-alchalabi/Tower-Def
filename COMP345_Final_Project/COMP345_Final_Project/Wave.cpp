#include "Wave.h"
#include <iterator>
Wave::Wave(void)
{
	waveNumber = 1;
	level = 1;
	numOfCritters = 8;
	moddedWave = 0;
	critterDeployed = 0;
	elapsedTime = 0;
}
Wave::~Wave(void)
{

}
void Wave::createCritters(int waveNumber, string mapPath){
	if (waveNumber % 3 == 0){
		critterVec.resize(numOfCritters*level);
	}
	moddedWave = waveNumber % 3;
	//filling vector with critter based on waveNumber
	switch (moddedWave){
	case 1:
		 critter = new Critter(waveNumber, CritterType::Normal, mapPath);
		 for (int i = 0; i<level * numOfCritters; ++i){
			critterVec.push_back(*critter);
		}
		deploy();
		break;
	case 2:
		critter = new Critter(waveNumber, CritterType::Fast, mapPath);
		for (int i = 0; i<level * numOfCritters; ++i){
			critterVec.push_back(*critter);
			
		}
		//deploy();
		break;
	case 0:
		critter = new Critter(waveNumber, CritterType::Slow, mapPath);
		for (int i = 0; i<level * numOfCritters; ++i){
			critterVec.push_back(*critter);
		}
		deploy();
		break;
		if (waveNumber % 3 == 0){
			level++;
		}
		waveNumber++;
	}
}
void Wave::deploy(){
	while (critterDeployed < numOfCritters*level){
		++critterDeployed;
		cout << "CD= " << critterDeployed << endl;
		move();
		
	}
		

}

void Wave::move(){
	for (int i=0; i<critterDeployed; ++i){
		cout << "deploying at " << i << endl;
		critterVec.at(i).move();
	}
}