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
	return (x > _borderLeft && x < _borderRight-1);
}

void CDINAUSOR::renderDinausor()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	mX = 8;
	int curX = mX + 2, curY = mY + 1;
	for (int cnt = 0; cnt < _numDino; cnt++) {
		for (int i = 0; i < 5; i++) {
			int befX = curX;
			for (int j = 0; j < 16; j++) {
				Common::setConsoleColor(YELLOW, BRIGHT_WHITE);
				Common::gotoXY(curX, curY);
				if (!isInLane(curX))
					curX = _left + 2;
				std::cout << data[i][j];
				++curX;
			}
			curX = befX;
			++curY;
		}
		curY -= 5;
		curX += 16 + _spaceDino;
	}
}