#include "Wave.h"
Wave::Wave(void)
{
	waveNumber = 1;
	level = 1;
	numOfCritters = 8;
	moddedWave = 0;
	dtime = 0;
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
		Critter *critter;
	case 1:
		 critter = new Critter(waveNumber, CritterType::Normal, "Path.txt");
		for (int i = 0; i<level * numOfCritters; ++i){
			critterVec[i] = *critter;

		}
		break;
	case 2:
		critter = new Critter(waveNumber, CritterType::Fast, "Path.txt");
		for (int i = 0; i<level * numOfCritters; ++i){
			critterVec[i] = *critter;
		}
		break;
	case 0:
		critter = new Critter(waveNumber, CritterType::Slow, "Path.txt");
		for (int i = 0; i<level * numOfCritters; ++i){
			critterVec[i] = *critter;

		}
		break;
		if (waveNumber % 3 == 0){
			level++;
		}
		waveNumber++;
	}
}
void Wave::deploy(float deploymentTime, vector<Critter>critterVec){


	clock_t startTime, elapsedTime;
	for (std::vector<Critter>::iterator it = critterVec.begin(); it != critterVec.end(); ++it){
		startTime = clock();
		//it->choosePath();
		elapsedTime = clock() / CLOCKS_PER_SEC;
		Sleep(it->getDeploymentTime() - elapsedTime);

		//elapsedTime = clock();
		//startTime += elapsedTime;

	}
}