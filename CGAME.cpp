#include "CGAME.h"

CGAME::CGAME()
{
	_state = PLAYING;

	truck = new CTRUCK(2, 0, _left, _top, 600);
	lightTruck = new CTRAFFICLIGHT(2, 0, _left, _top, 4, GREEN_LIGHT, 4);

	car = new CCAR(3, 1, _left, _top, 600);
	lightCar = new CTRAFFICLIGHT(3, 1, _left, _top, 4, RED_LIGHT, 4);

	bird = new CBIRD(4, 0, _left, _top, 50);
	lightBird = new CTRAFFICLIGHT(4, 0, _left, _top, 4, GREEN_LIGHT, 4);

	dino = new CDINAUSOR(5, 1, _left, _top, 500);
	lightDino = new CTRAFFICLIGHT(5, 1, _left, _top, 4, RED_LIGHT, 4);

	people = new CPEOPLE(6, 1, _left, _top);
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

//--------------------------------------------------------------

void CGAME::Create()
{
	truck->CreateList();
	car->CreateList();
	bird->CreateList();
	dino->CreateList();
}

void CGAME::Save()
{
	ofstream out("SaveList.txt");
	out << people->getLevel() << '\n';
	people->Save(out);
	truck->SaveList(out);
	lightTruck->Save(out);
	car->SaveList(out);
	lightCar->Save(out);
	bird->SaveList(out);
	lightBird->Save(out);
	dino->SaveList(out);
	lightDino->Save(out);
	out.close();
}

void CGAME::Load()
{
	ifstream in("SaveList.txt");
	int level;
	in >> level;
	people->setLevel(level);
	people->Load(in);
	truck->LoadList(in);
	lightTruck->Load(in);
	car->LoadList(in);
	lightCar->Load(in);
	bird->LoadList(in);
	lightBird->Load(in);
	dino->LoadList(in);
	lightDino->Load(in);
	in.close();
}

//--------------------------------------------------------------

void CGAME::DrawGame()
{
	Common::clearConsole();

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	//Vẽ tiêu đề level
	ifstream in("titles\\level.txt");
	int i = 1;
	while (!in.eof()) {
		Common::gotoXY(_left + 35, _top + i++);
		string tmp;
		getline(in, tmp);
		cout << tmp;
	}
	in.close();

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
		putchar(205);
	}
	Common::gotoXY(_left + 1, NUM_LANE * LANE_HEIGHT + _top);
	putchar(200);

	//Vẽ biên trái
	for (int i = 1; i < NUM_LANE * LANE_HEIGHT; i++) {
		Common::gotoXY(_left + 1, NUM_LANE * LANE_HEIGHT + _top - i);
		putchar(186);
	}

	//Vẽ đường ngang
	for (int i = 1; i < LANE_LENGTH; i++) {
		for (int j = LANE_HEIGHT; j < NUM_LANE * LANE_HEIGHT; j += LANE_HEIGHT) {
			Common::gotoXY(i + _left + 1, j + _top);
			putchar(196);
		}
	}
	DrawAsideMenu();
}

void CGAME::DrawAsideMenu()
{
	int SUB_LANE_LENGTH = 24;
	//Vẽ biên trên
	Common::gotoXY(_left + LANE_LENGTH + 10, _top);
	putchar(201);
	for (int i = 1; i < SUB_LANE_LENGTH; i++) 
		putchar(205);
	putchar(187);

	//Vẽ biên phải
	for (int i = 1; i < NUM_LANE * LANE_HEIGHT; i++) {
		Common::gotoXY(LANE_LENGTH + _left + 10 + SUB_LANE_LENGTH, i + _top);
		putchar(186);
	}
	Common::gotoXY(LANE_LENGTH + _left + 10 + SUB_LANE_LENGTH, NUM_LANE * LANE_HEIGHT + _top);
	putchar(188);

	//Vẽ biên dưới
	for (int i = 1; i < SUB_LANE_LENGTH; i++) {
		Common::gotoXY(LANE_LENGTH + _left + i + 10, NUM_LANE * LANE_HEIGHT + _top);
		putchar(205);
	}
	Common::gotoXY(LANE_LENGTH + _left + 10, NUM_LANE * LANE_HEIGHT + _top);
	putchar(200);

	//Vẽ biên trái
	for (int i = 1; i < NUM_LANE * LANE_HEIGHT; i++) {
		Common::gotoXY(_left + LANE_LENGTH + 10, NUM_LANE * LANE_HEIGHT + _top - i);
		putchar(186);
	}

	//Ghi nội dung aside menu
	ifstream in("titles\\AsideMenu.txt");
	int i = 1;
	Common::setConsoleColor(BRIGHT_WHITE, BLUE);
	while (!in.eof()) {
		Common::gotoXY(_left + LANE_LENGTH + 11, _top + i++);
		string tmp;
		getline(in, tmp);
		cout << tmp;
	}
	in.close();

}

void CGAME::DrawLevelNumber(int x)
{
	string source = "titles\\" + to_string(x);
	source += ".txt";
	ifstream in(source);
	int i = 1;
	while (!in.eof()) {
		mtx.lock();
		Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		Common::gotoXY(_left + 35 + 32, _top + i++);
		string tmp;
		getline(in, tmp);
		cout << tmp;
		mtx.unlock();
	}
	in.close();
}

