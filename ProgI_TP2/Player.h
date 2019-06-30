#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
public:
	Player(const int positions[], float minX, float maxX);
	~Player();

	void move(float velocity);
	void jump();
	void draw(RenderWindow * window);
	void update();
	FloatRect getBounds();
	int getCurrentPlatform();
	void getDamage();

protected:
	Texture _tx;
	Sprite _sprite;
	float _velocity = 0.0f;
	float _speed = 10.0f;
	bool colliding;
	int platformPositions[7];
	
	int currentPlatform;
	float x = 0;
	float y = 0;
	float velocityX = 0;
	float minX, maxX;
	bool faceLeft;


	void updateMovement();
};

