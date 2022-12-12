#include "CANIMAL.h"

CANIMAL::CANIMAL(int numLane, int direction, int left, int top, int wait)
{
	_numLane = numLane; _direction = direction;

	_borderLeft = left + 1; _borderRight = LANE_LENGTH + left + 1;

	mX = _left = left; mY = _top = top + (_numLane - 1) * 6;

	_wait = wait;

	srand(time(NULL));
	_offset = rand() % (LANE_LENGTH - 3) + 1;
}

bool CANIMAL::IsInLane(int x)
{
	return (x > _borderLeft && x < _borderRight - 1);
}

void CANIMAL::SaveList(ofstream& out)
{
	out << _num << ' ';
	for (int i = 0; i < _num; i++)
		out << curX[i] << ' ';
	out << '\n';
}

CDINAUSOR::CDINAUSOR(int numLane, int direction, int left, int top, int wait) : CANIMAL(numLane, direction, left, top, wait)
{
	_sizeX = 16; _sizeY = 5;

	_num = 4; _space = 10;

	_startPos = _borderLeft + 2;
}

void CDINAUSOR::CreateList()
{
	curX.push_back(_startPos);
	curY.push_back(mY + 1);

	for (int i = 1; i < _num; i++) {
		int tmp = curX[i - 1];
		curX.push_back(tmp + _sizeX + _space);
		curY.push_back(mY + 1);
	}
}

void CDINAUSOR::LoadList(ifstream& in)
{
	in >> _num;
	int tmp;
	for (int i = 0; i < _num; i++) {
		in >> tmp;
		curX.push_back(tmp);
		curY.push_back(mY + 1);
	}
}

void CDINAUSOR::Move()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int prevX;
	for (int cnt = 0; cnt < _num; cnt++) {
		prevX = curX[cnt];
		for (int i = 0; i < _sizeY; i++) {
			for (int j = 0; j < _sizeX; j++) {
				Common::setConsoleColor(BRIGHT_WHITE, BLACK);
				if (!IsInLane(curX[cnt]))
					curX[cnt] = _borderLeft + 2;
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
			curX[cnt] = _borderLeft + 2;
		curY[cnt] = mY + 1;
	}
	Sleep(_wait);
}

CBIRD::CBIRD(int numLane, int direction, int left, int top, int wait) : CANIMAL(numLane, direction, left, top, wait)
{
	_sizeX = 5; _sizeY = 1;

	_num = 6; _space = 13;

	_startPos = _borderRight - 2;
}

void CBIRD::CreateList()
{
	curX.push_back(_startPos);
	curY.push_back(mY + 3);

	for (int i = 1; i < _num; i++) {
		int tmp = curX[i - 1];
		curX.push_back(tmp - _sizeX - _space);
		curY.push_back(mY + 3);
	}
}

void CBIRD::LoadList(ifstream& in)
{
	in >> _num;
	int tmp;
	for (int i = 0; i < _num; i++) {
		in >> tmp;
		curX.push_back(tmp);
		curY.push_back(mY + 3);
	}
}

void CBIRD::Move()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int prevX;
	for (int cnt = _num - 1; cnt >= 0; cnt--) {
		prevX = curX[cnt];
		for (int i = 0; i < _sizeY; i++) {
			for (int j = _sizeX - 1; j >= 0; j--) {
				Common::setConsoleColor(BRIGHT_WHITE, BLACK);
				if (!IsInLane(curX[cnt]))
					curX[cnt] = _borderRight - 2;
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
			Common::gotoXY(prevX + 1, (int)curY[cnt] - i - 1);
			putchar(32);
			Common::gotoXY(_borderLeft + 1, (int)curY[cnt] - i - 1);
			putchar(32);
			mtx.unlock();
		}
		curX[cnt] = prevX - 1;
		if (!IsInLane(prevX - 1))
			curX[cnt] = _borderRight - 2;
		curY[cnt] = mY + 3;
	}
	Sleep(_wait);
}