#include "Wave.h"
#include <iterator>
Wave::Wave(void)
{
	waveNumber = 1;
	level = 1;
	numOfCritters = 4;
	moddedWave = 0;
	critterDeployed = 0;
}
Wave::~Wave(void)
{
	critterVec.clear();
	coordinates.clear();
	delete critter;

}

int Wave::getNumOfCritters(){
	return level*numOfCritters;
}
vector<Critter> Wave::getCritterVec(){
	return critterVec;
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

void Wave::readFile(string mapPath){
	int path;
	ifstream file(mapPath);
	while (file.is_open()){
		file >> line;
		if (file.eof()){
			break;
		}
			token = line.substr(0, line.find(delimiter));
			istringstream(token) >> x;
			coordinates.push_back(x);
			token = line.substr(line.find(delimiter) + 1);
			istringstream(token) >> y;
			coordinates.push_back(y);
	}
	file.close();
	
}

int Wave::getNumberOfDeployed(){
	return critterDeployed;
}
void Wave::deploy(){
	if (critterDeployed < numOfCritters){
		++critterDeployed;
	}
		move();
}

void Wave::move(){
	if (critterDeployed == ((numOfCritters*level))){
		for (int i = 0; i < numOfCritters*level; ++i){
			critterVec.at(i).move(coordinates);
		}
		
	}
	else{
		for (int i = 0; i < critterDeployed; ++i){
			critterVec.at(i).move(coordinates);
		}
	}
}

const vector<int> Wave::getCoordinateVec(){
	return coordinates;
}