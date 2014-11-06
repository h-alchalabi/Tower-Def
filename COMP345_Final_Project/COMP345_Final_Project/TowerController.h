#ifndef TOWERCONTROLLER_H
#define TOWERCONTROLLER_H

#include "Tower.h"
#include <vector>

class TowerController{
public:
	// constructor initialize the vector
	TowerController();
	// create and a tower to the list.
	void addTower(int type, int x, int y);
	// remove a tower from the list, trim list to proper size.
	void removeTower(Tower* tower);
	// upgrade a tower from the list
	void upgradeTower(Tower* tower);
	// print Tower stats of a single tower
	void printTowerStats(Tower* tower);
	// return the pointer to the tower at the given index.
	Tower* getTower(int i);
	// return the list of towers.
	vector<Tower> getTowerList();
private:
	vector<Tower> towerList;
};

#endif // !TOWERCONTROLLER_H
