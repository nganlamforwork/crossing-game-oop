#include "CTRAFFICLIGHT.h"


CTRAFFICLIGHT::CTRAFFICLIGHT(int numLane, int direction, int left, int top, int timing, bool initialState, int curTime)
{
	this->numLane = numLane; this->direction = direction;

	mX = this->left = left; mY = this->top = top + (numLane - 1) * 6;

	borderLeft = left + 1; borderRight = LANE_LENGTH + left + 1;

	state = initialState;
	this->timing = timing;
	countDown = curTime;
}

bool CTRAFFICLIGHT::GetState() 
{ 
	return state; 
};

void CTRAFFICLIGHT::ToggleState()
{ 
	state ^= 1; 
	countDown = timing; 
	Render();
};

void CTRAFFICLIGHT::Render()
{
	if (!direction) {
		mtx.lock();
		Common::gotoXY(borderLeft - 2, mY + 1);
		if (state == RED_LIGHT)
			Common::setConsoleColor(BRIGHT_WHITE, RED);
		else
			Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		putchar(219);
		mtx.unlock();

		mtx.lock();
		Common::gotoXY(borderLeft - 2, mY + 2);
		if (state == GREEN_LIGHT)
			Common::setConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
		else
			Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		putchar(219);
		mtx.unlock();
	}
	else {
		mtx.lock();
		Common::gotoXY(borderRight + 2, mY + 1);
		if (state == RED_LIGHT)
			Common::setConsoleColor(BRIGHT_WHITE, RED);
		else
			Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		putchar(219);
		mtx.unlock();

		mtx.lock();
		Common::gotoXY(borderRight + 2, mY + 2);
		if (state == GREEN_LIGHT)
			Common::setConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
		else
			Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		putchar(219);
		mtx.unlock();
	}
}

void CTRAFFICLIGHT::CountDown()
{
	countDown--;
	if (!countDown) ToggleState();
}

void CTRAFFICLIGHT::Save(ofstream& out)
{
	out << state << ' ' << countDown << '\n';
}

void CTRAFFICLIGHT::Load(ifstream& in)
{
	in >> state >> countDown;
}