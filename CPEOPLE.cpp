#include "CPEOPLE.h"

CPEOPLE::CPEOPLE(int numLane, int direction, int left, int top)
{
	this->numLane = numLane;
	this->direction = direction;
	this->left = left;
	this->top = top;
	this->borderLeft = this->left + 1;
	this->borderRight = LANE_LENGTH + this->left + 1;

	this->sizeX = 5, this->sizeY = 4;
	srand(time(NULL));
	mX = this->borderLeft + (rand() % (LANE_LENGTH - this->sizeX - 1) + 1);
	mY = top + (this->numLane - 1) * 6 + 1;

	mState = 1; //Alive

	this->level = 1;
}

void CPEOPLE::RenderPeople(int color)
{
	Common::setConsoleColor(BRIGHT_WHITE, color);
	int curX = mX;
	int curY = mY;

	int prevX;
	prevX = curX;
	for (int i = 0; i < this->sizeY; i++) {
		for (int j = 0; j < this->sizeX; j++) {
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
	for (int i = 0; i < this->sizeY; i++) {
		for (int j = 0; j < this->sizeX; j++) {
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
		this->numLane--;
		if (this->numLane > 1) RenderPeople(BLACK);
	}
}

void CPEOPLE::Down() {
	if (this->numLane + 1 <= 6 && IsInBoard(mX, mY + 6)) {
		DeletePeople();
		mY = mY + 6;
		this->numLane++;
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
	out << this->numLane << ' ' << mX << ' ' << mY << '\n';
}

void CPEOPLE::Load(ifstream& in)
{
	in >> this->numLane >> mX >> mY;
}

bool CPEOPLE::IsInBoard(int curX, int curY) {
	if (!(curX > this->borderLeft + 1 && curX + 5 < this->borderRight)) return false;
	if (!(this->numLane >= 1 && this->numLane <= 6)) return false;
	return true;
}

bool CPEOPLE::IsFinish()
{
	return this->numLane == 1;
}

bool CPEOPLE::IsImpact(CCAR* car)
{
	if (this->numLane != car->GetLane()) return 0;
	vector<int> curX = car->GetCurX();
	int sizeX = car->GetSizeX();
	for (int i = 0; i < (int)curX.size(); i++)
		if ((mX + this->sizeX - 1 < curX[i]) || (mX > curX[i] + sizeX - 1))
			continue;
		else {
			return 1;
		}
	return 0;
};

bool CPEOPLE::IsImpact(CTRUCK* truck)
{
	if (this->numLane != truck->GetLane()) return 0;
	vector<int> curX = truck->GetCurX();
	int sizeX = truck->GetSizeX();
	for (int i = 0; i < (int)curX.size(); i++)
		if ((mX > curX[i]) || (mX + this->sizeX - 1 < curX[i] - sizeX + 1))
			continue;
		else {
			return 1;
		}
	return 0;
};

bool CPEOPLE::IsImpact(CBIRD* bird)
{
	if (this->numLane != bird->GetLane()) return 0;
	vector<int> curX = bird->GetCurX();
	int sizeX = bird->GetSizeX();
	for (int i = 0; i < (int)curX.size(); i++)
		if ((mX > curX[i]) || (mX + this->sizeX - 1 < curX[i] - sizeX + 1))
			continue;
		else {
			return 1;
		}
	return 0;
};

bool CPEOPLE::IsImpact(CDINAUSOR* dino)
{ 
	if (this->numLane != dino->GetLane()) return 0;
	vector<int> curX = dino->GetCurX();
	int sizeX = dino->GetSizeX();
	for (int i = 0; i < (int)curX.size(); i++)
		if ((mX + this->sizeX - 1 < curX[i]) || (mX > curX[i] + sizeX - 1))
			continue;
		else {
			return 1;
		}
	return 0; 
};

void CPEOPLE::UpLevel()
{
	this->numLane = 6;
	mX = this->borderLeft + (rand() % (LANE_LENGTH - this->sizeX - 1) + 1);
	mY = this->top + (this->numLane - 1) * 6 + 1;
	RenderPeople(BLACK);
	++this->level;
}