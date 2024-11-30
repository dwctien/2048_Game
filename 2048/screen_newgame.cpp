#include "screen_newgame.h"

void formatName(string& name) {
	while (!name.empty() && name[name.length() - 1] == ' ') {
		name.pop_back();
	}

	while (!name.empty() && name[0] == ' ') {
		name.erase(0, 1);
	}
}

bool isDuplicated(string name, PlayerList& list) {

	// kiểm tra trùng tên trong top-20
	if (list.head == NULL) return false;
	PlayerNode* cur = list.head;
	while (cur != NULL) {
		if (cur->player.name == name) {
			return true;
		}
		cur = cur->next;
	}

	// kiểm tra trùng tên trong resume
	string file_name[] = { "player1.bin", "player2.bin", "player3.bin", "player4.bin", "player5.bin" };

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
		Player player_check;
		ifile.read((char*)(&check), sizeof(int));
		ifile.read((char*)(player_check.name.c_str()), sizeof(string));
		ifile.close();

		if (player_check.name == name) {
			return true;
		}
	}

	return false;
}

string getName(string noti, int x_body, int y_body, PlayerList& list) {
	string player_name = "";

	int count = 0;
	int j = noti.size() + x_body + 2;
	int i = 0;
	
	while (true) {
		char input = _getch();
		if (input == NEWLINE) {

			formatName(player_name);

			if (player_name == "") {
				gotoxy(x_body, y_body + 2);
				string noti1 = "Your name must have at least 1 character.";
				cout << noti1;
				Sleep(500);
				gotoxy(x_body, y_body + 2);
				for (int i = 0; i < noti1.size(); i++) cout << ' ';
				continue;
			}

			else if (isDuplicated(player_name, list)) {
				gotoxy(x_body, y_body + 2);
				string noti2 = "This name has been used.";
				cout << noti2;
				Sleep(500);
				gotoxy(x_body, y_body + 2);
				for (int i = 0; i < noti2.size(); i++) cout << ' ';
				continue;
			}

			gotoxy(x_body, y_body + 2);
			cout << "Confirm your name is: '" << player_name << "'";
			break;
		}
		if (input == 8) {
			if (!player_name.empty()) {
				--count;
				player_name.pop_back();
				gotoxy(j, y_body);
				cout << player_name << ' ';
			}
			else {
				continue;
			}
		}
		else if (input == -32) {
			char c = _getch();
			if (c == LEFT || c == RIGHT || c == UP || c == DOWN) {
				gotoxy(x_body, y_body + 2);
				string noti1 = "Please finish typing your name.";
				cout << noti1;
				Sleep(500);
				gotoxy(x_body, y_body + 2);
				for (int i = 0; i < noti1.size(); i++) cout << ' ';
				continue;
			}
		}
		else if (count == 15) {
			gotoxy(x_body, y_body + 2);
			string noti1 = "Your name cannot exceed 15 characters.";
			cout << noti1;
			Sleep(500);
			gotoxy(x_body, y_body + 2);
			for (int i = 0; i < noti1.size(); i++) cout << ' ';
			continue;
		}
		else if (!isalpha(input) && !isdigit(input)) {
			
			string noti1 = "Please enter a name using only ";
			string noti2 = "alphabetic characters and numbers.";
			gotoxy(x_body, y_body + 2);  cout << noti1;
			gotoxy(x_body, y_body + 3);  cout << noti2;
			Sleep(500);
			gotoxy(x_body, y_body + 2);
			for (int i = 0; i < noti1.size(); i++) cout << ' ';
			gotoxy(x_body, y_body + 3);
			for (int i = 0; i < noti2.size(); i++) cout << ' ';
			continue;
		}
		else {
			++count;
			player_name += input;
			gotoxy(j, y_body);
			cout << player_name;
		}
		gotoxy(j + player_name.size(), y_body);
	}
	return player_name;
}

