#include "Map.h"
#include "GameConstants.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Entity.h"
#include "Scenery.h"
#include "Path.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
/*
 * Private Functions
 */
void Map::resizeMap(){
	// Copy Stanley shiee
}
/*
 * Public Functions
 */
Map::Map(){
	validMap = false;
	this->width = 0;
	this->height = 0;
	this->start_x = 0;
	this->start_y = 0;
	this->end_x = 0;
	this->end_y = 0;
	this->pathSteps = 0;
}
Map::Map(int width, int height){
	init(width, height);
}
void Map::init(int width, int height){
	validMap = false;
	this->width = width;
	this->height = height;
	this->start_x = -1;
	this->start_y = -1;
	this->end_x = -1;
	this->end_y = -1;
	this->thePath;
	this->pathSteps;
	theMap.resize(this->width);
	for (int i = 0; i < this->width; ++i){
		theMap[i].resize(this->height);
		for (int j = 0; j < this->height; ++j){
			theMap[i][j] = new Scenery();
			theMap[i][j]->setPosition((i * 32), (j * 32));
		}
	}
}
bool Map::addEntity(int x, int y, Tower* tower){
	if (!inBounds(x, y)){
		return false;
	}
	if (typeid(*theMap[x][y]) == typeid(Scenery)){
		theMap[x][y] = tower;
		theMap[x][y]->setPosition((x * 32), (y * 32));
		return true;
	}
	return false;
}
bool Map::addEntity(int x, int y, Critter* critter){
	if (!inBounds(x, y)){
		return false;
	}
	if (typeid(*theMap[x][y]) == typeid(Path)){
		theMap[x][y] = critter;
		theMap[x][y]->setPosition((x * 32), (y * 32));
		return true;
	}
	return false;
}
bool Map::addEntity(int x, int y, Path* path){
	if (!inBounds(x, y)){
		return false;
	}

	if (path->getImageName() == GameConstants::END_IMAGE_NAME && typeid(*theMap[x][y]) == typeid(Path)){
		theMap[x][y] = path;
		theMap[x][y]->setPosition((x * 32), (y * 32));
		std::cout << "je suis ici" << std::endl;
		this->end_x = x;
		this->end_y = y;
		return true;
	}
	else if (typeid(*theMap[x][y]) == typeid(Scenery)){
		theMap[x][y] = path;
		theMap[x][y]->setPosition((x * 32), (y * 32));
		if (path->getImageName() == GameConstants::START_IMAGE_NAME){
			this->start_x = x;
			this->start_y = y;
		}
		++pathSteps;
		thePath.resize(thePath.size() + 2);
		thePath[(thePath.size() - 2)] = x;
		thePath[(thePath.size() - 1)] = y;
		return true;
	}
	return false;
}
void Map::removeEntity(Tower* tower){
	for (int i = 0; i < this->width; ++i){
		for (int j = 0; j < this->height; ++j){
			if (theMap[i][j] == tower){
				theMap[i][j] = new Scenery();
				theMap[i][j]->setPosition((i * 32), (j * 32));
			}
		}
	}
}
void Map::removeEntity(Critter* critter){
	for (int i = 0; i < this->width; ++i){
		for (int j = 0; j < this->height; ++j){
			if (theMap[i][j] == critter){
				if (i == this->start_x && j == this->start_y){
					theMap[i][j] = new Path(GameConstants::START_IMAGE_NAME);
				}
				else if (i == this->end_x && j == this->end_y){
					theMap[i][j] = new Path(GameConstants::END_IMAGE_NAME);
				}
				else{
					theMap[i][j] = new Path();
				}
				theMap[i][j]->setPosition((i * 32), (j * 32));
			}
		}
	}
}
void Map::removeEntity(Path* path){
	for (int i = 0; i < this->width; ++i){
		for (int j = 0; j < this->height; ++j){
			if (theMap[i][j] == path){
				theMap[i][j] = new Scenery();
				theMap[i][j]->setPosition((i * 32), (j * 32));
			}
		}
	}
}

