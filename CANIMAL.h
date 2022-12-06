#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include "Common.h"
#include "CTRAFFICLIGHT.h"

class CANIMAL {
protected:
	int mX, mY, _startPos, _numLane;
	int _borderLeft, _borderRight;
	int _sizeX, _sizeY;
	int _wait;
	CTRAFFICLIGHT* _light = nullptr;
	vector<int> curX, curY;

	bool IsInLane(int);
public:
	int getLane() { return _numLane; };
	int getSizeX() { return _sizeX; };
	vector<int> getCurX() { return curX; };
	virtual void CreateList() {};
	virtual void Move() {};
};

class CDINAUSOR : public CANIMAL {
	int _direction, _num, _space, _left, _top;
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
	int _direction, _num, _space, _left, _top;
	const char data[1][5] = { {'/','^','V','^','\\'} };

public:
	CBIRD(int, int, int, int, int);
	~CBIRD();
	void CreateList();
	void Move();

};