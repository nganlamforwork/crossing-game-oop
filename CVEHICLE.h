#pragma once
#include <iostream>
#include <vector>
#include "Common.h"
#include "CTRAFFICLIGHT.h"

class CVEHICLE {
protected:
	int mX, mY, _numLane;
	int _borderLeft, _borderRight;
	int _num, _space;
	int _sizeX, _sizeY;
	int _wait;
	int _startPos;
	CTRAFFICLIGHT* _light = nullptr;
	vector<int> curX, curY;

	bool IsInLane(int);
public:
	int getLane() { return _numLane; }
	int getSizeX() { return _sizeX; };
	vector<int> getCurX() { return curX; };
	virtual void CreateList() {};
	virtual void Move() {};
};

class CTRUCK : public CVEHICLE {
	int _direction, _left, _top;
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
	int _direction, _left, _top;
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