#include <iostream>
#include "Map.h"
using namespace std;
 
/*******************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//COMP345 - assignment 1
//October 17, 2014
//
//This file contains all the function prototypes
//
/*******************************************************************************************************************/

//Prompting the user to enter the coordinates for the element to be inserted, and then insert the element on the map
void insertCoord(int& coordX, int& coordY, int mapWidth, int mapHeight, GridType gridType, Map& gameMap);

//Function for user to add as much tower/critter as he/she wants on the map
void addCritterOrTower(int& coordX, int& coordY, int mapWidth, int mapHeight, GridType gridType, Map& gameMap);

//Function to validate the next path to be traced by the user on the X axis
int tracePathX(int pathCoordX, int pathCoordXRequest, int pathCoordY, int mapWidth, int mapHeight, Map& gameMap);

//Function to validate the next path to be traced by the user on the Y axis
int tracePathY(int pathCoordX, int pathCoordY, int pathCoordYRequest, int mapWidth, int mapHeight, Map& gameMap);