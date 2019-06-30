#include "pch.h"
#include "Game.h"
#include <iostream>

using namespace std;


Game::Game(){
	float positions[] = { 524, 450, 374, 298, 222, 150, 74 };
	for (int i = 0; i < 7; i++) {
		platformPositions[i] = positions[i];
	}

	_player = new Player(platformPositions);
	

	InitWindow();
	InitClock();
	InitSound();
	InitFloor1();
	InitFloor2();
	InitQueueFloors();
}


Game::~Game()
{
}

void Game::Loop()
{
	while (_window->isOpen())
	{
		if (!gameOver) {
			UpdateClock();
			EventHandling();
			InputHandling();
			MoveEnemies();
			Update();
			Draw();
			CheckWinCondition();
		}
		else {
			ShowGameOverScreen();
		}
	}
}

void Game::InputHandling() 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_player->move(-10.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_player->move(10.0f);
	} 
	else
	{
		_player->move(0.0f);
	}
}


void Game::EventHandling()
{
	Event evt;
	while (_window->pollEvent(evt))
	{
		switch (evt.type)
		{
			case Event::Closed:
				_window->close();
				break;
			case Event::KeyPressed:
				if (evt.key.code == sf::Keyboard::Space) {
					_player->jump();
					_jumpSound.play();
				}
		}
	}
}

void Game::Update()
{
	_player->update();
	UpdateEnemies();

}


void Game::Draw()
{
	_window->clear();
	_window->draw(_background);
	_window->draw(_txtTime);

	
	_player->draw(_window);
	DrawEnemies();
	
	_window->display();
}


void Game::InitWindow()
{
	_window = new RenderWindow(VideoMode(800, 600), "TP1");
	_window->setMouseCursorVisible(true);
	_window->setFramerateLimit(60);
	_txBackground.loadFromFile("Images/fondo_plataformas.png");
	_background.setTexture(_txBackground);
}


void Game::InitClock() {
	_time = sf::seconds(30.0f);
	int seconds = _time.asSeconds();

	if (!_font.loadFromFile("Less.otf"))
	{
		cout << "Couldn't load font";
	}

	_txtTime = Text(std::to_string(seconds), _font, 15);
	_txtTime.setFillColor(sf::Color::White);
	_txtTime.setPosition(15, 15);
}

void Game::InitSound()
{
	_jumpSb.loadFromFile("Sounds/smw_jump.wav");
	_correctSb.loadFromFile("Sounds/smw_coin.wav");
	_failSb.loadFromFile("Sounds/smw_stomp.wav");
	_clockSb.loadFromFile("Sounds/tick.wav");
	
	_jumpSound.setBuffer(_jumpSb);
	_correctSound.setBuffer(_correctSb);
	_failSound.setBuffer(_failSb);
	_clockSound.setBuffer(_clockSb);
}


void Game::UpdateClock() {
	int previousSecond = _time.asSeconds();
	_time -= _clock.restart();

	int seconds = _time.asSeconds();
	_txtTime.setString(std::to_string(seconds));

	if (seconds != previousSecond) {
		_clockSound.play();
	}
}

void Game::ShowGameOverScreen() {
	if(playerWon){
		_txtGameOver = Text("You won! Your remaining time was: ", _font, 15);
		_txtGameOver.setFillColor(sf::Color::Green);
		_txtGameOver.setPosition(200, 250);

		_txtTime.setFillColor(sf::Color::Green);
		_txtTime.setPosition(200, 290);
		_window->draw(_txtTime);

	}
	else {
		_txtGameOver = Text("You Lost!", _font, 15);
		_txtGameOver.setFillColor(sf::Color::Red);
		_txtGameOver.setPosition(200, 250);
		_txtTime.setFillColor(Color::Black);
	}

	Event evt;
	while (_window->waitEvent(evt))
	{
		if (evt.type == Event::Closed) {
			_window->close();
		}

		_window->clear(Color::Black);
		_window->draw(_txtGameOver);
		_window->draw(_txtTime);
		_window->display();
	}
}

void Game::CheckWinCondition() {
	/*if (lastCorrectIndex == amountOfBlocks) {
		gameOver = true;
		playerWon = true;
	}*/

	if (_time <= sf::seconds(0.0f)) {
		gameOver = true;
		playerWon = false;
	}

}

void Game::InitFloor1() {
	enemyStack1Left.Push(new Enemy(EnemyColor::blue, 50, platformPositions[1]));
	enemyStack1Left.Push(new Enemy(EnemyColor::red, 80, platformPositions[1]));
	enemyStack1Left.Push(new Enemy(EnemyColor::yellow, 110, platformPositions[1]));
	enemyStack1Left.Push(new Enemy(EnemyColor::green, 140, platformPositions[1]));

	floor1Enemy = NULL;
	floor1CountLeft = 4;
	floor1CountRight = 0;
	floor1MovingRight = true;
}

