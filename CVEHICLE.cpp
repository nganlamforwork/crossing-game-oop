#include "CVEHICLE.h"

CVEHICLE::CVEHICLE(int numLane, int direction, int left, int top)
{
	this->numLane = numLane; this->direction = direction;

	borderLeft = left + 1; borderRight = LANE_LENGTH + left + 1;

	mX = this->left = left; mY = this->top = top + (numLane - 1) * 6;

	srand(time(NULL));
	offset = rand() % (LANE_LENGTH - 3) + 1;
}

int CVEHICLE::GetLane() 
{ 
	return numLane; 
}

int CVEHICLE::GetSizeX() 
{ 
	return sizeX; 
};

vector<int> CVEHICLE::GetCurX() 
{ 
	return curX; 
};

bool CVEHICLE::IsInLane(int x)
{
	return (x > borderLeft && x < borderRight - 1);
}

void CVEHICLE::SaveList(ofstream& out)
{
	out << num << ' ';
	for (int i = 0; i < num; i++)
		out << curX[i] << ' ';
	out << '\n';
}

void CVEHICLE::LoadList(ifstream& in)
{
	in >> num;
	int tmp;
	for (int i = 0; i < num; i++) {
		in >> tmp;
		curX.push_back(tmp);
		curY.push_back(mY + 1);
	}
}

////////////////////////////////////////////////////////////////////////////

CCAR::CCAR(int numLane, int direction, int left, int top) : CVEHICLE(numLane, direction, left, top)
{
	sizeX = 6; sizeY = 5;

	num = numLevel[0]; space = spaceLevel[0]; wait = waitLevel[0];

	startPos = borderLeft + 2;
}

void CCAR::UpLevel(int newLevel)
{
	wait = waitLevel[newLevel];
	space = spaceLevel[newLevel];
	num = numLevel[newLevel];
}

void CCAR::CreateList()
{
	curX.clear();
	curY.clear();
	curX.push_back(startPos);
	curY.push_back(mY + 1);

	for (int i = 1; i < num; i++) {
		int tmp = curX[i - 1];
		curX.push_back(tmp + sizeX + space);
		curY.push_back(mY + 1);
	}
}

void CCAR::Move()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int prevX;
	for (int cnt = 0; cnt < num; cnt++) {
		prevX = curX[cnt];
		for (int i = 0; i < sizeY; i++) {
			for (int j = 0; j < sizeX; j++) {
				Common::setConsoleColor(BRIGHT_WHITE, BLACK);
				if (!IsInLane(curX[cnt]))
					curX[cnt] = borderLeft + 2;
				mtx.lock();
				Common::gotoXY(curX[cnt], curY[cnt]);
				std::cout << data[i][j];
				mtx.unlock();
				curX[cnt] = curX[cnt] + 1;
			}
			curX[cnt] = prevX;
			curY[cnt] = curY[cnt] + 1;
		}
		for (int i = 0; i < sizeY; i++) {
			mtx.lock();
			Common::gotoXY(prevX - 1, (int)curY[cnt] - i - 1);
			putchar(32);
			Common::gotoXY(borderRight - 2, (int)curY[cnt] - i - 1);
			putchar(32);
			mtx.unlock();
		}
		curX[cnt] = prevX + 1;
		if (!IsInLane(prevX + 1))
			curX[cnt] = borderLeft + 2;
		curY[cnt] = mY + 1;
	}
	Sleep(wait);
}

////////////////////////////////////////////////////////////////////////////

CTRUCK::CTRUCK(int numLane, int direction, int left, int top) : CVEHICLE(numLane, direction, left, top)
{
	sizeX = 17; sizeY = 4;

	num = numLevel[0]; space = spaceLevel[0]; wait = waitLevel[0];

	startPos = borderRight - 2;
}

void CTRUCK::UpLevel(int newLevel)
{
	wait = waitLevel[newLevel];
	space = spaceLevel[newLevel];
	num = numLevel[newLevel];
}

void CTRUCK::CreateList()
{
	curX.clear();
	curY.clear();
	curX.push_back(startPos);
	curY.push_back(mY + 1);

	for (int i = 1; i < num; i++) {
		int tmp = curX[i - 1];
		curX.push_back(tmp - sizeX - space);
		curY.push_back(mY + 1);
	}
}

void CTRUCK::Move()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int prevX;
	for (int cnt = num - 1; cnt >= 0; cnt--) {
		prevX = curX[cnt];
		for (int i = 0; i < sizeY; i++) {
			for (int j = sizeX - 1; j >= 0; j--) {
				Common::setConsoleColor(BRIGHT_WHITE, BLACK);
				if (!IsInLane(curX[cnt]))
					curX[cnt] = borderRight - 2;
				mtx.lock();
				Common::gotoXY(curX[cnt], curY[cnt]);
				std::cout << data[i][j];
				mtx.unlock();

				curX[cnt] = curX[cnt] - 1;
			}
			curX[cnt] = prevX;
			curY[cnt] = curY[cnt] + 1;
		}
		for (int i = 0; i < sizeY; i++) {
			mtx.lock();
			Common::gotoXY(prevX + 1, (int)curY[cnt] - i - 1);
			putchar(32);
			Common::gotoXY(borderLeft + 1, (int)curY[cnt] - i - 1);
			putchar(32);
			mtx.unlock();
		}
		curX[cnt] = prevX - 1;
		if (!IsInLane(prevX - 1))
			curX[cnt] = borderRight - 2;
		curY[cnt] = mY + 1;
	}
	Sleep(wait);
}