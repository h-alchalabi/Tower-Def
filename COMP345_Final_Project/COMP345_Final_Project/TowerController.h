#pragma once
#include "Tower.h"
#include "Map.h"
//#include "SharedSingleton.h"
#include <vector>

class TowerController{
public:
	// constructor initialize the vector
	TowerController();
	// create and a tower to the list.
	void addTower(int type, int x, int y, Map& map);
	// remove a tower from the list, trim list to proper size.
	void removeTower(int index, Map& map);
	// upgrade a tower from the list
	void upgradeTower(int index);
	// return the pointer to the tower at the given index.
	Tower* getTower(int i);
	// return the list of towers.
	vector<Tower> getTowerList();
	//return money in bank
	int getMoney();
	//set money for sales
	void setMoney(int money);
	//manage the purchases of tower
	void purchaseTower(int type);
	//get price of tower type
	int getPrice(int type);
	//
	void sellTower(Tower* tower);
	//return true or false depending if purchase is possible
	bool purchaseVerif(int type);
	// get size of tower list
	int size();
private:
	vector<Tower> towerList;
	Tower* tower;
	vector<Tower>::iterator i;
	int input;
	int index;
}; 