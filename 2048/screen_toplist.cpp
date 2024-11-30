#include "screen_toplist.h"

void screenTopList(Screen& screen) {

	ShowCur(0); // hide the cursor
	SetColor3(14);
	system("cls");

	int w_border = 130, h_border = 42;
	createBox(0, 0, w_border, h_border, 14, 0, "");

	showTitle("title_top20list.txt", (w_border - 80) / 2, 4);

	// tạo bảng
	SetColor3(15);
	int xo = (w_border - 75) / 2, yo = 13;
	for (int i = 0; i <= 75; i++) {
		gotoxy(xo + i, yo);			cout << (char)205;
		gotoxy(xo + i, yo + 2);		cout << (char)205;
		gotoxy(xo + i, yo + 23);	cout << (char)205;
	}
	for (int i = 0; i <= 22; i++) {
		gotoxy(xo, yo + i);			cout << (char)186;
		gotoxy(xo + 9, yo + i);		cout << (char)186;
		gotoxy(xo + 36, yo + i);	cout << (char)186;
		gotoxy(xo + 56, yo + i);	cout << (char)186;
		gotoxy(xo + 75, yo + i);	cout << (char)186;
	}
	// bo góc hàng yo
	gotoxy(xo, yo);				cout << (char)201;
	gotoxy(xo + 9, yo);			cout << (char)203;
	gotoxy(xo + 36, yo);		cout << (char)203;
	gotoxy(xo + 56, yo);		cout << (char)203;
	gotoxy(xo + 75, yo);		cout << (char)187;
	// bo góc hàng yo + 2
	gotoxy(xo, yo + 2);			cout << (char)204;
	gotoxy(xo + 9, yo + 2);		cout << (char)206;
	gotoxy(xo + 36, yo + 2);	cout << (char)206;
	gotoxy(xo + 56, yo + 2);	cout << (char)206;
	gotoxy(xo + 75, yo + 2);	cout << (char)185;
	// bo góc hàng yo + 23
	gotoxy(xo, yo + 23);		cout << (char)200;
	gotoxy(xo + 9, yo + 23);	cout << (char)202;
	gotoxy(xo + 36, yo + 23);	cout << (char)202;
	gotoxy(xo + 56, yo + 23);	cout << (char)202;
	gotoxy(xo + 75, yo + 23);	cout << (char)188;
	// đánh số xếp hạng
	for (int i = 1; i <= 20; i++) {
		if (i == 1) SetColor3(12);
		else if (i == 2) SetColor3(11);
		else if (i == 3) SetColor3(6);
		else SetColor3(15);

		if (i < 10) gotoxy(xo + 5, yo + 2 + i);
		else gotoxy(xo + 4, yo + 2 + i); 
		cout << i;
	}
	// đặt tên mỗi cột
	gotoxy(xo + 3, yo + 1);		cout << "RANK";
	gotoxy(xo + 19, yo + 1);	cout << "NAME";
	gotoxy(xo + 44, yo + 1);	cout << "SCORE";
	gotoxy(xo + 64, yo + 1);	cout << "TIME";

	// đọc thông tin của top20 từ file và in ra màn hình
	PlayerList list;
	list.init();
	readPlayerList("topplayers.bin", list);

	int line = 0;
	PlayerNode* cur = list.head;

	int cnt = 1;
	while (cur != NULL) {
		if (cnt == 1) SetColor3(12);
		else if (cnt == 2) SetColor3(11);
		else if (cnt == 3) SetColor3(6);
		else SetColor3(15);
		++cnt;
		gotoxy(xo + 16, yo + 3 + line); cout << cur->player.name;
		gotoxy(xo + 49 - (to_string(cur->player.score)).size(), yo + 3 + line); cout << cur->player.score;

		gotoxy(xo + 63, yo + 3 + line);
		if ((cur->player.time / 60) % 60 < 10) {
			if (cur->player.time == 3600) cout << "60:";
			else cout << "0" << (cur->player.time / 60) % 60 << ":";
		}
		else cout << (cur->player.time / 60) % 60 << ":";

		gotoxy(xo + 66, yo + 3 + line);
		if (cur->player.time % 60 < 10) {
			cout << "0" << cur->player.time % 60;
		}
		else cout << cur->player.time % 60;

		cur = cur->next;
		++line;
	}

	// tạo option trong màn hình TOP-20 LIST
	int w = 12, h = 2;
	int x = (w_border - w) / 2, y = 38;
	string text_newgame[] = { "<< BACK", " NEXT >>" };
	createBox(x, y, w, h, 14, 0, text_newgame[0]);
	
	int x_bar = x, y_bar = y + 1;
	createHighlightBar(x_bar, y_bar, w, h, 224, text_newgame[0]);

	while (true) {
		// kiểm tra sự kiện trên bàn phím
		if (_kbhit()) {
			char c = _getch();
			if (c == '\r') {
				SetColor3(15);
				screen = Menu;
				return;
			}
		}
	}
}