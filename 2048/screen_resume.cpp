#include "screen_resume.h"

void showResumeFile(int x, int y) {

	string file_name[] = { "player1.bin", "player2.bin", "player3.bin", "player4.bin", "player5.bin" };

	Player player;

	for (int i = 0; i < 5; i++) {
		ifstream ifile;
		ifile.open(file_name[i], ios::binary);

		if (!ifile.is_open()) {
			ofstream ofile;
			ofile.open(file_name[i], ios::binary);
			int empty = 0;
			ofile.write((char*)(&empty), sizeof(int));
			ofile.close();
			continue;
		}

		int check;
		ifile.read((char*)(&check), sizeof(int));
		if (check == 1) {
			ifile.read((char*)(player.name.c_str()), sizeof(string));
			gotoxy(x, y + i * 2);
			cout << player.name;
		}

		ifile.close();
	}
	return;
}

void showResumeFile2(int x, int y) {

	// tạo bảng
	SetColor3(15);
	int xo = x - 5, yo = y - 3;
	for (int i = 0; i <= 52; i++) {
		gotoxy(xo + i, yo);	 		cout << (char)205;
		gotoxy(xo + i, yo + 2);		cout << (char)205;
		gotoxy(xo + i, yo + 12);	cout << (char)205;
	}
	for (int i = 0; i <= 12; i++) {
		gotoxy(xo, yo + i);			cout << (char)186;
		gotoxy(xo + 23, yo + i);	cout << (char)186;
		gotoxy(xo + 38, yo + i);	cout << (char)186;
		gotoxy(xo + 52, yo + i);	cout << (char)186;
	}
	// bo góc hàng yo
	gotoxy(xo, yo);				cout << (char)201;
	gotoxy(xo + 23, yo);		cout << (char)203;
	gotoxy(xo + 38, yo);		cout << (char)203;
	gotoxy(xo + 52, yo);		cout << (char)187;
	// bo góc hàng yo + 2
	gotoxy(xo, yo + 2);			cout << (char)204;
	gotoxy(xo + 23, yo + 2);	cout << (char)206;
	gotoxy(xo + 38, yo + 2);	cout << (char)206;
	gotoxy(xo + 52, yo + 2);	cout << (char)185;
	// bo góc hàng yo + 23
	gotoxy(xo, yo + 12);		cout << (char)200;
	gotoxy(xo + 23, yo + 12);	cout << (char)202;
	gotoxy(xo + 38, yo + 12);	cout << (char)202;
	gotoxy(xo + 52, yo + 12);	cout << (char)188;

	// đặt tên cột
	gotoxy(xo + 10, yo + 1);	cout << "NAME";
	gotoxy(xo + 28, yo + 1);	cout << "SCORE";
	gotoxy(xo + 43, yo + 1);	cout << "TIME";

	// in thông tin 5 file resume
	string file_name[] = { "player1.bin", "player2.bin", "player3.bin", "player4.bin", "player5.bin" };

	Player player;

	for (int i = 0; i < 5; i++) {
		ifstream ifile;
		ifile.open(file_name[i], ios::binary);

		if (!ifile.is_open()) {
			ofstream ofile;
			ofile.open(file_name[i], ios::binary);
			int empty = 0;
			ofile.write((char*)(&empty), sizeof(int));
			ofile.close();

			SetColor3(14);
			gotoxy(x, y + i * 2);
			cout << "< EMPTY >";
			SetColor(15);

			continue;
		}

		int check;
		ifile.read((char*)(&check), sizeof(int));
		if (check == 1) {
			ifile.read((char*)(player.name.c_str()), sizeof(string));							// đọc tên người chơi
			ifile.read((char*)(&player.score), sizeof(unsigned int));							// đọc điểm người chơi
			ifile.read((char*)(&player.time), sizeof(unsigned int));							// đọc thời gian chơi
			
			gotoxy(x, y + i * 2);
			cout << player.name;

			gotoxy(x + 28 - to_string(player.score).size(), y + i * 2);
			cout << player.score;

			gotoxy(x + 38, y + i * 2);
			if ((player.time / 60) % 60 < 10) {
				if (player.time == 3600) cout << "60:";
				else cout << "0" << (player.time / 60) % 60 << ":";
			}
			else cout << (player.time / 60) % 60 << ":";

			gotoxy(x + 41, y + i * 2);
			if (player.time % 60 < 10) {
				cout << "0" << player.time % 60;
			}
			else cout << player.time % 60;
		}

		else if (check == 0) {
			SetColor3(14);
			gotoxy(x, y + i * 2);
			cout << "< EMPTY >";
			SetColor(15);
		}

		ifile.close();
	}
	return;
}

