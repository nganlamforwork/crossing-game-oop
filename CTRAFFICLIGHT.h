#pragma once
#include <iostream>
#include <fstream>
#include "Common.h"

using namespace std;

class CTRAFFICLIGHT {
	int _direction;
	int mX, mY;
	int _borderLeft, _borderRight, _left, _top;
	int _numLane, _timing, _countDown;
	bool _state;
public:
	CTRAFFICLIGHT(int, int, int, int, int, bool, int);
	~CTRAFFICLIGHT() {};

	bool getState() { return _state; };
	void toggleState();
	void Render();
	void countDown();
	void Save(ofstream&);
	void Load(ifstream&);
};