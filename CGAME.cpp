#include "CGAME.h"



CGAME::CGAME(int)
{
	DrawGame();
	truck = new CTRUCK(2, 0, _left, _top, 800);
	xe = new CCAR(3, 1, _left, _top, 600);
	bird = new CBIRD(4, 0, _left, _top, 50);
	kl = new CDINAUSOR(5, 1, _left, _top, 500);
}
CGAME::~CGAME()
{
}
void CGAME::DrawGame()
{
	Common::clearConsole();

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	//Vẽ biên trên
	Common::gotoXY(_left + 1, _top);
	putchar(201);
	for (int i = 1; i < LANE_LENGTH; i++) {
		//Sleep(2);
		putchar(205);
	}
	putchar(187);

	//Vẽ biên phải
	for (int i = 1; i < NUM_LANE * LANE_HEIGHT; i++) {
		//Sleep(5);
		Common::gotoXY(LANE_LENGTH + _left + 1, i + _top);
		putchar(186);
	}
	Common::gotoXY(LANE_LENGTH + _left + 1, NUM_LANE * LANE_HEIGHT + _top);
	putchar(188);


	//Vẽ biên dưới
	for (int i = 1; i < LANE_LENGTH; i++) {
		Common::gotoXY(LANE_LENGTH + _left - i + 1, NUM_LANE * LANE_HEIGHT + _top);
		//Sleep(2);
		putchar(205);
	}
	Common::gotoXY(_left + 1, NUM_LANE * LANE_HEIGHT + _top);
	putchar(200);

	//Ve biên trái
	for (int i = 1; i < NUM_LANE * LANE_HEIGHT; i++) {
		//Sleep(5);
		Common::gotoXY(_left + 1, NUM_LANE * LANE_HEIGHT + _top - i);
		putchar(186);
	}

	//Vẽ đường ngang
	for (int i = 1; i < LANE_LENGTH; i++) {
		for (int j = LANE_HEIGHT; j < NUM_LANE * LANE_HEIGHT; j += LANE_HEIGHT) {
			Common::gotoXY(i + _left + 1, j + _top);
			putchar(196);
		}
		//Sleep(2);
	}

	/*truck->RenderLight();
	xe->RenderLight();*/

}

void renderTruck(int _left, int _top, CPEOPLE*& people, CTRUCK*& truck, bool& alive) {
	while (alive) {
		truck->Move();
		if (people->IsImpact(truck)) alive = 0;
	}
}

void renderCar(int _left, int _top, CPEOPLE*& people, CCAR*& xe, bool& alive) {
	while (alive) {
		xe->Move();
		if (people->IsImpact(xe)) alive = 0;
	}
}

void renderBird(int _left, int _top, CPEOPLE*& people, CBIRD*& bird, bool& alive) {
	while(alive){
		bird->Move();
		if (people->IsImpact(bird)) alive = 0;
	}
}

void renderDino(int _left, int _top, CPEOPLE*& people, CDINAUSOR*& kl, bool& alive) {
	while (alive) {
		kl->Move();
		if (people->IsImpact(kl)) alive = 0;
	}
}

void renderPeople(int _left, int _top, CPEOPLE*& people, bool& alive) {
	while (alive) {
		people->Move();
	}
}

void CGAME::Move()
{
	people = new CPEOPLE(6, 1, _left, _top);
	people->RenderPeople(_left + 50, _top + (6 - 1) * 6 + 1);

	truck->CreateList();
	xe->CreateList();
	bird->CreateList();
	kl->CreateList();

	thread t2([&] {renderTruck(_left, _top, people, truck, _alive); });
	thread t3([&] {renderCar(_left, _top, people, xe, _alive); });
	thread t4([&] {renderBird(_left, _top, people, bird, _alive); });
	thread t5([&] {renderDino(_left, _top, people, kl, _alive); });
	//thread t6([&] {renderPeople(_left, _top, people, _alive); });
	while (_alive) {
		people->Move();
		/*if (people->IsImpact(truck) || people->IsImpact(xe) || people->IsImpact(bird) || people->IsImpact(kl)) {
			_alive = 0;
			break;
		}*/
	}
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	//t6.join();
}