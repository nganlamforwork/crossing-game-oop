#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <thread>
#include <vector>
#include "Common.h"
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include "CVEHICLE.h"

class CGAME {
	CDINAUSOR* kl;
	CCAR* xe;
	CBIRD* bird;
	CTRUCK* truck;
	CPEOPLE* people;
	int _left = 3, _top = 2;
	int NUM_LANE = 6;

	bool _alive = 1;
public:
	CGAME(int);
	~CGAME();
	void DrawGame();
	void Move();
};