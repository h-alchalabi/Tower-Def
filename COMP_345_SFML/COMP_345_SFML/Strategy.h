#include <iostream>
using namespace std;
#include <vector>
#include "Critter.h"

/*******************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//COMP345 - assignment 3
//November 20, 2014
//
//This is the strategy interface to be used in the strategy design pattern.
//
/*******************************************************************************************************************/

#pragma once
class Strategy {
public:
	virtual int execute(vector<Critter*> critters, int towerX, int towerY, int towerRange) = 0;
};