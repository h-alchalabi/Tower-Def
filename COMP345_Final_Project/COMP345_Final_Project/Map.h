#pragma once
#include "MapGrid.h"
#include <queue>

//Used to differenciate between loading and storing the path file
enum FileAction { STORE, LOAD };
//Used to check if the current file reader cursor is at the selected coordinates
enum CoordListLocation { BEFORE_SELECTED, SELECTED, AFTER_SELECTED };

/*******************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//COMP345 - assignment 1
//October 17, 2014
//
//This is the map class in order to create maps for the tower defense game.
//
/*******************************************************************************************************************/

class Map {

private:
	int width;
	int height;
	string mapName;
	string filePathName;
	string fileMapName;
	vector<vector<MapGrid>> cells;

public:
	~Map();
	Map();
	Map(int width, int height, string name);
	int getWidth() const;
	int getHeight() const;
	string getMapName() const;
	string getFilePathName() const;
	string getFileMapName() const;
	MapGrid getCell(int coordX, int coordY) const;
	void setWidth(int w);
	void setHeight(int h);
	void setCellType(int coordX, int coordY, GridType gridType, FileAction fileAction);
	void printMap() const;

	//Calculating the number of cells around the current cell
	int calcNumNeighbourPath(int coordX, int coordY) const;

	//Validating the next path to be traced by the user on the X axis
	int tracePathX(int pathCoordX, int pathCoordXRequest, int pathCoordY);

	//Validate the next path to be traced by the user on the Y axis
	int tracePathY(int pathCoordX, int pathCoordY, int pathCoordYRequest);

	//Prompting the user to enter the coordinates for the element to be inserted, and then insert the element on the map
	void insertCoord(int& coordX, int& coordY, GridType gridType, FileAction fileAction);

	//Having the user add as much tower/critter as he/she wants on the map
	void addCritterOrTower(int& coordX, int& coordY, GridType gridType);

	//Validating the end path
	bool validateEndPath(int coordX, int coordY);

	//Verify if the coordinate is near the start point
	bool isNeighbourStart(int coordX, int coordY);

	//Storing the created map in a text file
	void storeMapTxt();

	//Used to resize the map
	void resizeMap(int width, int height);

	//Used to erase the path after the selected coordinate
	void restartPaths(int xCoord, int yCoord);
};