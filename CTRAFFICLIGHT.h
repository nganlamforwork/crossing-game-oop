#pragma once
#include <iostream>
#include <fstream>
#include "COMMON.h"

using namespace std;

class CTRAFFICLIGHT {
	int direction;
	int mX, mY;
	int borderLeft, borderRight, left, top;
	int numLane, timing, countDown;
	bool state;
public:
	CTRAFFICLIGHT(int, int, int, int, int, bool, int);
	~CTRAFFICLIGHT() {};

	bool GetState();
	void ToggleState();

	void Render();

	void CountDown();

	void Save(ofstream&);
	void Load(ifstream&);
};