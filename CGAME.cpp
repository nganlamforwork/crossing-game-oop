#include "CGAME.h"

CGAME::CGAME(bool musicEffect)
{
	state = PLAYING;

	truck = new CTRUCK(2, 0, left, top);
	lightTruck = new CTRAFFICLIGHT(2, 0, left, top, 4, GREEN_LIGHT, 4);

	car = new CCAR(3, 1, left, top);
	lightCar = new CTRAFFICLIGHT(3, 1, left, top, 4, RED_LIGHT, 4);

	bird = new CBIRD(4, 0, left, top);

	dino = new CDINAUSOR(5, 1, left, top);

	people = new CPEOPLE(6, 1, left, top);

	musicEffect = musicEffect;
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

int CGAME::GetState()
{ 
	return state; 
};

bool CGAME::IsWin()
{ 
	return people->GetLevel() == 6; 
};

//--------------------------------------------------------------

void CGAME::Create()
{
	truck->CreateList();
	car->CreateList();
	bird->CreateList();
	dino->CreateList();
}

void CGAME::Load(string name)
{
	ifstream in(name);
	int level;
	in >> level;
	people->SetLevel(level);
	people->Load(in);
	truck->LoadList(in);
	lightTruck->Load(in);
	car->LoadList(in);
	lightCar->Load(in);
	bird->LoadList(in);
	dino->LoadList(in);
	in.close();
}

void CGAME::Save()
{
	string name;

	mtx.lock();
	Common::gotoXY(left + LANE_LENGTH + 11 + 1, top + 8);
	cout << "                      ";
	Common::gotoXY(left + LANE_LENGTH + 11 + 1, top + 10);
	cout << "                      ";
	Common::gotoXY(left + LANE_LENGTH + 11 + 1, top + 11);
	cout << "                      ";
	mtx.unlock();


	mtx.lock();
	Common::showCursor(1);
	Common::gotoXY(left + LANE_LENGTH + 11, top + 7);
	Common::setConsoleColor(BRIGHT_WHITE, BLUE);
	cout << "    Enter your name:";
	Common::gotoXY(left + LANE_LENGTH + 11 + 1, top + 8);
	getline(cin, name, '\n');
	mtx.unlock();

	name = "data\\" + name + ".txt";
	ofstream out(name);

	out << people->GetLevel() << '\n';
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
	Common::gotoXY(left + LANE_LENGTH + 11 + 3, top + 10);
	Common::setConsoleColor(BRIGHT_WHITE, BLUE);
	cout << "Save successfully!";
	Common::gotoXY(left + LANE_LENGTH + 11 + 2, top + 11);
	Common::setConsoleColor(BRIGHT_WHITE, BLUE);
	cout << "Press P to continue";
	mtx.unlock();
}

void CGAME::TogglePlaying()
{
	// toggle pausing - playing
	state = 1 - state;				// because playing is 0 and pausing is 1
	mtx.lock();
	Common::setConsoleColor(BRIGHT_WHITE, BLUE);
	Common::gotoXY(left + LANE_LENGTH + 11 + 8, top + 15);
	if (state != PLAYING)
		cout << "PLAYING";
	else
		cout << "PAUSING";
	mtx.unlock();
}

//--------------------------------------------------------------

void CGAME::RenderGame()
{
	DrawGame();
	DrawLevelNumber(people->GetLevel());
	lightTruck->Render();
	lightCar->Render();
}

//--------------------------------------------------------------

void CGAME::DrawEndGame(string fileName)
{
	int left = 0, top = 0;
	Common::clearConsole();
	GUI::Image(fileName, left + 40, top + 8, RED);
	GUI::Image("images\\flowers.txt", 26, 25, GREEN);

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
	while (people->GetState() && gameState != QUIT && gameState != DONE_LEVEL) {
		if (gameState == PLAYING) {
			Sleep(1000);
			truck->CountDown();
			car->CountDown();
		}
	}
}

void renderTruck(int left, int top, CPEOPLE*& people, CTRUCK*& truck, CTRAFFICLIGHT*& light, int& gameState, bool music) {
	truck->Move();
	while (people->GetState() && gameState != QUIT && gameState != DONE_LEVEL) {
		if (gameState == PLAYING && light->GetState() == GREEN_LIGHT) truck->Move();
		if (people->IsImpact(truck)) {
			if (music) Common::playSound(OHOH_SOUND);
			people->SetState(0);
			for (int i = 0; i < 6; i++) {
				people->RenderPeople(RED);
				Sleep(100);
				people->RenderPeople(BLACK);
				Sleep(100);
			}
		};
	}
}

void renderCar(int left, int top, CPEOPLE*& people, CCAR*& car, CTRAFFICLIGHT*& light, int& gameState, bool music) {
	car->Move();
	while (people->GetState() && gameState != QUIT && gameState != DONE_LEVEL) {
		if (gameState == PLAYING && light->GetState() == GREEN_LIGHT) car->Move();
		if (people->IsImpact(car)) {
			if (music) Common::playSound(OHOH_SOUND);
			people->SetState(0);
			for (int i = 0; i < 6; i++) {
				people->RenderPeople(RED);
				Sleep(100);
				people->RenderPeople(BLACK);
				Sleep(100);
			}
		};
	}
}

void renderBird(int left, int top, CPEOPLE*& people, CBIRD*& bird, int& gameState, bool music) {
	bird->Move();
	while(people->GetState() && gameState != QUIT && gameState != DONE_LEVEL){
		if (gameState == PLAYING) bird->Move();
		if (people->IsImpact(bird)) {
			if (music) Common::playSound(OHOH_SOUND);
			people->SetState(0);
			for (int i = 0; i < 6; i++) {
				people->RenderPeople(RED);
				Sleep(100);
				people->RenderPeople(BLACK);
				Sleep(100);
			}
		}
	}
}

void renderDino(int left, int top, CPEOPLE*& people, CDINAUSOR*& dino, int& gameState, bool music) {
	dino->Move();
	while (people->GetState() && gameState != QUIT && gameState != DONE_LEVEL) {
		if (gameState == PLAYING) dino->Move();
		if (people->IsImpact(dino)) {
			if (music) Common::playSound(OHOH_SOUND);
			people->SetState(0);
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

void CGAME::Start()
{
	while (people->GetState() && state != QUIT) {
		RenderGame();
		state = PLAYING;
		Move();
		if (state == DONE_LEVEL) {
			UpLevel();
		}
	}
}

void CGAME::Move()
{
	people->RenderPeople(BLACK);
	thread t2([&] {renderTruck(left, top, people, truck, lightTruck, state, musicEffect); });
	thread t3([&] {renderCar(left, top, people, car, lightCar, state, musicEffect); });
	thread t4([&] {renderBird(left, top, people, bird, state, musicEffect); });
	thread t5([&] {renderDino(left, top, people, dino,  state, musicEffect); });
	thread trafficLight([&] {handleTrafficLights(lightTruck, lightCar, people, state); });
	while (people->GetState() && state != QUIT && state != DONE_LEVEL) {
		int tmp;
		switch (tmp = Common::getConsoleInput()) {
		case 2:
		case 3:
		case 4:
		case 5:
			if (state == PLAYING) people->Move(tmp);
			break;
		case 9:									
			TogglePlaying();
			break;
		case 10:								//Saving
			TogglePlaying();
			Save();
			break;
		case 11:								// quit without saving
			state = QUIT;
			break;
		};

		if (people->IsFinish()) {
			state = DONE_LEVEL;
		}
	};
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	trafficLight.join();
}

//--------------------------------------------------------------

void CGAME::DrawGame()
{
	Common::clearConsole();

	GUI::Image("titles\\level.txt", left + 35, top + 1, BLUE);

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	//Vẽ biên trên
	Common::gotoXY(left + 1, top);
	putchar(201);
	for (int i = 1; i < LANE_LENGTH; i++) {
		//Sleep(2);
		putchar(205);
	}
	putchar(187);

	//Vẽ biên phải
	for (int i = 1; i < NUM_LANE * LANE_HEIGHT; i++) {
		//Sleep(5);
		Common::gotoXY(LANE_LENGTH + left + 1, i + top);
		putchar(186);
	}
	Common::gotoXY(LANE_LENGTH + left + 1, NUM_LANE * LANE_HEIGHT + top);
	putchar(188);


	//Vẽ biên dưới
	for (int i = 1; i < LANE_LENGTH; i++) {
		Common::gotoXY(LANE_LENGTH + left - i + 1, NUM_LANE * LANE_HEIGHT + top);
		putchar(205);
	}
	Common::gotoXY(left + 1, NUM_LANE * LANE_HEIGHT + top);
	putchar(200);

	//Vẽ biên trái
	for (int i = 1; i < NUM_LANE * LANE_HEIGHT; i++) {
		Common::gotoXY(left + 1, NUM_LANE * LANE_HEIGHT + top - i);
		putchar(186);
	}

	//Vẽ đường ngang
	for (int i = 1; i < LANE_LENGTH; i++) {
		for (int j = LANE_HEIGHT; j < NUM_LANE * LANE_HEIGHT; j += LANE_HEIGHT) {
			Common::gotoXY(i + left + 1, j + top);
			putchar(196);
		}
	}
	DrawAsideMenu();
}

void CGAME::DrawAsideMenu()
{
	int SUB_LANE_LENGTH = 24;
	//Vẽ biên trên
	Common::gotoXY(left + LANE_LENGTH + 10, top);
	putchar(201);
	for (int i = 1; i < SUB_LANE_LENGTH; i++)
		putchar(205);
	putchar(187);

	//Vẽ biên phải
	for (int i = 1; i < NUM_LANE * LANE_HEIGHT; i++) {
		Common::gotoXY(LANE_LENGTH + left + 10 + SUB_LANE_LENGTH, i + top);
		putchar(186);
	}
	Common::gotoXY(LANE_LENGTH + left + 10 + SUB_LANE_LENGTH, NUM_LANE * LANE_HEIGHT + top);
	putchar(188);

	//Vẽ biên dưới
	for (int i = 1; i < SUB_LANE_LENGTH; i++) {
		Common::gotoXY(LANE_LENGTH + left + i + 10, NUM_LANE * LANE_HEIGHT + top);
		putchar(205);
	}
	Common::gotoXY(LANE_LENGTH + left + 10, NUM_LANE * LANE_HEIGHT + top);
	putchar(200);

	//Vẽ biên trái
	for (int i = 1; i < NUM_LANE * LANE_HEIGHT; i++) {
		Common::gotoXY(left + LANE_LENGTH + 10, NUM_LANE * LANE_HEIGHT + top - i);
		putchar(186);
	}

	//Ghi nội dung aside menu
	GUI::Image("titles\\AsideMenu.txt", left + LANE_LENGTH + 11, top + 1, BLUE);
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
		Common::gotoXY(left + 35 + 32, top + i++);
		string tmp;
		getline(in, tmp);
		cout << tmp;
		mtx.unlock();
	}
	in.close();
}

void CGAME::UpLevel()
{
	if (musicEffect) if (musicEffect) Common::playSound(WIN_SOUND);
	people->UpLevel();
	if (people->GetLevel() == 6)
		people->SetState(0);	//Die
	else
		DrawLevelNumber(people->GetLevel());
	truck->UpLevel(people->GetLevel()-1);
	truck->CreateList();
	car->UpLevel(people->GetLevel()-1);
	car->CreateList();
	dino->UpLevel(people->GetLevel()-1);
	dino->CreateList();
	bird->UpLevel(people->GetLevel()-1);
	bird->CreateList();
}