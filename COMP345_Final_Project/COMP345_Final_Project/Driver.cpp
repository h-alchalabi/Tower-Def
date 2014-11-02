#include "Driver.h"
//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>

//using namespace sf;
using namespace std;
/***************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//COMP345 - assignment 1
//October 17, 2014
//
//Main application
//
/****************************************************************************************************************/
int main() {
	/*RenderWindow window(VideoMode(800, 600), "My window");
	CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	std::cout << "nuggets - test" << endl;
	// run the program as long as the window is open
	while (window.isOpen())
	{

	// check all the window's events that were triggered since the last iteration of the loop
	Event event;
	while (window.pollEvent(event))
	{
	// "close requested" event: we close the window
	if (event.type == Event::Closed)
	window.close();
	}
	*
	window.clear();
	window.draw(shape);
	window.display();
	*/
	/*Text text;
	text.setFont(font);
	text.setString("Hello World");
	text.setCharacterSize(24);
	text.setColor(Color::Red);
	window.clear();
	window.draw(text);
	window.display();*/
	//}
	int mapWidth, mapHeight;    //Map dimensions
	Map gameMap;				//The map that will be created for the user
	int pathCoordX, pathCoordY; //Used to keep track of the path traced by user
	int coordX, coordY;			//Coordination of the start point, towers, or critters to be added on the map
	char pathDirection = 's';   //Used to verify if user wants to end path tracing
	ofstream fileOpen("Path.txt");
	//Prompting the user to enter the dimensions of the map, create the map based on the input, and then display it
	do {
		//Minimum width user allowed to enter: 5
		std::cout << "Enter the width of the map (minimum length of 5): ";
		cin >> mapWidth;
	} while (mapWidth < 5);
	do {
		//Minimum height user allowed to enter: 5
		std::cout << "Enter the height of the map (minimum length of 5): ";
		cin >> mapHeight;
	} while (mapHeight < 5);
	gameMap = Map(mapWidth, mapHeight);
	gameMap.printMap();
	//Inserting the start point
	insertCoord(coordX, coordY, mapWidth, mapHeight, GridType::Start, gameMap);

	//Prompting the user to trace the path on the map
	pathCoordX = coordX;
	pathCoordY = coordY;
	fileOpen << pathCoordX << "," << pathCoordY << endl;
	//
	while (pathDirection != 'e') {
		std::cout << "\nEnter the next path of your map ('w' for up, 's' for down, 'a' for left, 'd' for right, and 'e' to end your path): " << endl;
		cin >> pathDirection;
		switch (pathDirection) {
		case 'w':
			//Going up
			pathCoordY = tracePathY(pathCoordX, pathCoordY, pathCoordY - 1, mapWidth, mapHeight, gameMap);
			fileOpen << pathCoordX << "," << pathCoordY << endl;
			break;
		case 's':
			//Going down
			pathCoordY = tracePathY(pathCoordX, pathCoordY, pathCoordY + 1, mapWidth, mapHeight, gameMap);
			fileOpen << pathCoordX << "," << pathCoordY << endl;
			break;
		case 'a':
			//Going left
			pathCoordX = tracePathX(pathCoordX, pathCoordX - 1, pathCoordY, mapWidth, mapHeight, gameMap);
			fileOpen << pathCoordX << "," << pathCoordY << endl;
			break;
		case 'd':
			//Going right
			pathCoordX = tracePathX(pathCoordX, pathCoordX + 1, pathCoordY, mapWidth, mapHeight, gameMap);
			fileOpen << pathCoordX << "," << pathCoordY << endl;
			break;
		case 'e':
			//End the path
			gameMap.setCellType(pathCoordX, pathCoordY, GridType::End);
			fileOpen << pathCoordX << "," << pathCoordY << endl;
			break;
		default:
			//Invalid input
			std::cout << "What you entered was invalid, try again" << endl;
			break;
		}
		//Updating the map to the user with the path that was traced
		gameMap.printMap();
	}
	//Inserting towers on the map
	addCritterOrTower(coordX, coordY, mapWidth, mapHeight, GridType::Tower, gameMap);
	//Inserting critters on the map
	addCritterOrTower(coordX, coordY, mapWidth, mapHeight, GridType::Critter, gameMap);

	std::cout << "\nYour map has been successfully created\n";

	return 0;
}
void insertCoord(int& coordX, int& coordY, int mapWidth, int mapHeight, GridType gridType, Map& gameMap) {
	//Used to determine if user input is valid
	bool validInput = false;
	//Used to determine if system outputs for the case of start point, critters or towers
	string type = (gridType == GridType::Start ? "start point" : (gridType == GridType::Critter ? "critter" : "tower"));
	while (!validInput) {
		//Prompting user to enter the x and y coordinates of the element to insert on the map
		std::cout << "\nEnter the coordination of the " << type << " to be added on the map." << endl;
		std::cout << "Coordination X: ";
		cin >> coordX;
		std::cout << "Coordination Y: ";
		cin >> coordY;
		//Validating the x and y coordinates entered by user
		if (coordX < mapWidth && coordX > -1 && coordY < mapHeight && coordY > -1) {
			switch (gridType) {
			case GridType::Critter:
				//Critter insertion validation
				if (gameMap.getCell(coordX, coordY).getType() == GridType::Path)
					validInput = true;
				else if (gameMap.getCell(coordX, coordY).getType() == GridType::Critter)
					std::cout << "You have already inserted a critter on these coordinates";
				else
					std::cout << "Unable to place critter in these coordinates because it is not a path. Please try again.\n\n";
				break;
			case GridType::Tower:
				//Tower insertion validation
				if (gameMap.getCell(coordX, coordY).getType() == GridType::Scenery)
					validInput = true;
				else if (gameMap.getCell(coordX, coordY).getType() == GridType::Tower)
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
	//Adding the element on the map and then display the map
	gameMap.setCellType(coordX, coordY, gridType);
	gameMap.printMap();
}
void addCritterOrTower(int& coordX, int& coordY, int mapWidth, int mapHeight, GridType gridType, Map& gameMap) {
	char moreInput; //Used to keep track for if the user wants to create more towers/critters
	do {
		//Inserting the critter or tower on the map
		insertCoord(coordX, coordY, mapWidth, mapHeight, gridType, gameMap);
		//Prompting the user to decide whether to add more critters or not
		std::cout << "Would you like to create more " << (gridType == GridType::Critter ? "critter" : "tower") <<
			"? (Enter 'y' for yes and 'n' for no): ";
		cin >> moreInput;
	} while (moreInput == 'y');
}
int tracePathX(int pathCoordX, int pathCoordXRequest, int pathCoordY, int mapWidth, int mapHeight, Map& gameMap) {
	if (!(pathCoordXRequest > -1 && pathCoordXRequest < mapWidth))
		std::cout << "\nUnable to move towards this direction since the path will be out of the map.\n";
	else if (gameMap.calcNumNeighbourPath(pathCoordXRequest, pathCoordY, mapWidth, mapHeight) > 1)
		std::cout << "\nUnable to move towards this direction since either the path is already traced, or it is close to an " <<
		"existent path.\n";
	else if (gameMap.getCell(pathCoordXRequest, pathCoordY).getType() == GridType::Start)
		std::cout << "\nUnable to move towards this directions since it is the start point";
	else {
		//Inserting the path on the map and then updating the X coordinate for the next path to trace
		gameMap.setCellType(pathCoordXRequest, pathCoordY, GridType::Path);
		pathCoordX = pathCoordXRequest;
	}
	return pathCoordX;
}
int tracePathY(int pathCoordX, int pathCoordY, int pathCoordYRequest, int mapWidth, int mapHeight, Map& gameMap) {
	if (!(pathCoordYRequest > -1 && pathCoordYRequest < mapHeight))
		std::cout << "\nUnable to move towards this direction since the path will be out of the map.\n";
	else if (gameMap.calcNumNeighbourPath(pathCoordX, pathCoordYRequest, mapWidth, mapHeight) > 1)
		std::cout << "\nUnable to move towards this direction since either the path is already traced, or it is close to an " <<
		"existent path.\n";
	else if (gameMap.getCell(pathCoordX, pathCoordYRequest).getType() == GridType::Start)
		std::cout << "\nUnable to move towards this directions since it is the start point";
	else {
		//Inserting the path on the map and then updating the Y coordinate for the next path to trace
		gameMap.setCellType(pathCoordX, pathCoordYRequest, GridType::Path);
		pathCoordY = pathCoordYRequest;
	}

	return pathCoordY;
}