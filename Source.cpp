#include <iostream>
#include "Common.h"
#include "Menu.h"

int main()
{
	Common::setUpConsole(18);

	Menu menu;
	menu.startApp();

	Common::clearConsole();
}