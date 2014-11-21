#include <iostream>
using namespace std;
#include <vector>
#include "Critter.h"
#include "Tower.h"

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
	virtual void execute(vector<Critter*> critters, Tower* tower) = 0;
};