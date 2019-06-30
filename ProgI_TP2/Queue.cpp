#include "pch.h"
#include "Queue.h"


Queue::Queue()
{
}


Queue::~Queue()
{
}

void Queue::Enqueue(Enemy * e)
{
	pnode newNode = new EnemyNode(e);

	if (last) {
		last->next = newNode;
	}

	last = newNode;

	if (!head) {
		head = newNode;
	}
}

Enemy * Queue::Dequeue()
{
	pnode node;
	Enemy* value;

	node = head;
	if (!node) return NULL;

	head = node->next;
	value = node->value;

	delete node;

	if (!head) {
		last = NULL;
	}

	return value;
}

Enemy * Queue::First()
{
	Enemy* value;

	if (!head) return NULL;

	value = head->value;

	return value;
}

Enemy * Queue::Last()
{
	Enemy* value;

	if (!last) return NULL;

	value = last->value;

	return value;
}


bool Queue::IsEmpty()
{
	return head == NULL;
}

void Queue::Update()
{
	pnode node = head;
	while (node) {
		node->value->update();
		node = node->next;
	}
}

void Queue::Draw(sf::RenderWindow * wnd)
{
	pnode node = head;
	while (node) {
		node->value->draw(wnd);
		node = node->next;
	}
}

void Queue::RepositionEnemies(float direction) {
	pnode node = head;
	while (node) {
		float newX;
			if (direction > 0) {
				newX = node->value->GetXPosition() + node->value->getBounds().width;
			}
			else {
				newX = node->value->GetXPosition() - node->value->getBounds().width;
			}
		node->value->SetXPosition(newX);
		node = node->next;
	}
}
