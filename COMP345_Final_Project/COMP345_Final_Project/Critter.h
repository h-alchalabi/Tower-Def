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
	const string delimiter = ",";
	int x, y;
	string line, token;
	ifstream* file;

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
	void move();
	string getMapPath();
	void setPositionX(int positionX);
	void setPositionY(int positionY);
	void towerCheck(char map[5][5], int rows, int columns);
	float getDeploymentTime();
	void handleCollision(Entity& e);
	~Critter();


};
