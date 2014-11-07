#include "SharedSingleton.h"

SharedSingleton* SharedSingleton::ss_ptr = NULL;

SharedSingleton::SharedSingleton(){
	money = 4000;
	//towerController = new TowerController();
}
SharedSingleton* SharedSingleton::getInstance(){
	if (!ss_ptr){
		ss_ptr = new SharedSingleton();
	}
	return ss_ptr;
}