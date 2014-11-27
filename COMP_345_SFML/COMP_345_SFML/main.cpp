#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "GameConstants.h"
#include "Map.h"
#include "Tower.h"
#include "FireTower.h"
#include "IceTower.h"
#include "ThunderTower.h"
#include "NormalTower.h"
#include "DecoratedTower.h"
#include "LevelUpTower.h"
#include "Wave.h"
#include "dirent.h"
#include "NearestCritterTowerStrategy.h"
#include "WeakestCritterStrategy.h"
#include <sstream>

using namespace std;

void dropTower(sf::RenderWindow& window, sf::Event sf_event, Map* map);
void startGame();
void createMap();
bool canMove(int current_x, int current_y, int new_x, int new_y, Map* map);
string getMapList();
void editMap();
bool openMapPrompt(Map* map);
void handleClick(sf::Event sf_event, Map* map, bool canPlace, vector<Tower*>& towerList);
void init();
void setTowerInfo(Tower* selectedTower, int mapWidthPixels, bool showButtons);
bool saveMapPrompt(Map* map, bool overwrite);
void resizeMap(Map* map);
void changeMapPath(Map* map);
void foo(int x, int y, Map*& map);
void towerAction(vector<Tower*> towerList, vector<Critter*> critterList, bool paused);
int findTowerIndex(Tower* tower, vector<Tower*> towerList);
bool gameOverPrompt();

namespace Selection{
	enum TowerType { NA, NORMAL, FIRE, ICE, THUNDER };
}

static Selection::TowerType towerType;

static sf::Sprite normalTowerButton, fireTowerButton, iceTowerButton, thunderTowerButton;
static sf::Texture normalTowerTexture, fireTowerTexture, iceTowerTexture, thunderTowerTexture;
static sf::RectangleShape towerSelectionRect(sf::Vector2<float>(40, 40));
static sf::RectangleShape strategySelectRect(sf::Vector2<float>(145, 25));
static sf::RectangleShape upgradeButton(sf::Vector2<float>(64, 20));
static sf::RectangleShape sellButton(sf::Vector2<float>(64, 20));
static sf::RectangleShape nearestStrategyButton(sf::Vector2<float>(140, 20));
static sf::RectangleShape weakestStrategyButton(sf::Vector2<float>(128, 20));
static sf::Text upgradeButtonText, sellButtonText, towerInfoText, strategyText, nearestStrategyText, weakestStrategyText, startGameText;
static sf::Font mainFont;
static sf::Sprite towerIcon;
static Tower* currentTower;

int main(){

	init();

	string errMsg;
	bool running = true;

	while (running){
		system("cls");
		cout << "--------------------------------------------------\n";
		cout << "\tMain Menu\n";
		cout << "--------------------------------------------------\n\n";
		cout << errMsg << endl << endl;
		cout << "c -> Create a Map.\n";
		cout << "e -> Edit a Map.\n";
		cout << "s -> Start the Game.\n";
		cout << "q -> Quit.\n\n";
		cout << "Input: ";
		char input;
		cin >> input;
		errMsg = "";
		switch (input){
		case 'c':{
					 createMap();
		} break;
		case 'e':{
					 editMap();
		} break;
		case 's':{
					 startGame();
		} break;
		case 'q':{
					 running = false;
		} break;
		default:{
					errMsg = "***** Invalid Input. Please Try Again. *****";
		} break;
		}
	}
	/*
	sf::RenderWindow window(sf::VideoMode(map->getWidth()*32, map->getHeight()*32), "SFML works!");
	window.setKeyRepeatEnabled(false);
	while (window.isOpen())
	{
	sf::Event event;
	while (window.pollEvent(event))
	{
	switch (event.type){
	case sf::Event::Closed:{
	window.close();
	} break;
	case sf::Event::MouseButtonPressed:
	{
	if (creatingMap){

	}
	}break;
	}
	}

	window.clear();
	map->printMap(window);
	window.display();
	}*/
	return 0;
}

