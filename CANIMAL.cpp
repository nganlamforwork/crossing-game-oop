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
	return (x > _borderLeft && x < _borderRight);
}

void CDINAUSOR::renderDinausor()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int cnt = 0; cnt < _numDino; cnt++)
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 16; j++) {
				Common::gotoXY(mX + j + 4 + cnt * (16 + _spaceDino), mY + i + 1);
				if (isInLane(mX + j + 4 + cnt * (16 + _spaceDino)))
					std::cout << data[i][j];
			}
}