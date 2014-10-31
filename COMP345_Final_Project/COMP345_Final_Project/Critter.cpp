#include "Critter.h"




// this constructor mofifies the critter depending on Wave
Critter::Critter(int waveNumber){
	
	hitPoints = 5*waveNumber;
	speed = speed*waveNumber;
	level = level*waveNumber;
	reward = 0*waveNumber;
	towerDamage = 1;
	positionX = 0;
	positionY = 0;
	rows = 0;
	columns = 0;
}



Critter::~Critter()
{
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

void Critter::incrementPositionX(){
	++positionX;
}

void Critter::incrementPositionY(){
	++positionY;
}

void Critter::choosePath(char map[5][5]){

	// start at [0][0] , end at [4][4]
	//takes user input, only cases of d,r,q work. 
	// will loop until user enters q, or user ends up at E. ([4][4] in our case)
	// if the user encounters a T, it takes damage
	while (map[rows][columns] != 'E'){
		cout << "choose a direction: r:right, d:down or q:exit : ";
		cin >> input;
		//going down
		if (input == 'd'){
			++rows;
			cout << "Critter chooses to go to position " << rows << columns << endl;
			if (map[rows][columns] == 'V' && rows <= 4){
				incrementPositionY(); 
				towerCheck(map, rows, columns);
				if (checkHealth() == true){
					break;
				}
				cout << "valid path" << endl;
				cout << map[rows][columns] << endl;

			}
			// if the next cell is E, the critter stops, since it's the end of the path
			//userPoints is also decremented because the critter reached the end
			else if (map[rows][columns] == 'E' && columns <= 4){
				incrementPositionY();
				cout << map[rows][columns] << endl;
				cout << "this is the end" << endl;
				//--Wave::userPoints;
			}



			else {
				cout << "invalid path, " << endl;
				cout << map[rows][columns] << endl;
				--rows;

			}
		}
		//going right
		else if (input == 'r'){
			++columns;
			cout << "Critter chooses to go to position " << rows << columns << endl;
			if (map[rows][columns] == 'V' && columns <= 4){
				incrementPositionX();
				//calls function towerCheck which checks if there are any towers adjacent to the critter
				towerCheck(map, rows, columns);
				//checkHealth() checks if the critter is dead, HP=0
				if (checkHealth() == true){
					break;
				}
				cout << "valid path" << endl;
				cout << map[rows][columns] << endl;
			}
			
			else{
				cout << "invalid letter, ";
				cout << map[rows][columns] << endl;
				--columns;
			}
		}

		else if (input == 'q'){
			exit(1);
		}
		else
			cout << "invalid letter, ";
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
void Critter::towerCheck(char map[5][5],int rows, int columns){
	//down tower
	if (map[rows+1][columns] == 'T'&& rows<4){
	//	this->hitPoints -= Wave::towerDamage;
		cout << "Critter HP= " << hitPoints << endl;
	}
	//right tower
	if (map[rows][columns +1] == 'T'&& columns<4){
	//	this->hitPoints -= Wave::towerDamage;
		cout << "Critter HP= " << hitPoints <<endl;
	}
	//up tower
	if (map[rows-1][columns] == 'T'&& rows>0){
	//	this->hitPoints -= Wave::towerDamage;
		cout << "Critter HP= " << hitPoints << endl;
	}
	//left tower
	if (map[rows][columns-1] == 'T'&& columns >0){
	//	this->hitPoints -= Wave::towerDamage;
		cout << "Critter HP= " << hitPoints << endl;
	}

}