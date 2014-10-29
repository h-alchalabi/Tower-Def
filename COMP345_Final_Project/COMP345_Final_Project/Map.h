#include "MapGrid.h"
#include <vector>
 
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
	vector<vector<MapGrid>> cells;

public:
	~Map();
	Map();
	Map(int width, int height);
	int getWidth() const;
	int getHeight() const;
	MapGrid getCell(int coordX, int coordY) const;
	void setWidth(int w);
	void setHeight(int h);
	void setCellType(int coordX, int coordY, GridType gridType);
	void printMap() const;

	//Calculating the number of cells around the current cell
	int calcNumNeighbourPath(int coordX, int coordY, int mapWidth, int mapHeight) const; 
};