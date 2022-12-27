#include "CGAME.h"

CGAME::CGAME(bool musicEffect)
{
	_state = PLAYING;

	truck = new CTRUCK(2, 0, _left, _top);
	lightTruck = new CTRAFFICLIGHT(2, 0, _left, _top, 4, GREEN_LIGHT, 4);

	car = new CCAR(3, 1, _left, _top);
	lightCar = new CTRAFFICLIGHT(3, 1, _left, _top, 4, RED_LIGHT, 4);

	bird = new CBIRD(4, 0, _left, _top);

	dino = new CDINAUSOR(5, 1, _left, _top);

	people = new CPEOPLE(6, 1, _left, _top);

	_musicEffect = musicEffect;
}

CGAME::~CGAME()
{
	delete truck;
	delete lightTruck;
	delete car;
	delete lightCar;
	delete dino;
	delete bird;
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
	string name;

	mtx.lock();
	Common::gotoXY(_left + LANE_LENGTH + 11 + 1, _top + 8);
	cout << "                      ";
	Common::gotoXY(_left + LANE_LENGTH + 11 + 1, _top + 10);
	cout << "                      ";
	Common::gotoXY(_left + LANE_LENGTH + 11 + 1, _top + 11);
	cout << "                      ";
	mtx.unlock();


	mtx.lock();
	Common::showCursor(1);
	Common::gotoXY(_left + LANE_LENGTH + 11, _top + 7);
	Common::setConsoleColor(BRIGHT_WHITE, BLUE);
	cout << "    Enter your name:";
	Common::gotoXY(_left + LANE_LENGTH + 11 + 1, _top + 8);
	getline(cin, name, '\n');
	mtx.unlock();

	name = "data\\" + name + ".txt";
	ofstream out(name);

	out << people->getLevel() << '\n';
	people->Save(out);
	truck->SaveList(out);
	lightTruck->Save(out);
	car->SaveList(out);
	lightCar->Save(out);
	bird->SaveList(out);
	dino->SaveList(out);

	out.close();

	mtx.lock();
	Common::showCursor(0);
	Common::gotoXY(_left + LANE_LENGTH + 11 + 3, _top + 10);
	Common::setConsoleColor(BRIGHT_WHITE, BLUE);
	cout << "Save successfully!";
	Common::gotoXY(_left + LANE_LENGTH + 11 + 2, _top + 11);
	Common::setConsoleColor(BRIGHT_WHITE, BLUE);
	cout << "Press P to continue";
	mtx.unlock();
}

void CGAME::Load(string name)
{
	ifstream in(name);
	int level;
	in >> level;
	people->setLevel(level);
	people->Load(in);
	truck->LoadList(in);
	lightTruck->Load(in);
	car->LoadList(in);
	lightCar->Load(in);
	bird->LoadList(in);
	dino->LoadList(in);
	in.close();
}

//--------------------------------------------------------------

