#include <iostream>
#include "Map.h"
#include <vector>
#include <fstream>
#include <string>
using namespace std;
 
/*******************************************************************************************************************/
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
	ofstream file("Map.txt");
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			switch (cells[i][j].getType()) {
				case GridType::Scenery:
					file << "0" << " ";
					cout << " - ";
					break;
				case GridType::Start:
					file << "1" << " ";
					cout << " S ";
					break;
				case GridType::End:
					file << "3" << " ";
					cout << " E ";
					break;
				case GridType::Path:
					file << "2" << " ";
					cout << " 0 ";
					break;
				case GridType::Tower:
					cout << " T ";
					break;
				case GridType::Critter:
					cout << " C ";
			}
		}
		file << endl;
		cout << endl;
	}
	cout << endl;
}

int Map::calcNumNeighbourPath(int coordX, int coordY) const {
	int numOfNeighbour = 0; //Used to determine the number of scenery cells that are around the current cell
	if (coordY == 0)
		//At the top of the map
		numOfNeighbour = cells[coordY + 1][coordX].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
	else if (coordY == (height - 1))
		//At the bottom of the map
		numOfNeighbour = cells[coordY - 1][coordX].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
	else {
		numOfNeighbour = cells[coordY - 1][coordX].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
		numOfNeighbour = cells[coordY + 1][coordX].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
	}

	if (coordX == 0)
		//On the far left side of the map
		numOfNeighbour = cells[coordY][coordX + 1].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
	else if (coordX == (width - 1))
		//On the far right side of the map
		numOfNeighbour = cells[coordY][coordX - 1].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
	else {
		numOfNeighbour = cells[coordY][coordX + 1].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
		numOfNeighbour = cells[coordY][coordX - 1].getType() == GridType::Scenery ? numOfNeighbour : numOfNeighbour + 1;
	}

	return numOfNeighbour;
}

Map::~Map(){}

int Map::tracePathX(int pathCoordX, int pathCoordXRequest, int pathCoordY) {
	if (!(pathCoordXRequest > -1 && pathCoordXRequest < width))
		std::cout << "\nUnable to move towards this direction since the path will be out of the map.\n";
	else if (calcNumNeighbourPath(pathCoordXRequest, pathCoordY) > 1)
		std::cout << "\nUnable to move towards this direction since either the path is already traced, or it is close to an " <<
		"existent path.\n";
	else if (cells[pathCoordY][pathCoordXRequest].getType() == GridType::Start)
		std::cout << "\nUnable to move towards this directions since it is the start point";
	else {
		//Inserting the path on the map and then updating the X coordinate for the next path to trace
		cells[pathCoordY][pathCoordXRequest].setType(GridType::Path);
		pathCoordX = pathCoordXRequest;
	}
	return pathCoordX;
}

int Map::tracePathY(int pathCoordX, int pathCoordY, int pathCoordYRequest) {
	if (!(pathCoordYRequest > -1 && pathCoordYRequest < height))
		std::cout << "\nUnable to move towards this direction since the path will be out of the map.\n";
	else if (calcNumNeighbourPath(pathCoordX, pathCoordYRequest) > 1)
		std::cout << "\nUnable to move towards this direction since either the path is already traced, or it is close to an " <<
		"existent path.\n";
	else if (cells[pathCoordYRequest][pathCoordX].getType() == GridType::Start)
		std::cout << "\nUnable to move towards this directions since it is the start point";
	else {
		//Inserting the path on the map and then updating the Y coordinate for the next path to trace
		cells[pathCoordYRequest][pathCoordX].setType(GridType::Path);
		pathCoordY = pathCoordYRequest;
	}

	return pathCoordY;
}

void Map::insertCoord(int& coordX, int& coordY, GridType gridType) {
	//Used to determine if user input is valid
	bool validInput = false;
	//Used to determine if system outputs for the case of start point, critters or towers
	string type = (gridType == GridType::Start ? "start point" : (gridType == GridType::Critter ? "critter" : "tower"));
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
			case GridType::Critter:
				//Critter insertion validation
				if (cells[coordY][coordX].getType() == GridType::Path)
					validInput = true;
				else if (cells[coordY][coordX].getType() == GridType::Critter)
					std::cout << "You have already inserted a critter on these coordinates";
				else
					std::cout << "Unable to place critter in these coordinates because it is not a path. Please try again.\n\n";
				break;
			case GridType::Tower:
				//Tower insertion validation
				if (cells[coordY][coordX].getType() == GridType::Scenery)
					validInput = true;
				else if (cells[coordY][coordX].getType() == GridType::Tower)
					std::cout << "You have already inserted a tower on these coordinates";
				else
					std::cout << "Unable to place tower in these coordinates because it is a path. Please try again.\n\n";
				break;
			default:
				//Start point validated
				validInput = true;
				break;
			}
		}
		else
			std::cout << "Either your X coordinate or your Y coordinate is invalid. Please try again.\n\n";
	}

	system("cls");

	//Adding the element on the map and then display the map
	cells[coordY][coordX].setType(gridType);
	printMap();
}

void Map::addCritterOrTower(int& coordX, int& coordY, GridType gridType) {
	char moreInput; //Used to keep track for if the user wants to create more towers/critters
	do {
		//Inserting the critter or tower on the map
		insertCoord(coordX, coordY, gridType);
		//Prompting the user to decide whether to add more critters or not
		std::cout << "Would you like to create more " << (gridType == GridType::Critter ? "critter" : "tower") <<
			"? (Enter 'y' for yes and 'n' for no): ";
		cin >> moreInput;
	} while (moreInput == 'y');
}

bool Map::validateEndPath(int pathCoordX, int pathCoordY) {
	bool isValidated = false;
	if (cells[pathCoordY][pathCoordX].getType() == GridType::Start) {
		cout << "Unable to end the path at the start point. Try again." << endl;
	}
	else if (cells[pathCoordY - 1][pathCoordX].getType() == GridType::Start ||
		cells[pathCoordY + 1][pathCoordX].getType() == GridType::Start ||
		cells[pathCoordY][pathCoordX - 1].getType() == GridType::Start ||
		cells[pathCoordY][pathCoordX + 1].getType() == GridType::Start) {
		cout << "Unable to end the path here because there are no path between the start and end point" << endl;
	} else {
		isValidated = true;
	}
	return isValidated;
}