#pragma once
#include "Critter.h"
#include <vector>
#include <time.h>
#include "windows.h"
class Wave
{
public:
	Wave(void);
	~Wave(void);
	void createCritters(int waveNumber);
	void deploy(float deploymentTime, vector<Critter>critter);
private:
	int waveNumber;
	int level;
	int numOfCritters;
	int moddedWave;
	int dtime;
	vector <Critter> critterVec;
	//Critter* critterHolder;
};