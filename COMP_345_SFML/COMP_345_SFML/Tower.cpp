#include "Tower.h"
#include "GameConstants.h"
#include <string>

using namespace std;

Tower::Tower() : Entity(GameConstants::TOWER_IMAGE_NAME) {}

string Tower::to_string() {
	stringstream ss;
	ss << "Tower:\n---------------------------------------" << endl;
	ss << "Level:\t\t\t" << getLevel() << endl;
	ss << "Base Price:\t\t" << getBasePrice() << endl;
	ss << "Sell Price:\t\t" << getSellPrice() << endl;
	ss << "Upgrade Price:\t\t" << getUpgradePrice() << endl;
	ss << "Damage:\t\t\t" << getDamage() << endl;
	ss << "Range:\t\t\t" << getRange() << endl;
	ss << "Fire Rate:\t\t" << getFireRate() << endl;
	string str = ss.str();
	return str;
}