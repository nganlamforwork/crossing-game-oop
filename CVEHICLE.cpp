#include "CVEHICLE.h"

CCAR::CCAR(int numLane, int direction, int left, int top)
{
	_numLane = numLane;
	_direction = direction;
	_numCar = 4;
	_spaceCar = 10;
	mX = _left = left;
	mY = _top = top + (_numLane - 1) * 6;
	_borderLeft = _left + 1;
	_borderRight = LANE_LENGTH + _left + 1;
}

bool CCAR::isInLane(int x)
{
	return (x > _borderLeft && x < _borderRight - 1);
}

void CCAR::renderCar()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	vector<int> curX;
	vector<int> curY;
	int sizeX = 6;
	int sizeY = 5;
	int startPos = _left + 3;
	curX.push_back(startPos);
	curY.push_back(mY + 1);
	for (int i = 1; i < _numCar; i++) {
		int tmp = curX[i - 1];
		curX.push_back(tmp + 16 + _spaceCar);
		curY.push_back(mY + 1);
	}
	int prevX;
	while (true) {
		Sleep(100);
		for (int cnt = 0; cnt < _numCar; cnt++) {
			prevX = curX[cnt];
			for (int i = 0; i < sizeY; i++) {
				for (int j = 0; j < sizeX; j++) {
					Common::setConsoleColor(BRIGHT_WHITE, BLACK);
					if (!isInLane(curX[cnt]))
						curX[cnt] = startPos;
					Common::gotoXY(curX[cnt], curY[cnt]);
					std::cout << data[i][j];
					curX[cnt] = curX[cnt] + 1;
				}
				curX[cnt] = prevX;
				curY[cnt] = curY[cnt] + 1;
			}
			for (int i = 0; i < sizeY; i++) {
				Common::gotoXY(prevX - 1, (int)curY[cnt] - i - 1);
				putchar(32);
				Common::gotoXY(_borderRight - 2, (int)curY[cnt] - i - 1);
				putchar(32);
			}
			curX[cnt] = prevX + 1;
			if (!isInLane(prevX + 1))
				curX[cnt] = startPos;
			curY[cnt] = mY + 1;
		}
	}
}

CTRUCK::CTRUCK(int numLane, int direction, int left, int top)
{
	_numLane = numLane;
	_direction = direction;
	_numTruck = 4;
	_spaceTruck = 10;
	mX = _left = left;
	mY = _top = top + (_numLane - 1) * 6;
	_borderLeft = _left + 1;
	_borderRight = LANE_LENGTH + _left + 1;
}

bool CTRUCK::isInLane(int x)
{
	return (x > _borderLeft && x < _borderRight - 1);
}

void CTRUCK::renderTruck()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	vector<int> curX;
	vector<int> curY;
	int sizeX = 17;
	int sizeY = 4;
	int startPos = _left + 3;
	curX.push_back(startPos);
	curY.push_back(mY + 1);
	for (int i = 1; i < _numTruck; i++) {
		int tmp = curX[i - 1];
		curX.push_back(tmp + 16 + _spaceTruck);
		curY.push_back(mY + 1);
	}
	int prevX;
	while (true) {
		Sleep(100);
		for (int cnt = 0; cnt < _numTruck; cnt++) {
			prevX = curX[cnt];
			for (int i = 0; i < sizeY; i++) {
				for (int j = 0; j < sizeX; j++) {
					Common::setConsoleColor(BRIGHT_WHITE, BLACK);
					if (!isInLane(curX[cnt]))
						curX[cnt] = startPos;
					Common::gotoXY(curX[cnt], curY[cnt]);
					std::cout << data[i][j];
					curX[cnt] = curX[cnt] + 1;
				}
				curX[cnt] = prevX;
				curY[cnt] = curY[cnt] + 1;
			}
			for (int i = 0; i < sizeY; i++) {
				Common::gotoXY(prevX - 1, (int)curY[cnt] - i - 1);
				putchar(32);
				Common::gotoXY(_borderRight - 2, (int)curY[cnt] - i - 1);
				putchar(32);
			}
			curX[cnt] = prevX + 1;
			if (!isInLane(prevX + 1))
				curX[cnt] = startPos;
			curY[cnt] = mY + 1;
		}
	}
}