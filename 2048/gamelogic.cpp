#include "gamelogic.h"

void moveLeft(int** table, int nRow, int nCol, unsigned int& score, bool& changed) {		// Hàm thực hiện dồn bảng sang trái, đồng thời trả về số điểm thu được và cho biết công việc dồn có được thực hiện hay không
	// Part 1: Tính tổng 2 phần tử và gộp lại
	for (int row = 0; row < nRow; row++) {
		int i = 0;												// chỉ số của mảng
		bool added = true;										// cho biết phép cộng gộp đã được thực hiện chưa
		int tmp, index;
		while (i < nCol) {
			while (table[row][i] == 0) ++i;						// bỏ qua phần tử 0
			if (added) {										// nếu phép cộng gộp đã được thực hiện rồi
				tmp = table[row][i];							// lưu giá trị số hạng đầu tiên của phép cộng gộp
				index = i;										// lưu chỉ số của số hạng đầu tiên của phép cộng gộp
				added = false;									// đánh dấu là chưa thực hiện phép cộng gộp
				++i;
				continue;										// duyệt phần tử tiếp theo của mảng
			}
			if (table[row][i] == tmp && i < nCol) {				// nếu phần tử bằng với số hạng đầu tiên của phép cộng gộp
				table[row][index] *= 2;							// tăng giá trị của số hạng đầu tiên lên gấp đôi
				score += table[row][index];						// cập nhật điểm số
				table[row][i] = 0;								// vì gộp 2 số lại nên số hạng thứ 2 lúc này bằng 0
				added = true;									// đánh dấu là đã thực hiện phép cộng gộp
				changed = true;									// đánh dấu là ma trận đã có sự thay đổi
			}
			else {												// nếu phần tử khác với số hạng đầu tiên của phép cộng gộp
				tmp = table[row][i];							// thực hiện giống như khi phép cộng đã được thực hiện rồi
				index = i;
				added = false;
			}
			++i;
		}
		// Part 2: Dồn các phần tử khác 0 về một phía (trái)
		int j = 0;												// chỉ số của mảng
		bool moved = true;										// cho biết phép di chuyển đã thực hiện chưa
		int zero;
		while (j < nCol) {
			if (table[row][j] == 0) {
				zero = j;										// lưu chỉ số của phần tử 0 đầu tiên
				moved = false;									// đánh dấu phép di chuyển chưa được thực hiện
				while (j < nCol && table[row][j] == 0) ++j;		// tìm đến phần tử khác 0 đầu tiên
			}
			if (j < nCol && !moved) {							// nếu phép di chuyển chưa được thực hiện
				table[row][zero] = table[row][j];				// thực hiện di chuyển
				table[row][j] = 0;
				moved = true;									// đánh dấu phép di chuyển đã được thực hiện
				changed = true;									// đánh dấu là ma trận đã có sự thay đổi
				j = zero;										// quay lại phần tử 0 đầu tiên để tiếp tục dồn số
			}
			++j;
		}
	}
}

void moveRight(int** table, int nRow, int nCol, unsigned int& score, bool& changed) {

	for (int row = 0; row < nRow; row++) {
		int i = nCol - 1;
		bool added = true;
		int tmp, index;
		while (i >= 0) {
			while (table[row][i] == 0) --i;
			if (added) {
				tmp = table[row][i];
				index = i;
				added = false;
				--i;
				continue;
			}
			if (table[row][i] == tmp && i >= 0) {
				table[row][index] *= 2;
				score += table[row][index];
				table[row][i] = 0;
				added = true;
				changed = true;
			}
			else if (i >= 0) {
				tmp = table[row][i];
				index = i;
				added = false;
			}
			--i;
		}

		int j = nCol - 1;
		bool moved = true;
		int zero;
		while (j >= 0) {
			if (table[row][j] == 0) {
				zero = j;
				moved = false;
				while (j >= 0 && table[row][j] == 0) --j;
			}
			if (j >= 0 && !moved) {
				table[row][zero] = table[row][j];
				table[row][j] = 0;
				moved = true;
				changed = true;
				j = zero;
			}
			--j;
		}
	}
}

void moveUp(int** table, int nRow, int nCol, unsigned int& score, bool& changed) {

	for (int col = 0; col < nCol; col++) {
		int i = 0;
		bool added = true;
		int tmp, index;
		while (i < nRow) {
			while (i < nRow - 1 && table[i][col] == 0) ++i;
			if (added) {
				tmp = table[i][col];
				index = i;
				added = false;
				++i;
				continue;
			}
			if (table[i][col] == tmp) {
				table[index][col] *= 2;
				score += table[index][col];
				table[i][col] = 0;
				added = true;
				changed = true;
			}
			else {
				tmp = table[i][col];
				index = i;
				added = false;
			}
			++i;
		}

		int j = 0;
		bool moved = true;
		int zero;
		while (j < nRow) {
			if (table[j][col] == 0) {
				zero = j;
				moved = false;
				while (j < nRow && table[j][col] == 0) ++j;
			}
			if (j < nRow && !moved) {
				table[zero][col] = table[j][col];
				table[j][col] = 0;
				moved = true;
				changed = true;
				j = zero;
			}
			++j;
		}
	}
}

