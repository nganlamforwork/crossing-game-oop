#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include "Common.h"
#include "CANIMAL.h"
#include "CVEHICLE.h"
#include <thread>

class CGAME {
	CDINAUSOR* kl;
	CCAR* xe;
	CBIRD* bird;
	CTRUCK* truck;
	int _left = 1, _top = 1;
	int NUM_LANE = 6;
public:
	CGAME(int);
	void drawGame();
	~CGAME();
};