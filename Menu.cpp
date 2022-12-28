#include "MENU.h"

Menu::Menu()
{
	curOption = 0;
	optionsSize = 4;
	curSubOption = 0;
	subOptionsSize = 3;
	xMenu = 60;
	yMenu = 21;
}

Menu::~Menu()
{
}

////////////////////////////////////////////////////////////////////////////
void Menu::StartApp()
{
	Common::setConsoleColor(BRIGHT_WHITE, AQUA);
	Common::gotoXY(left, top);
	std::cout << "Group 8 - 21CLC08 - HCMUS";

	Common::setConsoleColor(BRIGHT_WHITE, GRAY);
	Common::gotoXY(left - 20, top + 1);
	std::cout << "Tran Binh Kha - Le Vu Ngan Lam - Nguyen Hong Hanh - Huynh Hiep Phat";

	GUI::MainTitle(left, top);

	GUI::Image("images\\flower.txt",xMenu - 38, yMenu + 4, GREEN);
	GUI::Image("images\\flower.txt",xMenu + 40, yMenu + 4, GREEN);

	RenderOptionsMenu();
	RenderOptionsText(options, optionsSize, curOption);

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	ProcessMainInput();
}

////////////////////////////////////////////////////////////////////////////

void Menu::ProcessMainInput()
{
	bool loadMenu = 1;
	while (true) {
		if (!loadMenu) break;
		switch (Common::getConsoleInput()) {
		case 2:									//Up
			ChangeOption(-1, options, curOption, optionsSize);
			break;
		case 5:									//Down
			ChangeOption(1, options, curOption, optionsSize);
			break;
		case 6:									//Enter
			loadMenu = 0;
			break;
		default:
			if (musicEffect) Common::playSound(ERROR_SOUND);
		}
	}

	switch (curOption) {
	case 0:
		curSubOption = 0;
		SubMenu();
		break;
	case 1:
		ShowTutorial();
		break;
	case 2:
		ShowSettings();
		break;
	case 3:
		ExitGame();
		break;
	}
}

void Menu::RenderOptionsMenu()
{
	int left = xMenu, top = yMenu;
	int length = 35, height = optionsSize * 2;

	GUI::Image("images\\borderMenu.txt", left, top, BLACK);
}

void Menu::RenderOptionsText(const std::string optionsArr[], const int& size, const int& optionId)
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int left = xMenu + 12, top = yMenu + 2;
	for (int i = 0; i < size; i++) {
		Common::gotoXY(left, top + i * 2);
		cout << optionsArr[i];
	}
	RenderCurrentOption(optionsArr, size, optionId);
}

void Menu::DeleteOptionsText()
{
	int left = xMenu + 12, top = yMenu + 2;
	for (int i = 0; i < optionsSize; i++) {
		Common::gotoXY(left, top + i * 2);
		cout << "           ";
	}
}

void Menu::RenderCurrentOption(const std::string optionsArr[], const int& size, const int& optionId)
{
	if (musicEffect) Common::playSound(MOVE_SOUND);
	int left = xMenu + 12, top = yMenu + 2;
	Common::setConsoleColor(BRIGHT_WHITE, RED);

	mtx.lock();
	Common::gotoXY(left, top + optionId * 2);
	cout << optionsArr[optionId];

	Common::gotoXY(left - 3, top + optionId * 2);
	putchar(175);
	Common::gotoXY(left + 13, top + optionId * 2);
	putchar(174);
	mtx.unlock();
}

////////////////////////////////////////////////////////////////////////////

int Menu::GetCurrentOption()
{
	return curOption;
}

void Menu::SetCurrentOption(int opt)
{
	curOption = opt;
}

void Menu::OffCurrentOption(const std::string optionsArr[], const int& size, const int& optionId)
{
	int left = xMenu + 12, top = yMenu + 2;
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	mtx.lock();
	Common::gotoXY(left, top + optionId * 2);
	cout << optionsArr[optionId];

	Common::gotoXY(left - 3, top + optionId * 2);
	putchar(' ');
	Common::gotoXY(left + 13, top + optionId * 2);
	putchar(' ');
	mtx.unlock();
}

void Menu::ChangeOption(int direction, const std::string optionsArr[], int& option, const int& size) //-1: Up - 1: Down
{
	int tmp = option + direction;
	if (tmp < 0 || tmp >= size) {
		if (musicEffect) Common::playSound(ERROR_SOUND);
		return;
	}
	OffCurrentOption(optionsArr,size,option);
	option = tmp;
	RenderCurrentOption(optionsArr,size,option);
}

