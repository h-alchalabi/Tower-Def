#pragma once
#include "Critter.h"
#include <vector>
#include <time.h>
#include "windows.h"
#include <fstream>
class Wave
{
public:
	Wave(void);
	~Wave(void);
	void createCritters(int waveNumber, string mapPath);
	void deploy();
	void move();
	vector <Critter> getCritterVec();
	int getNumOfCritters();
	void readFile(string file);
	const string delimiter = ",";
	int x, y;
	string line, token;
	vector<int> coordinates;

private:
	int waveNumber;
	int level;
	int numOfCritters;
	int moddedWave;
	int critterDeployed;
	clock_t elapsedTime;
	Critter *critter;
	vector <Critter> critterVec;
	//Critter* critterHolder;
};