void init(){
	normalTowerTexture.loadFromFile("res/img/" + GameConstants::NORMAL_TOWER_IMAGE_NAME + ".png");
	fireTowerTexture.loadFromFile("res/img/" + GameConstants::FIRE_TOWER_IMAGE_NAME + ".png");
	iceTowerTexture.loadFromFile("res/img/" + GameConstants::ICE_TOWER_IMAGE_NAME + ".png");
	thunderTowerTexture.loadFromFile("res/img/" + GameConstants::THUNDER_TOWER_IMAGE_NAME + ".png");

	normalTowerButton.setTexture(normalTowerTexture);
	fireTowerButton.setTexture(fireTowerTexture);
	iceTowerButton.setTexture(iceTowerTexture);
	thunderTowerButton.setTexture(thunderTowerTexture);

	towerType = Selection::NA;

	mainFont.loadFromFile(GameConstants::FONT_FILE_PATH);

	towerInfoText.setFont(mainFont);
	towerInfoText.setColor(sf::Color::White);
	towerInfoText.setCharacterSize(GameConstants::FONT_SIZE);

	towerSelectionRect.setFillColor(sf::Color::Yellow);
	towerSelectionRect.setPosition(-100, -100);

	strategySelectRect.setFillColor(sf::Color::Yellow);
	strategySelectRect.setPosition(-100, -100);

	upgradeButton.setFillColor(sf::Color::Green);
	upgradeButton.setPosition(-100, -100);

	sellButton.setFillColor(sf::Color::Red);
	sellButton.setPosition(-100, -100);

	nearestStrategyButton.setFillColor(sf::Color::Blue);
	nearestStrategyButton.setPosition(-100, -100);

	weakestStrategyButton.setFillColor(sf::Color::Blue);
	weakestStrategyButton.setPosition(-100, -100);


	upgradeButtonText.setFont(mainFont);
	upgradeButtonText.setString("UPGRADE");
	upgradeButtonText.setCharacterSize(GameConstants::FONT_SIZE);
	upgradeButtonText.setColor(sf::Color::White);

	sellButtonText.setFont(mainFont);
	sellButtonText.setString("SELL");
	sellButtonText.setCharacterSize(GameConstants::FONT_SIZE);
	sellButtonText.setColor(sf::Color::White);

	strategyText.setFont(mainFont);
	strategyText.setString("STRATEGY");
	strategyText.setCharacterSize(GameConstants::FONT_SIZE);
	strategyText.setColor(sf::Color::White);

	nearestStrategyText.setFont(mainFont);
	nearestStrategyText.setString("NEAREST TO TOWER");
	nearestStrategyText.setCharacterSize(GameConstants::FONT_SIZE);
	nearestStrategyText.setColor(sf::Color::White);

	weakestStrategyText.setFont(mainFont);
	weakestStrategyText.setString("WEAKEST CRITTER");
	weakestStrategyText.setCharacterSize(GameConstants::FONT_SIZE);


	startGameText.setFont(mainFont);
	startGameText.setString("SPACE - Start a Critter Wave\nP - Pause/Resume Game");
	startGameText.setCharacterSize(GameConstants::FONT_SIZE);
	startGameText.setColor(sf::Color::White);
}