void clearResumeFile(int x, int y) {
	SetColor3(15);
	int xo = x - 5, yo = y - 3;
	for (int i = 0; i < 20; i++) {
		gotoxy(xo + i, yo + 3);		cout << " ";
		gotoxy(xo + i, yo + 5);		cout << " ";
		gotoxy(xo + i, yo + 7);		cout << " ";
		gotoxy(xo + i, yo + 11);	cout << " ";
		gotoxy(xo + i, yo + 13);	cout << " ";
	}
	for (int i = 0; i < 12; i++) {
		gotoxy(xo + 25 + i, yo + 3);	cout << " ";
		gotoxy(xo + 25 + i, yo + 5);	cout << " ";
		gotoxy(xo + 25 + i, yo + 7);	cout << " ";
		gotoxy(xo + 25 + i, yo + 11);	cout << " ";
		gotoxy(xo + 25 + i, yo + 13);	cout << " ";
	}
	for (int i = 0; i < 12; i++) {
		gotoxy(xo + 38 + i, yo + 3);	cout << " ";
		gotoxy(xo + 38 + i, yo + 5);	cout << " ";
		gotoxy(xo + 38 + i, yo + 7);	cout << " ";
		gotoxy(xo + 38 + i, yo + 11);	cout << " ";
		gotoxy(xo + 38 + i, yo + 13);	cout << " ";
	}
}

void chooseResumeFile(int x, int y, bool& bottom, string& player_name) {

	int x_arrow = x - 3, y_arrow = y;
	int x_prev = x_arrow, y_prev = y_arrow;
	bool check = true;
	
	if (bottom == true) {
		for (int i = 0; i <= 6; i += 2) {
			SetColor3(15);
			gotoxy(x_arrow, y_arrow + i);
			cout << " ";
		}
		y_arrow = y + 8;
		y_prev = y_arrow;
	}

	SetColor3(14);
	while (true) {
		if (check) {
			// xóa mũi tên cũ
			gotoxy(x_prev, y_prev);
			cout << " ";
			x_prev = x_arrow, y_prev = y_arrow;

			// in mũi tên mới
			gotoxy(x_arrow, y_arrow);
			cout << (char)16;
			check = false;
		}

		// kiểm tra sự kiện trên bàn phím
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				check = true;
				char c = _getch();
				if (c == UP) {
					if (y_arrow > y) {
						y_arrow -= 2;
					}
					else {
						y_arrow = y + 8;
					}
				}
				else if (c == DOWN) {
					if (y_arrow < y + 8) {
						y_arrow += 2;
					}
					else {
						y_arrow = y;
					}
				}
			}
			if (c == NEWLINE) {
				int pos = (whereY() - y) / 2;
				player_name = to_string(pos);
				return;
			}
		}
	}

}

void deleteResumeFile(int x, int y, string player_name) {
	SetColor3(10);
	gotoxy(44, 28); cout << "DO YOU ACTUALLY WANT TO DELETE THIS GAME?";
	gotoxy(44, 30); cout << "       [y] YES           [n] NO          ";

	while (true) {
		char c = _getch();
		if (c == 'y') {
			gotoxy(44, 28); cout << "                                           ";
			gotoxy(44, 30); cout << "                                           ";
			
			string file_name[] = { "player1.bin", "player2.bin", "player3.bin", "player4.bin", "player5.bin" };

			ofstream ofile;
			ofile.open(file_name[stoi(player_name)], ios::binary | ios::trunc);

			int empty = 0;
			ofile.write((char*)(&empty), sizeof(int));
			ofile.close();

			clearResumeFile(x, y);
			showResumeFile2(x, y);
			return;
		}
		else if (c == 'n') {
			gotoxy(44, 28); cout << "                                           ";
			gotoxy(44, 30); cout << "                                           ";
			return;
		}
	}
}

bool isEmptyFile(string player_name) {
	string file_name[] = { "player1.bin", "player2.bin", "player3.bin", "player4.bin", "player5.bin" };

	ifstream ifile;
	ifile.open(file_name[stoi(player_name)], ios::binary);

	if (!ifile.is_open()) {
		ofstream ofile;
		ofile.open(file_name[stoi(player_name)], ios::binary);
		int empty = 0;
		ofile.write((char*)(&empty), sizeof(int));
		ofile.close();
		return true;
	}

	int check = -1;
	ifile.read((char*)(&check), sizeof(int));
	ifile.close();
	if (check == 0) return true;

	if (check == 1) return false;
}

