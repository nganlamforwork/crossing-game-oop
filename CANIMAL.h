#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include "Common.h"
#include "CTRAFFICLIGHT.h"

class CANIMAL {
protected:
	int mX, mY, _startPos;
	int _numLane, _direction;
	int _num, _space;
	int _borderLeft, _borderRight, _left, _top;
	int _sizeX, _sizeY;
	int _wait;
	vector<int> curX, curY;

	bool IsInLane(int);
public:
	CANIMAL(int, int, int, int, int);
	~CANIMAL() {};
	int getLane() { return _numLane; };
	int getSizeX() { return _sizeX; };
	vector<int> getCurX() { return curX; };
	virtual void CreateList() {};
	virtual void Move() {};
};

class CDINAUSOR : public CANIMAL {
	const char data[5][16] = { {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','_','_',' '},
								{' ',' ',' ',' ','_','_','.','-','-','-','.','_','/',' ','_',')'},
								{' ','_','_','/',' ',' ',' ',' ',' ',' ',' ',' ',' ','/',' ',' '},
								{'/','_','_','.','\'','|','_','|','-','-','|','_','|',' ',' ',' '} };

public:
	CDINAUSOR(int, int, int, int, int);
	~CDINAUSOR() {};
	void CreateList();
	void Move();
};

class CBIRD : public CANIMAL {
	const char data[1][5] = { {'/','^','V','^','\\'} };

public:
	CBIRD(int, int, int, int, int);
	~CBIRD() {};
	void CreateList();
	void Move();

};