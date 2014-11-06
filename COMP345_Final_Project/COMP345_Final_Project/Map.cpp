#include <iostream>
#include "Map.h"
#include <vector>
#include <fstream>
#include <string>
using namespace std;
ofstream file;

/*******************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//COMP345 - assignment 1
//October 17, 2014
//
//This is the map class in order to create maps for the Tower defense game.
//
/*******************************************************************************************************************/

Map::Map() {
	width = 0;
	height = 0;
}

Map::Map(int w, int h, string name) :
width(w),
height(h),
mapName(name){
	filePathName = "Path/" + mapName + "_Path.txt";
	fileMapName = "map/" + mapName + "_map.txt";

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
	if (ifstream(filePathName.c_str())) {
		cout << "file exist";
		file.open(filePathName, ios::app);
	}
	else {
		cout << "file not exist";
		file.open(filePathName);
	}
		

	cells[coordY][coordX].setType(gridType);
	if (gridType == GridType::START || gridType == GridType::PATH){
		file << coordX << "," << coordY << endl;
	}

	file.close();
}

void Map::printMap() const {
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			switch (cells[i][j].getType()) {
			case GridType::SCENERY:
				cout << " - ";
				break;
			case GridType::START:
				cout << " S ";
				break;
			case GridType::END:
				cout << " E ";
				break;
			case GridType::PATH:
				cout << " 0 ";
				break;
			}
		}
		cout << endl;
	}
	cout << endl;
}

int Map::calcNumNeighbourPath(int coordX, int coordY) const {
	int numOfNeighbour = 0; //Used to determine the number of scenery cells that are around the current cell
	if (coordY == 0)
		//At the top of the map
		numOfNeighbour = cells[coordY + 1][coordX].getType() == GridType::SCENERY ? numOfNeighbour : numOfNeighbour + 1;
	else if (coordY == (height - 1))
		//At the bottom of the map
		numOfNeighbour = cells[coordY - 1][coordX].getType() == GridType::SCENERY ? numOfNeighbour : numOfNeighbour + 1;
	else {
		numOfNeighbour = cells[coordY - 1][coordX].getType() == GridType::SCENERY ? numOfNeighbour : numOfNeighbour + 1;
		numOfNeighbour = cells[coordY + 1][coordX].getType() == GridType::SCENERY ? numOfNeighbour : numOfNeighbour + 1;
	}

	if (coordX == 0)
		//On the far left side of the map
		numOfNeighbour = cells[coordY][coordX + 1].getType() == GridType::SCENERY ? numOfNeighbour : numOfNeighbour + 1;
	else if (coordX == (width - 1))
		//On the far right side of the map
		numOfNeighbour = cells[coordY][coordX - 1].getType() == GridType::SCENERY ? numOfNeighbour : numOfNeighbour + 1;
	else {
		numOfNeighbour = cells[coordY][coordX + 1].getType() == GridType::SCENERY ? numOfNeighbour : numOfNeighbour + 1;
		numOfNeighbour = cells[coordY][coordX - 1].getType() == GridType::SCENERY ? numOfNeighbour : numOfNeighbour + 1;
	}

	return numOfNeighbour;
}

Map::~Map(){

}

int Map::tracePathX(int PathCoordX, int PathCoordXRequest, int PathCoordY) {
	if (!(PathCoordXRequest > -1 && PathCoordXRequest < width))
		std::cout << "\nUnable to move towards this direction since the Path will be out of the map.\n";
	else if (calcNumNeighbourPath(PathCoordXRequest, PathCoordY) > 1)
		std::cout << "\nUnable to move towards this direction since either the Path is already traced, or it is close to an " <<
		"existent Path.\n";
	else if (cells[PathCoordY][PathCoordXRequest].getType() == GridType::START)
		std::cout << "\nUnable to move towards this directions since it is the start point";
	else {
		//Inserting the Path on the map and then updating the X coordinate for the next Path to trace
		//cells[PathCoordY][PathCoordXRequest].setType(GridType::PATH);
		setCellType(PathCoordXRequest, PathCoordY, GridType::PATH);
		PathCoordX = PathCoordXRequest;
	}
	return PathCoordX;
}

int Map::tracePathY(int PathCoordX, int PathCoordY, int PathCoordYRequest) {
	if (!(PathCoordYRequest > -1 && PathCoordYRequest < height))
		std::cout << "\nUnable to move towards this direction since the Path will be out of the map.\n";
	else if (calcNumNeighbourPath(PathCoordX, PathCoordYRequest) > 1)
		std::cout << "\nUnable to move towards this direction since either the Path is already traced, or it is close to an " <<
		"existent Path.\n";
	else if (cells[PathCoordYRequest][PathCoordX].getType() == GridType::START)
		std::cout << "\nUnable to move towards this directions since it is the start point";
	else {
		//Inserting the Path on the map and then updating the Y coordinate for the next Path to trace
		//cells[PathCoordYRequest][PathCoordX].setType(GridType::PATH);
		setCellType(PathCoordX, PathCoordYRequest, GridType::PATH);
		PathCoordY = PathCoordYRequest;
	}

	return PathCoordY;
}