void CGAME::RenderGame()
{
	DrawGame();
	DrawLevelNumber(people->getLevel());
	lightTruck->Render();
	lightCar->Render();
	lightBird->Render();
	lightDino->Render();
}

//--------------------------------------------------------------
void CGAME::DrawEndGame(string fileName)
{
	int left = 0, top = 0;
	Common::clearConsole();
	ifstream endgame(fileName);
	string s;
	int i = 0;

	Common::setConsoleColor(BRIGHT_WHITE, RED);
	while (!endgame.eof()) {
		Common::gotoXY(left + 40, top + 8 + i);
		getline(endgame, s);
		cout << s;
		i++;
	}
	endgame.close();

	Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	ifstream bg;
	bg.open("images\\flowers.txt");

	i = 0;
	string line;
	while (!bg.eof()) {
		Common::gotoXY(left + 26, top + 25 + i);
		getline(bg, line);
		cout << line << '\n';
		i++;
	}
	bg.close();

	for (int time = 5; time >= 0; time--) {
		Common::setConsoleColor(BRIGHT_WHITE, BLUE);
		Common::gotoXY(left + 46, top + 18);
		cout << "Goodbye! The game will automatically exit after " << time << " second";
		if (time > 1) cout << 's';
		else cout << ' ';
		Sleep(1000);
	}
}

//--------------------------------------------------------------

void handleTrafficLights(CTRAFFICLIGHT*& truck, CTRAFFICLIGHT*& car, CTRAFFICLIGHT*& dino, CTRAFFICLIGHT*& bird, CPEOPLE*& people, int& gameState)
{
	while (people->getState() && gameState != QUIT_AND_SAVE && gameState != QUIT_NOT_SAVE) {
		if (gameState == PLAYING) {
			Sleep(1000);
			truck->countDown();
			car->countDown();
			dino->countDown();
			bird->countDown();
		}
	}
}

void renderTruck(int _left, int _top, CPEOPLE*& people, CTRUCK*& truck, CTRAFFICLIGHT*& light, int& gameState) {
	truck->Move();
	while (people->getState() && gameState != QUIT_AND_SAVE && gameState != QUIT_NOT_SAVE) {
		if (gameState == PLAYING && light->getState() == GREEN_LIGHT) truck->Move();
		if (people->IsImpact(truck)) {
			people->setState(0);
		};
	}
}

void renderCar(int _left, int _top, CPEOPLE*& people, CCAR*& car, CTRAFFICLIGHT*& light, int& gameState) {
	car->Move();
	while (people->getState() && gameState != QUIT_AND_SAVE && gameState != QUIT_NOT_SAVE) {
		if (gameState == PLAYING && light->getState() == GREEN_LIGHT) car->Move();
		if (people->IsImpact(car)) {
			people->setState(0);
		};
	}
}

void renderBird(int _left, int _top, CPEOPLE*& people, CBIRD*& bird, CTRAFFICLIGHT*& light, int& gameState) {
	bird->Move();
	while(people->getState() && gameState != QUIT_AND_SAVE && gameState != QUIT_NOT_SAVE){
		if (gameState == PLAYING && light->getState() == GREEN_LIGHT) bird->Move();
		if (people->IsImpact(bird)) {
			people->setState(0);
		}
	}
}

void renderDino(int _left, int _top, CPEOPLE*& people, CDINAUSOR*& dino, CTRAFFICLIGHT*& light, int& gameState) {
	dino->Move();
	while (people->getState() && gameState != QUIT_AND_SAVE && gameState != QUIT_NOT_SAVE) {
		if (gameState == PLAYING && light->getState() == GREEN_LIGHT) dino->Move();
		if (people->IsImpact(dino)) {
			people->setState(0);
		};
	}
}

//--------------------------------------------------------------

void CGAME::Move()
{
	people->RenderPeople();
	thread t2([&] {renderTruck(_left, _top, people, truck, lightTruck, _state); });
	thread t3([&] {renderCar(_left, _top, people, car, lightCar, _state); });
	thread t4([&] {renderBird(_left, _top, people, bird, lightBird, _state); });
	thread t5([&] {renderDino(_left, _top, people, dino, lightDino, _state); });
	thread trafficLight([&] {handleTrafficLights(lightTruck, lightCar, lightBird, lightDino, people, _state); });
	while (people->getState() && _state != QUIT_AND_SAVE && _state != QUIT_NOT_SAVE) {
		int tmp;
		switch (tmp = Common::getConsoleInput()) {
		case 2:
		case 3:
		case 4:
		case 5:
			if (_state == PLAYING) people->Move(tmp);
			break;
		case 9:									// toggle pausing - playing
			_state = 1 - _state;				// because playing is 0 and pausing is 1
			mtx.lock();
			Common::setConsoleColor(BRIGHT_WHITE, BLUE);
			Common::gotoXY(_left + LANE_LENGTH + 11 + 8, _top + 13);
			if (_state != PLAYING)
				cout << "PLAYING";
			else
				cout << "PAUSING";
			mtx.unlock();
			break;
		case 10:								// quit without saving
			_state = QUIT_NOT_SAVE;
			break;
		case 11:								// saving and quit game
			_state = QUIT_AND_SAVE;
			break;
		};

		if (people->IsFinish()) {
			people->UpLevel();
			if (people->getLevel() == 6)
				people->setState(0);	//Die
			else
				DrawLevelNumber(people->getLevel());
		}
	};
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	trafficLight.join();
}