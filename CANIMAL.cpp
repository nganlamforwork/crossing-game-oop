#include "CANIMAL.h"

mutex mAnimal;

CDINAUSOR::CDINAUSOR(int numLane, int direction, int left, int top)
{
	_numLane = numLane;
	_direction = direction;
	_numDino = 2;
	_spaceDino = 10;
	mX = _left = left;
	mY = _top = top + (_numLane - 1) * 6;
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
	vector<int> curX;
	vector<int> curY;
	int sizeX = 16;
	int sizeY = 5;
	int startPos = _left + 3;
	curX.push_back(startPos);
	curY.push_back(mY + 1);
	for (int i = 1; i < _numDino; i++) {
		int tmp = curX[i - 1];
		curX.push_back(tmp + 16 + _spaceDino);
		curY.push_back(mY + 1);
	}
	int prevX;
	while (true) {
		Sleep(100);
		for (int cnt = 0; cnt < _numDino; cnt++) {
			prevX = curX[cnt];
			for (int i = 0; i < sizeY; i++) {
				for (int j = 0; j < sizeX; j++) {
					Common::setConsoleColor(BRIGHT_WHITE, BLACK);
					if (!isInLane(curX[cnt]))
						curX[cnt] = startPos;
					mmm.lock();
					Common::gotoXY(curX[cnt], curY[cnt]);
					std::cout << data[i][j];
					mmm.unlock();
					curX[cnt] = curX[cnt] + 1;
				}
				curX[cnt] = prevX;
				curY[cnt] = curY[cnt] + 1;
			}
			for (int i = 0; i < sizeY; i++) {
			mmm.lock();
				Common::gotoXY(prevX - 1, (int)curY[cnt] - i - 1);
				putchar(32);
				Common::gotoXY(_borderRight - 2, (int)curY[cnt] - i - 1);
				putchar(32);

			mmm.unlock();
			}
			curX[cnt] = prevX + 1;
			if (!isInLane(prevX + 1))
				curX[cnt] = startPos;
			curY[cnt] = mY + 1;
		}
	}
}

CBIRD::CBIRD(int numLane, int direction, int left, int top)
{
	_numLane = numLane;
	_direction = direction;
	_numBird = 2;
	_spaceBird = 10;
	mX = _left = left;
	mY = _top = top + (_numLane - 1) * 6;
	_borderLeft = _left + 1;
	_borderRight = LANE_LENGTH + _left + 1;
}

bool CBIRD::isInLane(int x)
{
	return (x > _borderLeft && x < _borderRight - 1);
}

void CBIRD::renderBird()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	vector<int> curX;
	vector<int> curY;
	int sizeX = 5;
	int sizeY = 1;
	int startPos = _left + 3;
	curX.push_back(startPos);
	curY.push_back(mY + 3);
	for (int i = 1; i < _numBird; i++) {
		int tmp = curX[i - 1];
		curX.push_back(tmp + 16 + _spaceBird);
		curY.push_back(mY + 3);
	}
	int prevX;
	while (true) {
		Sleep(100);
		for (int cnt = 0; cnt < _numBird; cnt++) {
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
			curY[cnt] = mY + 3;
		}
	}
}