void chooseMenuResume(int x, int y, int x1, int y1, int w, int h, bool& bottom, bool& newgame, string& player_name, string text_resume[], Screen& screen) {
	// xử lý di chuyển qua lại trong menu
	int x_bar = x1 + 40, y_bar = y1 + 1;				// tọa độ của ô chữ trong menu
	int x_prev = x_bar, y_prev = y_bar;
	string text_prev = text_resume[0];
	int text_idx = 2, idx_prev = 2;
	bool check = true;

	while (true) {
		if (check) {
			// xóa highlight của ô chữ vừa đi qua
			gotoxy(x_prev, y_prev);
			createHighlightBar(x_prev, y_prev, w, h, 14, text_resume[idx_prev]);
			x_prev = x_bar, y_prev = y_bar;

			// highlight ô chữ vừa nhảy đến
			createHighlightBar(x_bar, y_bar, w, h, 224, text_resume[text_idx]);
			idx_prev = text_idx;
			check = false;
		}

		// kiểm tra sự kiện trên bàn phím
		if (_kbhit()) {
			SetColor3(15);
			gotoxy(47, 28); cout << "                                           ";
			char c = _getch();
			if (c == -32) {
				check = true;
				char c = _getch();
				if (c == LEFT) {
					if (x_bar >= x1 + 1) {
						x_bar -= 20;
						--text_idx;
					}
					else {
						x_bar = x1 + 40;
						text_idx = 2;
					}

				}
				else if (c == RIGHT) {
					if (x_bar < x1 + 40) {
						x_bar += 20;
						++text_idx;
					}
					else {
						x_bar = x1;
						text_idx = 0;
					}
				}
				else if (c == UP) {
					createHighlightBar(x_bar, y1 + 1, w, h, 14, text_resume[idx_prev]);
					bottom = true;
					return;
				}
			}
			if (c == NEWLINE) {
				if (x_bar == x1) {
					screen = Menu;
					SetColor3(15);
					return;
				}
				else if (x_bar == x1 + 20) {
					if (isEmptyFile(player_name)) {
						SetColor3(10);
						gotoxy(52, 28); cout << "CANNOT DELETE THE EMPTY GAME!";
					}
					else {
						deleteResumeFile(x, y, player_name);
					}
					check = true;
				}
				else {
					if (isEmptyFile(player_name)) {
						SetColor3(10);
						gotoxy(52, 28); cout << "CANNOT PLAY THE EMPTY GAME!";
						check = true;
					}
					else {
						SetColor3(10);
						gotoxy(44, 28); cout << "DO YOU ACTUALLY WANT TO PLAY THIS GAME?";
						gotoxy(44, 30); cout << "       [y] YES           [n] NO          ";

						while (true) {
							char key = _getch();
							if (key == 'y') {
								screen = PlayGame;
								newgame = false;
								SetColor3(15);
								return;
							}
							else if (key == 'n') {
								gotoxy(44, 28); cout << "                                           ";
								gotoxy(44, 30); cout << "                                           ";
								break;
							}
						}
						
					}
				}
			}
		}
	}
}

void screenResume(Screen& screen, bool& newgame, string& player_name) {
	system("cls");
	ShowCur(0);

	int w_border = 130, h_border = 42;
	createBox(0, 0, w_border, h_border, 14, 0, "");

	showTitle("title_resume.txt", (w_border - 50) / 2, 4);

	string noti = "Use arrow keys to navigate / Press [Enter] to select";
	gotoxy((w_border - noti.size()) / 2, h_border - 1);
	cout << noti;

	// tạo option trong màn hình SETTING
	int x1 = 39, y1 = 34, w = 12, h = 2;
	string text_resume[] = { "<< BACK", "DELETE"," PLAY >>"};
	createBox(x1, y1, w, h, 14, 0, text_resume[0]);
	createBox(x1 + 20, y1, w, h, 14, 0, text_resume[1]);
	createBox(x1 + 40, y1, w, h, 14, 0, text_resume[2]);

	// hiển thị danh sách người chơi đã lưu lại trò chơi
	int x = 44, y = 16;
	showResumeFile2(x, y);
	
	bool bottom = false;

	while (true) {
		chooseResumeFile(x, y, bottom, player_name);
		chooseMenuResume(x, y, x1, y1, w, h, bottom, newgame, player_name, text_resume, screen);
		if (screen == Menu || screen == PlayGame) {
			break;
		}
	}
}