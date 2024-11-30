#include "screen_setting.h"

void changeSetting(int n, int x, int y, int w, int h, string text[4][7], int& table_size, int& unre, bool& set_default, bool& bottom, int& delay) {
	// di chuyển lên xuống trong setting
	int x_bar = x, y_bar = y;								// tọa độ của ô chữ trong menu
	int x_prev = x_bar, y_prev = y_bar;
	string text_prev = text[0][0];
	int text_i = 0, i_prev = 0, j_prev = 0;
	int text_j[4] = { 0, 0, 0, 0 };
	bool check = true;										// kiểm tra con trỏ hiện tại đang ở vị trí của ô chữ

	if (set_default == true) {
		table_size = 0;
		unre = 0;
		delay = 0;
	}

	text_j[0] = table_size;
	text_j[1] = unre;
	text_j[3] = delay;

	createHighlightBar(x_prev, y_prev, w, h, 14, text[0][text_j[0]]);
	createHighlightBar(x_prev, y_prev + 2, w, h, 14, text[1][text_j[1]]);
	createHighlightBar(x_prev, y_prev + 4, w, h, 14, text[2][0]);
	createHighlightBar(x_prev, y_prev + 6, w, h, 14, text[3][text_j[3]]);

	if (set_default == true) {
		return;
	}

	if (bottom == true) {
		y_bar = y + (n - 1) * 2;
		y_prev = y_bar;
		text_i = 3;
		i_prev = 3;
	}

	while (true) {
		if (check) {
			// xóa highlight của ô chữ vừa đi qua
			SetColor3(14);
			gotoxy(x_prev - 1, y_prev);		cout << " ";
			gotoxy(x_prev + w + 1, y_prev);	cout << " ";
			createHighlightBar(x_prev, y_prev, w, h, 14, text[i_prev][j_prev]);
			x_prev = x_bar;
			y_prev = y_bar;

			// highlight ô chữ vừa nhảy đến
			if ((text_i == 0 && text_j[0] == 0) || (text_i == 1 && text_j[1] == 0) \
				|| (text_i == 2 && text_j[2] == 0) || (text_i == 3 && text_j[3] == 0)) {
				SetColor3(8);
				gotoxy(x_bar - 1, y_bar);
				cout << "<";
			}
			else {
				SetColor3(14);
				gotoxy(x_bar - 1, y_bar);
				cout << "<";
			}

			if ((text_i == 0 && text_j[0] == 6) || (text_i == 1 && text_j[1] == 2) \
				|| (text_i == 2 && text_j[2] == 1) || (text_i == 3 && text_j[3] == 5)) {
				SetColor3(8);
				gotoxy(x_bar + w + 1, y_bar);
				cout << ">";
			}
			else {
				SetColor3(14);
				gotoxy(x_bar + w + 1, y_bar);
				cout << ">";
			}
			
			createHighlightBar(x_bar, y_bar, w, h, 224, text[text_i][text_j[text_i]]);
			i_prev = text_i;
			j_prev = text_j[text_i];
			check = false;
		}

		// kiểm tra sự kiện trên bàn phím
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				check = true;
				char c = _getch();
				if (c == UP && y_bar > y) {
					y_bar -= 2;
					--text_i;
				}
				else if (c == DOWN) {
					if (y_bar < y + h * (n - 1)) {
						y_bar += 2;
						++text_i;
					}
					else {
						SetColor3(14);
						gotoxy(x_prev - 1, y_prev);		cout << " ";
						gotoxy(x_prev + w + 1, y_prev);	cout << " ";
						createHighlightBar(x_prev, y_prev, w, h, 14, text[i_prev][j_prev]);
						return;
					}
				}
				else if (c == LEFT) {
					if (text_j[text_i] > 0) {
						--text_j[text_i];
						if (text_i == 0) table_size = text_j[text_i];
						else if (text_i == 1) unre = text_j[text_i];
						else if (text_i == 3) delay = text_j[text_i];
					}
				}
				else if (c == RIGHT) {
					if (text_i == 0 && text_j[0] < 6) {
						++text_j[text_i];
						table_size = text_j[text_i];
					}
					else if (text_i == 1 && text_j[1] < 2) {
						++text_j[text_i];
						unre = text_j[text_i];
					}
					else if (text_i == 2 && text_j[2] < 1) {
						++text_j[text_i];
					}
					else if (text_i == 3 && text_j[3] < 5) {
						++text_j[text_i];
						delay = text_j[text_i];
					}
				}
			}
		}
	}
}

