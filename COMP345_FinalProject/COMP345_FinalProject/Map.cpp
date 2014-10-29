#include <iostream>
#include "Map.h"
#include <vector>
using namespace std;

/*****************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//COMP345 - assignment 1
//October 17, 2014
//
//This is the map class in order to create maps for the tower defense game.
//
/*******************************************************************************************************************/

Map::Map() {
	width = 0;
	height = 0;
}

Map::Map(int w, int h) :
width(w),
height(h) {
	//Creating multidimensional vector for the map
	cells.resize(height);
	for (int i = 0; i < height; i++) {
		cells[i].resize(width);
	}
}

int Map::getWidth() const {
	return width;
}

int Map::getHeight() const {
	return height;
}

MapGrid Map::getCell(int coordX, int coordY) const {
	return cells[coordY][coordX];
}

void Map::setWidth(int w) {
	width = w;
}

void Map::setHeight(int h) {
	height = h;
}

void Map::setCellType(int coordX, int coordY, GridType gridType) {
	cells[coordY][coordX].setType(gridType);
}

void Map::printMap() const {
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			switch (cells[i][j].getType()) {
				case GridType::Scenery:
					cout << " - ";
					break;
				case GridType::Start:
					cout << " S ";
					break;
				case GridType::End:
					cout << " E ";
					break;
				case GridType::Path:
					cout << " 0 ";
					break;
				case GridType::Tower:
					cout << " T ";
					break;
				case GridType::Critter:
					cout << " C ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

int Map::calcNumNeighbourPath(int coordX, int coordY, int mapWidth, int mapHeight) const {
	int numOfNeighbour = 0; //Used to determine the number of scenery cells that are around the current cell
	if (coordY == 0)
		//At the top of the map
		numOfNeighbour = cells[coordY + 1][coordX].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
	else if (coordY == (mapHeight - 1))
		//At the bottom of the map
		numOfNeighbour = cells[coordY - 1][coordX].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
	else {
		numOfNeighbour = cells[coordY - 1][coordX].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
		numOfNeighbour = cells[coordY + 1][coordX].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
	}

	if (coordX == 0)
		//On the far left side of the map
		numOfNeighbour = cells[coordY][coordX + 1].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
	else if (coordX == (mapWidth - 1))
		//On the far right side of the map
		numOfNeighbour = cells[coordY][coordX - 1].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
	else {
		numOfNeighbour = cells[coordY][coordX + 1].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
		numOfNeighbour = cells[coordY][coordX - 1].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
	}

	return numOfNeighbour;
}

Map::~Map(){}
