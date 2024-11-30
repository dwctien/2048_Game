#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

#include "system.h"
#include "myvector.h"

// di chuyển và hợp nhất sang trái
void moveLeft(int** table, int nRow, int nCol, unsigned int& score, bool& changed);

// di chuyển và hợp nhất sang phải
void moveRight(int** table, int nRow, int nCol, unsigned int& score, bool& changed);

// di chuyển và hợp nhất lên trên
void moveUp(int** table, int nRow, int nCol, unsigned int& score, bool& changed);

// di chuyển và hợp nhất xuống dưới
void moveDown(int** table, int nRow, int nCol, unsigned int& score, bool& changed);

// tạo một ô ngẫu nhiên có giá trị 2 hoặc 4
void randomCell(int** a, int nRow, int nCol);

// chuẩn bị trước khi bắt đầu chơi game mới
void prepare(int xo, int yo, int nRow, int nCol, int width, int height, int** table);

// in khung kích thước row x col
void printFrame(int xo, int yo, int row, int col, int width, int height);

// in số trong table
void printNumber(int xo, int yo, int row, int col, int width, int height, int** t);

// kiểm tra table đã full chưa
bool isFull(int** table, int nRow, int nCol);

// kiểm tra table không còn tạo được nước đi
bool isBlocked(int** table, int nRow, int nCol);

// kiểm tra người chơi thắng (đạt 2048)
bool isWin(int** table, int nRow, int nCol);

// kiểm tra người chơi thua (không còn tạo được nước đi hợp lệ)
bool isLose(int** table, int nRow, int nCol);

#endif // !_GAMELOGIC_H_