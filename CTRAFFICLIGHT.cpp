#include "CTRAFFICLIGHT.h"


CTRAFFICLIGHT::CTRAFFICLIGHT(int numLane, int direction, int left, int top)
{
	_numLane = numLane;
	_direction = direction;
	mX = _left = left;
	mY = _top = top + (_numLane - 1) * 6;
	_borderLeft = _left + 1;
	_borderRight = LANE_LENGTH + _left + 1;
}

void CTRAFFICLIGHT::Render()
{
	mtx.lock();
	Common::gotoXY(_borderLeft - 2, mY + 1);
	Common::setConsoleColor(BRIGHT_WHITE, RED);
	putchar(219);
	Common::setConsoleColor(BRIGHT_WHITE, RED);
	putchar(219);
	mtx.unlock();

	mtx.lock();
	Common::gotoXY(_borderLeft - 2, mY + 2);
	Common::setConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
	putchar(219);
	Common::setConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
	putchar(219);
	mtx.unlock();
}