void createMap(){
	int width, height;
	string errMsg = "";
	while (true){
		system("cls");
		cout << "--------------------------------------------------\n";
		cout << "\tCreating a Map\n";
		cout << "--------------------------------------------------\n\n";
		cout << errMsg << endl << endl;
		cout << "Please enter the width of the map(min: " << GameConstants::MIN_WIDTH << ", max: " << GameConstants::MAX_WIDTH << "): ";
		errMsg = "";
		try{
			cin >> width;
		}
		catch (...){
			errMsg = "***** Invalid Input. Please Try Again. *****";
			continue;
		}
		if (width >= GameConstants::MIN_WIDTH && width <= GameConstants::MAX_WIDTH){
			break;
		}
		else{
			stringstream ss;
			ss << "***** Width must be between " << GameConstants::MIN_WIDTH << " and " << GameConstants::MAX_WIDTH << " [inclusive]. *****";
			errMsg = ss.str();
		}
	}
	while (true){
		system("cls");
		cout << "--------------------------------------------------\n";
		cout << "\tCreating a Map\n";
		cout << "--------------------------------------------------\n\n";
		cout << errMsg << endl << endl;
		cout << "Please enter the height of the map(min: " << GameConstants::MIN_HEIGHT << ", max: " << GameConstants::MAX_HEIGHT << "): ";
		errMsg = "";
		try{
			cin >> height;
		}
		catch (...){
			errMsg = "***** Invalid Input. Please Try Again. *****";
			continue;
		}
		if (height >= GameConstants::MIN_HEIGHT && height <= GameConstants::MAX_HEIGHT){
			break;
		}
		else{
			stringstream ss;
			ss << "***** Height must be between " << GameConstants::MIN_HEIGHT << " and " << GameConstants::MAX_HEIGHT << " [inclusive]. *****";
			errMsg = ss.str();
		}
	}

	string startPrompt, createPrompt;

	Map* map = new Map(width, height);

	sf::Text outText("", mainFont);
	outText.setColor(sf::Color::White);
	outText.setCharacterSize(GameConstants::FONT_SIZE);
	outText.setPosition(0, map->getHeight() * 32);

	sf::RenderWindow window(sf::VideoMode(map->getWidth() * 32, map->getHeight() * 32 + 75), "Creating a Map");
	window.setKeyRepeatEnabled(false);
	map->printMap(window);
	window.display();
	sf::Event sf_event;


	int start_x, start_y;

	startPrompt = "------------------------------------\n";
	startPrompt += "\tCreating a Map\n";
	startPrompt += "-----------------------------------\n\n";
	startPrompt += "Please select(click)\n";
	startPrompt += "the start location.";

	createPrompt = "------------------------------------\n";
	createPrompt += "\tCreating a Map\n";
	createPrompt += "-----------------------------------\n\n";
	createPrompt += "Use Arrow Keys to move.\n";
	createPrompt += "Press E ot end the path.";

	outText.setString(startPrompt);

	//	map->addEntity(start_x, start_y, new Path(GameConstants::START_IMAGE_NAME));

	bool editingMap = true;
	bool canExit = false;
	bool startChosen = false;
	int current_x, current_y;

	while (window.isOpen() && editingMap){
		while (window.pollEvent(sf_event)){
			switch (sf_event.type){
			case sf::Event::Closed:{
									   window.close();
			} break;
			case sf::Event::KeyPressed:{
										   if (startChosen){
											   switch (sf_event.key.code){
											   case sf::Keyboard::Up:{
																		 if (canMove(current_x, current_y, current_x, current_y - 1, map)){
																			 --current_y;
																			 map->addEntity(current_x, current_y, new Path());
																			 canExit = true;
																		 }

											   } break;
											   case sf::Keyboard::Left:{
																		   if (canMove(current_x, current_y, current_x - 1, current_y, map)){
																			   --current_x;
																			   map->addEntity(current_x, current_y, new Path());
																			   canExit = true;
																		   }
											   } break;
											   case sf::Keyboard::Down:{
																		   if (canMove(current_x, current_y, current_x, current_y + 1, map)){
																			   ++current_y;
																			   map->addEntity(current_x, current_y, new Path());
																			   canExit = true;
																		   }
											   } break;
											   case sf::Keyboard::Right:{
																			if (canMove(current_x, current_y, current_x + 1, current_y, map)){
																				++current_x;
																				map->addEntity(current_x, current_y, new Path());
																				canExit = true;
																			}
											   } break;
											   case sf::Keyboard::E:{
																		if (canExit){
																			editingMap = false;
																			map->addEntity(current_x, current_y, new Path(GameConstants::END_IMAGE_NAME));
																		}
											   } break;
											   default: break;
											   }
										   }
			}break;
			case sf::Event::MouseButtonPressed:{
												   if (!startChosen){
													   if (sf_event.mouseButton.button == sf::Mouse::Left){
														   int block_x = sf_event.mouseButton.x / 32;
														   int block_y = sf_event.mouseButton.y / 32;
														   if (map->addEntity(block_x, block_y, new Path(GameConstants::START_IMAGE_NAME))){
															   startChosen = true;
															   outText.setString(createPrompt);
															   current_x = start_x = block_x;
															   current_y = start_y = block_y;
														   }
													   }
												   }
			} break;
			}
		}

		window.clear();
		map->printMap(window);

		window.draw(outText);
		window.display();
	}
	window.close();
	string dump = "";
	if (!map->validateMap()){
		system("cls");
		cout << "------------------------------------\n";
		cout << "\tCreating a Map\n";
		cout << "-----------------------------------\n\n";
		cout << "Invalid map. Cannot be saved.\n";
		cout << "Enter any value to continue . . .";
		cin >> dump;
		return;
	}
	saveMapPrompt(map, false);
}
void editMap(){
	Map* map = new Map();
	if (!openMapPrompt(map)){
		return;
	}

	string mapName = map->getMapName();
	bool onMenu = true;
	bool changePath = false;
	bool resizeMap = false;
	bool makingPath = false;
	bool newPath = false;
	bool canEnd = false;

	int current_x = 0, current_y = 0, start_x = 0, start_y = 0;

	string mainEditString = "R - Resize Map\nC - Change Path\nQ - Quit";
	string resizingString = "Up - Add Row Above\nDown - Add Row Below\nLeft - Add Column To Left\nRight - Add Column To Right\nQ - Back to menu";
	string changePathString1 = "Select a point along your path to start editing.\nTo restart the path, press R.";
	string makingPathString = "Use the Arrow Keys to move.\nE - End the Path.";
	string newPathString = "Please select(click) the start location.";


	sf::Text instructionText(mainEditString, mainFont);
	instructionText.setCharacterSize(GameConstants::FONT_SIZE);
	instructionText.setColor(sf::Color::White);
	instructionText.setPosition(4, GameConstants::MAX_HEIGHT * 32 + 4);

	sf::RenderWindow window(sf::VideoMode(GameConstants::MAX_WIDTH * 32, GameConstants::MAX_HEIGHT * 32 + 96), "Edit a Map");
	window.setKeyRepeatEnabled(false);
	while (window.isOpen()){
		sf::Event sf_event;
		while (window.pollEvent(sf_event)){
			switch (sf_event.type){
			case sf::Event::Closed:{
									   window.close();
			} break;
			case sf::Event::KeyPressed:{
										   switch (sf_event.key.code){
										   case sf::Keyboard::R:{
																	if (changePath){
																		map = new Map(map->getWidth(), map->getHeight());
																		map->setMapName(mapName);
																		changePath = false;
																		newPath = true;
																	}
																	else if (onMenu){
																		onMenu = false;
																		resizeMap = true;
																	}
										   } break;
										   case sf::Keyboard::C:{
																	if (onMenu){
																		onMenu = false;
																		changePath = true;
																	}
										   } break;
										   case sf::Keyboard::Q:{
																	if (resizeMap){
																		resizeMap = false;
																		onMenu = true;
																	}
																	else if (onMenu){
																		window.close();
																	}
										   } break;
										   case sf::Keyboard::E:{
																	if (makingPath && canEnd){
																		makingPath = false;
																		canEnd = false;
																		onMenu = true;
																		map->addEntity(current_x, current_y, new Path(GameConstants::END_IMAGE_NAME));
																	}
										   } break;
										   case sf::Keyboard::Up:{
																	 if (resizeMap && map->getHeight() < GameConstants::MAX_HEIGHT){
																		 map->resize(map->getWidth(), map->getHeight() + 1, false, true);
																	 }
																	 else if (makingPath){
																		 if (canMove(current_x, current_y, current_x, current_y - 1, map)){
																			 --current_y;
																			 map->addEntity(current_x, current_y, new Path());
																			 canEnd = true;
																		 }
																	 }
										   } break;
										   case sf::Keyboard::Down:{
																	   if (resizeMap && map->getHeight() < GameConstants::MAX_HEIGHT){
																		   map->resize(map->getWidth(), map->getHeight() + 1, false, false);
																	   }
																	   else if (makingPath){
																		   if (canMove(current_x, current_y, current_x, current_y + 1, map)){
																			   ++current_y;
																			   map->addEntity(current_x, current_y, new Path());
																			   canEnd = true;
																		   }
																	   }
										   } break;
										   case sf::Keyboard::Left:{
																	   if (resizeMap && map->getWidth() < GameConstants::MAX_WIDTH){
																		   map->resize(map->getWidth() + 1, map->getHeight(), true, false);
																	   }
																	   else if (makingPath){
																		   if (canMove(current_x, current_y, current_x - 1, current_y, map)){
																			   --current_x;
																			   map->addEntity(current_x, current_y, new Path());
																			   canEnd = true;
																		   }
																	   }
										   } break;
										   case sf::Keyboard::Right:{
																		if (resizeMap && map->getWidth() < GameConstants::MAX_WIDTH){
																			map->resize(map->getWidth() + 1, map->getHeight(), false, false);
																		}
																		else if (makingPath){
																			if (canMove(current_x, current_y, current_x + 1, current_y, map)){
																				++current_x;
																				map->addEntity(current_x, current_y, new Path());
																				canEnd = true;
																			}
																		}
										   } break;
										   }
			} break;
			case sf::Event::MouseButtonPressed:{
												   if (sf_event.mouseButton.button == sf::Mouse::Left){
													   int block_x = sf_event.mouseButton.x / 32;
													   int block_y = sf_event.mouseButton.y / 32;
													   if (map->inBounds(block_x, block_y)){
														   if (newPath){
															   map->addEntity(block_x, block_y, new Path(GameConstants::START_IMAGE_NAME));
															   current_x = start_x = block_x;
															   current_y = start_y = block_y;
															   newPath = false;
															   makingPath = true;
														   }
														   else if (changePath && typeid(*map->getEntity(block_x, block_y)) == typeid(Path)){
															   foo(block_x, block_y, map);
															   current_x = start_x = block_x;
															   current_y = start_y = block_y;
															   changePath = false;
															   makingPath = true;
															   if (map->getEntity(block_x, block_y)->getImageName() != GameConstants::START_IMAGE_NAME){
																   canEnd = true;
															   }
														   }
													   }
												   }
			} break;
			}
		}

		window.clear();
		map->printMap(window);
		if (resizeMap){
			instructionText.setString(resizingString);
		}
		else if (changePath){
			instructionText.setString(changePathString1);
		}
		else if (onMenu){
			instructionText.setString(mainEditString);
		}
		else if (newPath){
			instructionText.setString(newPathString);
		}
		else if (makingPath){
			instructionText.setString(makingPathString);
		}
		window.draw(instructionText);
		window.display();
	}
	saveMapPrompt(map, true);
}
/*
Critters stop at wave 9
Decrement user HP && check if User be dead.
Tower Firing, scoring etc...
*/
void startGame(){ //TODO
	Map* map = new Map();
	string scrap;
	if (!openMapPrompt(map)){
		system("cls");
		cout << "------------------------------------\n";
		cout << "\tStart a Game\n";
		cout << "-----------------------------------\n\n";
		cout << "There are no Maps to Play on.\n";
		cout << "Please create a map before starting a game.\n";
		cout << "Enter any value to continue . . .";
		cin >> scrap;
		return;
	}

	do {

		Wave* wave = new Wave();
		int waveNumber = 1;

		towerType = Selection::NA;

		upgradeButton.setPosition(-100, -100);
		sellButton.setPosition(-100, -100);
		nearestStrategyButton.setPosition(-100, -100);
		weakestStrategyButton.setPosition(-100, -100);
		upgradeButtonText.setPosition(-100, -100);
		sellButtonText.setPosition(-100, -100);
		strategyText.setPosition(-100, -100);
		nearestStrategyButton.setPosition(-100, -100);
		weakestStrategyButton.setPosition(-100, -100);
		nearestStrategyText.setPosition(-100, -100);
		weakestStrategyText.setPosition(-100, -100);



		startGameText.setPosition(4, map->getHeight() * 32 + 16);

		normalTowerButton.setPosition(16, map->getHeight() * 32 + 48);
		fireTowerButton.setPosition(64, map->getHeight() * 32 + 48);
		iceTowerButton.setPosition(112, map->getHeight() * 32 + 48);
		thunderTowerButton.setPosition(160, map->getHeight() * 32 + 48);

		towerIcon.setPosition(-100, -100);
		towerInfoText.setPosition(map->getWidth() * 32 + 4, 64);
		towerInfoText.setString("");

		sf::Text pausedText("PAUSED", mainFont);
		pausedText.setColor(sf::Color::White);
		pausedText.setCharacterSize(GameConstants::FONT_SIZE);
		pausedText.setPosition(0, 0);

		GameConstants::resetMoney();
		GameConstants::resetHP();

		sf::Text playerMoneyText(GameConstants::getMoneyString(), mainFont);
		playerMoneyText.setColor(sf::Color::White);
		playerMoneyText.setCharacterSize(GameConstants::FONT_SIZE);
		playerMoneyText.setPosition(map->getWidth() * 32 + 4, map->getHeight() * 32 + 48);

		sf::Text playerHPText(GameConstants::getHPString(), mainFont);
		playerHPText.setColor(sf::Color::White);
		playerHPText.setCharacterSize(GameConstants::FONT_SIZE);
		playerHPText.setPosition(map->getWidth() * 32 + 4, map->getHeight() * 32 + 64);

		sf::Text waveNumberText("Next Wave:\t1", mainFont);
		waveNumberText.setColor(sf::Color::White);
		waveNumberText.setCharacterSize(GameConstants::FONT_SIZE);
		waveNumberText.setPosition(map->getWidth() * 32 + 4, map->getHeight() * 32 + 80);

		vector<Tower*> towerList;

		sf::RenderWindow window(sf::VideoMode(map->getWidth() * 32 + 192, map->getHeight() * 32 + 96), "Starting Game");
		window.setKeyRepeatEnabled(false);
		bool doneGame = false;
		map->printMap(window);
		while (window.isOpen() && !doneGame)
		{
			sf::Event sf_event;
			while (window.pollEvent(sf_event)){
				switch (sf_event.type){
				case sf::Event::Closed:{
										   window.close();
				} break;
				case sf::Event::KeyPressed:{
											   switch (sf_event.key.code){
											   case sf::Keyboard::P:{
																		if (!wave->doneWave()){
																			if (wave->isPaused()){
																				wave->resumeWave();
																			}
																			else{
																				wave->pauseWave();
																			}
																		}
											   }break;
											   case sf::Keyboard::Space:{
																			if (waveNumber >= GameConstants::NUMBER_OF_WAVES){
																				doneGame = true;
																			}
																			else if (wave->doneWave()){
																				wave->createWave(waveNumber++);
																				stringstream ss;
																				ss << "Next Wave:\t" << waveNumber;
																				waveNumberText.setString(ss.str());
																			}
											   }break;
											   }
				} break;
				case sf::Event::MouseButtonPressed:{
													   if (sf_event.mouseButton.button == sf::Mouse::Button::Left){
														   handleClick(sf_event, map, wave->doneWave(), towerList);
													   }
				} break;
				}
			}
			window.clear();
			if (!wave->doneWave()){
				towerAction(towerList, wave->getCritterVector(), wave->isPaused());
				if (!wave->deploy(map)){
					doneGame = true;
				}
			}
			map->printMap(window);
			window.draw(towerIcon);
			window.draw(towerInfoText);
			if (towerType != Selection::NA){
				window.draw(towerSelectionRect);
			}
			window.draw(strategySelectRect);
			window.draw(startGameText);
			window.draw(normalTowerButton);
			window.draw(fireTowerButton);
			window.draw(iceTowerButton);
			window.draw(thunderTowerButton);
			playerMoneyText.setString(GameConstants::getMoneyString());
			window.draw(playerMoneyText);
			playerHPText.setString(GameConstants::getHPString());
			window.draw(playerHPText);
			window.draw(upgradeButton);
			window.draw(sellButton);
			window.draw(upgradeButtonText);
			window.draw(sellButtonText);
			window.draw(strategyText);
			window.draw(nearestStrategyButton);
			window.draw(weakestStrategyButton);
			window.draw(nearestStrategyText);
			window.draw(weakestStrategyText);

			window.draw(waveNumberText);
			if (wave->isPaused()){
				window.draw(pausedText);
			}
			window.display();
		}

		strategySelectRect.setPosition(-100, -100);
		window.close();
		map->loadMap(map->getMapName());
	} while (gameOverPrompt());
}
bool canMove(int current_x, int current_y, int new_x, int new_y, Map* map){
	if (!map->inBounds(new_x, new_y) || (current_x == new_x && current_y == new_y)){
		return false;
	}
	else if (map->numOfNeighborPaths(new_x, new_y) > 1){
		return false;
	}
	return true;
}
bool openMapPrompt(Map* map){
	string errMsg = "", mapList, fileName;
	mapList = getMapList();
	if (mapList == ""){
		return false;
	}
	while (true){
		system("cls");
		cout << "------------------------------------\n";
		cout << "\tOpen a Map\n";
		cout << "-----------------------------------\n\n";
		cout << "File List:\n";
		cout << mapList << endl << endl;
		cout << errMsg << endl << endl;
		cout << "Enter the file name for the map (no spaces): ";
		cin >> fileName;
		errMsg = "";
		if (map->loadMap(fileName)){
			break;
		}
		else{
			errMsg = "***** File Does Not Exist. Please Try Again. *****";
		}
	}
	return true;
}
string getMapList(){
	string fileList = "";
	DIR* dir;
	struct dirent* ent;
	dir = opendir("res/info/maps");
	if (dir != NULL){
		ent = readdir(dir);
		while (ent != NULL){
			if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){
				string temp = ent->d_name;
				fileList += "\n" + temp.substr(0, temp.size() - 8);
			}
			ent = readdir(dir);
		}
		closedir(dir);
	}
	else {
		cout << "Couldn't Open Directory.";
		system("exit");
	}
	return fileList;
}
void handleClick(sf::Event sf_event, Map* map, bool canPlace, vector<Tower*>& towerList){
	int currentTowerIndex = findTowerIndex(currentTower, towerList);
	int x = sf_event.mouseButton.x;
	int y = sf_event.mouseButton.y;
	int block_x = (x - (x % 32)) / 32;
	int block_y = (y - (y % 32)) / 32;
	if (!map->inBounds(block_x, block_y)){ // TODO make use of this for upgrading
		if (upgradeButton.getGlobalBounds().contains(x, y) && canPlace){
			if (GameConstants::spendMoney(currentTower->getUpgradePrice())){
				map->removeEntity(currentTower);
				towerList.erase(towerList.begin() + currentTowerIndex);
				int old_x = currentTower->getSprite().getPosition().x / 32;
				int old_y = currentTower->getSprite().getPosition().y / 32;
				currentTower = new  LevelUpTower(currentTower);
				map->addEntity(old_x, old_y, currentTower);
				towerList.push_back(currentTower);
				setTowerInfo(currentTower, map->getWidth() * 32, true);
			}
			towerSelectionRect.setPosition(-40, -40);
			towerType = Selection::NA;

		}
		else if (sellButton.getGlobalBounds().contains(x, y) && canPlace){
			map->removeEntity(currentTower);
			towerList.erase(towerList.begin() + currentTowerIndex);
			GameConstants::collectMoney(currentTower->getSellPrice());
			towerIcon.setPosition(-100, -100);
			towerInfoText.setString("");

			upgradeButton.setPosition(-100, -100);
			sellButton.setPosition(-100, -100);

			upgradeButtonText.setPosition(-100, -100);
			sellButtonText.setPosition(-100, -100);

			towerSelectionRect.setPosition(-100, -100);
			towerType = Selection::NA;

			currentTower = NULL;
		}
		else if (nearestStrategyButton.getGlobalBounds().contains(x, y)){
			strategySelectRect.setSize(sf::Vector2<float>(nearestStrategyButton.getSize().x + 8, nearestStrategyButton.getSize().y + 8));
			strategySelectRect.setPosition(nearestStrategyButton.getPosition().x - 4, nearestStrategyButton.getPosition().y - 4);
			currentTower->setStrategy(new NearestCritterTowerStrategy());

		}

		else if (weakestStrategyButton.getGlobalBounds().contains(x, y)){
			strategySelectRect.setSize(sf::Vector2<float>(weakestStrategyButton.getSize().x + 8, weakestStrategyButton.getSize().y + 8));
			strategySelectRect.setPosition(weakestStrategyButton.getPosition().x - 4, weakestStrategyButton.getPosition().y - 4);
			currentTower->setStrategy(new WeakestCritterStrategy());
		}
		else if (normalTowerButton.getGlobalBounds().contains(x, y)){
			towerSelectionRect.setPosition(normalTowerButton.getPosition().x - 4, normalTowerButton.getPosition().y - 2);
			towerType = Selection::NORMAL;
			setTowerInfo(new NormalTower(), map->getWidth() * 32, false);
		}
		else if (fireTowerButton.getGlobalBounds().contains(x, y)){
			towerSelectionRect.setPosition(fireTowerButton.getPosition().x - 4, normalTowerButton.getPosition().y - 4);
			towerType = Selection::FIRE;
			setTowerInfo(new FireTower(new NormalTower()), map->getWidth() * 32, false);
		}
		else if (iceTowerButton.getGlobalBounds().contains(x, y)){
			towerSelectionRect.setPosition(iceTowerButton.getPosition().x - 4, normalTowerButton.getPosition().y - 4);
			towerType = Selection::ICE;
			setTowerInfo(new IceTower(new NormalTower()), map->getWidth() * 32, false);
		}
		else if (thunderTowerButton.getGlobalBounds().contains(x, y)) {
			towerSelectionRect.setPosition(thunderTowerButton.getPosition().x - 4, normalTowerButton.getPosition().y - 4);
			towerType = Selection::THUNDER;
			setTowerInfo(new ThunderTower(new NormalTower()), map->getWidth() * 32, false);
		}
		else {
			towerSelectionRect.setPosition(-40, -40);
			towerType = Selection::NA;
		}
		return;
	}
	if (typeid(*(map->getEntity(block_x, block_y))) == typeid(NormalTower) ||
		typeid(*(map->getEntity(block_x, block_y))) == typeid(IceTower) ||
		typeid(*(map->getEntity(block_x, block_y))) == typeid(FireTower) ||
		typeid(*(map->getEntity(block_x, block_y))) == typeid(ThunderTower) ||
		typeid(*(map->getEntity(block_x, block_y))) == typeid(LevelUpTower)
		){
		currentTower = (Tower*)map->getEntity(block_x, block_y);
		setTowerInfo(currentTower, map->getWidth() * 32, true);
		towerSelectionRect.setPosition(-40, -40);
		strategySelectRect.setPosition(-100, -100);
		towerType = Selection::NA;
		if (typeid(*(currentTower->getStrategy())) == typeid(NearestCritterTowerStrategy)){
			strategySelectRect.setSize(sf::Vector2<float>(nearestStrategyButton.getSize().x + 8, nearestStrategyButton.getSize().y + 8));
			strategySelectRect.setPosition(nearestStrategyButton.getPosition().x - 4, nearestStrategyButton.getPosition().y - 4);
		}
		else{
			strategySelectRect.setSize(sf::Vector2<float>(weakestStrategyButton.getSize().x + 8, weakestStrategyButton.getSize().y + 8));
			strategySelectRect.setPosition(weakestStrategyButton.getPosition().x - 4, weakestStrategyButton.getPosition().y - 4);
		}
	}
	else if (canPlace){
		switch (towerType){
		case Selection::NORMAL:{
								   Tower* toAdd = new NormalTower();
								   if (GameConstants::spendMoney(toAdd->getBasePrice())){
									   map->addEntity(block_x, block_y, toAdd);
									   towerList.push_back(toAdd);
								   }
		} break;
		case Selection::FIRE:{
								 Tower* toAdd = new FireTower(new NormalTower());
								 if (GameConstants::spendMoney(toAdd->getBasePrice())){
									 map->addEntity(block_x, block_y, toAdd);
									 towerList.push_back(toAdd);
								 }
		} break;
		case Selection::ICE:{
								Tower* toAdd = new IceTower(new NormalTower());
								if (GameConstants::spendMoney(toAdd->getBasePrice())){
									map->addEntity(block_x, block_y, toAdd);
									towerList.push_back(toAdd);
								}
		} break;
		case Selection::THUNDER:{
									Tower* toAdd = new ThunderTower(new NormalTower());
									if (GameConstants::spendMoney(toAdd->getBasePrice())) {
										map->addEntity(block_x, block_y, toAdd);
										towerList.push_back(toAdd);
									}
		} break;
		}
	}
}
void setTowerInfo(Tower* selectedTower, int mapWidthPixels, bool showButtons){
	currentTower = selectedTower;
	towerIcon = selectedTower->getSprite();
	towerIcon.setPosition(mapWidthPixels + 48, 16);
	string type = "NORMAL";
	if (selectedTower->getImageName() == GameConstants::FIRE_TOWER_IMAGE_NAME){
		type = "FIRE";
	}
	else if (selectedTower->getImageName() == GameConstants::ICE_TOWER_IMAGE_NAME){
		type = "ICE";
	}
	else if (selectedTower->getImageName() == GameConstants::THUNDER_TOWER_IMAGE_NAME) {
		type = "THUNDER";
	}
	stringstream ss;
	ss << "Level:         " << selectedTower->getLevel() << endl;
	ss << "Type:          " << type << endl;
	ss << "Base Price:    " << selectedTower->getBasePrice() << endl;
	ss << "Upgrade Price: " << selectedTower->getUpgradePrice() << endl;
	ss << "Sell Price:    " << selectedTower->getSellPrice() << endl;
	ss << "Damage:        " << selectedTower->getDamage() << endl;
	ss << "Range:         " << selectedTower->getLevel() << endl;
	ss << "Fire Rate      " << selectedTower->getFireRate() << endl;
	string temp;
	towerInfoText.setString(ss.str());

	if (showButtons){
		upgradeButton.setPosition(mapWidthPixels + 4, 148);
		sellButton.setPosition(mapWidthPixels + 84, 148);
		nearestStrategyButton.setPosition(mapWidthPixels + 15, 212);
		weakestStrategyButton.setPosition(mapWidthPixels + 15, 244);
		upgradeButtonText.setPosition(upgradeButton.getPosition().x + 4, upgradeButton.getPosition().y + 6);
		sellButtonText.setPosition(sellButton.getPosition().x + 16, sellButton.getPosition().y + 6);
		strategyText.setPosition(mapWidthPixels + 50, 194);
		nearestStrategyText.setPosition(nearestStrategyButton.getPosition().x + 4, nearestStrategyButton.getPosition().y + 6);
		weakestStrategyText.setPosition(weakestStrategyButton.getPosition().x + 4, weakestStrategyButton.getPosition().y + 6);
	}
	else {
		upgradeButton.setPosition(-100, -100);
		sellButton.setPosition(-100, -100);
		upgradeButtonText.setPosition(-100, -100);
		sellButtonText.setPosition(-100, -100);
		strategyText.setPosition(-100, -100);
		nearestStrategyButton.setPosition(-100, -100);
		nearestStrategyText.setPosition(-100, -100);
		weakestStrategyButton.setPosition(-100, -100);
		weakestStrategyText.setPosition(-100, -100);
	}
}

