#include "Map.h"
#include <iostream>
//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "Wave.h"
#include <windows.h>

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

void openMapTxt(string mapName, string mapFileName, Map& gameMap);
void mapCreateOrEdit(Map& gameMap);
void startGame(Map& gameMap);

int main() {
	Map gameMap;				//The map that will be created for the user
	char gameOption;            //Used to prompt user to select options throughout the game
	bool validInput = false;    //Used during input validation

	cout << "Welcome to the tower defense game.";
	Sleep(3000);

	do {
		//Prompting the user to choose between creating or editing the map, start the game, and exit the game
		system("cls");
		do {
			cout << "Please enter one of the following option:" << endl << "c -> Create or edit a map" << endl <<
				"s -> Start the game" << endl << "e -> Exit game\n";
			cin >> gameOption;

			if (!(gameOption == 'c' || gameOption == 's' || gameOption == 'e'))
				cout << "What you entered is invalid. Please try again.\n\n";
			else
				validInput = true;
		} while (!validInput);
		system("cls");

		if (gameOption == 'c')
			mapCreateOrEdit(gameMap);  //Creating or editing a map
		else if (gameOption == 's')
			startGame(gameMap);        //Starting the game
	} while (gameOption != 'e');

	//End of application
	cout << "See you soon!\n";
	return 0;
}

void mapCreateOrEdit(Map& gameMap) {
	int mapWidth, mapHeight;    //Map dimensions
	int pathCoordX, pathCoordY; //Used to keep track of the path traced by user
	int coordX, coordY;			//Coordination of the start point, towers, or critters to be added on the map
	char pathDirection = 's';   //Used to verify if user wants to end path tracing
	char gameOption;            //Used to prompt user to select options throughout the game
	string mapName;             //The name of the map to be loaded or to be stored
	string mapFileName;         //Used to create the text file from the file name entered by user
	bool validInput = false;    //Used during input validation

	//Prompting the user whether he/she wants to create a map or use an existing map
	do {
		cout << "Enter the following to select an option:" << endl 
			<< "c -> Create a map" << endl 
			<< "x -> Edit an existent map" << endl
			<< "t -> Add towers to an existing map" << endl
			<< "e -> Return to Main Menu";
		cin >> gameOption;

		if (!(gameOption == 'c' || gameOption == 'x' || gameOption == 't' || gameOption == 'e'))
			cout << "What you entered is invalid. Please try again.\n\n";
		else
			validInput = true;

	} while (!validInput);
	system("cls");

	if (gameOption == 'c') {
		//Prompting the user to enter the name of the map
		validInput = false;
		do {
			cout << "Enter the name of your map: ";
			cin >> mapName;
			mapFileName = "map/" + mapName + "_map.txt";
			if (ifstream(mapFileName.c_str()))
				cout << "This map already exists. Please enter another name\n\n";
			else
				validInput = true;
		} while (!validInput);
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
					gameMap.setCellType(pathCoordX, pathCoordY, GridType::END, FileAction::STORE);
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

		gameMap.storeMapTxt();
		
		cout << "\nYour map has been successfully created\n";
	}
	else {
		//Prompt user to select one of the existent map
		do {
			cout << "Enter the name of the map that you want to edit: ";
			cin >> mapName;
			mapFileName = "map/" + mapName + "_map.txt";
			if (ifstream(mapFileName.c_str()))
				validInput = true;
			else
				cout << "This map does not exist. Please try again\n\n";
		} while (!validInput);

		openMapTxt(mapName, mapFileName, gameMap);
	}
}

void startGame(Map& gameMap) {
	bool validInput = false;
	string mapName;
	string mapFileName;

	do {
		cout << "Enter the name of the map that you want to play with: ";
		cin >> mapName;
		mapFileName = "map/" + mapName + "_map.txt";
		if (ifstream(mapFileName.c_str()))
			validInput = true;
		else
			cout << "This map does not exist. Please try again\n\n";
	} while (!validInput);

	openMapTxt(mapName, mapFileName, gameMap);

	//string mapPath = "path/" + mapName + "_path.txt";
	Wave* wave = new Wave();
	wave->createCritters(1, gameMap.getFilePathName());
	int size = wave->getCritterVec().size();
	vector <Critter> temp = wave->getCritterVec();
	int numOfCrit = wave->getNumOfCritters();
	
	while (true){
		for (int i = 0; i < numOfCrit; ++i){
			gameMap.setCellType(temp.at(i).getPositionX(), temp.at(i).getPositionY(), GridType::CRITTER, FileAction::STORE);
			gameMap.printMap();
			Sleep(3000);
		}
		cin >> size;

	}
	
}

void openMapTxt(string mapName, string mapFileName, Map& gameMap) {
	ifstream mapFile(mapFileName);  //Used to open the file that contains the map to be loaded
	unsigned char ch;               //Used for verifications of data in the file
	int mapWidth = 0;               //Used to retrieve the width of the map from the file
	int mapHeight = 0;              //Used to retrieve the height of the map from the file
	bool isMaxHeight = false;       //Used during the process of retrieving the height of the map
	int xCoord = 0;                 //Used during the process of creating the map object
	int yCoord = 0;					//Used during the process of creating the map object

	//Retrieving the width and height of the map from the file and then creating a map object from that
	while (!mapFile.eof()) {
		ch = mapFile.get();
		if (ch == '\n') {
			mapWidth++;
			isMaxHeight = true;
		} else if (!isMaxHeight && ch != ' ')
			mapHeight++;
	}
	gameMap = Map(mapWidth, mapHeight, mapName);

	//Reread the file to retrieve the content of the map and transfer them to the map object
	mapFile.clear();
	mapFile.seekg(0, ios_base::beg);
	while (!mapFile.eof()) {
		ch = mapFile.get();
		switch (ch) {
		case '0':
			gameMap.setCellType(xCoord++, yCoord, GridType::SCENERY, FileAction::LOAD);
			break;
		case '1':
			gameMap.setCellType(xCoord++, yCoord, GridType::START, FileAction::LOAD);
			break;
		case '2':
			gameMap.setCellType(xCoord++, yCoord, GridType::PATH, FileAction::LOAD);
			break;
		case '3':
			gameMap.setCellType(xCoord++, yCoord, GridType::END, FileAction::LOAD);
			break;
		case '\n':
			yCoord++;
			xCoord = 0;
			break;
		}
	}

	//Displaying the map
	gameMap.printMap();

	//Closing the file
	mapFile.close();
}
