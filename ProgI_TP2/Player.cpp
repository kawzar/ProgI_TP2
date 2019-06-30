#include "pch.h"
#include "Player.h"
#include <stdio.h>
#include <iostream>

using namespace std;


Player::Player(const int positions[])
{
	_tx.loadFromFile("Images/jumper.png");
	_sprite.setTexture(_tx);
	_sprite.setOrigin(_tx.getSize().x / 2, _tx.getSize().y);
	x = 160;
	faceLeft = true;
	currentPlatform = 0;

	for (int i = 0; i < 7; i++) {
		platformPositions[i] = positions[i];
	}

	y = platformPositions[currentPlatform];
}


Player::~Player()
{
}

void Player::draw(RenderWindow * window) {
	window->draw(_sprite);
}

void Player::update() {
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

void Player::move(float velocity) {
	velocityX = velocity;
}

void Player::jump() {

	if (currentPlatform < 6) {
		currentPlatform++;
		y = platformPositions[currentPlatform];
	}
}

void Player::updateMovement() {
	x += velocityX;
}

FloatRect Player::getBounds() {
	return _sprite.getGlobalBounds();
}

Vector2f Player::getColliderPosition() {
	return Vector2f(_sprite.getPosition());
}

void Player::collide() {
	colliding = true;
}

bool Player::isColliding() {
	return colliding;
}