#include "CPEOPLE.h"

CPEOPLE::CPEOPLE(int numLane, int direction, int left, int top)
{
	_numLane = numLane;
	_direction = direction;
	_left = left;
	_top = top;
	_borderLeft = _left + 1;
	_borderRight = LANE_LENGTH + _left + 1;

	_sizeX = 5, _sizeY = 4;
	srand(time(NULL));
	mX = _borderLeft + (rand() % (LANE_LENGTH - _sizeX - 1) + 1);
	mY = top + (_numLane - 1) * 6 + 1;

	mState = 1; //Alive

	_level = 1;
}

void CPEOPLE::RenderPeople(int color)
{
	Common::setConsoleColor(BRIGHT_WHITE, color);
	int curX = mX;
	int curY = mY;

	int prevX;
	prevX = curX;
	for (int i = 0; i < _sizeY; i++) {
		for (int j = 0; j < _sizeX; j++) {
			mtx.lock();
			Common::setConsoleColor(BRIGHT_WHITE, color);
			Common::gotoXY(curX, curY);
			std::cout << data[i][j];
			mtx.unlock();

			curX = curX + 1;
		}
		curX = prevX;
		curY = curY + 1;
	}
}

void CPEOPLE::DeletePeople()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int curX = mX;
	int curY = mY;

	int prevX;
	prevX = curX;
	for (int i = 0; i < _sizeY; i++) {
		for (int j = 0; j < _sizeX; j++) {
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
		RenderPeople(BLACK);
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
		RenderPeople(BLACK);
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
		DeletePeople();
		mY = mY - 6;
		_numLane--;
		if (_numLane > 1) RenderPeople(BLACK);
	}
}

void CPEOPLE::Down() {
	if (_numLane + 1 <= 6 && IsInBoard(mX, mY + 6)) {
		DeletePeople();
		mY = mY + 6;
		_numLane++;
		RenderPeople(BLACK);
	}
}

void CPEOPLE::Move(int type) {
	switch (type) {
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
	}
}

void CPEOPLE::Save(ofstream& out)
{
	out << _numLane << ' ' << mX << ' ' << mY << '\n';
}

void CPEOPLE::Load(ifstream& in)
{
	in >> _numLane >> mX >> mY;
}

bool CPEOPLE::IsInBoard(int curX, int curY) {
	if (!(curX > _borderLeft + 1 && curX + 5 < _borderRight)) return false;
	if (!(_numLane >= 1 && _numLane <= 6)) return false;
	return true;
}

bool CPEOPLE::IsFinish()
{
	return _numLane == 1;
}

bool CPEOPLE::IsImpact(CCAR* car)
{
	if (_numLane != car->getLane()) return 0;
	vector<int> curX = car->getCurX();
	int sizeX = car->getSizeX();
	for (int i = 0; i < (int)curX.size(); i++)
		if ((mX + _sizeX - 1 < curX[i]) || (mX > curX[i] + sizeX - 1))
			continue;
		else {
			return 1;
		}
	return 0;
};

bool CPEOPLE::IsImpact(CTRUCK* truck)
{
	if (_numLane != truck->getLane()) return 0;
	vector<int> curX = truck->getCurX();
	int sizeX = truck->getSizeX();
	for (int i = 0; i < (int)curX.size(); i++)
		if ((mX > curX[i]) || (mX + _sizeX - 1 < curX[i] - sizeX + 1))
			continue;
		else {
			return 1;
		}
	return 0;
};

bool CPEOPLE::IsImpact(CBIRD* bird)
{
	if (_numLane != bird->getLane()) return 0;
	vector<int> curX = bird->getCurX();
	int sizeX = bird->getSizeX();
	for (int i = 0; i < (int)curX.size(); i++)
		if ((mX > curX[i]) || (mX + _sizeX - 1 < curX[i] - sizeX + 1))
			continue;
		else {
			return 1;
		}
	return 0;
};

bool CPEOPLE::IsImpact(CDINAUSOR* dino)
{ 
	if (_numLane != dino->getLane()) return 0;
	vector<int> curX = dino->getCurX();
	int sizeX = dino->getSizeX();
	for (int i = 0; i < (int)curX.size(); i++)
		if ((mX + _sizeX - 1 < curX[i]) || (mX > curX[i] + sizeX - 1))
			continue;
		else {
			return 1;
		}
	return 0; 
};

void CPEOPLE::UpLevel()
{
	_numLane = 6;
	mX = _borderLeft + (rand() % (LANE_LENGTH - _sizeX - 1) + 1);
	mY = _top + (_numLane - 1) * 6 + 1;
	RenderPeople(BLACK);
	++_level;
}