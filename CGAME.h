#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <thread>
#include <vector>
#include "COMMON.h"
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include "CVEHICLE.h"
#include "CTRAFFICLIGHT.h"

class CGAME {
private:
	CDINAUSOR* dino;
	CCAR* car;			CTRAFFICLIGHT* lightCar;
	CBIRD* bird;
	CTRUCK* truck;		CTRAFFICLIGHT* lightTruck;
	CPEOPLE* people;
	int _left = 3, _top = 2;
	int NUM_LANE = 6;
	int _state;


	void UpLevel();

public:
	CGAME();
	~CGAME();

	int getState() { return _state; };
	bool isWin() { return people->getLevel() == 6; };

	void Create();
	void Load(string);
	void Save();
	void togglePlaying();

	void DrawGame();
	void DrawAsideMenu();
	void DrawLevelNumber(int);
	void RenderGame();

	void DrawEndGame(string);

	void Start();
	void Move();
};