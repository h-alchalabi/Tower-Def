#include "Map.h"
#include <iostream>
//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "Wave.h"
#include <windows.h>
#include "Tower.h"
#include "TowerController.h"
#include "SharedSingleton.h" 

//using namespace sf;
using namespace std;

/***************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//Amanda Tom - 6633463
//Awais Ali - 6849040
//Haani Al-Chalabi - 9521577
//Van Do - 6526276
//Djamil Francis - 1308637
//
//COMP345 - Final Project
//
//Main application
//
/****************************************************************************************************************/

void openMapTxt(string mapName, string mapFileName, Map& gameMap);
void mapCreateOrEdit(Map& gameMap);
void startGame(Map& gameMap);
void createMap(Map& gameMap);
void loadMap(Map& gameMap);
void placeTowers(Map& gameMap);
void editMap(Map& gameMap);
void traceMap(int pathCoordX, int pathCoordY, Map& gameMap);

SharedSingleton* ss_ptr = SharedSingleton::getInstance();

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
	char gameOption;            //Used to prompt user to select options throughout the game
	bool validInput = false;    //Used during input validation

	//Prompting the user whether he/she wants to create a map or use an existing map
	do {
		cout << "Enter the following to select an option:" << endl
			<< "c -> Create a map" << endl
			<< "x -> Edit an existing map" << endl
			<< "e -> Return to Main Menu" << endl;
		cin >> gameOption;

		if (!(gameOption == 'c' || gameOption == 'x' || gameOption == 'e'))
			cout << "What you entered is invalid. Please try again.\n\n";
		else
			validInput = true;

	} while (!validInput);
	system("cls");

	if (gameOption == 'c') {
		createMap(gameMap);
	}
	else if (gameOption == 'x'){
		loadMap(gameMap);
		editMap(gameMap);
	}
}
void placeTowers(Map& gameMap){
	char selection = '0';
	while (selection != 'e'){
		while (true){
			system("cls");
			gameMap.printMap();
			cout << "What would you like to do? (Money: " << ss_ptr->money << "):" << endl
				<< "b -> Buy a Tower" << endl
				<< "u -> Upgrade a Tower" << endl
				<< "s -> Sell a Tower" << endl
				<< "e -> Start Wave" << endl;
			cin >> selection;
			if (selection == 'b' || selection == 'u' || selection == 's' || selection == 'e'){
				break;
			}
		}
		switch (selection){
		case 'b':{
					 
					 while (true){
						 cout << "Which type of tower would you like to buy? (Money: " << ss_ptr->money << "):" << endl
							 << "1 -> Normal Tower" << endl
							 << "2 -> Slowing Tower" << endl
							 << "e -> Go back to previous menu" << endl;
						 cin >> selection;
						 if (selection == '1' || selection == '2' || selection == 'e'){
							 break;
						 }
						 cout << "Invalid Selection." << endl;
					 }
					 int type = -1;
					 if (selection == '1'){
						 type = 0;
					 }
					 else if (selection == '2'){
						 type = 1;
					 }
					 else{
						 return;
					 }
					 cout << endl << Tower::towerPreview(type) << endl;
					 while (true){
						 cout << endl << "Would you like to purchase this tower? (y/n): ";
						 cin >> selection;
						 if (selection == 'y' || selection == 'n'){
							 break;
						 }
						 cout << "Invalid Selection.";
					 }
					 int coordX = 0, coordY = 0;
					 if (selection == 'y'){
						 int tempX = 0, tempY = 0;
						 ss_ptr->tc_ptr->addTower(type, tempX, tempY, gameMap);
					 }

		}break;
		case 'u':{
					 while (true){
						 int input = -1;
						 cout << "Current number of towers owned: " << ss_ptr->tc_ptr->size() << endl;
						 for (int i = 0; i != ss_ptr->tc_ptr->size(); ++i){
							 cout << "Index " << i << "\tType: " << ss_ptr->tc_ptr->getTower(i)->getType() <<
								 "\tUpgrade Cost value: " << ss_ptr->tc_ptr->getTower(i)->getUpgradeCost() << endl;
						 }
						 while (true){
							 cout << "\nTo upgrade a tower, input its index:" << endl;
							 cin >> input;
							 if (input >= 0 && input < ss_ptr->tc_ptr->size()){
								 break;
							 }
						 }
						 while (true){
							 cout << endl << "Would you like to upgrade this tower? (y/n): ";
							 cin >> selection;
							 if (selection == 'y' || selection == 'n'){
								 break;
							 }
							 cout << "Invalid Selection.";
						 }
						 if (selection == 'y'){
							 ss_ptr->tc_ptr->upgradeTower(input);
							 ss_ptr->tc_ptr->getTower(input)->printTowerStats();
							 Sleep(3000);
							 break;
						 }
					 }
		}break;
		case 's':{
					 while (true){
						 int input = -1;
						 cout << "Current number of towers owned: " << ss_ptr->tc_ptr->size() << endl;
						 for (int i = 0; i != ss_ptr->tc_ptr->size(); ++i){
							 cout << "Index " << i << "\tType: " << ss_ptr->tc_ptr->getTower(i)->getType() <<
								 "\tSell value: " << ss_ptr->tc_ptr->getTower(i)->getResellVal() << endl;
						 }
						 while (true){
							 cout << "\nTo sell a tower, input its index:" << endl;
							 cin >> input;
							 if (input >= 0 && input < ss_ptr->tc_ptr->size()){
								 break;
							 }
						 }
						 while (true){
							 cout << endl << "Would you like to sell this tower? (y/n): ";
							 cin >> selection;
							 if (selection == 'y' || selection == 'n'){
								 break;
							 }
							 cout << "Invalid Selection.";
						 }
						 if (selection == 'y'){
							 ss_ptr->tc_ptr->removeTower(input, gameMap);
							 break;
						 }
					 }
			}break;

		}
	}

}
void loadMap(Map& gameMap){
	string mapName;             //The name of the map to be loaded or to be stored
	string mapFileName;         //Used to create the text file from the file name entered by user
	bool validInput = false;
	do {
		cout << "Enter the name of the map that you want to open: ";
		cin >> mapName;
		mapFileName = "map/" + mapName + "_map.txt";
		if (ifstream(mapFileName.c_str()))
			validInput = true;
		else
			cout << "This map does not exist. Please try again\n\n";
	} while (!validInput);

	openMapTxt(mapName, mapFileName, gameMap);
}

