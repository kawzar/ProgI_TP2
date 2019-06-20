#include "Node.h"



Node::Node(int v, Node* n = NULL)
{
	value = v;
	next = n;
}


Node::~Node()
{
}
