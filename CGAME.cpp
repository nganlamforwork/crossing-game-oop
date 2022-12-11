#include "CGAME.h"

CGAME::CGAME(int)
{
	_isPlaying = 1;
	DrawGame();

	truck = new CTRUCK(2, 0, _left, _top, 600);
	lightTruck = new CTRAFFICLIGHT(2, 0, _left, _top, 4, GREEN_LIGHT);
	lightTruck->Render();

	car = new CCAR(3, 1, _left, _top, 600);
	lightCar = new CTRAFFICLIGHT(3, 1, _left, _top, 4, RED_LIGHT);
	lightCar->Render();

	bird = new CBIRD(4, 0, _left, _top, 50);
	lightBird = new CTRAFFICLIGHT(4, 0, _left, _top, 4, GREEN_LIGHT);
	lightBird->Render();

	dino = new CDINAUSOR(5, 1, _left, _top, 500);
	lightDino = new CTRAFFICLIGHT(5, 1, _left, _top, 4, RED_LIGHT);
	lightDino->Render();
}
CGAME::~CGAME()
{
	delete truck;
	delete lightTruck;
	delete car;
	delete lightCar;
	delete dino;
	delete lightDino;
	delete bird;
	delete lightBird;
	delete people;
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

}

void handleTrafficLights(CTRAFFICLIGHT*& truck, CTRAFFICLIGHT*& car, CTRAFFICLIGHT*& dino, CTRAFFICLIGHT*& bird, CPEOPLE*& people, bool& isPlaying)
{
	while (people->getState()) {
		if (isPlaying) {
			Sleep(1000);
			truck->countDown();
			car->countDown();
			dino->countDown();
			bird->countDown();
		}
	}
}

void renderTruck(int _left, int _top, CPEOPLE*& people, CTRUCK*& truck, CTRAFFICLIGHT*& light, bool& isPlaying) {
	truck->Move();
	while (people->getState()) {
		if (isPlaying && light->getState() == GREEN_LIGHT) truck->Move();
		if (people->IsImpact(truck)) {
			ofstream o("result.xt");
			o << "Car!";
			o.close();
			people->setState(0);
		};
	}
}

void renderCar(int _left, int _top, CPEOPLE*& people, CCAR*& car, CTRAFFICLIGHT*& light, bool& isPlaying) {
	car->Move();
	while (people->getState()) {
		if (isPlaying && light->getState() == GREEN_LIGHT) car->Move();
		if (people->IsImpact(car)) {
			ofstream o("result.xt");
			o << "Car!";
			o.close();
			people->setState(0);
		};
	}
}

void renderBird(int _left, int _top, CPEOPLE*& people, CBIRD*& bird, CTRAFFICLIGHT*& light, bool& isPlaying) {
	bird->Move();
	while(people->getState()){
		if (isPlaying && light->getState() == GREEN_LIGHT) bird->Move();
		if (people->IsImpact(bird)) {
			ofstream o("result.xt");
			o << "Bird!";
			o.close();
			people->setState(0);
		}
	}
}

void renderDino(int _left, int _top, CPEOPLE*& people, CDINAUSOR*& dino, CTRAFFICLIGHT*& light, bool& isPlaying) {
	dino->Move();
	while (people->getState()) {
		if (isPlaying && light->getState() == GREEN_LIGHT) dino->Move();
		if (people->IsImpact(dino)) {
			ofstream o("result.xt");
			o << "Dino!";
			o.close();
			people->setState(0);
		};
	}
}

void CGAME::Move()
{
	people = new CPEOPLE(6, 1, _left, _top);
	people->RenderPeople();

	truck->CreateList();
	car->CreateList();
	bird->CreateList();
	dino->CreateList();

	thread t2([&] {renderTruck(_left, _top, people, truck, lightTruck, _isPlaying); });
	thread t3([&] {renderCar(_left, _top, people, car, lightCar, _isPlaying); });
	thread t4([&] {renderBird(_left, _top, people, bird, lightBird, _isPlaying); });
	thread t5([&] {renderDino(_left, _top, people, dino, lightDino, _isPlaying); });
	thread trafficLight([&] {handleTrafficLights(lightTruck, lightCar, lightBird, lightDino, people, _isPlaying); });
	while (people->getState()) {
		int tmp;
		switch (tmp = Common::getConsoleInput()) {
		case 2:
		case 3:
		case 4:
		case 5:
			if (_isPlaying) people->Move(tmp);
			break;
		case 9:
			_isPlaying ^= 1;
			break;
		};

		if (people->IsFinish()) {
			people->UpLevel();
			if (people->getLevel() == 6)
				people->setState(0);	//Die
		}
	}
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	trafficLight.join();
}