void Game::InitFloor2() {
	enemyStack2Left.Push(new Enemy(EnemyColor::blue, 50, platformPositions[2]));
	enemyStack2Left.Push(new Enemy(EnemyColor::red, 80, platformPositions[2]));
	enemyStack2Left.Push(new Enemy(EnemyColor::yellow, 110, platformPositions[2]));
	enemyStack2Left.Push(new Enemy(EnemyColor::green, 140, platformPositions[2]));

	floor2Enemy = NULL;
	floor2CountLeft = 4;
	floor2CountRight = 0;
	floor2MovingRight = true;
}

void Game::InitQueueFloors()
{
	floor3Enemy = NULL;
	floor4Enemy = NULL;
	floor5Enemy = NULL;
	floor6Enemy = NULL;

	enemyQueue3.Enqueue(new Enemy(EnemyColor::blue, 140, platformPositions[3]));
	enemyQueue3.Enqueue(new Enemy(EnemyColor::red, 110, platformPositions[3]));
	enemyQueue3.Enqueue(new Enemy(EnemyColor::yellow, 80, platformPositions[3]));
	enemyQueue3.Enqueue(new Enemy(EnemyColor::green, 50, platformPositions[3]));

	enemyQueue4.Enqueue(new Enemy(EnemyColor::blue, 660, platformPositions[4]));
	enemyQueue4.Enqueue(new Enemy(EnemyColor::red, 690, platformPositions[4]));
	enemyQueue4.Enqueue(new Enemy(EnemyColor::yellow, 720, platformPositions[4]));
	enemyQueue4.Enqueue(new Enemy(EnemyColor::green, 750, platformPositions[4]));

	enemyQueue5.Enqueue(new Enemy(EnemyColor::blue, 140, platformPositions[5]));
	enemyQueue5.Enqueue(new Enemy(EnemyColor::red, 110, platformPositions[5]));
	enemyQueue5.Enqueue(new Enemy(EnemyColor::yellow, 80, platformPositions[5]));
	enemyQueue5.Enqueue(new Enemy(EnemyColor::green, 50, platformPositions[5]));

	enemyQueue6.Enqueue(new Enemy(EnemyColor::blue, 660, platformPositions[6]));
	enemyQueue6.Enqueue(new Enemy(EnemyColor::red, 690, platformPositions[6]));
	enemyQueue6.Enqueue(new Enemy(EnemyColor::yellow, 720, platformPositions[6]));
	enemyQueue6.Enqueue(new Enemy(EnemyColor::green, 750, platformPositions[6]));
}			  


void Game::UpdateEnemies() {
	enemyStack1Left.Update();
	enemyStack1right.Update();
	enemyStack2Left.Update();
	enemyStack2right.Update();

	enemyQueue3.Update();
	enemyQueue4.Update();
	enemyQueue5.Update();
	enemyQueue6.Update();
}

void Game::DrawEnemies() {
	enemyStack1Left.Draw(_window);
	enemyStack1right.Draw(_window);
	enemyStack2Left.Draw(_window);
	enemyStack2right.Draw(_window);
	
	enemyQueue3.Draw(_window);
	enemyQueue4.Draw(_window);
	enemyQueue5.Draw(_window);
	enemyQueue6.Draw(_window);
}

void Game::MoveEnemies() {
	MoveFloor1();
	MoveFloor2();
	MoveQueueFloors();
}

void Game::MoveFloor1() {
	if (floor1MovingRight && floor1Enemy == NULL && !enemyStack1Left.IsEmpty()) {
		floor1Enemy = enemyStack1Left.Last();
		floor1Enemy->move(1.0f);
	}
	else if (!floor1MovingRight && floor1Enemy == NULL && !enemyStack1right.IsEmpty()) {
		floor1Enemy = enemyStack1right.Last();
		floor1Enemy->move(-1.0f);
	}
	else if (floor1MovingRight && floor1Enemy && floor1Enemy->IsMovingRight() && ((enemyStack1right.Last() && floor1Enemy->GetXPosition() >= enemyStack1right.Last()->GetXPosition() - floor1Enemy->getBounds().width)|| floor1Enemy->GetXPosition() >= 750)) { 
		floor1Enemy->move(0.0f); // stop moving
		enemyStack1right.Push(floor1Enemy); // change stack
		enemyStack1Left.Pop();
		floor1Enemy = NULL;
		floor1CountRight++;
		floor1CountLeft--;

		if (floor1CountRight == 4) {
			floor1MovingRight = false;
		}
	}
	else if (!floor1MovingRight && floor1Enemy && floor1Enemy->IsMovingLeft() && ((enemyStack1Left.Last() && floor1Enemy->GetXPosition() <= enemyStack1Left.Last()->GetXPosition() + floor1Enemy->getBounds().width) || floor1Enemy->GetXPosition() <= 50)) {
		floor1Enemy->move(-0.0f); // stop moving
		enemyStack1Left.Push(floor1Enemy); // change stack
		enemyStack1right.Pop();
		floor1Enemy = NULL;
		floor1CountLeft++;
		floor1CountRight--;

		if (floor1CountLeft == 4) {
			floor1MovingRight = true;
		}
	}
}

