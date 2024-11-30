#include "mystack.h"

int getExponent(int value) {
	return (int)log2(value);
}

Node* makeNodeInt(int** table, int row, int col, unsigned int score) {
	Node* newNode = new Node;

	char** matrix = new char* [row];
	for (int i = 0; i < row; i++) {
		matrix[i] = new char[col];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (table[i][j] == 0) matrix[i][j] = (char)0;
			else matrix[i][j] = (char)getExponent(table[i][j]);
		}
	}

	newNode->matrix = matrix;
	newNode->row = row;
	newNode->col = col;
	newNode->score = score;
	newNode->next = NULL;
	return newNode;
}

Node* makeNodeChar(char** table, int row, int col, unsigned int score) {
	Node* newNode = new Node;

	char** matrix = new char* [row];
	for (int i = 0; i < row; i++) {
		matrix[i] = new char[col];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix[i][j] = table[i][j];
		}
	}

	newNode->matrix = matrix;
	newNode->row = row;
	newNode->col = col;
	newNode->score = score;
	newNode->next = NULL;
	return newNode;
}

void deleteNode(Node& node) {
	for (int i = 0; i < node.row; i++) {
		delete[] node.matrix[i];
	}
	delete[] node.matrix;
}

void myStack::init() {
	head = NULL;
	size = 0;
}

void myStack::pushInt(int** matrix, int row, int col, int score) {
	Node* newNode = makeNodeInt(matrix, row, col, score);
	if (head == NULL) {
		head = newNode;
		++size;
		return;
	}
	newNode->next = head;
	head = newNode;
	++size;
}

void myStack::pushChar(char** matrix, int row, int col, unsigned int score) {
	Node* newNode = makeNodeChar(matrix, row, col, score);
	if (head == NULL) {
		head = newNode;
		++size;
		return;
	}
	newNode->next = head;
	head = newNode;
	++size;
}

void myStack::pop() {
	if (head == NULL) {
		return;
	}
	Node* del = head;
	head = head->next;
	deleteNode(*del);
	delete del;
	--size;
}

void myStack::top(int** table, int row, int col, unsigned int& score) {
	if (head == NULL) return;
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if ((int)head->matrix[i][j] == 0) table[i][j] = 0;
			else table[i][j] = pow(2, (int)head->matrix[i][j]);
		}
	}

	score = head->score;
}

void myStack::deleteStack() {
	while (head != NULL) {
		Node* del = head;
		head = head->next;
		deleteNode(*del);
		delete del;
	}
	size = 0;
}