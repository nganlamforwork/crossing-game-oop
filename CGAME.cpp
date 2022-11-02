#include "CGAME.h"

CGAME::CGAME(int)
{
	drawGame();
}
void CGAME::drawGame() 
{
	Common::clearConsole();
	Common::gotoXY(0, 0);
	Sleep(1500);
}
CGAME::~CGAME() 
{

}