void Game::MoveFloor2() {
	if (_time <= sf::seconds(28.0f)) {
		if (floor2MovingRight && floor2Enemy == NULL && !enemyStack2Left.IsEmpty()) {
			floor2Enemy = enemyStack2Left.Last();
			floor2Enemy->move(1.0f);
		}
		else if (!floor2MovingRight && floor2Enemy == NULL && !enemyStack2right.IsEmpty()) {
			floor2Enemy = enemyStack2right.Last();
			floor2Enemy->move(-1.0f);
		}
		else if (floor2MovingRight && floor2Enemy && floor2Enemy->IsMovingRight() && ((enemyStack2right.Last() && floor2Enemy->GetXPosition() >= enemyStack2right.Last()->GetXPosition() - floor2Enemy->getBounds().width) || floor2Enemy->GetXPosition() >= 750)) {
			floor2Enemy->move(0.0f); // stop moving
			enemyStack2right.Push(floor2Enemy); // change stack
			enemyStack2Left.Pop();
			floor2Enemy = NULL;
			floor2CountRight++;
			floor2CountLeft--;

			if (floor2CountRight == 4) {
				floor2MovingRight = false;
			}
		}
		else if (!floor2MovingRight && floor2Enemy && floor2Enemy->IsMovingLeft() && ((enemyStack2Left.Last() && floor2Enemy->GetXPosition() <= enemyStack2Left.Last()->GetXPosition() + floor2Enemy->getBounds().width) || floor2Enemy->GetXPosition() <= 50)) {
			floor2Enemy->move(-0.0f); // stop moving
			enemyStack2Left.Push(floor2Enemy); // change stack
			enemyStack2right.Pop();
			floor2Enemy = NULL;
			floor2CountLeft++;
			floor2CountRight--;

			if (floor2CountLeft == 4) {
				floor2MovingRight = true;
			}
		}
	}
}

void Game::MoveQueueFloors()
{
	if (_time <= sf::seconds(28.5f)) {
		if (floor3Enemy == NULL) {
			floor3Enemy = enemyQueue3.First();
			floor3Enemy->move(1.0f);
		}
		else if (floor3Enemy->GetXPosition() >= 800) {
			floor3Enemy->move(0.0f);
			enemyQueue3.RepositionEnemies(1.0f);
			floor3Enemy->SetXPosition(enemyQueue3.Last()->GetXPosition() - enemyQueue3.Last()->getBounds().width);
			enemyQueue3.Enqueue(enemyQueue3.Dequeue());
			floor3Enemy = NULL;
		}
	}

	if (_time <= sf::seconds(28.0f)) {
		if (floor4Enemy == NULL) {
			floor4Enemy = enemyQueue4.First();
			floor4Enemy->move(-1.0f);
		}
		else if (floor4Enemy->GetXPosition() <= 0) {
			floor4Enemy->move(0.0f);
			enemyQueue4.RepositionEnemies(-1.0f);
			floor4Enemy->SetXPosition(enemyQueue4.Last()->GetXPosition() + enemyQueue4.Last()->getBounds().width);
			enemyQueue4.Enqueue(enemyQueue4.Dequeue());
			floor4Enemy = NULL;
		}
	}

	if (_time <= sf::seconds(27.5f)) {
		if (floor5Enemy == NULL) {
			floor5Enemy = enemyQueue5.First();
			floor5Enemy->move(1.0f);
		}
		else if (floor5Enemy->GetXPosition() >= 800) {
			floor5Enemy->move(0.0f);
			enemyQueue5.RepositionEnemies(1.0f);
			floor5Enemy->SetXPosition(enemyQueue5.Last()->GetXPosition() - enemyQueue5.Last()->getBounds().width);
			enemyQueue5.Enqueue(enemyQueue5.Dequeue());
			floor5Enemy = NULL;
		}
	}

	if (_time <= sf::seconds(27.0f)) {
		if (floor6Enemy == NULL) {
			floor6Enemy = enemyQueue6.First();
			floor6Enemy->move(-1.0f);
		}
		else if (floor6Enemy->GetXPosition() <= 0) {
			floor6Enemy->move(0.0f);
			enemyQueue6.RepositionEnemies(-1.0f);
			floor6Enemy->SetXPosition(enemyQueue6.Last()->GetXPosition() + enemyQueue6.Last()->getBounds().width);
			enemyQueue6.Enqueue(enemyQueue6.Dequeue());
			floor6Enemy = NULL;
		}
	}
}
