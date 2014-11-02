#pragma once
#include <iostream>
enum CritterType { Normal, Fast, Slow };
using namespace std;
class Critter
{
private:
	int reward;
	int hitPoints;
	int speed;
	int level;
	int positionX, positionY;
	char input;
	int rows, columns;
	int towerDamage;
	CritterType type;
	int deploymentTime;

public:
	Critter();
	Critter(int wave, CritterType type, string mapPath);
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
	float getDeploymentTime();
	~Critter();


};
