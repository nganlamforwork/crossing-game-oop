#pragma once

#include "CVEHICLE.h"
#include "CANIMAL.h"

class CPEOPLE {
	int _numLane, _direction, _left, _top;
	int mX, mY;
	int _borderLeft, _borderRight;
	bool mState; //Trạng thái sống chết
	const char data[4][5] = {
		{' ',' ','O',' ',' '},
		{'|','[',' ',']','|'},
		{'\'',' ','|',' ','\''},
		{' ','/',' ','\\',' '}
	};
public:
	CPEOPLE();
	CPEOPLE(int, int, int, int);
	void Up();
	void Left();
	void Right();
	void Down();
	bool IsInBoard(int, int);
	void RenderPeople(int, int);
	void DeletePeople(int, int);
	void Move();
	bool isImpact(const CVEHICLE*&);
	bool isImpact(const CANIMAL*&);
	bool isFinish();
};