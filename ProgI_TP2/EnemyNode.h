#pragma once
#define NULL nullptr
#include "Enemy.h"

class EnemyNode
{
public:
	EnemyNode(Enemy* v, EnemyNode* n = NULL);
	~EnemyNode();

private:
	Enemy* value;
	EnemyNode* next;

	friend class Stack;
	friend class Queue;
};
typedef EnemyNode *pnode;