void Map::insertCoord(int& coordX, int& coordY, GridType gridType) {
	//Used to determine if user input is valid
	bool validInput = false;
	//Used to determine if system outputs for the case of start point, critters or Towers
	string type = (gridType == GridType::START ? "start point" : (gridType == GridType::CRITTER ? "critter" : "tower"));
	while (!validInput) {
		//Prompting user to enter the x and y coordinates of the element to insert on the map
		std::cout << "\nEnter the coordinates of the " << type << " to be added on the map." << endl;
		std::cout << "Coordinate X: ";
		cin >> coordX;
		std::cout << "Coordinate Y: ";
		cin >> coordY;
		//Validating the x and y coordinates entered by user
		if (coordX < width && coordX > -1 && coordY < height && coordY > -1) {
			switch (gridType) {
			case GridType::CRITTER:
				//critter insertion validation
				if (cells[coordY][coordX].getType() == GridType::PATH)
					validInput = true;
				else if (cells[coordY][coordX].getType() == GridType::CRITTER)
					std::cout << "You have already inserted a critter on these coordinates";
				else
					std::cout << "Unable to place critter in these coordinates because it is not a Path. Please try again.\n\n";
				break;
			case GridType::TOWER:
				//Tower insertion validation
				if (cells[coordY][coordX].getType() == GridType::SCENERY)
					validInput = true;
				else if (cells[coordY][coordX].getType() == GridType::TOWER)
					std::cout << "You have already inserted a tower on these coordinates";
				else
					std::cout << "Unable to place tower in these coordinates because it is a Path. Please try again.\n\n";
				break;
			default:
				//START point validated
				validInput = true;
				break;
			}
		}
		else
			std::cout << "Either your X coordinate or your Y coordinate is invalid. Please try again.\n\n";
	}

	system("cls");

	//Adding the element on the map and then display the map
	setCellType(coordY, coordX, gridType);
	//cells[coordY][coordX].set(gridType);
	printMap();
}

void Map::addCritterOrTower(int& coordX, int& coordY, GridType gridType) {
	char moreInput; //Used to keep track for if the user wants to create more towers/critters
	do {
		//Inserting the critter or tower on the map
		insertCoord(coordX, coordY, gridType);
		//Prompting the user to decide whether to add more critters or not
		std::cout << "Would you like to create more " << (gridType == GridType::CRITTER ? "critter" : "tower") <<
			"? (Enter 'y' for yes and 'n' for no): ";
		cin >> moreInput;
	} while (moreInput == 'y');
}

bool Map::validateEndPath(int coordX, int coordY) {
	bool isValidated = false;
	if (cells[coordY][coordX].getType() == GridType::START)
		cout << "Unable to end the Path at the start point. Try again." << endl;
	else if (isNeighbourStart(coordX, coordY))
		cout << "Unable to end the Path here because there are no Path between the start and end point" << endl;
	else
		isValidated = true;
	return isValidated;
}

bool Map::isNeighbourStart(int coordX, int coordY) {
	bool isNeighbourSTART;
	if (coordY == 0)
		//At the top of the map
		isNeighbourSTART = cells[coordY + 1][coordX].getType() == GridType::START ? true : false;
	else if (coordY == (height - 1))
		//At the bottom of the map
		isNeighbourSTART = cells[coordY - 1][coordX].getType() == GridType::START ? true : false;
	else {
		isNeighbourSTART = cells[coordY - 1][coordX].getType() == GridType::START ? true : false;
		isNeighbourSTART = cells[coordY + 1][coordX].getType() == GridType::START ? true : false;
	}

	if (coordX == 0)
		//On the far left side of the map
		isNeighbourSTART = cells[coordY][coordX + 1].getType() == GridType::START ? true : false;
	else if (coordX == (width - 1))
		//On the far right side of the map
		isNeighbourSTART = cells[coordY][coordX - 1].getType() == GridType::START ? true : false;
	else {
		isNeighbourSTART = cells[coordY][coordX + 1].getType() == GridType::START ? true : false;
		isNeighbourSTART = cells[coordY][coordX - 1].getType() == GridType::START ? true : false;
	}

	return isNeighbourSTART;
}

void Map::storeMapTxt() {
	file.open("map/" + mapName.append("_map.txt"));
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			switch (cells[i][j].getType()) {
			case GridType::SCENERY:
				file << "0" << " ";
				break;
			case GridType::START:
				file << "1" << " ";
				break;
			case GridType::END:
				file << "3" << " ";
				break;
			case GridType::PATH:
				file << "2" << " ";
				break;
			}
		}
		file << endl;
	}

	file.close();
}