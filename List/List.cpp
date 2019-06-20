#include "List.h"



List::List()
{
	first = current = NULL;
}


List::~List()
{
}

void List::Next() {
	if (current) {
		current = current->next;
	}
}

void List::First() {
	current = first;
}

void List::Last() {
	current = first;
	if (!IsEmpty()) {
		while (current->next) {
			Next();
		}
	}

}

bool List::IsEmpty() {
	return first == NULL;
}

void List::Insert(int v) {
	pnode previous;

	if (IsEmpty() || first->value > v) {
		first = new Node(v, first);
	}
	else {
		previous = first;

		while (previous->next && previous->next->value <= v) {
			previous = previous->next;
		}

		previous->next = new Node(v, previous->next);
	}
}

void List::Delete(int v) {
	pnode previous, node;

	node = first;
	previous = NULL;

	while (node && node->value < v) {
		previous = node;
		node = node->next;
	}

	if (!node || node->value != v) {
		return;
	}
	else { // delete node
		if (!previous) { // first element
			first = node->next;
		}
		else { // other
			previous->next = node->next;
		}
	}
}