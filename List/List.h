#pragma once
#include "Node.h"
class List
{
public:
	List();
	~List();

	void Next();
	void First();
	void Last();
	bool IsEmpty();
	void Insert(int v);
	void Delete(int v);
private:
	pnode first;
	pnode current;
};

