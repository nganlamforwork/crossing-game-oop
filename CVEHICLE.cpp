#include "CVEHICLE.h"

CVEHICLE::CVEHICLE(int numLane, int direction, int left, int top, int wait)
{
	_numLane = numLane; _direction = direction;

	_borderLeft = left + 1; _borderRight = LANE_LENGTH + left + 1;

	mX = _left = left; mY = _top = top + (_numLane - 1) * 6;

	_wait = wait;
}

bool CVEHICLE::IsInLane(int x)
{
	return (x > _borderLeft && x < _borderRight - 1);
}

CCAR::CCAR(int numLane, int direction, int left, int top, int wait) : CVEHICLE(numLane, direction, left, top, wait)
{
	_sizeX = 6; _sizeY = 5;

	_num = 4; _space = 10;

	_startPos = _borderLeft + 3;
}

void CCAR::CreateList()
{
	curX.push_back(_startPos);
	curY.push_back(mY + 1);

	for (int i = 1; i < _num; i++) {
		int tmp = curX[i - 1];
		curX.push_back(tmp + 6 + _space);
		curY.push_back(mY + 1);
	}
}

void CCAR::Move()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int prevX;
	for (int cnt = 0; cnt < _num; cnt++) {
		prevX = curX[cnt];
		for (int i = 0; i < _sizeY; i++) {
			for (int j = 0; j < _sizeX; j++) {
				Common::setConsoleColor(BRIGHT_WHITE, BLACK);
				if (!IsInLane(curX[cnt]))
					curX[cnt] = _startPos;
				mtx.lock();
				Common::gotoXY(curX[cnt], curY[cnt]);
				std::cout << data[i][j];
				mtx.unlock();
				curX[cnt] = curX[cnt] + 1;
			}
			curX[cnt] = prevX;
			curY[cnt] = curY[cnt] + 1;
		}
		for (int i = 0; i < _sizeY; i++) {
			mtx.lock();
			Common::gotoXY(prevX - 1, (int)curY[cnt] - i - 1);
			putchar(32);
			Common::gotoXY(_borderRight - 2, (int)curY[cnt] - i - 1);
			putchar(32);
			mtx.unlock();
		}
		curX[cnt] = prevX + 1;
		if (!IsInLane(prevX + 1))
			curX[cnt] = _startPos;
		curY[cnt] = mY + 1;
	}
	Sleep(_wait);
}

CTRUCK::CTRUCK(int numLane, int direction, int left, int top, int wait) : CVEHICLE(numLane, direction, left, top, wait)
{
	_sizeX = 17; _sizeY = 4;

	_num = 4; _space = 10;

	_startPos = _borderRight - 3;
}

void CTRUCK::CreateList()
{
	curX.push_back(_startPos);
	curY.push_back(mY + 1);

	for (int i = 1; i < _num; i++) {
		int tmp = curX[i - 1];
		curX.push_back(tmp - 17 - _space);
		curY.push_back(mY + 1);
	}
}

void CTRUCK::Move()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int prevX;
	for (int cnt = _num - 1; cnt >= 0; cnt--) {
		prevX = curX[cnt];
		for (int i = 0; i < _sizeY; i++) {
			for (int j = _sizeX - 1; j >= 0; j--) {
				Common::setConsoleColor(BRIGHT_WHITE, BLACK);
				if (!IsInLane(curX[cnt]))
					curX[cnt] = _startPos;
				mtx.lock();
				Common::gotoXY(curX[cnt], curY[cnt]);
				std::cout << data[i][j];
				mtx.unlock();

				curX[cnt] = curX[cnt] - 1;
			}
			curX[cnt] = prevX;
			curY[cnt] = curY[cnt] + 1;
		}
		for (int i = 0; i < _sizeY; i++) {
			mtx.lock();
			Common::gotoXY(_borderLeft + 1, (int)curY[cnt] - i - 1);
			putchar(32);
			Common::gotoXY(prevX + 1, (int)curY[cnt] - i - 1);
			putchar(32);
			Common::gotoXY(_borderRight - 2, (int)curY[cnt] - i - 1);
			putchar(32);
			mtx.unlock();
		}

		curX[cnt] = prevX - 1;
		if (!IsInLane(prevX - 1))
			curX[cnt] = _startPos;
		curY[cnt] = mY + 1;
	}
	Sleep(_wait);
}