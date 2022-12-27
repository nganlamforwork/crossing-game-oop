#include <iostream>
#include "Common.h"
#include "Menu.h"
#include <mutex>

mutex mtx;

int main()
{
	Common::setUpConsole(16);

	Menu menu;
	menu.startApp();

	Common::clearConsole();
}