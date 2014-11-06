#include "MapGrid.h"
#include <iostream>
 
/*******************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//COMP345 - assignment 1
//October 17, 2014
//
//The map grid class which contains information of each grid on the tower defense game map.
//
/*******************************************************************************************************************/

MapGrid::MapGrid() {
	coordX = 0;
	coordY = 0;
	gridType = GridType::SCENERY;
}

MapGrid::~MapGrid() {}

int MapGrid::getCoordX() const {
	return coordX;
}

int MapGrid::getCoordY() const {
	return coordY;
}

GridType MapGrid::getType() const {
	return gridType;
}

void MapGrid::setCoordX(int x) {
	coordX = x;
}

void MapGrid::setCoordY(int y) {
	coordY = y;
}

void MapGrid::setType(GridType t) {
	gridType = t;
}

