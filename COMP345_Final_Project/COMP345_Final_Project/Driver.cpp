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
int main() {
	int mapWidth, mapHeight;    //Map dimensions
	Map gameMap;				//The map that will be created for the user
	int pathCoordX, pathCoordY; //Used to keep track of the path traced by user
	int coordX, coordY;			//Coordination of the start point, towers, or critters to be added on the map
	char pathDirection = 's';   //Used to verify if user wants to end path tracing
	ofstream fileOpen("Path.txt");
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

	gameMap = Map(mapWidth, mapHeight);
	gameMap.printMap();
	//Inserting the start point
	gameMap.insertCoord(coordX, coordY, GridType::Start);

	//Prompting the user to trace the path on the map
	pathCoordX = coordX;
	pathCoordY = coordY;
	fileOpen << pathCoordX << "," << pathCoordY << endl;
	while (pathDirection != 'e') {
		cout << "\nEnter the next path of your map ('w' for up, 's' for down, 'a' for left, 'd' for right, and 'e' to end your path): " << endl;
		cin >> pathDirection;
		system("cls");
		switch (pathDirection) {
		case 'w':
			//Going up
			pathCoordY = gameMap.tracePathY(pathCoordX, pathCoordY, pathCoordY - 1);
			fileOpen << pathCoordX << "," << pathCoordY << endl;
			break;
		case 's':
			//Going down
			pathCoordY = gameMap.tracePathY(pathCoordX, pathCoordY, pathCoordY + 1);
			fileOpen << pathCoordX << "," << pathCoordY << endl;
			break;
		case 'a':
			//Going left
			pathCoordX = gameMap.tracePathX(pathCoordX, pathCoordX - 1, pathCoordY);
			fileOpen << pathCoordX << "," << pathCoordY << endl;
			break;
		case 'd':
			//Going right
			pathCoordX = gameMap.tracePathX(pathCoordX, pathCoordX + 1, pathCoordY);
			fileOpen << pathCoordX << "," << pathCoordY << endl;
			break;
		case 'e':
			//End the path
			if (!gameMap.validateEndPath(pathCoordX, pathCoordY)) {
				pathDirection = 's';
			} else {
				gameMap.setCellType(pathCoordX, pathCoordY, GridType::End);
				fileOpen << pathCoordX << "," << pathCoordY << endl;
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
	gameMap.addCritterOrTower(coordX, coordY, GridType::Tower);
	//Inserting critters on the map
	gameMap.addCritterOrTower(coordX, coordY, GridType::Critter);

	cout << "\nYour map has been successfully created\n";
	return 0;
}