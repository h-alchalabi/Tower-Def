#pragma once
#include <iostream>
#include "Entity.h"
#include <sstream>
#include<fstream>
enum CritterType { Normal, Fast, Slow };
using namespace std;
class Critter : public Entity
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
	string mapPath;
	CritterType type;
	int deploymentTime;
	int x, y;
	int steps;
public:
	Critter();
	Critter(int wave, CritterType type, string mapPath);
	int getLevel();
	void setLevel(int level);
	int getSteps();
	int getHitPoints();
	void setHitPoints(int hitPoints);
	int getSpeed();
	void setSpeed(int speed);
	int getReward();
	void setReward(int reward);
	int getPositionX();
	int getPositionY();
	bool checkHealth();
	void setSteps(int steps);
	void move(vector <int> coordinates);
	int* previousPos(vector<int> coordinates);
	void setPositionX(int positionX);
	void setPositionY(int positionY);
	float getDeploymentTime();
	void handleCollision(Entity& e);
	~Critter();


};
