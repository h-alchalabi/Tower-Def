#include "Tower.h"
#include "GameConstants.h"
#include <string>

using namespace std;

Tower::Tower() : Entity(GameConstants::TOWER_IMAGE_NAME){}

Tower::Tower(int x, int y, int level, int damage, int range, int fireRate, int basePrice, int sellPrice,
	int upgradedPrice) : Entity(GameConstants::TOWER_IMAGE_NAME) {
	this->x = x;
	this->y = y;
	this->level = level;
	this->damage = damage;
	this->range = range;
	this->fireRate = fireRate;
	this->basePrice = basePrice;
	this->sellPrice = sellPrice;
	this->upgradedPrice = upgradedPrice;
}

int Tower::getX() {
	return x;
}

int Tower::getY() {
	return y;
}

int Tower::getLevel() {
	return level;
}

int Tower::getDamage() {
	return damage;
}

int Tower::getRange() {
	return range;
}

int Tower::getFireRate() {
	return fireRate;
}

int Tower::getBasePrice() {
	return basePrice;
}

int Tower::getSellPrice() {
	return sellPrice;
}

int Tower::getUpgradePrice() {
	return upgradedPrice;
}

void Tower::setX(int x) {
	this->x = x;
}

void Tower::setY(int y) {
	this->y = y;
}

void Tower::setLevel(int level) {
	this->level = level;
}

void Tower::setDamage(int damage) {
	this->damage = damage;
}

void Tower::setRange(int range) {
	this->range = range;
}

void Tower::setFireRate(int fireRate) {
	this->fireRate = fireRate;
}

void Tower::setBasePrice(int basePrice) {
	this->basePrice = basePrice;
}

void Tower::setSellPrice(int sellPrice) {
	this->sellPrice = sellPrice;
}

void Tower::setUpgradedPrice(int upgradedPrice) {
	this->upgradedPrice = upgradedPrice;
}

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