void CGAME::DrawGame()
{
	Common::clearConsole();

	Common::setConsoleColor(BRIGHT_WHITE, BLUE);
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
		Common::setConsoleColor(BRIGHT_WHITE, BLUE);
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

void handleTrafficLights(CTRAFFICLIGHT*& truck, CTRAFFICLIGHT*& car, CPEOPLE*& people, int& gameState)
{
	while (people->getState() && gameState != QUIT && gameState != DONE_LEVEL) {
		if (gameState == PLAYING) {
			Sleep(1000);
			truck->countDown();
			car->countDown();
		}
	}
}

void renderTruck(int _left, int _top, CPEOPLE*& people, CTRUCK*& truck, CTRAFFICLIGHT*& light, int& gameState, bool music) {
	truck->Move();
	while (people->getState() && gameState != QUIT && gameState != DONE_LEVEL) {
		if (gameState == PLAYING && light->getState() == GREEN_LIGHT) truck->Move();
		if (people->IsImpact(truck)) {
			if (music) Common::playSound(OHOH_SOUND);
			people->setState(0);
			for (int i = 0; i < 6; i++) {
				people->RenderPeople(RED);
				Sleep(100);
				people->RenderPeople(BLACK);
				Sleep(100);
			}
		};
	}
}

void renderCar(int _left, int _top, CPEOPLE*& people, CCAR*& car, CTRAFFICLIGHT*& light, int& gameState, bool music) {
	car->Move();
	while (people->getState() && gameState != QUIT && gameState != DONE_LEVEL) {
		if (gameState == PLAYING && light->getState() == GREEN_LIGHT) car->Move();
		if (people->IsImpact(car)) {
			if (music) Common::playSound(OHOH_SOUND);
			people->setState(0);
			for (int i = 0; i < 6; i++) {
				people->RenderPeople(RED);
				Sleep(100);
				people->RenderPeople(BLACK);
				Sleep(100);
			}
		};
	}
}

void renderBird(int _left, int _top, CPEOPLE*& people, CBIRD*& bird, int& gameState, bool music) {
	bird->Move();
	while(people->getState() && gameState != QUIT && gameState != DONE_LEVEL){
		if (gameState == PLAYING) bird->Move();
		if (people->IsImpact(bird)) {
			if (music) Common::playSound(OHOH_SOUND);
			people->setState(0);
			for (int i = 0; i < 6; i++) {
				people->RenderPeople(RED);
				Sleep(100);
				people->RenderPeople(BLACK);
				Sleep(100);
			}
		}
	}
}

void renderDino(int _left, int _top, CPEOPLE*& people, CDINAUSOR*& dino, int& gameState, bool music) {
	dino->Move();
	while (people->getState() && gameState != QUIT && gameState != DONE_LEVEL) {
		if (gameState == PLAYING) dino->Move();
		if (people->IsImpact(dino)) {
			if (music) Common::playSound(OHOH_SOUND);
			people->setState(0);
			for (int i = 0; i < 6; i++) {
				people->RenderPeople(RED);
				Sleep(100);
				people->RenderPeople(BLACK);
				Sleep(100);
			}
		};
	}
}

//--------------------------------------------------------------

void CGAME::togglePlaying()
{
	// toggle pausing - playing
	_state = 1 - _state;				// because playing is 0 and pausing is 1
	mtx.lock();
	Common::setConsoleColor(BRIGHT_WHITE, BLUE);
	Common::gotoXY(_left + LANE_LENGTH + 11 + 8, _top + 15);
	if (_state != PLAYING)
		cout << "PLAYING";
	else
		cout << "PAUSING";
	mtx.unlock();
}

void CGAME::Start()
{
	while (people->getState() && _state != QUIT) {
		RenderGame();
		_state = PLAYING;
		Move();
		if (_state == DONE_LEVEL) {
			UpLevel();
		}
	}
}

void CGAME::Move()
{
	people->RenderPeople(BLACK);
	thread t2([&] {renderTruck(_left, _top, people, truck, lightTruck, _state, _musicEffect); });
	thread t3([&] {renderCar(_left, _top, people, car, lightCar, _state, _musicEffect); });
	thread t4([&] {renderBird(_left, _top, people, bird, _state, _musicEffect); });
	thread t5([&] {renderDino(_left, _top, people, dino,  _state, _musicEffect); });
	thread trafficLight([&] {handleTrafficLights(lightTruck, lightCar, people, _state); });
	while (people->getState() && _state != QUIT && _state != DONE_LEVEL) {
		int tmp;
		switch (tmp = Common::getConsoleInput()) {
		case 2:
		case 3:
		case 4:
		case 5:
			if (_state == PLAYING) people->Move(tmp);
			break;
		case 9:									
			togglePlaying();
			break;
		case 10:								//Saving
			togglePlaying();
			Save();
			break;
		case 11:								// quit without saving
			_state = QUIT;
			break;
		};

		if (people->IsFinish()) {
			_state = DONE_LEVEL;
		}
	};
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	trafficLight.join();
}

void CGAME::UpLevel()
{
	if (_musicEffect) if (_musicEffect) Common::playSound(WIN_SOUND);
	people->UpLevel();
	if (people->getLevel() == 6)
		people->setState(0);	//Die
	else
		DrawLevelNumber(people->getLevel());
	truck->UpLevel(people->getLevel()-1);
	truck->CreateList();
	car->UpLevel(people->getLevel()-1);
	car->CreateList();
	dino->UpLevel(people->getLevel()-1);
	dino->CreateList();
	bird->UpLevel(people->getLevel()-1);
	bird->CreateList();
}