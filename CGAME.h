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
	int _state;

public:
	CGAME(int);
	~CGAME();

	void RenderGame();

	void Create();
	void Load();
	void Save();

	int getState() { return _state; };

	void DrawLevelNumber(int);
	void DrawGame();
	void DrawAsideMenu();
	void Move();
	bool isWin() { return people->getLevel() == 6; };
};