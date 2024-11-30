#include "screen_menu.h"

void chooseMenu(int n, int x, int y, int w, int h, int text_color, int back_color, bool& resume, string text[], Screen& screen) {

	// di chuyển lên xuống trong menu
	int x_bar = x, y_bar = y + 1;				// tọa độ của ô chữ trong menu
	int x_prev = x_bar, y_prev = y_bar;
	string text_prev = text[0];
	int text_idx = 0, idx_prev = 0;
	bool check = true;					// kiểm tra con trỏ hiện tại đang ở vị trí của ô chữ
	while (true) {
		if (check) {
			// xóa highlight của ô chữ vừa đi qua
			gotoxy(x_prev, y_prev);
			createHighlightBar(x_prev, y_prev, w, h, 14, text[idx_prev]);
			x_prev = x_bar, y_prev = y_bar;

			// highlight ô chữ vừa nhảy đến
			createHighlightBar(x_bar, y_bar, w, h, 224, text[text_idx]);
			idx_prev = text_idx;
			check = false;
		}

		// kiểm tra sự kiện trên bàn phím
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				check = true;
				char c = _getch();
				if (c == UP) {
					if (y_bar > y + 1) {
						if ((whereY() - y) / 3 == 4 && resume == false) {
							y_bar -= 6;
							text_idx -= 2;
						}
						else {
							y_bar -= 3;
							--text_idx;
						}
					}
					else {
						y_bar = y + (h + 1) * n - 2;
						text_idx = n - 1;
					}

				}
				else if (c == DOWN) {
					if (y_bar <= y + (h + 1) * (n - 1) - 2) {
						if ((whereY() - y) / 3 == 2 && resume == false) {
							y_bar += 6;
							text_idx += 2;
						}
						else {
							y_bar += 3;
							++text_idx;
						}
					}
					else {
						y_bar = y + 1;
						text_idx = 0;
					}
				}
			}
			if (c == NEWLINE) {
				SetColor2(0, 7);
				int pos = (whereY() - y) / 3;
				if (pos == 0) {
					screen = NewGame;
				}
				else if (pos == 1) {
					screen = Setting;
				}
				else if (pos == 2) {
					screen = TopList;
				}
				else if (pos == 3 && resume == true) {
					screen = Resume;
				}
				else if (pos == 4) {
					screen = PVPGame;
				}
				else if (pos == 5) {
					screen = Quit;
				}
				return;
			}
		}
	}
}

void screenMenu(Screen& screen) {
	int x = 31, y = 18, w = 15, h = 2, text_color = 14, back_color = 0;
	int n = 6;
	string text[] = { "NEW GAME", "SETTINGS", "TOP20 LIST", "RESUME", "PVP MODE", "QUIT"};

	bool playgame = false;

	ShowCur(0); // hide the cursor
	SetColor3(14);
	system("cls");

	int w_border = 130, h_border = 42;

	// hiển thị tên trò chơi
	showTitle("title_2048_large.txt", (w_border - 71) / 2, 4);
	createBox(0, 0, w_border, h_border, 14, 0, "");

	string intro1 = "A PROJECT BY 23120173";
	string intro2 = "Programming Techniques | FIT@HCMUS | 2024";
	gotoxy((w_border - intro1.size()) / 2, h_border - 2); cout << intro1;
	gotoxy((w_border - intro2.size()) / 2, h_border - 1); cout << intro2;

	// kiểm tra chức năng có khả dụng không
	bool resume = false;
	for (int i = 0; i < 5; i++) {
		if (isEmptyFile(to_string(i)) == false) {
			resume = true;
		}
	}

	// hiển thị các option trong menu
	for (int i = 0; i < n; i++) {
		createBox((w_border - w) / 2, y + (i * 3), w, h, text_color, back_color, text[i]);
		if (i == 3 && resume == false) {
			createBox((w_border - w) / 2, y + (i * 3), w, h, 8, back_color, text[i]);
		}
	}

	chooseMenu(n, (w_border - w) / 2, y, w, h, text_color, back_color, resume, text, screen);
}
