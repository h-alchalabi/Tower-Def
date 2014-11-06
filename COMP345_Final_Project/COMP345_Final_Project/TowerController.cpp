#include "TowerController.h"
#include "Tower.h"

#include <vector>

Tower* tower;
vector<Tower>::iterator i;
int input;
int index;

void TowerController::addTower(int type, int posX, int posY){
	tower = new Tower(type);
	//Need to tell the tower where it is placed on the map
	towerList.push_back(*tower);
	cout << "You purchased a " << tower->getType() << endl;
};

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
};

void TowerController::upgradeTower(Tower* tower){
	cout << "Current number of towers owned: " << towerList.size() << endl;
	index = 0;
	for (i = towerList.begin(); i != towerList.end(); ++i){
		cout << "Index " << index << "\tType: " << i->getType() <<
			"\tResell value: " << i->getResellVal() << endl;
		++index;
	}
	cout << "\nTo upgrade a tower, input its index." << endl;
	cin >> input;

	towerList.at(index).setUpgradeStats();
}

void TowerController::printTowerStats(Tower* tower){
	cout << "\n Tower Stats" <<
			"\n========================" <<
			"\nType: " << tower->getType() <<
			"\nBuying Cost: " << tower->getBuyCost() <<
			"\nResell Vall: " << tower->getResellVal() <<
			"\nAttack Range: " << tower->getRange() <<
			"\nPower: " << tower->getAtk() <<
			"\nRate of Fire Attack: " << tower->getRate() <<
			"\nUpgrade Cost: " << tower->getUpgradeCost() << endl;
}