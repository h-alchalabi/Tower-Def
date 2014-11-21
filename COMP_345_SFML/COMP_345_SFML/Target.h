#include "Strategy.h"
#include "Critter.h"
#include "Tower.h"
#include <vector>
#include <iostream>
using namespace std;

/*******************************************************************************************************************/
//Stanley Naikang Luu - 6604706
//COMP345 - assignment 3
//November 20, 2014
//
//This is the target class that will be used by a tower to use one of the strategy objects.
//
/*******************************************************************************************************************/

#pragma once
class Target {
public:
	Target();
	Target(Strategy *initStrategy);
	void setStrategy(Strategy *newStrategy);
	void executeStrategy(vector<Critter*> critters, Tower* tower);
private:
	Strategy* strategy;
};