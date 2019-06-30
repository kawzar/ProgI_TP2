#include "pch.h"
#include "Player.h"
#include <stdio.h>
#include <iostream>

using namespace std;


Player::Player(const int positions[], float minX, float maxX)
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
	this->minX = minX;
	this->maxX = maxX;
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

	if (x >= maxX) {
		x = maxX;
	}

	if (x <= minX) {
		x = minX;
	}
}

FloatRect Player::getBounds() {
	return _sprite.getGlobalBounds();
}

int Player::getCurrentPlatform()
{
	return currentPlatform;
}

void Player::getDamage()
{
	currentPlatform = 0;
	y = platformPositions[0];
}