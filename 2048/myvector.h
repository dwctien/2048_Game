#ifndef _MYVECTOR_H_
#define _MYVECTOR_H_

#include "system.h"

struct VectorNode {							// mỗi phần tử (node) của vector gồm một cặp số (x,y)
	int x, y;
	VectorNode* next;
};

VectorNode* makeVectorNode(int x, int y);

struct myVector {
	int size;
	VectorNode* head;
};

void initVector(myVector& v);				// khởi tạo vector rỗng

void v_push(myVector& v, int x, int y);		// thêm phần tử mới vào vector

int v_ix(myVector& v, int index);			// lấy ra thành phần thứ nhất của phần tử có chỉ số index trong vector 

int v_iy(myVector& v, int index);			// lấy ra thành phần thứ hai của phần tử có chỉ số index trong vector 

void deleteVector(myVector& v);				// giải phóng vùng nhớ của từng phần tử trong vector

#endif // !_MYVECTOR_H_