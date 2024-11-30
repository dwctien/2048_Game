#include "myvector.h"

VectorNode* makeVectorNode(int x, int y) {
	VectorNode* newNode = new VectorNode;
	newNode->x = x;
	newNode->y = y;
	newNode->next = NULL;
	return newNode;
}

void initVector(myVector& v) {
	v.head = NULL;
	v.size = 0;
}

void v_push(myVector& v, int x, int y) {
	VectorNode* newNode = makeVectorNode(x, y);
	if (v.head == NULL) {
		v.head = newNode;
		++v.size;
		return;
	}
	VectorNode* cur = v.head;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = newNode;
	++v.size;
}

int v_ix(myVector& v, int index) {
	int pos = 0;
	VectorNode* cur = v.head;
	while (pos < index) {
		++pos;
		cur = cur->next;
	}
	return cur->x;
}

int v_iy(myVector& v, int index) {
	int pos = 0;
	VectorNode* cur = v.head;
	while (pos < index) {
		++pos;
		cur = cur->next;
	}
	return cur->y;
}

void deleteVector(myVector& v) {
	while (v.head != NULL) {
		VectorNode* del = v.head;
		v.head = v.head->next;
		delete del;
	}
}