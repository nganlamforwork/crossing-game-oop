#pragma once
#include <iostream>
#include <vector>
#include "Common.h"

class CVEHICLE {
protected:
	int mX, mY;
	int _borderLeft, _borderRight;
	int _num, _space;
	int _sizeX, _sizeY;

	bool isInLane(int);
public:
	virtual void Move() {};
};

class CTRUCK : public CVEHICLE {
	int _numLane, _direction, _left, _top;
	const char data[4][17] = { {' ',' ',' ','_','_',' ',' ',' ','_','_','_','_','_','_','_','_'},
								{' ','_','/','/',']','|',' ','|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
								{'|','_','_','_','_','|','-','|','_','_','_','_','_','_','_','_','|'},
								{' ',' ','O',' ',' ',' ',' ',' ',' ','O',' ',' ',' ',' ','O',' ',' '},
							};

public:
	CTRUCK(int, int, int, int);
	~CTRUCK();
	void Move();
};

class CCAR : public CVEHICLE {
	int _numLane, _direction, _left, _top;
	const char data[5][6] = { {' ',' ',' ',' ',' ',' '},
		{' ',' ','_','_',' ',' '},
								{' ','(',' ','o',')',' '},
								{'(','o','\\','/','o',')'},
								{' ','\"',' ',' ','\"',' '} };

public:
	CCAR(int, int, int, int);
	~CCAR();
	void Move();

};