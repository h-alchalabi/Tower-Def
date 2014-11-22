#pragma once
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;

class GameConstants{
public:
	static const string START_IMAGE_NAME;
	static const string END_IMAGE_NAME;
	static const string PATH_IMAGE_NAME;
	static const string SCENERY_IMAGE_NAME;
	static const string NORMAL_TOWER_IMAGE_NAME;
	static const string FIRE_TOWER_IMAGE_NAME;
	static const string ICE_TOWER_IMAGE_NAME;
	static const string CRITTER_IMAGE_NAME;
	static const string NORMAL_CRITTER_IMAGE_NAME;
	static const string FAST_CRITTER_IMAGE_NAME;
	static const string SLOW_CRITTER_IMAGE_NAME;
	static const string FONT_FILE_PATH;
	static const sf::Int32 NORMAL_CRITTER_DEPLOY_TIME;
	static const sf::Int32 FAST_CRITTER_DEPLOY_TIME;
	static const sf::Int32 SLOW_CRITTER_DEPLOY_TIME;
	static const int NUMBER_OF_WAVES;
	static const float FONT_SIZE;
	static int getMoney();
	static bool spendMoney(int amount);
	static bool collectMoney(int amount);
	static void resetMoney();
	static std::string getMoneyString();
private:
	static int money;
	GameConstants();
};