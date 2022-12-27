#include "MENU.h"

//mutex mtx;

Menu::Menu()
{
	_curOption = 0;
	_optionsSize = 4;
	_curSubOption = 0;
	_subOptionsSize = 3;
	_xMenu = 60;
	_yMenu = 21;
}
Menu::~Menu()
{
}

////////////////////////////////////////////////////////////////////////////
void Menu::startApp()
{
	Common::setConsoleColor(BRIGHT_WHITE, AQUA);
	Common::gotoXY(_left, _top);
	std::cout << "Group 8 - 21CLC08 - HCMUS";
	renderFlowers();
	renderOptionsMenu();
	renderOptionsText(_options, _optionsSize, _curOption);
	renderGameTitle();
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	processMainInput();
}

void Menu::processMainInput()
{
	bool loadMenu = 1;
	while (true) {
		if (!loadMenu) break;
		switch (Common::getConsoleInput()) {
		case 2:									//Up
			changeOption(-1, _options, _curOption, _optionsSize);
			break;
		case 5:									//Down
			changeOption(1, _options, _curOption, _optionsSize);
			break;
		case 6:									//Enter
			if (_curOption !=2) loadMenu = 0;
			else
				Common::playSound(ERROR_SOUND);
			break;
		default:
			Common::playSound(ERROR_SOUND);
		}
	}

	switch (_curOption) {
	case 0:
		_curSubOption = 0;
		subMenu();
		break;
	case 1:
		showTutorial();
		break;
	case 2:
		Common::playSound(ERROR_SOUND);
		break;
	case 3:
		exitGame();
		break;
	}
}

void Menu::renderGameTitle()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	unsigned char M[] = {
						' ', '_', '_', ' ',' ', ' ',' ','_','_', ' ', ' ', ' ',
						'/', '\\',' ', '"','-', '.','/',' ',' ', '\\',' ', ' ',
						'\\',' ', '\\',' ','\\','-','.','/','\\',' ', '\\',' ',
						' ','\\',' ','\\','_','\\',' ','\\',' ','\\','_','\\',
						' ',' ','\\','/','_','/',' ',' ','\\','/','_','/'
	};
	unsigned char A[] = {
						' ','_','_','_','_','_','_',' ',' ',' ',
						'/','\\',' ',' ','_','_',' ','\\',' ',' ',
						'\\',' ','\\',' ',' ','_','_',' ','\\',' ',
						' ','\\',' ','\\','_','\\',' ','\\','_','\\',
						' ',' ','\\','/','_','/','\\','/','_','/'
	};
	unsigned char T[] = {
						' ','_','_','_','_','_','_',' ',
						'/','\\','_','_',' ',' ','_','\\',
						'\\','/','_','/','\\',' ','\\','/',
						' ',' ',' ','\\',' ','\\','_','\\',
						' ',' ',' ',' ','\\','/','_','/'
	};
	unsigned char C[] = {
						' ','_','_','_','_','_','_',' ',' ',' ',
						'/','\\',' ',' ','_','_','_','\\',' ',' ',
						'\\',' ','\\',' ','\\','_','_','_','_',' ',
						' ','\\',' ','\\','_','_','_','_','_','\\',
						' ',' ','\\','/','_','_','_','_','_','/',
	};
	unsigned char H[] = {
						' ','_','_',' ',' ','_','_',' ',' ',' ',
						'/','\\',' ','\\','_','\\',' ','\\',' ',' ',
						'\\',' ','\\',' ',' ','_','_',' ','\\',' ',
						' ','\\',' ','\\','_','\\',' ','\\','_','\\',
						' ',' ','\\','/','_','/','\\','/','_','/',
	};
	unsigned char I[] = {
						' ','_','_',' ',' ',' ',
						'/','\\',' ','\\',' ',' ',
						'\\',' ','\\',' ','\\',' ',
						' ','\\',' ','\\','_','\\',
						' ',' ','\\','/','_','/',
	};
	unsigned char N[] = {
						' ','_','_',' ',' ',' ','_','_',' ',' ',' ',
						'/','\\',' ','"','-','.','\\',' ','\\',' ',' ',
						'\\',' ','\\',' ','\\','-','.',' ',' ','\\',' ',
						' ','\\',' ','\\','_','\\','\\','"','\\','_','\\',
						' ',' ','\\','/','_','/',' ','\\','/','_','/',
	};
	unsigned char G[] = {
						' ','_','_','_','_','_','_',' ',' ',' ',
						'/','\\',' ',' ','_','_','_','\\',' ',' ',
						'\\',' ','\\',' ','\\','_','_',' ','\\',' ',
						' ','\\',' ','\\','_','_','_','_','_','\\',
						' ',' ','\\','/','_','_','_','_','_','/',
	};
	unsigned char E[] = {
						' ','_','_','_','_','_','_',' ',' ',' ',
						'/','\\',' ',' ','_','_','_','\\',' ',' ',
						'\\',' ','\\',' ',' ','_','_','\\',' ',' ',
						' ','\\',' ','\\','_','_','_','_','_','\\',
						' ',' ','\\','/','_','_','_','_','_','/',
	};
	unsigned char R[] = {
						' ','_','_','_','_','_','_',' ',' ',' ',
						'/','\\',' ',' ','=','=',' ','\\',' ',' ',
						'\\',' ','\\',' ',' ','_','_','<',' ',' ',
						' ','\\',' ','\\','_','\\',' ','\\','_','\\',
						' ',' ','\\','/','_','/','/',' ','_','/',
	};
	unsigned char O[] = {
						' ','_','_','_','_','_','_',' ',' ',' ',' ',
						'/','\\',' ',' ','_','_',' ','\\',' ',' ',
						' ','\\',' ','\\',' ','\\','/','\\',' ','\\',' ',
						' ',' ','\\',' ','\\','_','_','_','_','_','\\',
						' ',' ',' ','\\','/','_','_','_','_','_','/',' '
	};
	unsigned char S[] = {
						' ','_','_','_','_','_','_',' ',' ',' ',
						'/','\\',' ',' ','_','_','_','\\',' ',' ',
						'\\',' ','\\','_','_','_',' ',' ','\\',' ',
						' ','\\','/','\\','_','_','_','_','_','\\',
						' ',' ','\\','/','_','_','_','_','_','/'
	};
	unsigned char space[] = {
						' ',' ',' ',' ',
						' ',' ',' ',' ',
						' ',' ',' ',' ',
						' ',' ',' ',' ',
						' ',' ',' ',' '
	};


	unsigned char* word[] = { C, R, O, S, S, I, N, G, G, A, M, E };
	int sizeOfWord = (sizeof(word) / sizeof(word[0]));
	int wide[] = { 10, 10, 11, 10, 10, 6, 11, 10, 10, 10, 12, 10 };
	int color[] = { AQUA, LIGHT_AQUA, LIGHT_BLUE, BLUE, LIGHT_PURPLE, PURPLE };

	int colorCount = 0, left = 0;
	int loop = 1;
	while (loop--) {

		left = _left - 26;
		for (int i = 0; i < sizeOfWord; i++) {
			for (int j = 0; j < 5; j++) {
				for (int k = 0; k < wide[i]; k++) {
					mtx.lock();
					Common::setConsoleColor(BRIGHT_WHITE, color[colorCount % 6]);
					if (i > 7) Common::gotoXY(left + k, _top + 11 + j);
					else Common::gotoXY(left + k, _top + 5 + j);
					putchar(word[i][j * wide[i] + k]);
					mtx.unlock();
				}
			}
			left += wide[i] + 1;
			if (i == 7) left = _left - 8;
		}
		Sleep(200);
		colorCount++;
	}
}

