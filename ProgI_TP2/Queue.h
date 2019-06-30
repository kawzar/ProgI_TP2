#pragma once
#include "EnemyNode.h"

class Queue
{
public:
	Queue();
	~Queue();

	void Enqueue(Enemy* e);
	Enemy* Dequeue();
	Enemy* Last();
	Enemy* First();
	bool IsEmpty();
	void Update();
	void Draw(sf::RenderWindow* wnd);
	void RepositionEnemies(float relativeDistance);

private:
	pnode head;
	pnode last;
};

