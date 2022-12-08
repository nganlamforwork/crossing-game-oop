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
#include "CTRAFFICLIGHT.h"

class CGAME {
	CDINAUSOR* dino;	CTRAFFICLIGHT* lightDino;
	CCAR* car;			CTRAFFICLIGHT* lightCar;
	CBIRD* bird;		CTRAFFICLIGHT* lightBird;
	CTRUCK* truck;		CTRAFFICLIGHT* lightTruck;
	CPEOPLE* people;
	int _left = 3, _top = 2;
	int NUM_LANE = 6;

public:
	CGAME(int);
	~CGAME();
	void DrawGame();
	void Move();
};