void Menu::renderOptionsMenu()
{
	int left = _xMenu, top = _yMenu;
	int length = 35, height = _optionsSize * 2;

	std::ifstream bg;
	bg.open("images\\borderMenu.txt");

	int i = 0;
	std::string line;
	while (!bg.eof()) {
		getline(bg, line);
		Common::gotoXY(left, top + i);
		Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		cout << line << '\n';
		i++;
	}
	bg.close();

}

void Menu::renderOptionsText(const std::string optionsArr[], const int& size, const int& optionId)
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int left = _xMenu + 12, top = _yMenu + 2;
	for (int i = 0; i < size; i++) {
		Common::gotoXY(left, top + i * 2);
		cout << optionsArr[i];
	}
	renderCurrentOption(optionsArr, size, optionId);
}

void Menu::deleteOptionsText()
{
	int left = _xMenu + 12, top = _yMenu + 2;
	for (int i = 0; i < _optionsSize; i++) {
		Common::gotoXY(left, top + i * 2);
		cout << "           ";
	}
}

void Menu::renderCurrentOption(const std::string optionsArr[], const int& size, const int& optionId)
{
	Common::playSound(MOVE_SOUND);
	int left = _xMenu + 12, top = _yMenu + 2;
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

void Menu::renderFlowers()
{
	Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	std::ifstream bg;
	bg.open("images\\flower.txt");

	int i = 0;
	std::string line;
	while (!bg.eof()) {
		getline(bg, line);

		Common::gotoXY(_xMenu - 38, _yMenu + 4 + i);
		cout << line << '\n';

		Common::gotoXY(_xMenu + 40, _yMenu + 4 + i);
		cout << line << '\n';

		i++;
	}
	bg.close();
}

////////////////////////////////////////////////////////////////////////////

int Menu::getCurrentOption()
{
	return _curOption;
}

void Menu::setCurrentOption(int opt)
{
	_curOption = opt;
}

void Menu::offCurrentOption(const std::string optionsArr[], const int& size, const int& optionId)
{
	int left = _xMenu + 12, top = _yMenu + 2;
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

void Menu::changeOption(int direction, const std::string optionsArr[], int& option, const int& size) //-1: Up - 1: Down
{
	int tmp = option + direction;
	if (tmp < 0 || tmp >= size) {
		Common::playSound(ERROR_SOUND);
		return;
	}
	offCurrentOption(optionsArr,size,option);
	option = tmp;
	renderCurrentOption(optionsArr,size,option);
}

////////////////////////////////////////////////////////////////////////////

void Menu::subMenu()
{
	deleteOptionsText();
	renderOptionsText(_subOptions, _subOptionsSize, _curSubOption);

	bool loadSubMenu = 1;
	while (true) {
		if (!loadSubMenu) break;
		switch (Common::getConsoleInput()) {
		case 2:									//Up
			changeOption(-1, _subOptions, _curSubOption, _subOptionsSize);
			break;
		case 5:									//Down
			changeOption(1, _subOptions, _curSubOption, _subOptionsSize);
			break;
		case 6:									//Enter
			loadSubMenu = 0;
			break;
		default:
			Common::playSound(ERROR_SOUND);
		}
	}

	switch (_curSubOption) {
	case 0:
		play(NEW_GAME);
		break;
	case 1:
		loadGameScreen();
		break;
	case 2:
		startApp();
		break;
	}
}

void Menu::loadGameScreen()
{
	int left = 0, top = 0;
	Common::clearConsole();
	ifstream endgame("titles\\LoadGame.txt");
	string s;
	int i = 0;

	Common::setConsoleColor(BRIGHT_WHITE, RED);
	while (!endgame.eof()) {
		Common::gotoXY(left + 45, top + 8 + i);
		getline(endgame, s);
		cout << s;
		i++;
	}
	endgame.close();

	Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	ifstream bg;
	bg.open("images\\flowers.txt");

	i = 0;
	string line;
	while (!bg.eof()) {
		Common::gotoXY(left + 26, top + 25 + i);
		getline(bg, line);
		cout << line << '\n';
		i++;
	}
	bg.close();

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
			cout << "Please re-enter! Your name does not exit in our database!";
		}
	} while (1);

	Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	Common::gotoXY(left + 46, top + 21);
	Common::showCursor(0);
	cout << "       Get data successfully! Please wait 1 second!      ";
	Sleep(1000);

	play(LOAD_GAME, name);
}