////////////////////////////////////////////////////////////////////////////

void Menu::SubMenu()
{
	DeleteOptionsText();
	RenderOptionsText(subOptions, subOptionsSize, curSubOption);

	bool loadSubMenu = 1;
	while (true) {
		if (!loadSubMenu) break;
		switch (Common::getConsoleInput()) {
		case 2:									//Up
			ChangeOption(-1, subOptions, curSubOption, subOptionsSize);
			break;
		case 5:									//Down
			ChangeOption(1, subOptions, curSubOption, subOptionsSize);
			break;
		case 6:									//Enter
			loadSubMenu = 0;
			break;
		default:
			if (musicEffect) Common::playSound(ERROR_SOUND);
		}
	}

	switch (curSubOption) {
	case 0:
		Play(NEW_GAME);
		break;
	case 1:
		LoadGameScreen();
		break;
	case 2:
		StartApp();
		break;
	}
}

void Menu::LoadGameScreen()
{
	int left = 0, top = 0;
	Common::clearConsole();

	GUI::Image("titles\\LoadGame.txt", 45, 8, RED);
	GUI::Image("images\\flowers.txt", 26, 25, GREEN);

	Common::gotoXY(left + 70, top + 18);
	cout << "Enter your name: ";

	string name;

	do {
		Common::gotoXY(left + 46, top + 19);
		cout << "                                                            ";
		Common::gotoXY(left + 46, top + 19);
		Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		Common::showCursor(1);
		getline(cin, name, '\n');
		name = "data\\" + name + ".txt";

		ifstream tmp(name);
		if (!tmp.fail()) break;
		else {
			Common::showCursor(0);
			Common::setConsoleColor(BRIGHT_WHITE, RED);
			Common::gotoXY(left + 46, top + 21);
			cout << "Please re-enter! Your name does not exits in our database!";
		}
	} while (1);

	Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	Common::gotoXY(left + 46, top + 21);
	Common::showCursor(0);
	cout << "       Get data successfully! Please wait a second!       ";
	Sleep(1000);

	Play(LOAD_GAME, name);
}

void Menu::Play(bool option, string name)
{
	CGAME newGame(musicEffect);
	if (option == NEW_GAME)
		newGame.Create();
	else if (option == LOAD_GAME)
		newGame.Load(name);

	newGame.Start();

	if (newGame.GetState() == QUIT) {
		newGame.DrawEndGame("titles\\QuitNotSave.txt");
	}
	else
		if (newGame.IsWin())
			newGame.DrawEndGame("titles\\YouWin.txt");
		else
			newGame.DrawEndGame("titles\\YouLose.txt");
	Sleep(100);
}

void Menu::Play(bool option)
{
	Play(option, "");
}

void Menu::ShowTutorial()
{
	Common::clearConsole();
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int left = 22, top = 4;						//Left and top of title
	int height = 15, width = 30;

	GUI::Image("titles\\HowToPlay.txt", 22, 4, GREEN);
	GUI::Image("titles\\tutorial.txt", 56, 14, BLACK);
	GUI::Image("images\\menuMonster.txt", 4, 18, AQUA);

	bool loop = 1;
	while (loop) {
		switch (Common::getConsoleInput()) {
		case 8:
			loop = 0;
			break;
		default:
			if (musicEffect) Common::playSound(ERROR_SOUND);
		}
	}
	Common::clearConsole();
	StartApp();
}

void Menu::ShowSettings()
{
	Common::clearConsole();
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	int left = 38, top = 4;						//Left and top of title
	GUI::Image("titles\\Settings.txt", left, top, GREEN);
	left = 83, top = 18;
	GUI::Image("images\\settingsMenu.txt", left, top, BLACK);
	left = 24, top = 18;
	GUI::Image("images\\menuMonster.txt", left, top, AQUA);

	bool loop = 1;
	while (loop) {
		switch (Common::getConsoleInput()) {
		case 8:
			loop = 0;
			break;
		case 12:
			musicEffect = 1;
			break;
		case 13:
			musicEffect = 0;
			break;
		default:
			if (musicEffect) Common::playSound(ERROR_SOUND);
		}
	}
	Common::clearConsole();
	StartApp();
}

void Menu::ExitGame()
{
	Common::clearConsole();
	exit(0);
}