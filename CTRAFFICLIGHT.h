#pragma once
#include <iostream>
#include "Common.h"

using namespace std;

class CTRAFFICLIGHT {
	int _direction;
	int mX, mY;
	int _borderLeft, _borderRight, _left, _top;
	int _numLane;
public:
	CTRAFFICLIGHT(int, int, int, int);
	~CTRAFFICLIGHT() {};
	void Render();
};