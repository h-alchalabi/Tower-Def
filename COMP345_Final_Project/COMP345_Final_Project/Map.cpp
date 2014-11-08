#include <iostream>
#include "Map.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
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
	filePathName = "path/" + mapName + "_path.txt";
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

string Map::getMapName() const {
	return mapName;
}

string Map::getFileMapName() const {
	return fileMapName;
}

string Map::getFilePathName() const {
	return filePathName;
}

void Map::setWidth(int w) {
	width = w;
}

void Map::setHeight(int h) {
	height = h;
}

void Map::setCellType(int coordX, int coordY, GridType gridType, FileAction fileAction) {
	cells[coordY][coordX].setType(gridType);

	//Storing the path in a file
	if (fileAction == FileAction::STORE) {
		if (ifstream(filePathName.c_str())) {
			file.open(filePathName, ios::app);
		}
		else {
			file.open(filePathName);
		}

		if (gridType == GridType::START || gridType == GridType::PATH){
			file << coordX << "," << coordY << endl;
		}

		file.close();
	}
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
			case GridType::CRITTER:
				cout << " C ";
				break;
			case GridType::TOWER:
				cout << " T ";
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
		setCellType(PathCoordXRequest, PathCoordY, GridType::PATH, FileAction::STORE);
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
		setCellType(PathCoordX, PathCoordYRequest, GridType::PATH, FileAction::STORE);
		PathCoordY = PathCoordYRequest;
	}

	return PathCoordY;
}

void Map::insertCoord(int& coordX, int& coordY, GridType gridType, FileAction fileAction) {
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
				//start point validated
				validInput = true;
				break;
			}
		}
		else
			std::cout << "Either your X coordinate or your Y coordinate is invalid. Please try again.\n\n";
	}

	system("cls");

	//Adding the element on the map and then display the map
	setCellType(coordX, coordY, gridType, fileAction);
	//cells[coordY][coordX].set(gridType);
	printMap();
}

void Map::addCritterOrTower(int& coordX, int& coordY, GridType gridType) {
	char moreInput; //Used to keep track for if the user wants to create more towers/critters
	do {
		//Inserting the critter or tower on the map
		insertCoord(coordX, coordY, gridType, FileAction::STORE);
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
	//file.open("map/" + mapName.append("_map.txt"));
	file.open(fileMapName);
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

void Map::resizeMap(int width, int height) {
	//Update the width and height to the map object
	setWidth(width);
	setHeight(height);

	//Resize the vector inside the map
	cells.resize(height);
	for (int i = 0; i < height; i++) {
		cells[i].resize(width);
	}
}

void Map::restartPaths(int coordX, int coordY) {
	//Used to retrieve the x and y coordinates of the path stored in the path file
	int x, y;
	//Used to retrieve the next line in the file
	string line;
	//Used to retrieve the x and y coordinates of each line retrieved from the file
	string token;
	string delimiter = ",";
	//Used to store the x and y coordinates that are not going to be removed
	queue<int> coordinates;
	//Used to read and overwrite the existent path file
	fstream file(filePathName);
	//Used to check if the current file reader cursor is at the selected coordinates
	CoordListLocation coordListLocation = CoordListLocation::BEFORE_SELECTED;

	while (!file.eof()) {
		//Retrieve the x and y coordinates of the current line
		file >> line;
		token = line.substr(0, line.find(delimiter));
		istringstream(token) >> x;
		token = line.substr(line.find(delimiter) + 1);
		istringstream(token) >> y;

		//File reader cursor reads the coordinate selected by the user
		if (x == coordX && y == coordY) {
			coordListLocation = CoordListLocation::SELECTED;
		}

		if (coordListLocation == CoordListLocation::BEFORE_SELECTED) {
			//Store the coordinates that are not going to be removed
			coordinates.push(x);
			coordinates.push(y);
		}
		else if (coordListLocation == CoordListLocation::SELECTED)
			coordListLocation = CoordListLocation::AFTER_SELECTED;
		else
			//Remove the coordinates after the selected coordinates on the map
			cells[y][x].setType(GridType::SCENERY);
	}
	file.close();

	//Overwrite the existent path file with the new path that was kept
	fstream file1(filePathName);
	string newCoordinates, x_str, y_str;
	bool doneTrunc = false;
	while (!doneTrunc) {
		/*
		x = coordinates.front();
		coordinates.pop();
		y = coordinates.front();
		coordinates.pop();
		newCoordinates = x + "," + y;
		file << newCoordinates << endl;
		*/
		file1 >> line;
		if (file1.eof()){
			break;
		}
		token = line.substr(0, line.find(delimiter));
		istringstream(token) >> x;
		istringstream(token) >> x_str;
		//coordinates.push_back(x);
		token = line.substr(line.find(delimiter) + 1);
		istringstream(token) >> y;
		istringstream(token) >> y_str;
		//coordinates.push_back(y);
		newCoordinates += (x_str + "," + y_str);
		newCoordinates += "\n";
		if (x == coordX && y == coordY){
			doneTrunc == true;
		}
		
	}
	file1.close();
	 
	file1.open(filePathName, std::fstream::out|std::fstream::trunc);
	file1 << newCoordinates;
	file1.close();
}