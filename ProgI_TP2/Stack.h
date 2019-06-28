#pragma once
#include "EnemyNode.h"
#include <SFML/Graphics.hpp>

class Stack
{
public:
	Stack();
	~Stack();

	void Push(Enemy* e);
	Enemy* Pop();
	Enemy* Last();
	bool IsEmpty();
	void Update();
	void Draw(sf::RenderWindow* wnd);

private:
	pnode head;
	pnode last;
};

