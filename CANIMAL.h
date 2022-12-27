#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include <ctime>
#include <fstream>
#include "COMMON.h"
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
	CANIMAL(int, int, int, int);
	~CANIMAL() {};
	int getLane() { return _numLane; }
	int getSizeX() { return _sizeX; };
	vector<int> getCurX() { return curX; };
	virtual void UpLevel(int) = 0;
	virtual void CreateList() = 0;
	void SaveList(ofstream&);
	virtual void LoadList(ifstream&) = 0;
	virtual void Move() = 0;
};

class CDINAUSOR : public CANIMAL {
	const char data[5][16] = { {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','_','_',' '},
								{' ',' ',' ',' ','_','_','.','-','-','-','.','_','/',' ','_',')'},
								{' ','_','_','/',' ',' ',' ',' ',' ',' ',' ',' ',' ','/',' ',' '},
								{'/','_','_','.','\'','|','_','|','-','-','|','_','|',' ',' ',' '} };
	const int _numLevel[5] = { 2, 3, 3, 4, 4 };
	const int _spaceLevel[5] = { 30, 25, 20, 15, 10 };
	const int _waitLevel[5] = {500, 500, 450, 450, 400};

public:
	CDINAUSOR(int, int, int, int);
	~CDINAUSOR() {};
	void UpLevel(int);
	void CreateList();
	void LoadList(ifstream&);
	void Move(); 
};

class CBIRD : public CANIMAL {
	const char data[1][5] = { {'/','^','V','^','\\'} };

	const int _numLevel[5] = { 4, 5, 5, 6, 6 };
	const int _spaceLevel[5] = { 25, 25, 20, 20, 13 };
	const int _waitLevel[5] = { 200, 200, 150, 150, 100 };
public:
	CBIRD(int, int, int, int);
	~CBIRD() {};
	void UpLevel(int);
	void CreateList();
	void LoadList(ifstream&);
	void Move();
};