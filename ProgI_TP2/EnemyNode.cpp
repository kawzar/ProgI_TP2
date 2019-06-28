#include "pch.h"
#include "EnemyNode.h"


EnemyNode::EnemyNode(Enemy* v, EnemyNode* n)
{
	value = v;
	next = n;
}


EnemyNode::~EnemyNode()
{
}
