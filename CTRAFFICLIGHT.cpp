#include "CTRAFFICLIGHT.h"


CTRAFFICLIGHT::CTRAFFICLIGHT(int numLane, int direction, int left, int top, int timing, bool initialState)
{
	_numLane = numLane; _direction = direction;

	mX = _left = left; mY = _top = top + (_numLane - 1) * 6;

	_borderLeft = _left + 1; _borderRight = LANE_LENGTH + _left + 1;

	_state = initialState;
	_timing = _countDown = timing;
}

void CTRAFFICLIGHT::toggleState()
{ 
	_state ^= 1; 
	_countDown = _timing; 
	Render();
};

void CTRAFFICLIGHT::Render()
{
	if (!_direction) {
		mtx.lock();
		Common::gotoXY(_borderLeft - 2, mY + 1);
		if (_state == RED_LIGHT)
			Common::setConsoleColor(BRIGHT_WHITE, RED);
		else
			Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		putchar(219);
		mtx.unlock();

		mtx.lock();
		Common::gotoXY(_borderLeft - 2, mY + 2);
		if (_state == GREEN_LIGHT)
			Common::setConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
		else
			Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		putchar(219);
		mtx.unlock();
	}
	else {
		mtx.lock();
		Common::gotoXY(_borderRight + 2, mY + 1);
		if (_state == RED_LIGHT)
			Common::setConsoleColor(BRIGHT_WHITE, RED);
		else
			Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		putchar(219);
		mtx.unlock();

		mtx.lock();
		Common::gotoXY(_borderRight + 2, mY + 2);
		if (_state == GREEN_LIGHT)
			Common::setConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
		else
			Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		putchar(219);
		mtx.unlock();
	}
}

void CTRAFFICLIGHT::countDown()
{
	_countDown--;
	if (!_countDown) toggleState();
}