void Map::printMap(sf::RenderWindow& window){
	for (int i = 0; i < this->width; ++i){
		for (int j = 0; j < this->height; ++j){
			window.draw(theMap[i][j]->getSprite());
		}
	}
}
bool Map::validateMap(){ // TODO
	if (this->start_x == -1 || this->start_y == -1 || this->end_x == -1 || this->end_y == -1){
		return false;
	}
	for (int i = 0; i < theMap.size(); ++i){
		for (int j = 0; j < theMap[i].size(); ++j){
			if (typeid(*theMap[i][j]) == typeid(Path)){
				if (this->numOfNeighborPaths(i, j) > 2){
					return false;
				}
			}
		}
	}
	return true;
}
bool Map::saveMap(std::string fileName, bool overwrite){
	std::fstream file;
	file.open("res/info/maps/" + fileName + "_map.txt");
	if (file && !overwrite){
		return false;
	}
	else {
		std::cout << "swagger" << std::endl;
		file.open("res/info/maps/" + fileName + "_map.txt", ios::out);
		// iterate thru j then i, becasue we are writing the file line by line
		// and j represents the line number.
		for (int j = 0; j < this->height; ++j){
			for (int i = 0; i < this->width; ++i){
				if (i == this->start_x && j == this->start_y){
					file << "S";
				}
				else if (i == this->end_x && j == this->end_y){
					file << "E";
				}
				else if (typeid(*theMap[i][j]) == typeid(Path) || typeid(*theMap[i][j]) == typeid(Critter)){
					file << "P";
				}
				else {
					file << "-";
				}
			}
			file << std::endl;
		}
		file.close();
		file.open("res/info/paths/" + fileName + "_path.txt", ios::out);
		for (int i = 0; i < thePath.size(); i += 2){
			file << thePath[i] << "," << thePath[i + 1] << std::endl;
		}
		file.close();
	}
	return true;
}
bool Map::loadMap(std::string fileName){
	std::fstream file;
	file.open("res/info/maps/" + fileName + "_map.txt");
	if (file){
		// get the width & height of the map
		this->height = 0;
		std::string line, token;
		while (file.is_open()){
			file >> line;
			if (file.eof()){
				break;
			}
			if (this->height == 0){
				width = line.size();
			}
			this->height++;
		}
		file.close();
		this->init(width, height);
		file.open("res/info/maps/" + fileName + "_map.txt");
		for (int j = 0; j < this->height; ++j){
			file >> line;
			for (int i = 0; i < this->width; ++i){
				token = line.substr(i);
				if (token.substr(0, 1) == "S"){
					addEntity(i, j, new Path(GameConstants::START_IMAGE_NAME));
				}
				else if (token.substr(0, 1) == "E"){
					addEntity(i, j, new Path);
					addEntity(i, j, new Path(GameConstants::END_IMAGE_NAME));
				}
				else if (token.substr(0, 1) == "P"){
					addEntity(i, j, new Path());
				}
			}
		}
		file.close();

		//Loading the path
		file.open("res/info/paths/" + fileName + "_path.txt");
		char delimiter = ',';
		thePath.resize(0);
		pathSteps = 0;
		while (file.is_open()){
			file >> line;
			if (file.eof()){
				break;
			}
			int x, y;
			token = line.substr(0, line.find(delimiter));
			istringstream(token) >> x;
			thePath.push_back(x);
			token = line.substr(line.find(delimiter) + 1);
			istringstream(token) >> y;
			thePath.push_back(y);
			++pathSteps;
		}
	}
	else{
		return false;
	}
	return true;
}
bool Map::inBounds(int x, int y){
	return (x >= 0 && x < this->width && y >= 0 && y < this->height);
}
/*
Scenarios for Update:

WHAAAAAAA!?!?!?

*/
void Map::update(){ //TODO

}
// getters and setters
void Map::setWidth(int width){
	this->width = width;
}
int Map::getWidth() const{
	return this->width;
}
void Map::setHeight(int height){
	this->height = height;
}
int Map::getHeight() const{
	return this->height;
}
void Map::setStartX(int start_x){
	this->start_x = start_x;
}
int Map::getStartX() const{
	return this->start_x;
}
void Map::setStartY(int start_y){
	this->start_y = start_y;
}
int Map::getStartY() const{
	return this->start_y;
}
void Map::setEndX(int end_x){
	this->end_x = end_x;
}
int Map::getEndX() const{
	return this->end_x;
}
void Map::setEndY(int end_y){
	this->end_y = end_y;
}
int Map::getEndY() const{
	return this->end_y;
}
Entity* Map::getEntity(int x, int y){
	if (inBounds(x, y)){
		return theMap[x][y];
	}
	return NULL;
}
int Map::numOfNeighborPaths(int x, int y){
	int numOfNeighbors = 0;
	if (inBounds(x - 1, y) && typeid(*theMap[x - 1][y]) == typeid(Path)){
		++numOfNeighbors;
	}
	if (inBounds(x, y - 1) && typeid(*theMap[x][y - 1]) == typeid(Path)){
		++numOfNeighbors;
	}
	if (inBounds(x + 1, y) && typeid(*theMap[x + 1][y]) == typeid(Path)){
		++numOfNeighbors;
	}
	if (inBounds(x, y + 1) && typeid(*theMap[x][y + 1]) == typeid(Path)){
		++numOfNeighbors;
	}
	return numOfNeighbors;
}
std::vector<int> Map::getPath(){
	return thePath;
}
int Map::getPathSteps(){
	return pathSteps;
}