string getNamePVP(string noti, int x_body, int y_body, string other_name) {
	string player_name = "";

	int count = 0;
	int j = noti.size() + x_body + 2;
	int i = 0;

	while (true) {
		char input = _getch();
		if (input == NEWLINE) {

			formatName(player_name);

			if (player_name == "") {
				gotoxy(x_body, y_body + 2);
				string noti1 = "Your name must have at least 1 character.";
				cout << noti1;
				Sleep(500);
				gotoxy(x_body, y_body + 2);
				for (int i = 0; i < noti1.size(); i++) cout << ' ';
				continue;
			}

			else if (player_name == other_name) {
				gotoxy(x_body, y_body + 2);
				string noti2 = "The name of Player A and B must be different!";
				cout << noti2;
				Sleep(500);
				gotoxy(x_body, y_body + 2);
				for (int i = 0; i < noti2.size(); i++) cout << ' ';
				continue;
			}

			gotoxy(x_body, y_body + 2);
			cout << "Confirm the name is: '" << player_name << "'";
			break;
		}
		if (input == 8) {
			if (!player_name.empty()) {
				--count;
				player_name.pop_back();
				gotoxy(j, y_body);
				cout << player_name << ' ';
			}
			else {
				continue;
			}
		}
		else if (input == -32) {
			char c = _getch();
			if (c == 72 || c == 80 || c == 75 || c == 77) {
				gotoxy(x_body, y_body + 2);
				string noti1 = "Please finish typing your name.";
				cout << noti1;
				Sleep(500);
				gotoxy(x_body, y_body + 2);
				for (int i = 0; i < noti1.size(); i++) cout << ' ';
				continue;
			}
		}
		else if (count == 15) {
			gotoxy(x_body, y_body + 2);
			string noti1 = "Your name cannot exceed 15 characters.";
			cout << noti1;
			Sleep(500);
			gotoxy(x_body, y_body + 2);
			for (int i = 0; i < noti1.size(); i++) cout << ' ';
			continue;
		}
		else {
			++count;
			player_name += input;
			gotoxy(j, y_body);
			cout << player_name;
		}
		gotoxy(j + player_name.size(), y_body);
	}
	return player_name;
}

void chooseNewgameMenu(int x, int y, int w, int h, string text_newgame[], string& player1_name, string& player2_name, bool& newgame, Screen& screen) {

	SetColor3(14);
		
	// xử lý di chuyển qua lại trong menu
	int x_bar = x + 20, y_bar = y + 1;				// tọa độ của ô chữ trong menu
	int x_prev = x_bar, y_prev = y_bar;
	string text_prev = text_newgame[1];
	int text_idx = 1, idx_prev = 0;
	bool check = true;

	while (true) {
		if (check) {
			// xóa highlight của ô chữ vừa đi qua
			gotoxy(x_prev, y_prev);
			createHighlightBar(x_prev, y_prev, w, h, 14, text_newgame[idx_prev]);
			x_prev = x_bar, y_prev = y_bar;

			// highlight ô chữ vừa nhảy đến
			createHighlightBar(x_bar, y_bar, w, h, 224, text_newgame[text_idx]);
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
			}
			if (c == NEWLINE) {
				if (x_bar == x) {
					player1_name = "";
					player2_name = "";
					screen = Menu;
					SetColor3(15);
					return;
				}
				else {
					newgame = true;
					screen = PlayGame;
					SetColor3(15);
					return;
				}
			}
		}
	}
}

void chooseTime(int x, int y, int& time_battle) {
	SetColor3(14);
	gotoxy(72, 27); cout << "TIME DURATION";

	// tạo option
	int w = 11, h = 2;
	string text_time[] = { "30s", "60s", "120s"};

	// xử lý di chuyển qua lại trong menu
	int x_bar = x, y_bar = y + 1;				// tọa độ của ô chữ trong menu
	int x_prev = x_bar, y_prev = y_bar;
	string text_prev = text_time[0];
	int text_idx = 0, idx_prev = 0;
	bool check = true;

	createHighlightBar(x_bar, y_bar, w, h, 14, text_time[0]);
	createHighlightBar(x_bar + 14, y_bar, w, h, 14, text_time[1]);
	createHighlightBar(x_bar + 28, y_bar, w, h, 14, text_time[2]);


	while (true) {
		if (check) {
			// xóa highlight của ô chữ vừa đi qua
			gotoxy(x_prev, y_prev);
			createHighlightBar(x_prev, y_prev, w, h, 14, text_time[idx_prev]);
			x_prev = x_bar, y_prev = y_bar;

			// highlight ô chữ vừa nhảy đến
			createHighlightBar(x_bar, y_bar, w, h, 224, text_time[text_idx]);
			idx_prev = text_idx;
			check = false;
		}

		// kiểm tra sự kiện trên bàn phím
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				check = true;
				char c = _getch();
				if (c == 75) {
					if (x_bar >= x + 1) {
						x_bar -= 14;
						--text_idx;
					}

				}
				else if (c == 77) {
					if (x_bar < x + 20) {
						x_bar += 14;
						++text_idx;
					}
				}
			}
			if (c == NEWLINE) {
				int pos = (whereX() - x) / 13;
				if (pos == 0) {
					time_battle = 30;
				}
				else if (pos == 1) {
					time_battle = 60;
				}
				else if (pos == 3) {
					time_battle = 120;
				}
				return;
			}
		}
	}

}

