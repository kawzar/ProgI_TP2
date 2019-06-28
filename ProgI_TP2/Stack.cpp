#include "pch.h"
#include "Stack.h"


Stack::Stack()
{
}


Stack::~Stack()
{
}

void Stack::Push(Enemy* e) {
	pnode newNode = new EnemyNode(e, head);
	head = newNode;
}

Enemy* Stack::Pop() {
	pnode node;
	Enemy* e;

	if (IsEmpty()) return NULL;

	node = head;
	head = node->next;

	e = node->value;
	delete node;

	return e;
}

Enemy* Stack::Last() {
	Enemy* e;

	if (IsEmpty()) return NULL;

	e = head->value;

	return e;
}

bool Stack::IsEmpty() {
	return head == NULL;
}

void Stack::Update() {
	pnode node = head;
	while (node) {
		node->value->update();
		node = node->next;
	}
}

void Stack::Draw(sf::RenderWindow* wnd) {
	pnode node = head;
	while (node) {
		node->value->draw(wnd);
		node = node->next;
	}
}