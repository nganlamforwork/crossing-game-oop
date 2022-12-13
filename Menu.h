#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>

#include "Common.h"
#include "CGAME.h"

#define EASY 4
#define MEDIUM 6
#define HARD 8

#define NEW_GAME 0
#define LOAD_GAME 1

class Menu
{
	//bool loadEffectTitle = 1;
	const std::string _options[4] = { "Play","Tutorial","Leaderboard","Exit" };
	const std::string _subOptions[3] = { "New Game","Load Game", "Back" };
	int _optionsSize, _curOption;
	int _subOptionsSize, _curSubOption;
	int _xMenu, _yMenu;
	int _left = 60, _top = 1;

public:
	Menu();
	~Menu();

	void startApp();
	void processMainInput();
	void renderGameTitle();
	void renderOptionsMenu();
	void renderOptionsText(const std::string[], const int&, const int&);
	void deleteOptionsText();
	void renderCurrentOption(const std::string[], const int&, const int&);

	void renderFlowers();

	int getCurrentOption();
	void setCurrentOption(int opt);
	void offCurrentOption(const std::string[], const int&, const int&);
	void changeOption(int direction, const std::string[], int&, const int&);

	void subMenu();
	void showTutorial();
	void showLeaderboard();
	void exitGame();

	void play(bool);
};