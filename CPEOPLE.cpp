#include "CPEOPLE.h"

CPEOPLE::CPEOPLE(int numLane, int direction, int left, int top)
{
	_numLane = numLane;
	_direction = direction;
	mX = left + 50;
	mY = top + (_numLane - 1) * 6 + 1;
	_left = left;
	_top = top;
	_borderLeft = _left + 1;
	_borderRight = LANE_LENGTH + _left + 1;
}

void CPEOPLE::RenderPeople(int posX, int posY)
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int curX = posX;
	int curY = posY;
	int sizeX = 5;
	int sizeY = 4;
	int prevX;
	prevX = curX;
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			Common::setConsoleColor(BRIGHT_WHITE, BLACK);
			mtx.lock();
			Common::gotoXY(curX, curY);
			std::cout << data[i][j];
			mtx.unlock();

			curX = curX + 1;
		}
		curX = prevX;
		curY = curY + 1;
	}
}

void CPEOPLE::DeletePeople(int posX, int posY)
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int curX = posX;
	int curY = posY;
	int sizeX = 5;
	int sizeY = 4;
	int prevX;
	prevX = curX;
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			mtx.lock();
			Common::gotoXY(curX, curY);
			putchar(32);
			mtx.unlock();

			curX = curX + 1;
		}
		curX = prevX;
		curY = curY + 1;
	}
}

void CPEOPLE::Left() {
	if (IsInBoard(mX - 1, mY)) {
		mX = mX - 1;
		RenderPeople(mX, mY);
		for (int i = 0; i < 4; i++) {
			mtx.lock();
			Common::gotoXY(mX + 5, mY + i);
			putchar(32);
			mtx.unlock();
		}
	}
}

void CPEOPLE::Right() {
	if (IsInBoard(mX + 1, mY)) {
		mX = mX + 1;
		RenderPeople(mX, mY);
		for (int i = 0; i < 4; i++) {
			mtx.lock();
			Common::gotoXY(mX - 1, mY + i);
			putchar(32);
			mtx.unlock();
		}
	}
}

void CPEOPLE::Up() {
	if (IsInBoard(mX, mY - 6)) {
		DeletePeople(mX, mY);
		mY = mY - 6;
		RenderPeople(mX, mY);
	}
}

void CPEOPLE::Down() {
	if (IsInBoard(mX, mY + 6)) {
		DeletePeople(mX, mY);
		mY = mY + 6;
		RenderPeople(mX, mY);
	}
}

void CPEOPLE::Move() {
	switch (Common::getConsoleInput()) {
	case 2:
		Up();
		break;
	case 3:
		Left();
		break;
	case 4:
		Right();
		break;
	case 5:
		Down();
		break;
	default:
		int x = 0;
	}
}

bool CPEOPLE::IsInBoard(int curX, int curY) {
	if (!(curX > _borderLeft+1 && curX + 5 < _borderRight)) return false;
	if (!(curY > _top && curY + 4 < _top + (_numLane - 1) * 6+6)) return false;
	return true;
}