void Menu::play(bool option, string name)
{
	CGAME newGame;
	if (option == NEW_GAME)
		newGame.Create();
	else if (option == LOAD_GAME)
		newGame.Load(name);

	newGame.Start();

	if (newGame.getState() == QUIT) {
		newGame.Save();
		newGame.DrawEndGame("titles\\QuitNotSave.txt");
	}
	else
		if (newGame.isWin())
			newGame.DrawEndGame("titles\\YouWin.txt");
		else
			newGame.DrawEndGame("titles\\YouLose.txt");
	Sleep(100);
}

void Menu::play(bool option)
{
	play(option, "");
}

void Menu::showTutorial()
{
	Common::clearConsole();
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int left = 22, top = 4;						//Left and top of title
	int height = 15, width = 30;

	ifstream in;
	in.open("titles\\HowToPlay.txt");
	string s;
	int i = 0;

	Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	while (getline(in, s)) {
		Common::gotoXY(left, top + i);
		cout << s;
		i++;
	}
	in.close();

	left = 56, top = 14;

	in.open("titles\\tutorial.txt");
	i = 0;

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	while (getline(in, s)) {
		Common::gotoXY(left, top + i);
		cout << s;
		i++;
	}
	in.close();

	left = 4, top = 18;

	in.open("images\\menuMonster.txt");
	i = 0;

	Common::setConsoleColor(BRIGHT_WHITE, AQUA);
	while (getline(in, s)) {
		Common::gotoXY(left, top + i);
		cout << s;
		i++;
	}
	in.close();

	bool loop = 1;
	while (loop) {
		switch (Common::getConsoleInput()) {
		case 8:
			loop = 0;
			break;
		default:
			Common::playSound(ERROR_SOUND);
		}
	}
	Common::clearConsole();
	startApp();
}

void Menu::exitGame()
{
	Common::clearConsole();
	exit(0);
}