#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Stack.h"

using namespace sf;
using namespace std;

class Game
{
public:
	Game();
	~Game();
	void Loop();

private:
	RenderWindow *_window;
	Texture _txBackground;
	Sprite _background;
	Player* _player;
	Clock _clock;
	Time _time;
	Text _txtTime;
	Text _txtGameOver;
	Font _font;
	SoundBuffer _clockSb;
	SoundBuffer _jumpSb;
	SoundBuffer _correctSb;
	SoundBuffer _failSb;
	Sound _clockSound;
	Sound _jumpSound;
	Sound _correctSound;
	Sound _failSound;

	Stack enemyStack1Left, enemyStack1right;
	Enemy* floor1Enemy;

	Stack enemyStack2Left, enemyStack2right;
	Enemy* floor2Enemy;

	bool gameOver;
	bool playerWon;
	bool floor1MovingRight, floor2MovingRight;
	int floor1CountLeft, floor1CountRight, floor2CountRight, floor2CountLeft;
	int platformPositions[7];

	const int amountOfBlocks = 10;

	void EventHandling();
	void Update();
	void Draw();
	void InitWindow();
	void InitSound();
	void InputHandling();
	void UpdateClock();
	void InitClock();
	void ShowGameOverScreen();
	void CheckWinCondition();
	void UpdateEnemies();
	void DrawEnemies();
	void InitFloor1();
	void InitFloor2();
	void MoveEnemies();
	void MoveFloor1();
	void MoveFloor2();
};

