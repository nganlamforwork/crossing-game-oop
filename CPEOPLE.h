#pragma once
#include <ctime>
#include <fstream>
#include "CVEHICLE.h"
#include "CANIMAL.h"

class CPEOPLE {
	int numLane, direction, left, top;
	int borderLeft, borderRight;
	int sizeX, sizeY;
	int level;

	int mX, mY;
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
	~CPEOPLE() {};

	int GetLevel() { return level; };
	void SetLevel(int x) { level = x; };
	bool GetLane() { return numLane; };
	bool GetState() { return mState; };
	void SetState(int x) { mState = x; };

	void Up();
	void Left();
	void Right();
	void Down();

	void RenderPeople(int);
	void DeletePeople();

	void Move(int);
	void Save(ofstream&);
	void Load(ifstream&);

	//bool IsImpact(const CVEHICLE*&);
	bool IsImpact(CCAR*);
	bool IsImpact(CTRUCK*);
	bool IsImpact(CBIRD*);
	bool IsImpact(CDINAUSOR*);
	bool IsFinish();
	bool IsDead();

	void UpLevel();

private:
	bool IsInBoard(int, int);
};