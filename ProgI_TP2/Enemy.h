#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
enum EnemyColor { red, green, blue, yellow };

class Enemy
{
public:
	Enemy(EnemyColor color,float posX, float posY);
	~Enemy();

	void move(float velocity);
	void draw(RenderWindow * window);
	void update();
	FloatRect getBounds();
	float GetXPosition();
	bool IsMovingRight();
	bool IsMovingLeft();

private:
	Texture _tx;
	Sprite _sprite;
	float _velocity = 0.0f;
	float _speed = 5.0f;
	bool colliding;

	float x, y = 0;
	float velocityX = 0;
	bool isGrounded;
	bool faceLeft;
	bool movingRight;

	void updateMovement();
};

