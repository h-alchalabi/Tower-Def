using namespace std;
enum GridType { Start, End, Path, Scenery, Tower, Critter };

/*******************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//COMP345 - assignment 1
//October 17, 2014
//
//The map grid class which contains information of each grid on the tower defense game map.
//
/*******************************************************************************************************************/

class MapGrid {

private:
	int coordX;        //X coordinate of the grid
	int coordY;        //Y coordinate of the grid
	GridType gridType; //The grid's type
public:
	~MapGrid();
	MapGrid();
	int getCoordX() const;
	int getCoordY() const;
	GridType getType() const;
	void setCoordX(int x);
	void setCoordY(int y);
	void setType(GridType t);
};