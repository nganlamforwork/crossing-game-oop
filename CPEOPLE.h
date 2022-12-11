#pragma once

#include "CVEHICLE.h"
#include "CANIMAL.h"

class CPEOPLE {
	int _numLane, _direction, _left, _top;
	int _borderLeft, _borderRight;
	int _sizeX, _sizeY;

	int mX, mY;
	bool mState; //Trạng thái sống chết

	const char data[4][5] = {
		{' ',' ','O',' ',' '},
		{'|','[',' ',']','|'},
		{'\'',' ','|',' ','\''},
		{' ','/',' ','\\',' '}
	};

private:
	bool IsInBoard(int, int);

public:
	CPEOPLE();
	CPEOPLE(int, int, int, int);
	~CPEOPLE() {};

	bool getLane() { return _numLane; };
	bool getState() { return mState; };
	void setState(int x) { mState = 0; };

	void Up();
	void Left();
	void Right();
	void Down();

	void RenderPeople(int, int);
	void DeletePeople(int, int);

	void Move();

	//bool IsImpact(const CVEHICLE*&);
	bool IsImpact(CCAR*);
	bool IsImpact(CTRUCK*);
	bool IsImpact(CBIRD*);
	bool IsImpact(CDINAUSOR*);
	bool IsFinish();
	bool IsDead();
};