#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>

#include "COMMON.h"
#include "CGAME.h"
#include "GUI.h"

#define NEW_GAME 0
#define LOAD_GAME 1

class Menu
{
	const std::string options[4] = { "Play","Tutorial", "Settings", "Exit" };
	const std::string subOptions[3] = { "New Game","Load Game", "Back" };
	int optionsSize, curOption;
	int subOptionsSize, curSubOption;
	int xMenu, yMenu;
	int left = 60, top = 1;
	bool musicEffect = 1;

public:
	Menu();
	~Menu();

	void StartApp();

private: 
	void ProcessMainInput();
	void RenderOptionsText(const std::string[], const int&, const int&);
	void DeleteOptionsText();

	int GetCurrentOption();
	void SetCurrentOption(int opt);

	void OnCurrentOption(const std::string[], const int&, const int&);
	void OffCurrentOption(const std::string[], const int&, const int&);
	void ChangeOption(int direction, const std::string[], int&, const int&);

	void SubMenu();
	void ShowTutorial();
	void ShowSettings();
	void ExitGame();

	void LoadGameScreen();

	void Play(bool, string);
	void Play(bool);
};