#include "pch.h"
#include "Enemy.h"


Enemy::Enemy(EnemyColor color, float posX, float posY)
{
	switch (color) {
	case EnemyColor::green:
		_tx.loadFromFile("Images/shell_verde.png");
		break;
	case EnemyColor::blue:
		_tx.loadFromFile("Images/shell_azul.png");
		break;
	case EnemyColor::red:
		_tx.loadFromFile("Images/shell_rojo.png");
		break;
	case EnemyColor::yellow:
		_tx.loadFromFile("Images/shell_amarillo.png");
		break;
	}
	_sprite.setTexture(_tx);
	_sprite.setOrigin(_tx.getSize().x / 2, _tx.getSize().y);
	
	origX = x = posX;
	y = posY;

	faceLeft = true;
}


Enemy::~Enemy()
{
}




void Enemy::draw(RenderWindow * window) {
	window->draw(_sprite);
}

void Enemy::update() {
	updateMovement();

	if (velocityX > 0.0f && faceLeft)
	{
		_sprite.setScale(-1.f, 1.f);
		faceLeft = false;
	}
	else if (velocityX < 0.0f && !faceLeft)
	{
		_sprite.setScale(1.f, 1.f);
		faceLeft = true;
	}

	_sprite.setPosition(x, y);

}

void Enemy::move(float velocity) {
	velocityX = velocity;
}

void Enemy::updateMovement() {
	
	x += velocityX * _speed;
}

FloatRect Enemy::getBounds() {
	return _sprite.getGlobalBounds();
}

float Enemy::GetXPosition() {
	return x;
}

bool Enemy::IsMovingRight() {
	return velocityX > 0.0f;
}

bool Enemy::IsMovingLeft() {
	return velocityX < 0.0f;
}

void Enemy::SetXPosition(float xpos) {
	x = xpos;
}

float Enemy::GetOriginalXPosition() {
	return origX;
}