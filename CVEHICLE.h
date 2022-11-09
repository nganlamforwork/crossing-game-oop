#pragma once
#include <iostream>
#include <vector>
#include "Common.h"

class CVEHICLE {
protected:
	int mX, mY;
	int _borderLeft, _borderRight;
public:
	//virtual void Move(int, int);
};

class CTRUCK : public CVEHICLE {
public:
	//…
};

class CCAR : public CVEHICLE {
	int _numLane, _direction, _numCar, _spaceCar, _left, _top;
	const char data[5][6] = { {' ',' ','_','_',' ',' '},
		{' ',' ','_','_',' ',' '},
								{' ','(',' ','o',')',' '},
								{'(','o','\\','/','o',')'},
								{' ','\"',' ',' ','\"',' '} };
private:
	bool isInLane(int);

public:
	CCAR(int, int, int, int);
	~CCAR();
	void renderCar();


};