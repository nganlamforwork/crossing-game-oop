#include "CTRAFFICLIGHT.h"


CTRAFFICLIGHT::CTRAFFICLIGHT(int numLane, int direction, int left, int top, int timing)
{
	mX = _left = left;	mY = _top = top; 
	
	_numLane = numLane; _direction = direction;

	_borderLeft = _left + 1;
	_borderRight = LANE_LENGTH + _left + 1;

	_state = GREEN_LIGHT;
	_timing = _countDown = timing;
}

void CTRAFFICLIGHT::Render()
{
	if (!_direction) {
		mtx.lock();
		Common::gotoXY(_borderLeft - 2, mY + 1);
		Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		putchar(219);
		mtx.unlock();

		mtx.lock();
		Common::gotoXY(_borderLeft - 2, mY + 2);
		Common::setConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
		putchar(219);
		mtx.unlock();
	}
	else {
		mtx.lock();
		Common::gotoXY(_borderRight + 2, mY + 1);
		Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		putchar(219);
		mtx.unlock();

		mtx.lock();
		Common::gotoXY(_borderRight + 2, mY + 2);
		Common::setConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
		putchar(219);
		mtx.unlock();
	}
}