void screenNewGame(Screen& screen, bool& newgame, string& player_name) {

	ShowCur(0); // hide the cursor
	SetColor3(15);
	system("cls");

	int w_border = 130, h_border = 42;
	createBox(0, 0, w_border, h_border, 14, 0, "");

	showTitle("title_newgame.txt", (w_border - 68) / 2, 4);

	int x_body = (w_border - 40) / 2, y_body = 17;

	// tạo option trong màn hình NEW GAME
	int x = x_body, y = y_body + 8, w = 12, h = 2;
	string text_newgame[] = { "<< BACK", " NEXT >>" };
	createBox(x, y, w, h, 14, 0, text_newgame[0]);
	createBox(x + 20, y, w, h, 14, 0, text_newgame[1]);

	gotoxy(x_body, y_body);
	string noti = "Type your name: "; cout << noti;

	gotoxy(x_body + noti.size() + 1, y_body - 1);		cout << (char)201 << (char)205;
	gotoxy(x_body + noti.size() + 1, y_body + 1);		cout << (char)200 << (char)205;
	gotoxy(x_body + noti.size() + 16, y_body - 1);		cout << (char)205 << (char)187;
	gotoxy(x_body + noti.size() + 16, y_body + 1);		cout << (char)205 << (char)188;
	gotoxy(x_body + noti.size() + 2, y_body);
	for (int i = 0; i < 15; i++) cout << ' ';

	// tạo danh sách lưu thông tin top-20 --> để kiểm tra trùng tên
	PlayerList list;
	list.init();
	readPlayerList("topplayers.bin", list);

	player_name = getName(noti, x_body, y_body, list);
	string player2_name = "";

	list.deleteList();

	chooseNewgameMenu(x, y, w, h, text_newgame, player_name, player2_name, newgame, screen);
}

void screenNewGamePVP(Screen& screen, string& player1_name, string& player2_name, int& time_battle) {
	ShowCur(0); // hide the cursor
	SetColor3(15);
	system("cls");

	int w_border = 130, h_border = 42;
	createBox(0, 0, w_border, h_border, 14, 0, "");
	showTitle("title_pvpgame.txt", (w_border - 68) / 2, 4);

	createBox(15, 15, 43, 18, 14, 0, "");
	gotoxy(18, 15); cout << " RULE ";                                      
	gotoxy(17, 18); cout << "In this PvP mode, two players compete";
	gotoxy(17, 19); cout << "on  their  own  4x4  tables  within  a";
	gotoxy(17, 20); cout << "specific time frame.";
	gotoxy(17, 22); cout << "After this time, the player with the ";
	gotoxy(17, 23); cout << "higher score wins. ";
	gotoxy(17, 25); cout << "Watch out! If a player cannot make a ";
	gotoxy(17, 26); cout << "valid move, they lose immediately.";
	gotoxy(17, 28); cout << "No undo, redo, save game, or pause game.";
	gotoxy(17, 30); cout << "ENJOY THE GAME ^^";

	int x_body = 72;
	bool newgame = true;

	// tạo option trong màn hình NEW GAME
	int x = x_body, y = 31, w = 12, h = 2;
	string text_newgame[] = { "<< BACK", " NEXT >>" };
	createBox(x, y, w, h, 14, 0, text_newgame[0]);
	createBox(x + 20, y, w, h, 14, 0, text_newgame[1]);
	
	// Nhập tên người chơi 1
	int y1_body = 15;
	gotoxy(x_body, y1_body);
	SetColor3(3);
	string noti1 = "NAME OF PLAYER A: "; cout << noti1;

	gotoxy(x_body + noti1.size() + 1, y1_body - 1);		cout << (char)201 << (char)205;
	gotoxy(x_body + noti1.size() + 1, y1_body + 1);		cout << (char)200 << (char)205;
	gotoxy(x_body + noti1.size() + 16, y1_body - 1);	cout << (char)205 << (char)187;
	gotoxy(x_body + noti1.size() + 16, y1_body + 1);	cout << (char)205 << (char)188;
	gotoxy(x_body + noti1.size() + 2, y1_body);
	for (int i = 0; i < 15; i++) cout << ' ';

	player1_name = getNamePVP(noti1, x_body, y1_body, "");

	// Nhập tên người chơi 2
	int y2_body = 21;
	gotoxy(x_body, y2_body);
	SetColor3(12);
	string noti2 = "NAME OF PLAYER B: "; cout << noti2;

	gotoxy(x_body + noti2.size() + 1, y2_body - 1);		cout << (char)201 << (char)205;
	gotoxy(x_body + noti2.size() + 1, y2_body + 1);		cout << (char)200 << (char)205;
	gotoxy(x_body + noti2.size() + 16, y2_body - 1);	cout << (char)205 << (char)187;
	gotoxy(x_body + noti2.size() + 16, y2_body + 1);	cout << (char)205 << (char)188;
	gotoxy(x_body + noti2.size() + 2, y2_body);
	for (int i = 0; i < 15; i++) cout << ' ';

	player2_name = getNamePVP(noti1, x_body, y2_body, player1_name);

	chooseTime(71, 27, time_battle);

	chooseNewgameMenu(x, y, w, h, text_newgame, player1_name, player2_name, newgame, screen);
}