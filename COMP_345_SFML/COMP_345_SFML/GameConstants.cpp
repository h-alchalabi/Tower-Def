#include "GameConstants.h"
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;

const string GameConstants::START_IMAGE_NAME = "start";
const string GameConstants::END_IMAGE_NAME = "end";
const string GameConstants::PATH_IMAGE_NAME = "path";
const string GameConstants::SCENERY_IMAGE_NAME = "scenery";
const string GameConstants::NORMAL_TOWER_IMAGE_NAME = "normal_tower";
const string GameConstants::FIRE_TOWER_IMAGE_NAME = "fire_tower";
const string GameConstants::ICE_TOWER_IMAGE_NAME = "ice_tower";
const string GameConstants::CRITTER_IMAGE_NAME = "critter";
const string GameConstants::NORMAL_CRITTER_IMAGE_NAME = "critter";
const string GameConstants::FAST_CRITTER_IMAGE_NAME = "critter";
const string GameConstants::SLOW_CRITTER_IMAGE_NAME = "critter";
const string GameConstants::FONT_FILE_PATH = "res/font/emulogic.ttf";
const sf::Int32 GameConstants::NORMAL_CRITTER_DEPLOY_TIME = 1000;
const sf::Int32 GameConstants::FAST_CRITTER_DEPLOY_TIME = 500;
const sf::Int32 GameConstants::SLOW_CRITTER_DEPLOY_TIME = 1500;
const int GameConstants::NUMBER_OF_WAVES = 9;
const float GameConstants::FONT_SIZE = 8;