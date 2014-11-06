#include "Map.h"
#include <iostream>
//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>

//using namespace sf;
using namespace std;

/***************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//Amanda Tom -
//Awais Ali -
//Haani Al-Chalabi -
//Van Do - 
//Djamil Francis - 
//
//COMP345 - Final Project
//
//
//Main application
//
/****************************************************************************************************************/

void openMapTxt(string mapName, string mapFileName);

int main() {
	int mapWidth, mapHeight;    //Map dimensions
	Map gameMap;				//The map that will be created for the user
	int pathCoordX, pathCoordY; //Used to keep track of the path traced by user
	int coordX, coordY;			//Coordination of the start point, towers, or critters to be added on the map
	char pathDirection = 's';   //Used to verify if user wants to end path tracing
	char mapOption;
	string mapName;
	string mapFileName;
	bool validInput = false;
	
	//Prompting the user whether he/she wants to create a map or use an existing map
	do {
		cout << "Welcome to the tower defense game. Enter the following to select an option:" << endl <<
			"c -> Create a map" << endl << "u -> Use an existent map" << endl;
		cin >> mapOption;
		
		if (!(mapOption == 'c' || mapOption == 'u'))
			cout << "What you entered is invalid. Please try again.\n\n";
	} while (!(mapOption == 'c' || mapOption == 'u'));
	system("cls");

	if (mapOption == 'c') {
		//Prompting the user to enter the name of the map
		cout << "Enter the name of your map: ";
		cin >> mapName;
		system("cls");

		//Prompting the user to enter the dimensions of the map, create the map based on the input, and then display it
		do {
			//Minimum width user allowed to enter: 5
			cout << "Enter the width of the map (minimum length of 5): ";
			cin >> mapWidth;
		} while (mapWidth < 5);
		do {
			//Minimum height user allowed to enter: 5
			cout << "Enter the height of the map (minimum length of 5): ";
			cin >> mapHeight;
		} while (mapHeight < 5);

		system("cls");

		gameMap = Map(mapWidth, mapHeight, mapName);
		gameMap.printMap();
		//Inserting the start point
		gameMap.insertCoord(coordX, coordY, GridType::START);

		//Prompting the user to trace the path on the map
		pathCoordX = coordX;
		pathCoordY = coordY;
		while (pathDirection != 'e') {
			cout << "\nEnter the next path of your map ('w' for up, 's' for down, 'a' for left, 'd' for right, and 'e' to end your path): " << endl;
			cin >> pathDirection;
			system("cls");
			switch (pathDirection) {
			case 'w':
				//Going up
				pathCoordY = gameMap.tracePathY(pathCoordX, pathCoordY, pathCoordY - 1);
				break;
			case 's':
				//Going down
				pathCoordY = gameMap.tracePathY(pathCoordX, pathCoordY, pathCoordY + 1);
				break;
			case 'a':
				//Going left
				pathCoordX = gameMap.tracePathX(pathCoordX, pathCoordX - 1, pathCoordY);
				break;
			case 'd':
				//Going right
				pathCoordX = gameMap.tracePathX(pathCoordX, pathCoordX + 1, pathCoordY);
				break;
			case 'e':
				//End the path
				if (!gameMap.validateEndPath(pathCoordX, pathCoordY)) {
					pathDirection = 's';
				}
				else {
					gameMap.setCellType(pathCoordX, pathCoordY, GridType::END);
				}
				break;
			default:
				//Invalid input
				cout << "What you entered was invalid. Try again" << endl;
				break;
			}

			//Updating the map to the user with the path that was traced
			gameMap.printMap();
		}
		//Inserting towers on the map
		//gameMap.addCritterOrTower(coordX, coordY, GridType::Tower);
		//Inserting critters on the map
		//gameMap.addCritterOrTower(coordX, coordY, GridType::Critter);

		gameMap.storeMapTxt();

		cout << "\nYour map has been successfully created\n";
	} else {
		//Prompt user to select one of the existent map
		do {
			cout << "Enter the name of the map that you want to load: ";
			cin >> mapName;
			mapFileName = "map/" + mapName + "_map.txt";
			if (ifstream(mapFileName.c_str())) {
				validInput = true;
			} else {
				cout << "This map does not exist. Please try again\n\n";
			}
		} while (!validInput);

		openMapTxt(mapName, mapFileName);
	}
	return 0;
}

void openMapTxt(string mapName, string mapFileName) {
	Map gameMap;
	ifstream mapFile(mapFileName);
	unsigned char ch;
	int mapWidth = 0;
	int mapHeight = 0;

	while (!mapFile.eof()) {
		if (mapFile.get() == '\n')
			mapWidth++;
	}

	gameMap = Map(mapWidth, mapHeight, mapName);
	cout << gameMap.getHeight() << " " << gameMap.getWidth();
	//mapFile.seekg(0, ios::beg);

	/*while (!mapFile.eof()) {
		ch = mapFile.get();
		switch (ch) {
			case '0':

		}
	}*/
}