void moveDown(int** table, int nRow, int nCol, unsigned int& score, bool& changed) {

	for (int col = 0; col < nCol; col++) {
		int i = nRow - 1;
		bool added = true;
		int tmp, index;
		while (i >= 0) {
			while (i > 0 && table[i][col] == 0) --i;
			if (added) {
				tmp = table[i][col];
				index = i;
				added = false;
				--i;
				continue;
			}
			if (table[i][col] == tmp) {
				table[index][col] *= 2;
				score += table[index][col];
				table[i][col] = 0;
				added = true;
				changed = true;
			}
			else {
				tmp = table[i][col];
				index = i;
				added = false;
			}
			--i;
		}

		int j = nRow - 1;
		bool moved = true;
		int zero;
		while (j >= 0) {
			if (table[j][col] == 0) {
				zero = j;
				moved = false;
				while (j >= 0 && table[j][col] == 0) --j;
			}
			if (j >= 0 && !moved) {
				table[zero][col] = table[j][col];
				table[j][col] = 0;
				moved = true;
				changed = true;
				j = zero;
			}
			--j;
		}
	}
}

void randomCell(int** a, int nRow, int nCol) {
	myVector empty;
	initVector(empty);

	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nCol; j++) {
			if (a[i][j] == 0) {
				v_push(empty, i, j);
			}
		}
	}

	int index = rand() % empty.size;
	int value = 2 + (2 * (rand() % 2));
	a[v_ix(empty, index)][v_iy(empty, index)] = value;

	deleteVector(empty);
}

void prepare(int xo, int yo, int nRow, int nCol, int width, int height, int** table) {
	randomCell(table, nRow, nCol);
	randomCell(table, nRow, nCol);
	printFrame(xo, yo, nRow, nCol, width, height);
	printNumber(xo, yo, nRow, nCol, width, height, table);
}

void printFrame(int xo, int yo, int row, int col, int width, int height) {
	int line = 0;
	for (int i = 0; i < height * row - (row - 1); i++) {
		gotoxy(xo, yo + line++);
		for (int j = 0; j < width * col - (col - 1); j++) {
			if (i % (height - 1) == 0) {
				if (i == 0) {
					if (j == 0) cout << (char)201;
					else if (j == width * col - col) cout << (char)187;
					else if (j % (width - 1) == 0) cout << (char)209;
					else cout << (char)205;
				}
				else if (i == height * row - row) {
					if (j == 0) cout << (char)200;
					else if (j == width * col - col) cout << (char)188;
					else if (j % (width - 1) == 0) cout << (char)207;
					else cout << (char)205;
				}
				else {
					if (j == 0) cout << (char)199;
					else if (j == width * col - col) cout << (char)182;
					else if (j % (width - 1) == 0) cout << (char)197;
					else cout << (char)196;
				}
			}
			else {
				if (j == 0 || j == width * col - col) cout << (char)186;
				else if (j % (width - 1) == 0) cout << (char)179;
				else cout << " ";
			}
		}
	}
}

void printNumber(int xo, int yo, int row, int col, int width, int height, int** t) {

	int color_code[] = { 15, 144, 224, 96, 192, 208, 64 };

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (t[i][j] == 0) SetColor3(color_code[0]);
			else {
				int k = 1;
				while (true) {
					if (pow(2, k) == t[i][j]) {
						SetColor3(color_code[(k % 6) + 1]);
						break;
					}
					++k;
				}
			}
			for (int k = 1; k <= height - 2; k++) {
				gotoxy(xo + j * (width - 1) + 1, yo + i * (height - 1) + k);
				for (int i = 0; i < width - 2; i++) cout << " ";
			}
			if (t[i][j] != 0) {
				gotoxy(xo + j * (width - 1) + (width - (int)(to_string(t[i][j])).size()) / 2, yo + i * (height - 1) + (height / 2));
				cout << t[i][j];

			}
		}
	}
}

bool isFull(int** table, int nRow, int nCol) {
	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nCol; j++) {
			if (table[i][j] == 0) {
				return 0;
			}
		}
	}
	return 1;
}

bool isBlocked(int** table, int nRow, int nCol) {
	int x[4] = { 0, -1, 1, 0 };
	int y[4] = { -1, 0, 0, 1 };

	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nCol; j++) {
			for (int k = 0; k < 4; k++) {
				int i1 = i + x[k], j1 = j + y[k];
				if (i1 >= 0 && i1 < nRow && j1 >= 0 && j1 < nCol && table[i][j] == table[i1][j1]) {
					return 0;
				}
			}
		}
	}

	return 1;
}

bool isWin(int** table, int nRow, int nCol) {
	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nCol; j++) {
			if (table[i][j] == 2048) {
				return true;
			}
		}
	}
	return false;
}

bool isLose(int** table, int nRow, int nCol) {
	return isFull(table, nRow, nCol) && isBlocked(table, nRow, nCol);
}