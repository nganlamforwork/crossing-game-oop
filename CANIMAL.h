#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include <ctime>
#include <fstream>
#include "Common.h"
#include "CTRAFFICLIGHT.h"

class CANIMAL {
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
	CANIMAL(int, int, int, int, int);
	~CANIMAL() {};
	int getLane() { return _numLane; }
	int getSizeX() { return _sizeX; };
	vector<int> getCurX() { return curX; };
	virtual void CreateList() {};
	void SaveList(ofstream&);
	void LoadList(ifstream&);
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