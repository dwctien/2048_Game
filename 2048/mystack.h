#ifndef _MYSTACK_H_
#define _MYSTACK_H_

#include "system.h"

int getExponent(int value);

struct Node {
	char** matrix;
	int row;
	int col;
	unsigned int score;
	Node* next;
};

Node* makeNodeInt(int** table, int row, int col, unsigned int score);

Node* makeNodeChar(char** table, int row, int col, unsigned int score);

void deleteNode(Node& node);

struct myStack {
	Node* head;
	int size;
	
	void init();															// khởi tạo stack rỗng
	void pushInt(int** matrix, int row, int col, int score);			// thêm ma trận kiểu int** vào stack
	void pushChar(char** matrix, int row, int col, unsigned int score);		// thêm ma trận kiểu chr** vào stack
	void pop();																// xóa phần tử cuối của stack
	void top(int** table, int row, int col, unsigned int& score);			// lấy ra phần tử cuối của stack
	void deleteStack();														// giải phóng vùng nhớ của từng phần tử trong stack
};

#endif // !_MYSTACK_H_
