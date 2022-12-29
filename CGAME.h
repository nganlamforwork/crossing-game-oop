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
#include "GUI.h"

class CGAME {
private:
	CDINAUSOR* dino;
	CCAR* car;			
	CTRAFFICLIGHT* lightCar;
	CBIRD* bird;
	CTRUCK* truck;		
	CTRAFFICLIGHT* lightTruck;
	CPEOPLE* people;
	int left = 3, top = 2;
	int NUM_LANE = 6;
	int state;
	bool musicEffect = 1;

public:
	CGAME(bool);
	~CGAME();

	int GetState();
	bool IsWin();

	void Create();
	void Load(string);
	void Save();
	void TogglePlaying();

	void RenderGame();

	void DrawEndGame(string);

	void Start();
	void Move();

private:
	void DrawGame();
	void DrawAsideMenu();
	void DrawLevelNumber(int);
	void UpLevel();
};