//#include "TowerController.h"
#include "Tower.h"
#include "SharedSingleton.h"
#include "Map.h"
#include <vector>

SharedSingleton* ss2_ptr = SharedSingleton::getInstance();

TowerController::TowerController(){
}
void TowerController::addTower(int type, int posX, int posY, Map& map){
	purchaseTower(type);
	tower = new Tower(type);
	map.insertCoord(posX, posY, GridType::TOWER, FileAction::LOAD);
	tower->setPostionX(posX);
	tower->setPostionY(posY);
	towerList.push_back(*tower); 
	//cout << "You purchased a " << tower->getType() << endl;
}

void TowerController::removeTower(Tower* tower){
	cout << "Current number of towers owned: " << towerList.size() << endl;
	index = 0;
	for (i = towerList.begin(); i != towerList.end(); ++i){
		cout << "Index " << index << "\tType: " << i->getType() <<
			"\tResell value: " << i->getResellVal() << endl;
		++index;
	}
	cout << "\nTo sell a tower, input its index." << endl;
	cin >> input;

	towerList.erase(towerList.begin() + input);
}

void TowerController::upgradeTower(Tower* tower){
	cout << "Current number of towers owned: " << towerList.size() << endl;
	index = 0;
	for (i = towerList.begin(); i != towerList.end(); ++i){
		cout << "Index " << index << "\tType: " << i->getType() <<
			"\tUpgrade Cost value: " << i->getUpgradeCost() << endl;
		++index;
	}
	cout << "\nTo upgrade a tower, input its index." << endl;
	cin >> input;

	towerList.at(index).setUpgradeStats();
}
int TowerController::getPrice(int type){
	if (type == 1)
		return 175;
	return 150;
}
void TowerController::purchaseTower(int type){
	cout << "good job" << endl;
	ss2_ptr->money -= getPrice(type);
}
void TowerController::sellTower(Tower* tower){
	ss2_ptr->money += tower->getResellVal();
}