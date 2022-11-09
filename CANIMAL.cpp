#include "CANIMAL.h"

CDINAUSOR::CDINAUSOR(int numLane, int direction, int left, int top)
{
	_numLane = numLane;
	_direction = direction;
	_numDino = 5;
	_spaceDino = 6;
	mX = _left = left;
	mY = _top = top;
	_borderLeft = _left + 1;
	_borderRight = LANE_LENGTH + _left + 1;
}

bool CDINAUSOR::isInLane(int x)
{
	return (x > _borderLeft && x < _borderRight - 1);
}

void CDINAUSOR::renderDinausor()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	mX = 30;
	int curX = 0, curY = 0, prevX;
	while (true) {
		mX += 2;
		curX = mX + 2;
		curY = mY + 1;
		Sleep(100);
		for (int cnt = 0; cnt < _numDino; cnt++) {
			for (int i = 0; i < 5; i++) {
				prevX = curX;
				for (int j = 0; j < 16; j++) {
					Common::setConsoleColor(BRIGHT_WHITE, BLACK);
					Common::gotoXY(curX, curY);
					if (!isInLane(curX))
						curX = _left + 2;
					std::cout << data[i][j];
					++curX;
				}
				curX = prevX;
				++curY;
			}
			//Sleep(200);
			for (int i = 0; i < 5; i++) {
				Common::gotoXY(prevX - 1, curY - i - 1);
				putchar(32);
				Common::gotoXY(prevX - 2, curY - i - 1);
				putchar(32);
			}
			curY -= 5;
			curX += 16 + _spaceDino;
		}
	}
}