void resizeMap(Map* map){

}
void changeMapPath(Map* map){

}
bool saveMapPrompt(Map* map, bool overwrite){
	string errMsg = "", fileName = "";
	char input;
	while (true){
		system("cls");
		cout << "------------------------------------\n";
		cout << "\tSaving Map\n";
		cout << "-----------------------------------\n\n";
		cout << errMsg << endl << endl;
		cout << "would you like to save this map? (y/n): ";
		cin >> input;
		errMsg = "";
		if (input == 'n' || input == 'y'){
			break;
		}
		else{
			errMsg = "***** Invalid Input. Please Try Again. *****";
		}
	}
	if (input == 'n'){
		return false;
	}
	errMsg = "";
	if (overwrite){
		cout << map->saveMap(map->getMapName(), true);
		return true;
	}
	while (true){
		system("cls");
		cout << "------------------------------------\n";
		cout << "\tSaving Map\n";
		cout << "-----------------------------------\n\n";
		cout << errMsg << endl << endl;
		cout << "Enter the file name for this map (no spaces): ";
		cin >> fileName;
		errMsg = "";
		if (map->saveMap(fileName, false)){
			break;
		}
		else{
			errMsg = "***** File Already Exists. Please Try Again. *****";
		}
	}

	system("cls");
	cout << "------------------------------------\n";
	cout << "\tSaving Map\n";
	cout << "-----------------------------------\n\n";
	cout << "Map Saved as: \"" << fileName << "\".\n";
	cout << "Enter any value to continue . . .";
	cin >> fileName;
	return true;
}
void foo(int x, int y, Map*& map){
	vector<int> newPath;
	vector<int> oldPath = map->getPath();
	for (int i = 0; i < oldPath.size(); i += 2){
		newPath.push_back(oldPath[i]);
		newPath.push_back(oldPath[i + 1]);
		if (x == oldPath[i] && y == oldPath[i + 1]){
			break;
		}
	}
	string mapName = map->getMapName();
	map = new Map(map->getWidth(), map->getHeight());
	map->setMapName(mapName);
	for (int i = 0; i < newPath.size(); i += 2){
		if (i == 0){
			map->addEntity(newPath[i], newPath[i + 1], new Path(GameConstants::START_IMAGE_NAME));
		}
		else{
			map->addEntity(newPath[i], newPath[i + 1], new Path());
		}
	}
}
void towerAction(vector<Tower*> towerList, vector<Critter*> critterList, bool paused){

	for (int i = 0; i < towerList.size(); ++i){
		if (!paused && towerList[i]->isPaused()){
			towerList[i]->resume();
		}
		else if (paused && !towerList[i]->isPaused()){
			towerList[i]->pause();
		}
		towerList[i]->attack(critterList);
	}
}

int findTowerIndex(Tower* tower, vector<Tower*> towerList){
	for (int i = 0; i < towerList.size(); ++i){
		if (towerList[i] == tower){
			return i;
		}
	}
	return -1;
}

bool gameOverPrompt() {
	string errMsg = "", fileName = "";

	char input;
	while (true){
		system("cls");
		cout << "------------------------------------\n";
		cout << "\tGame Over!\n";
		cout << "-----------------------------------\n\n";
		cout << errMsg << endl << endl;
		cout << "Try again? (y/n): ";
		cin >> input;
		errMsg = "";
		if (input == 'n' || input == 'y'){
			break;
		}
		else{
			errMsg = "***** Invalid Input. Please Try Again. *****";
		}
	}

	if (input == 'n')
		return false;
	else {
		return true;
	}
}