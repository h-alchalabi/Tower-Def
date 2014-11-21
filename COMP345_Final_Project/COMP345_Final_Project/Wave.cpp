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
{//deconstructors
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
void Wave::createCritters(int waveNumber, string mapPath){//Creating a critter and filling out the vector.
	if (waveNumber % 3 == 0){//if it is the start of a wave, then resize the critterVec to the apporiate size, this function is only needed at the start.
		critterVec.resize(numOfCritters*level);
	}
	moddedWave = waveNumber % 3;
	//filling vector with critter based on waveNumber
	switch (moddedWave){//To select apporiate critter.
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
		break;
	case 0:
		critter = new Critter(waveNumber, CritterType::Slow, mapPath);
		for (int i = 0; i<level * numOfCritters; ++i){
			critterVec.push_back(*critter);
		}
		deploy();
		break;
	}
	if (waveNumber % 3 == 0){//if we reached one of each type we increase the level.
		level++;
	}
	waveNumber++;//increment the wave each time.
}

void Wave::readFile(string mapPath){//Reading from the path txt file of the map.
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
void Wave::deploy(){//To deploy the critters and to move them.
	if (critterDeployed < numOfCritters){//if we have already deployed all the critters than simply move them
		++critterDeployed;				 //if they haven't all been deployed than increment the counter and move.
	}
		move();
}

void Wave::move(){//moving all critters
	if (critterDeployed == ((numOfCritters*level))){ //if all the critter's have been deployed then we simply move them all.
		for (int i = 0; i < numOfCritters*level; ++i){
			critterVec.at(i).move(coordinates);
		}
		
	}
	else{//if not all critters have been deployed than we only move the critters that have been deployed
		for (int i = 0; i < critterDeployed; ++i){
			critterVec.at(i).move(coordinates);
		}
	}
} 

const vector<int> Wave::getCoordinateVec(){
	return coordinates;
}

int* Wave::getStartPos(){
	int* startPos = new int[2];
	startPos[0] = coordinates.at(0);
	startPos[1] = coordinates.at(1);
	return startPos;
}