void exitSetting(int x, int y, int w, int h, string text_setting[], bool& menu, bool& set_default, bool& bottom) {
	// xử lý di chuyển qua lại trong menu
	int x_bar = x, y_bar = y + 1;				// tọa độ của ô chữ trong menu
	int x_prev = x_bar, y_prev = y_bar;
	string text_prev = text_setting[0];
	int text_idx = 0, idx_prev = 0;
	bool check = true;

	if (set_default == true) {
		x_bar = x + 20;
		text_idx = 1;
		set_default = false;
	}

	while (true) {
		if (check) {
			// xóa highlight của ô chữ vừa đi qua
			gotoxy(x_prev, y_prev);
			createHighlightBar(x_prev, y_prev, w, h, 14, text_setting[idx_prev]);
			x_prev = x_bar, y_prev = y_bar;

			// highlight ô chữ vừa nhảy đến
			createHighlightBar(x_bar, y_bar, w, h, 224, text_setting[text_idx]);
			idx_prev = text_idx;
			check = false;
		}

		// kiểm tra sự kiện trên bàn phím
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				check = true;
				char c = _getch();
				if (c == LEFT) {
					if (x_bar >= x + 1) {
						x_bar -= 20;
						--text_idx;
					}
					else {
						x_bar = x + 20;
						text_idx = 1;
					}

				}
				else if (c == RIGHT) {
					if (x_bar < x + 20) {
						x_bar += 20;
						++text_idx;
					}
					else {
						x_bar = x;
						text_idx = 0;
					}
				}
				else if (c == 72) {
					bottom = true;
					createHighlightBar(x_prev, y_prev, w, h, 14, text_setting[idx_prev]);
					return;
				}
			}
			if (c == NEWLINE) {
				if (x_bar == x) {
					menu = true;
					return;
				}
				else {
					set_default = true;
					return;
				}
			}
		}
	}
}

void screenSetting(Screen& screen, int& table_size, int& unre, int& delay) {
	
	ShowCur(0);
	SetColor3(15);
	system("cls");

	int w_border = 130, h_border = 42;
	createBox(0, 0, w_border, h_border, 14, 0, "");

	showTitle("title_setting.txt", (w_border - 55) / 2, 4);

	// tạo các option để người chơi lựa chọn, thay đổi
	int xo = (w_border - 40) / 2, yo = 16, wo = 15, ho = 2;
	gotoxy(xo + 2, yo + 1);		cout << "SIZE OF TABLE :";
	gotoxy(xo + 2, yo + 3);		cout << "UNDO AND REDO :";
	gotoxy(xo + 2, yo + 5);		cout << "        THEME :";
	gotoxy(xo + 2, yo + 7);		cout << " RANDOM DELAY :";

	string text_option[4][7] = {
		{ "4 x 4", "5 x 5", "6 x 6", "7 x 7", "8 x 8", "9 x 9", "10 x 10" },
		{ "None", "Undo only", "Both"},
		{ "Dark", "Light" },
		{ "0 ms", "100 ms", "200 ms", "300 ms", "400 ms", "500 ms"}
	};

	int x = (w_border - 36) / 2, y = 36, w = 14, h = 2;
	string text_setting[] = { "SAVE & BACK", "DEFAULT" };
	createBox(x, y, w, h, 14, 0, text_setting[0]);
	createBox(x + 20, y, w, h, 14, 0, text_setting[1]);
	bool menu = false, set_default = false, bottom = false;

	while (true) {
		changeSetting(4, xo + 20, yo + 1, wo, ho, text_option, table_size, unre, set_default, bottom, delay);
		exitSetting(x, y, w, h, text_setting, menu, set_default, bottom);
		if (menu == true) {
			screen = Menu;
			break;
		}
	}
}