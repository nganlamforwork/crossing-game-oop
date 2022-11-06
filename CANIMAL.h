#pragma once
#include <iostream>
#include "Common.h"

class CANIMAL {
protected:
	int mX, mY;
	int _borderLeft, _borderRight;
public:
	/*virtual void Move(int, int);
	virtual void Tell();*/
};

class CDINAUSOR : public CANIMAL {
	int _numLane, _direction, _numDino, _spaceDino, _left, _top;
	const char data[5][16] = { {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','_','_',' '},
								{' ',' ',' ',' ','_','_','.','-','-','-','.','_','/',' ','_',')'},
								{' ','_','_','/',' ',' ',' ',' ',' ',' ',' ',' ',' ','/',' ',' '},
								{'/','_','_','.','\'','|','_','|','-','-','|','_','|',' ',' ',' '} };

private: 
	bool isInLane(int);

public:
	CDINAUSOR(int, int, int, int);
	~CDINAUSOR();
	void renderDinausor();
};

class CBIRD : public CANIMAL {
public:

};