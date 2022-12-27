#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include <ctime>
#include "COMMON.h"
#include "CTRAFFICLIGHT.h"

class CVEHICLE {
protected:
	int mX, mY, _startPos = 0, _offset;
	int _numLane, _direction;
	int _num = 0, _space = 0;
	int _borderLeft, _borderRight, _left, _top;
	int _sizeX = 0, _sizeY = 0;
	int _wait;
	vector<int> curX, curY;

	bool IsInLane(int);
public:
	CVEHICLE(int, int, int, int);
	~CVEHICLE() {};
	int getLane() { return _numLane; }
	int getSizeX() { return _sizeX; };
	vector<int> getCurX() { return curX; };
	virtual void UpLevel(int) = 0;
	virtual void CreateList() = 0;
	void SaveList(ofstream&);
	void LoadList(ifstream&);
	virtual void Move() = 0;
};

class CTRUCK : public CVEHICLE {
	const char data[4][17] = { {' ',' ',' ','_','_',' ',' ',' ','_','_','_','_','_','_','_','_'},
								{' ','_','/','/',']','|',' ','|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
								{'|','_','_','_','_','|','-','|','_','_','_','_','_','_','_','_','|'},
								{' ',' ','O',' ',' ',' ',' ',' ',' ','O',' ',' ',' ',' ','O',' ',' '},
	};
	const int _numLevel[5] = { 2, 3, 3, 4, 4 };
	const int _spaceLevel[5] = { 30, 25, 20, 15, 10 };
	const int _waitLevel[5] = { 800, 750, 700, 650, 600 };

public:
	CTRUCK(int, int, int, int);
	~CTRUCK() {};
	void UpLevel(int);
	void CreateList();
	void Move();
};

class CCAR : public CVEHICLE {
	const char data[5][6] = { {' ',' ',' ',' ',' ',' '},
		{' ',' ','_','_',' ',' '},
								{' ','(',' ','o',')',' '},
								{'(','o','\\','/','o',')'},
								{' ','\"',' ',' ','\"',' '} };
	const int _numLevel[5] = { 3, 4, 5, 6, 7 };
	const int _spaceLevel[5] = { 30, 25, 20, 15, 10 };
	const int _waitLevel[5] = { 700, 700, 650, 650, 600 };

public:
	CCAR(int, int, int, int);
	~CCAR() {};
	void UpLevel(int);
	void CreateList();
	void Move();

};