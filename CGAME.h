#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include "Common.h"
#include "CANIMAL.h"

class CGAME {
	CDINAUSOR* kl;
	int _left = 1, _top = 1;
	int NUM_LANE = 6;
public:
	CGAME(int);
	void drawGame();
	~CGAME();
};