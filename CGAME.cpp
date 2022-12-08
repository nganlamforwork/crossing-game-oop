#include "CGAME.h"

CGAME::CGAME(int)
{
	DrawGame();

	truck = new CTRUCK(2, 0, _left, _top, 100);
	lightTruck = new CTRAFFICLIGHT(2, 0, _left, _top, 5);
	lightTruck->Render();

	car = new CCAR(3, 1, _left, _top, 600);
	lightCar = new CTRAFFICLIGHT(3, 1, _left, _top, 10);
	lightCar->Render();

	bird = new CBIRD(4, 0, _left, _top, 50);
	lightBird = new CTRAFFICLIGHT(4, 0, _left, _top, 5);
	lightBird->Render();

	dino = new CDINAUSOR(5, 1, _left, _top, 500);
	lightDino = new CTRAFFICLIGHT(5, 1, _left, _top, 10);
	lightDino->Render();
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

void handleTrafficLights(CTRAFFICLIGHT*& truck, CTRAFFICLIGHT*& car, CTRAFFICLIGHT*& dino, CTRAFFICLIGHT*& bird, CPEOPLE*& people)
{
	while (people->getState()) {
		Sleep(1000);
		truck->countDown();
		car->countDown();
		dino->countDown();
		bird->countDown();
	}
}

void renderTruck(int _left, int _top, CPEOPLE*& people, CTRUCK*& truck, CTRAFFICLIGHT*& light) {
	while (people->getState()) {
		if (light->getState() == GREEN_LIGHT) truck->Move();
		if (people->IsImpact(truck)) people->setState(0);
	}
}

void renderCar(int _left, int _top, CPEOPLE*& people, CCAR*& car, CTRAFFICLIGHT*& light) {
	while (people->getState()) {
		if (light->getState() == GREEN_LIGHT) car->Move();
		if (people->IsImpact(car)) people->setState(0);
	}
}

void renderBird(int _left, int _top, CPEOPLE*& people, CBIRD*& bird, CTRAFFICLIGHT*& light) {
	while(people->getState()){
		if (light->getState() == GREEN_LIGHT) bird->Move();
		if (people->IsImpact(bird)) people->setState(0);
	}
}

void renderDino(int _left, int _top, CPEOPLE*& people, CDINAUSOR*& dino, CTRAFFICLIGHT*& light) {
	while (people->getState()) {
		if (light->getState() == GREEN_LIGHT) dino->Move();
		if (people->IsImpact(dino)) people->setState(0);
	}
}

void renderPeople(int _left, int _top, CPEOPLE*& people) {
	while (people->getState()) {
		people->Move();
	}
}

void CGAME::Move()
{
	people = new CPEOPLE(6, 1, _left, _top);
	people->RenderPeople(_left + 50, _top + (6 - 1) * 6 + 1);

	truck->CreateList();
	car->CreateList();
	bird->CreateList();
	dino->CreateList();

	thread t2([&] {renderTruck(_left, _top, people, truck, lightTruck); });
	thread t3([&] {renderCar(_left, _top, people, car, lightCar); });
	thread t4([&] {renderBird(_left, _top, people, bird, lightBird); });
	thread t5([&] {renderDino(_left, _top, people, dino, lightDino); });
	thread trafficLight([&] {handleTrafficLights(lightTruck, lightCar, lightBird, lightDino, people); });
	while (people->getState()) {
		people->Move();
		/*if (people->IsImpact(truck) || people->IsImpact(xe) || people->IsImpact(bird) || people->IsImpact(kl)) {
			people->getState() = 0;
			break;
		}*/
	}
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	trafficLight.join();
}