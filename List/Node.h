#pragma once
#define NULL nullptr

class Node
{
public:
	Node(int v, Node* next = NULL);
	~Node();

private:
	int value;
	Node* next;

	friend class List;
};
typedef Node *pnode;
