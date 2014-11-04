#include "Wave.h"

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
void Wave::createCritters(int waveNumber){
	if (waveNumber % 3 == 0){
		critterVec.resize(numOfCritters*level);
	}
	moddedWave = waveNumber % 3;
	//filling vector with critter based on waveNumber
	switch (moddedWave){
	case 1:
		 critter = new Critter(waveNumber, CritterType::Normal, "Path.txt");
		for (int i = 0; i<level * numOfCritters; ++i){
			critterVec.push_back(*critter);
		}
		break;
	case 2:
		critter = new Critter(waveNumber, CritterType::Fast, "Path.txt");
		for (int i = 0; i<level * numOfCritters; ++i){
			critterVec.push_back(*critter);
		}
		break;
	case 0:
		critter = new Critter(waveNumber, CritterType::Slow, "Path.txt");
		for (int i = 0; i<level * numOfCritters; ++i){
			critterVec.push_back(*critter);
		}
		break;
		if (waveNumber % 3 == 0){
			level++;
		}
		waveNumber++;
	}
}
void Wave::deploy(float deploymentTime, vector<Critter>critterVec){


	if (critterVec.at(critterDeployed).getDeploymentTime() - elapsedTime <=0){
		//critterVec.at(critterDeployed).deploy();
		++critterDeployed;

		elapsedTime = 0;
	}
	

	
}

void Wave::move(){
	for (int i = 0; i < critterDeployed; ++i){
		//critterVec.at(i).choosePath();
	}
}