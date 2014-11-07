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
}

void TowerController::removeTower(int index, Map& map){
	sellTower(&towerList.at(index));
	int x =	towerList.at(index).getPositionX();
	int y = towerList.at(index).getPositionY();
	map.setCellType(x, y, GridType::SCENERY, FileAction::LOAD);
	towerList.erase(towerList.begin() + input);
	towerList.shrink_to_fit();
}

void TowerController::upgradeTower(int index){
	ss2_ptr->money -= towerList.at(index).getUpgradeCost();
	towerList.at(index).setUpgradeStats();
}
int TowerController::getPrice(int type){
	if (type == 1)
		return 175;
	return 150;
}
void TowerController::purchaseTower(int type){
	ss2_ptr->money -= getPrice(type);
}
void TowerController::sellTower(Tower* tower){
	ss2_ptr->money += tower->getResellVal();
}

Tower* TowerController::getTower(int i){
	return &(towerList.at(i));
}
int TowerController::size(){
	return towerList.size();
}