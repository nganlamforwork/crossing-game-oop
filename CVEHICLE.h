#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include "Common.h"
#include "CTRAFFICLIGHT.h"

class CVEHICLE {
protected:
	int mX, mY, _startPos = 0;
	int _numLane, _direction;
	int _num = 0, _space = 0;
	int _borderLeft, _borderRight, _left, _top;
	int _sizeX = 0, _sizeY = 0;
	int _wait;
	vector<int> curX, curY;

	bool IsInLane(int);
public:
	CVEHICLE(int, int, int, int, int);
	~CVEHICLE() {};
	int getLane() { return _numLane; }
	int getSizeX() { return _sizeX; };
	vector<int> getCurX() { return curX; };
	virtual void CreateList() {};
	virtual void Move() {};
};

class CTRUCK : public CVEHICLE {
	const char data[4][17] = { {' ',' ',' ','_','_',' ',' ',' ','_','_','_','_','_','_','_','_'},
								{' ','_','/','/',']','|',' ','|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
								{'|','_','_','_','_','|','-','|','_','_','_','_','_','_','_','_','|'},
								{' ',' ','O',' ',' ',' ',' ',' ',' ','O',' ',' ',' ',' ','O',' ',' '},
	};

public:
	CTRUCK(int, int, int, int, int);
	~CTRUCK() {};
	void CreateList();
	void Move();
};

class CCAR : public CVEHICLE {
	const char data[5][6] = { {' ',' ',' ',' ',' ',' '},
		{' ',' ','_','_',' ',' '},
								{' ','(',' ','o',')',' '},
								{'(','o','\\','/','o',')'},
								{' ','\"',' ',' ','\"',' '} };

public:
	CCAR(int, int, int, int, int);
	~CCAR() {};
	void CreateList();
	void Move();

};