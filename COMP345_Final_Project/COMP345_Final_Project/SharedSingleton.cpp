#include "SharedSingleton.h"
#include "TowerController.h"

SharedSingleton* SharedSingleton::ss_ptr = NULL;
TowerController* SharedSingleton::tc_ptr = NULL;

SharedSingleton::SharedSingleton(){
	money = 4000;
	tc_ptr = new TowerController();
}
SharedSingleton* SharedSingleton::getInstance(){
	if (!ss_ptr){
		ss_ptr = new SharedSingleton();
	}
	return ss_ptr;
}