#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer.h"

class Observable{
public:
	Observable();
	virtual ~Observable();
	void addObserver(Observer* o);
	void removeObserver(Observer* o);
protected:
	void notify();
private:
	const int observerCap = 10;
	Observer** observers;
};

#endif // OBSERVABLE_H