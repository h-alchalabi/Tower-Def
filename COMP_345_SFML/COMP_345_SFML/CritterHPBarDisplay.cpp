#include "CritterHPBarDisplay.h"

CritterHPBarDisplay::CritterHPBarDisplay(Critter* critter) {
	this->critter = critter;
}

CritterHPBarDisplay::~CritterHPBarDisplay(){}

void CritterHPBarDisplay::update() {
	// sets the HPBarLength as HP changes
	critter->setHPBarLength(critter->getHP() * 28 / critter->getMaxHP());
}