void createMap(Map& gameMap){
	int mapWidth, mapHeight;    //Map dimensions
	int pathCoordX, pathCoordY; //Used to keep track of the path traced by user
	int coordX, coordY;			//Coordination of the start point, towers, or critters to be added on the map
	string mapName;             //The name of the map to be loaded or to be stored
	string mapFileName;         //Used to create the text file from the file name entered by user
	bool validInput = false;

	//Prompting the user to enter the name of the map
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
	gameMap.insertCoord(coordX, coordY, GridType::START, FileAction::STORE);

	//Prompting the user to trace the path on the map
	pathCoordX = coordX;
	pathCoordY = coordY;
	traceMap(pathCoordX, pathCoordY, gameMap);
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

	placeTowers(gameMap);

	Wave* wave = new Wave();
	wave->createCritters(1, gameMap.getFilePathName()); //Creating the critters and giving them a path to follow.
	wave->readFile(gameMap.getFilePathName()); //Reading that file and storing it into a vector for the critters to follow.
	int numOfCrit = wave->getNumOfCritters();
	int x, y;
	int* previousIndex = new int[2];
	int* startPos = new int[2];
	startPos = wave->getStartPos();
	int critterNoMore = 0;

	while (critterNoMore <= numOfCrit + 2){
		wave->deploy();
		for (int i = 0; i < wave->getNumberOfDeployed(); ++i){
			Critter c = wave->getCritterVec().at(i);
			x = c.getPositionX();
			y = c.getPositionY();
			if (gameMap.getCell(x, y).getType() == GridType::END){ //If the next position the critter attemps to move is the End index, then don't allow him to move
				++critterNoMore;									//increment the number of critters that have passed.
				if (critterNoMore >= numOfCrit){					//if all the critters have passed the revert the previous tile to a scenery tile.
					previousIndex = c.previousPos(wave->getCoordinateVec());
					gameMap.setCellType(previousIndex[0], previousIndex[1], GridType::PATH, FileAction::LOAD);
				}
			}//If it is not the end tile
			else {
				//If the next tile is not empty, then move the critter to it and attempt to revert the old tile into a path tile.
				gameMap.setCellType(x, y, GridType::CRITTER, FileAction::LOAD);
				if (c.getSteps() - 2 > 0){
					previousIndex = c.previousPos(wave->getCoordinateVec());
					gameMap.setCellType(previousIndex[0], previousIndex[1], GridType::PATH, FileAction::LOAD);
				} //reverting the old space.
			}

		}
		system("cls");
		gameMap.printMap();
		Sleep(500);

	}
	gameMap.setCellType(startPos[0], startPos[1], GridType::START, FileAction::LOAD);
	delete wave;

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
			mapHeight++;
			isMaxHeight = true;
		}
		else if (!isMaxHeight && ch != ' ')
			mapWidth++;
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

