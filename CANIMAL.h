#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include "Common.h"
#include "CTRAFFICLIGHT.h"

class CANIMAL {
protected:
	int mX, mY;
	int _borderLeft, _borderRight;
	int _sizeX, _sizeY;
	int _wait;

	bool isInLane(int);
public:
	virtual void Move() {};
	/*virtual void Move(int, int);
	virtual void Tell();*/
};

class CDINAUSOR : public CANIMAL {
	int _numLane, _direction, _num, _space, _left, _top;
	const char data[5][16] = { {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','_','_',' '},
								{' ',' ',' ',' ','_','_','.','-','-','-','.','_','/',' ','_',')'},
								{' ','_','_','/',' ',' ',' ',' ',' ',' ',' ',' ',' ','/',' ',' '},
								{'/','_','_','.','\'','|','_','|','-','-','|','_','|',' ',' ',' '} };

public:
	CDINAUSOR(int, int, int, int, int);
	~CDINAUSOR();
	void Move();
};

class CBIRD : public CANIMAL {
	int _numLane, _direction, _num, _space, _left, _top;
	const char data[1][5] = { {'/','^','V','^','\\'} };

public:
	CBIRD(int, int, int, int, int);
	~CBIRD();
	void Move();

};