#include "CGAME.h"

void renderTruck(int _left, int _top, int lane, CTRUCK* truck) {
	truck = new CTRUCK(lane, 1, _left, _top);
	truck->renderTruck();
}

void renderDino(int _left, int _top, int lane, CDINAUSOR* kl) {
	kl = new CDINAUSOR(lane, 1, _left, _top);
	kl->renderDinausor();
}

void renderCar(int _left, int _top, int lane, CCAR* xe) {
	xe = new CCAR(lane, 1, _left, _top);
	xe->renderCar();
}

void renderBird(int _left, int _top, int lane, CBIRD* bird) {
	bird = new CBIRD(lane, 1, _left, _top);
	bird->renderBird();
}

CGAME::CGAME(int)
{
	drawGame();
	/*kl = new CDINAUSOR(3, 1, _left, _top);
	kl->renderDinausor();*/
	/*xe = new CCAR(2, 1, _left, _top);
	xe->renderCar();*/
	/*bird = new CBIRD(2, 1, _left, _top);
	bird->renderBird();
	truck = new CTRUCK(3, 1, _left, _top);
	truck->renderTruck();*/
	thread t1(renderTruck, _left, _top, 1, truck);
	thread t2(renderDino, _left, _top, 2, kl);
	thread t3(renderCar, _left, _top, 3, xe);
	thread t4(renderBird, _left, _top, 4, bird);
	thread t5(renderDino, _left, _top, 5, kl);
	thread t6(renderCar, _left, _top, 6, xe);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	//thread t1([this] { renderTruck(_left, _top, truck); });
	//Sleep(50);
	//thread t2([this] { renderDino(_left, _top, kl); });

	//Sleep(10000);
}
void CGAME::drawGame()
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


	//Ve biên dưới
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

}
CGAME::~CGAME()
{

}