void traceMap(int pathCoordX, int pathCoordY, Map& gameMap) {
	char pathDirection = 's';

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

void editMap(Map& gameMap) {
	char gameOption;            //Used to prompt user to select options throughout the game
	bool validInput = false;    //Used during input validation

	do {
		//Prompting the user whether he/she wants to resize the map, or change the path
		do {
			cout << "Enter the following to select an option:" << endl
				<< "r -> Resize the map (can only expand the map)" << endl
				<< "c -> Change the path" << endl
				<< "e -> Exit editor" << endl;
			cin >> gameOption;

			if (!(gameOption == 'c' || gameOption == 'r' || gameOption == 'e'))
				cout << "What you entered is invalid. Please try again.\n\n";
			else
				validInput = true;

		} while (!validInput);
		system("cls");
		gameMap.printMap();
		if (gameOption == 'r') {
			//Resizing the map
			validInput = false;
			int newMapWidth;
			int newMapHeight;

			//Prompting the user to enter the new dimension of the map
			do {

				cout << "Enter the new dimensions of the map (you can only expand the map)\n";
				cout << "Width: ";
				cin >> newMapWidth;
				cout << "Height: ";
				cin >> newMapHeight;

				if (newMapWidth <= gameMap.getWidth() || newMapHeight <= gameMap.getHeight())
					cout << "Either the width or the height that you've entered is not valid (same dimension or " <<
					"smaller dimension than the actual map). Please try again\n\n";
				else
					validInput = true;
			} while (!validInput);

			//Print the map with the new dimensions
			system("cls");
			gameMap.resizeMap(newMapWidth, newMapHeight);
			gameMap.printMap();
			gameMap.storeMapTxt();
		}
		else if (gameOption == 'c') {
			//Coordinates selected by user to start the new path
			int xStartEditCoord;
			int yStartEditCoord;
			//Used to verify user input
			validInput = false;

			//Prompting the user to enter the coordinates where he/she wants to start the new path
			do {
				cout << "Enter the X and Y coordinates of where you want to start your new path\n";
				cout << "x coordinate: ";
				cin >> xStartEditCoord;
				cout << "y coordinate: ";
				cin >> yStartEditCoord;
				if (!(xStartEditCoord > -1 && xStartEditCoord < gameMap.getWidth()) ||
					!(yStartEditCoord > -1 && yStartEditCoord < gameMap.getHeight()))
					cout << "These coordinates that you entered are out of the map";
				else if (gameMap.getCell(xStartEditCoord, yStartEditCoord).getType() == GridType::START ||
					gameMap.getCell(xStartEditCoord, yStartEditCoord).getType() == GridType::PATH ||
					gameMap.getCell(xStartEditCoord, yStartEditCoord).getType() == GridType::END)
					validInput = true;
				else
					cout << "The coordinates that you have selected is not a start point, path, or end point." <<
					"\nPlease try again\n";
			} while (!validInput);
			system("cls");

			//Erase the path after the selected coordinates
			gameMap.restartPaths(xStartEditCoord, yStartEditCoord);
			if (gameMap.getCell(xStartEditCoord, yStartEditCoord).getType() == GridType::END){
				gameMap.setCellType(xStartEditCoord, yStartEditCoord, GridType::PATH, FileAction::STORE);
			}
			gameMap.printMap();
			//Trace the map from the selected coordinates
			traceMap(xStartEditCoord, yStartEditCoord, gameMap);
		}
	} while (gameOption != 'e');
}