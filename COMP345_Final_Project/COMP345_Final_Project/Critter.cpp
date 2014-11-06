#include "Critter.h"
#include <fstream>



Critter::Critter(){

}

// this constructor mofifies the critter depending on Wave
Critter::Critter(int waveNumber, CritterType type, string critterMapPath){

	hitPoints = 5 * waveNumber;
	speed = speed*waveNumber;
	level = 1;
	reward = 1 * level;
	positionX = 0;
	positionY = 0;
	deploymentTime = 3.0f;
	mapPath = critterMapPath;

}


Critter::~Critter()
{
	// close file here.
}

string Critter::getMapPath(){
	return mapPath;
}
float Critter::getDeploymentTime(){
	return deploymentTime;
}
int Critter::getLevel(){
	return level;
}

void Critter::setLevel(int level){
	this->level = level;
}

int Critter::getHitPoints(){
	return hitPoints;
}

void Critter::setHitPoints(int hitPoints){
	this->hitPoints = hitPoints;
}

int Critter::getSpeed(){
	return speed;
}

void Critter::setSpeed(int speed){
	this->speed = speed;
}

int Critter::getReward(){
	return reward;
}

void Critter::setReward(int reward){
	this->reward = reward;
}

int Critter::getPositionX(){
	return positionX;
}

int Critter::getPositionY(){
	return positionY;
}

void Critter::setPositionX(int positionX){
	this->positionX = positionX;
}

void Critter::setPositionY(int positionY){
	this->positionY = positionY;
}

void Critter::move(){
	ifstream file(mapPath);
	string line1;
	if (!file.eof()){
		file >> line1;
		if (file.eof()){
			return;
		}
		else{
			token = line1.substr(0, line1.find(delimiter));
			istringstream(token) >> x;
			positionX = x;
			token = line1.substr(line1.find(delimiter) + 1);
			istringstream(token) >> y;
			positionY = y;
			cout << positionX << "," << positionY << endl;
		}
	}
		

}
//check the health of critter
// increments reward if critter is dead
bool Critter::checkHealth(){
	if (hitPoints <= 0){
		++reward;
		//++Wave::userPoints;
		cout << "Critter is dead" << endl;
		cout << "Reward = " << reward << endl;
		//cout << "User points = " << Wave::userPoints << endl;

		return true;
	}
	else
		return false;
}

// checking for towers in order to decrement hitPoints
void Critter::towerCheck(char map[5][5], int rows, int columns){
	//down tower
	if (map[rows + 1][columns] == 'T'&& rows<4){
		//	this->hitPoints -= Wave::towerDamage;
		cout << "Critter HP= " << hitPoints << endl;
	}
	//right tower
	if (map[rows][columns + 1] == 'T'&& columns<4){
		//	this->hitPoints -= Wave::towerDamage;
		cout << "Critter HP= " << hitPoints << endl;
	}
	//up tower
	if (map[rows - 1][columns] == 'T'&& rows>0){
		//	this->hitPoints -= Wave::towerDamage;
		cout << "Critter HP= " << hitPoints << endl;
	}
	//left tower
	if (map[rows][columns - 1] == 'T'&& columns >0){
		//	this->hitPoints -= Wave::towerDamage;
		cout << "Critter HP= " << hitPoints << endl;
	}

}

void Critter::handleCollision(Entity& e){
	// check if missle has hit (via hitboxes)
	// if yes, handle the collision by dealing damage and destroying missle.
	// missle should be destroyed via the Missle Controller.
}

