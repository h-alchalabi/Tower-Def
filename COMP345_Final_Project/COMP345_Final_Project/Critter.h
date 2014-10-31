#pragma once
#include <iostream>
using namespace std;
class Critter
{
public:
	Critter();
	Critter(int Wave);
	int getLevel();
	void setLevel(int level);
	int getHitPoints();
	void setHitPoints(int hitPoints);
	int getSpeed();
	void setSpeed(int speed);
	int getReward();
	void setReward(int reward);
	int getPositionX();
	int getPositionY();
	bool checkHealth();
	void choosePath(char map[5][5]);
	void incrementPositionX();
	void incrementPositionY();
	void towerCheck(char map[5][5], int rows, int columns);
	
	~Critter();

private:
	int reward;
	int hitPoints;
	int speed;
	int level;
	int positionX, positionY;
	char input;
	int rows, columns;
	int towerDamage;
};
