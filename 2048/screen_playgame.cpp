#include "screen_playgame.h"

mutex m; // tạo sự đồng bộ, tránh xung đột giữa các luồng

PlayerNode* makeNode(Player player1) {
	PlayerNode* newnode = new PlayerNode;
	newnode->player = player1;
	newnode->next = NULL;
	return newnode;
}

void PlayerList::init() {
	head = NULL;
	size = 0;
}

void PlayerList::pushFront(Player player1) {
	PlayerNode* newnode = makeNode(player1);
	if (head == NULL) {
		head = newnode;
		++size;
		return;
	}
	newnode->next = head;
	head = newnode;
	++size;
}

void PlayerList::pushBack(Player player1) {
	PlayerNode* newnode = makeNode(player1);
	if (head == NULL) {
		pushFront(player1);
		return;
	}
	PlayerNode* cur = head;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = newnode;
	++size;
}

void PlayerList::popFront() {
	if (head == NULL) return;
	PlayerNode* del = head;
	head = head->next;
	delete del;
	--size;
}

void PlayerList::popBack() {
	if (head == NULL) return;
	if (head->next == NULL) {
		PlayerNode* del = head;
		head = NULL;
		delete del;
		--size;
	}

	PlayerNode* cur = head;
	while (head->next != NULL && cur->next->next != NULL) {
		cur = cur->next;
	}
	PlayerNode* del = cur->next;
	cur->next = del->next;
	delete del;
	--size;
}

void PlayerList::insertPlayer(Player player1) {
	
	if (head == NULL) {
		pushFront(player1);
		return;
	}

	if (head->player.name == player1.name) {
		if (head->player.score < player1.score) {
			head->player.score = player1.score;
			head->player.time = player1.time;
		}
		return;
	}

	// kiểm tra tên trùng trong danh sách (nghĩa là người chơi đang resume), nếu điểm cao hơn thì xóa người chơi cũ trong list
	for (PlayerNode* i = head; i->next != NULL; i = i->next) {
		if (i->next->player.name == player1.name) {
			if (i->next->player.score > player1.score || (i->next->player.score == player1.score && i->next->player.time < player1.time)) {
				return;
			}
			else {
				PlayerNode* del = i->next;
				i->next = del->next;
				delete del;
				--size;
				break;
			}
		}
	}

	// thêm người chơi hiện tại vào list mà không làm mất tính tăng dần theo score
	if (head->player.score < player1.score) {
		pushFront(player1);
	}
	else {
		bool check = true;
		for (PlayerNode* i = head; i->next != NULL; i = i->next) {
			if (i->next->player.score < player1.score || (i->next->player.score == player1.score && i->next->player.time > player1.time)) {
				PlayerNode* newnode = makeNode(player1);
				newnode->next = i->next;
				i->next = newnode;
				++size;
				check = false;
				break;
			}
		}
		if (check) pushBack(player1);
	}

	if (size == 21) popBack();
}

void PlayerList::deleteList() {
	while (head != NULL) {
		PlayerNode* del = head;
		head = head->next;
		delete del;
	}
	size = 0;
}

void myClock(unsigned int& time, bool& pause, bool& out, bool& timeover, Screen& screen) {

	Sleep(4000);

	while (true) {
		if (out == true) {
			return;
		}

		if (pause == false) {
			m.lock();

			if (time >= 3600) {
				timeover = true;
				clearNoti();
				SetColor3(10);
				gotoxy(92, 16);	cout << "You've spent too much time on this";
				gotoxy(92, 17); cout << "game. Let's start a new game!";
				gotoxy(92, 19); cout << "Press [Enter] to return to menu";

				while (true) {
					char c = _getch();
					if (c == NEWLINE) {
						screen = Menu;
						m.unlock();
						return;
					}
				}
			}

			SetColor3(10);
			gotoxy(109, 32);
			if ((time / 60) % 60 < 10) {
				cout << "0" << (time / 60) % 60 << ":";
			}
			else cout << (time / 60) % 60 << ":";

			gotoxy(112, 32);
			if (time % 60 < 10) {
				cout << "0" << time % 60;
			}
			else cout << time % 60;
			m.unlock();

			Sleep(1000);
			++time;
		}
	}
}

void countDown1(int x, int y) {
	m.lock();
	SetColor3(12);
	showTitle("text_3.txt", x, y);
	Sleep(1000);

	SetColor3(11);
	showTitle("text_2.txt", x, y);
	Sleep(1000);

	SetColor3(10);
	showTitle("text_1.txt", x, y);
	Sleep(1000);

	SetColor3(14);
	showTitle("text_0.txt", x, y);
	Sleep(1000);

	SetColor(14);
	m.unlock();
}

void writePlayerList(string filename, PlayerList& list) {

	ofstream ofile;
	ofile.open(filename, ios::binary | ios::trunc);

	ofile.write((char*)(&list.size), sizeof(int));
	PlayerNode* cur = list.head;
	while (cur != NULL) {
		ofile.write((char*)(cur->player.name.c_str()), sizeof(string));
		ofile.write((char*)(&cur->player.score), sizeof(unsigned int));
		ofile.write((char*)(&cur->player.time), sizeof(unsigned int));

		PlayerNode* del = cur;
		cur = cur->next;
		delete del;
	}
	list.head = NULL;

	ofile.close();
}

void readPlayerList(string filename, PlayerList& list) {
	ifstream ifile;
	ifile.open(filename, ios::binary);

	if (!ifile.is_open()) {
		ofstream ofile;
		ofile.open(filename, ios::binary);
		int empty = 0;
		ofile.write((char*)(&empty), sizeof(int));
		ofile.close();
		return;
	}

	int size;
	ifile.read((char*)(&size), sizeof(int));
	Player tmp;
	
	for (int i = 0; i < size; i++) {
		ifile.read((char*)(tmp.name.c_str()), sizeof(string));
		ifile.read((char*)(&tmp.score), sizeof(unsigned int));
		ifile.read((char*)(&tmp.time), sizeof(unsigned int));
		list.pushBack(tmp);
	}

	ifile.close();
}

void writeGameData(string filename, int** table, int nRow, int nCol, myStack& undo, myStack& redo, Player& player, bool endless) {

	ofstream ofile;
	ofile.open(filename, ios::binary | ios::trunc);

	int notempty = 1;
	ofile.write((char*)(&notempty), sizeof(int));											// đánh dấu file không rỗng
	ofile.write((char*)(player.name.c_str()), sizeof(string));								// ghi tên người chơi
	ofile.write((char*)(&player.score), sizeof(unsigned int));								// ghi điểm người chơi
	ofile.write((char*)(&player.time), sizeof(unsigned int));								// ghi thời gian chơi
	ofile.write((char*)(&endless), sizeof(bool));
	
	for (int i = 0; i < nRow; i++) {														// ghi trạng thái của table hiện tại
		ofile.write(reinterpret_cast <char*> (&table[i][0]), sizeof(int) * nCol);
	}

	ofile.write((char*)(&undo.size), sizeof(int));											// ghi số phần tử của undo
	int undo_size = undo.size;
	for (int k = 0; k < undo_size; k++) {													// ghi trạng thái của các table cũ trong undo
		for (int i = 0; i < nRow; i++) {
			ofile.write(reinterpret_cast <char*> (&undo.head->matrix[i][0]), sizeof(char) * nCol);
		}
		ofile.write((char*)(&undo.head->score), sizeof(unsigned int));
		undo.pop();
	}
	undo.head = NULL;

	ofile.write((char*)(&redo.size), sizeof(int));											// ghi số phần tử của undo
	int redo_size = redo.size;
	for (int k = 0; k < redo_size; k++) {													// ghi trạng thái của các table cũ trong redo
		for (int i = 0; i < nRow; i++) {
			ofile.write(reinterpret_cast <char*> (&redo.head->matrix[i][0]), sizeof(char) * nCol);
		}
		ofile.write((char*)(&redo.head->score), sizeof(unsigned int));
		redo.pop();
	}
	redo.head = NULL;

	ofile.close();
}

void readGameData(string filename, int** table, int& nRow, int& nCol, myStack& undo, myStack& redo, Player& player, bool& endless) {

	ifstream ifile;
	ifile.open(filename, ios::binary);

	if (!ifile.is_open()) {
		ofstream ofile;
		ofile.open(filename, ios::binary);
		int empty = 0;
		ofile.write((char*)(&empty), sizeof(int));
		ofile.close();
	}

	int notempty = 1;
	ifile.read((char*)(&notempty), sizeof(int));
	ifile.read((char*)(player.name.c_str()), sizeof(string));							// đọc tên người chơi
	ifile.read((char*)(&player.score), sizeof(unsigned int));							// đọc điểm người chơi
	ifile.read((char*)(&player.time), sizeof(unsigned int));							// đọc thời gian chơi
	ifile.read((char*)(&endless), sizeof(bool));

	for (int i = 0; i < nRow; i++) {													// đọc trạng thái của table hiện tại
		ifile.read(reinterpret_cast <char*> (&table[i][0]), sizeof(int) * nCol);
	}
	
	char** tmp = new char* [nRow];														// ma trận tạm để đọc thông tin từ file, sau đó push vào stack
	for (int i = 0; i < nRow; i++) {
		tmp[i] = new char[nCol];
	}

	ifile.read((char*)(&undo.size), sizeof(int));										// đọc số phần tử trong undo
	myStack undo_tmp;																	// tạo stack tạm để không làm mất tính thứ tự của stack ban đầu
	undo_tmp.init();
	int undo_score_tmp;
	int undo_size = undo.size;
	for (int k = 0; k < undo_size; k++) {												// đọc trạng thái của các table cũ trong undo
		for (int i = 0; i < nRow; i++) {
			ifile.read(reinterpret_cast <char*> (&tmp[i][0]), sizeof(char) * nCol);
		}
		ifile.read((char*)(&undo_score_tmp), sizeof(unsigned int));
		undo_tmp.pushChar(tmp, nRow, nCol, undo_score_tmp);
	}
	for (int k = 0; k < undo_size; k++) {
		undo.pushChar(undo_tmp.head->matrix, nRow, nCol, undo_tmp.head->score);
		undo_tmp.pop();
	}
	undo.size = undo_size;
	
	ifile.read((char*)(&redo.size), sizeof(int));										// đọc số phần tử trong redo
	myStack redo_tmp;																	// tạo stack tạm để không làm mất tính thứ tự của stack ban đầu
	redo_tmp.init();
	int redo_score_tmp;
	int redo_size = redo.size;
	for (int k = 0; k < redo_size; k++) {												// đọc trạng thái của các table cũ trong undo
		for (int i = 0; i < nRow; i++) {
			ifile.read(reinterpret_cast <char*> (&tmp[i][0]), sizeof(char) * nCol);
		}
		ifile.read((char*)(&redo_score_tmp), sizeof(unsigned int));
		redo_tmp.pushChar(tmp, nRow, nCol, redo_score_tmp);
	}
	for (int k = 0; k < redo_size; k++) {
		redo.pushChar(redo_tmp.head->matrix, nRow, nCol, redo_tmp.head->score);
		redo_tmp.pop();
	}
	redo.size = redo_size;
	
	undo_tmp.deleteStack();
	redo_tmp.deleteStack();
	for (int i = 0; i < nRow; i++) {
		delete[] tmp[i];
	}
	delete[] tmp;

	ifile.close();
}

void showGameInfo(int xo, int yo, int width, int height, int row, int col, Player& player, int unre, int best_score, bool endless) {

	m.lock();
	SetColor3(15);

	showTitle("text_2048.txt", 93, 2);
	showTitle("text_classic_large.txt", 93, 5);
	gotoxy(109, 4); cout << "---------------";
	gotoxy(93, 8);	cout << "---------------- STANDARD PHASE";
	if (endless == true) {
		gotoxy(93, 8);	cout << "----------------- ENDLESS PHASE";
	}

	createBox(90, 10, 36, 16, 14, 0, "");
	gotoxy(93, 10);		cout << " NOTIFICATION ";

	createBox(90, 28, 36, 12, 14, 0, "");
	gotoxy(93, 28);		cout << " GAME INFO ";
	gotoxy(93, 30);		cout << "PLAYER        : " << player.name;
	gotoxy(93, 32);		cout << "TIME          :";
	gotoxy(93, 34);		cout << "CURRENT SCORE : ";
	gotoxy(93, 36);		cout << "BEST SCORE    : ";

	SetColor3(15);
	gotoxy(109, 34);	cout << player.score;
	gotoxy(109, 36);	cout << best_score;

	SetColor3(14);
	gotoxy(93, 38);		//cout << "[u] UNDO   [r] REDO   [e] EXIT";
	if (unre == 0) SetColor3(8);;
	cout << "[u] UNDO";
	SetColor3(14);

	gotoxy(104, 38);
	if (unre == 0 || unre == 1) SetColor3(8);
	cout << "[r] REDO";
	SetColor3(14);

	gotoxy(115, 38); cout << "[e] EXIT";
	m.unlock();
}

void doExit(int xo, int yo, int nRow, int nCol, int width, int height, int** table, myStack& undo, myStack& redo, Player& player, char& key_press, bool& cont, bool& endless, bool newgame) {
	
	// xác nhận lại người chơi có thực sự muốn thoát game
	m.lock();
	SetColor3(10);
	gotoxy(92, 15);		cout << "Are you sure you want to exit?";
	gotoxy(92, 17);		cout << "[b] YES, without saving the game";
	gotoxy(92, 18);		cout << "[y] YES, with saving the game";
	gotoxy(92, 19);		cout << "[n] NO";
	m.unlock();

	string file_name[] = { "player1.bin", "player2.bin", "player3.bin", "player4.bin", "player5.bin" };

	// lưu game hiện tại vào 1 trong 5 file player.bin nếu còn file trống
	while (true) {
		key_press = _getch();
		if (key_press == 'b') {
			cont = false;
			return;
		}
		else if (key_press == 'y') {

			// nếu game được chơi từ resume thì bỏ qua file rỗng và ghi đè thông tin lên file cũ cùng tên player
			if (newgame == false) {
				for (int i = 0; i < 5; i++) {
					ifstream ifile;
					ifile.open(file_name[i], ios::binary);

					if (!ifile.is_open()) {
						continue;
					}

					int check;
					Player player_check;
					ifile.read((char*)(&check), sizeof(int));
					ifile.read((char*)(player_check.name.c_str()), sizeof(string));
					ifile.close();

					if (player_check.name == player.name) {
						writeGameData(file_name[i], table, nRow, nCol, undo, redo, player, endless);
						cont = false;
						return;
					}
				}
			}

			// nếu game được chơi từ newgame thì tìm file rỗng đầu tiên để ghi thông tin game
			int index = -1;

			for (int i = 0; i < 5; i++) {
				ifstream ifile;
				ifile.open(file_name[i], ios::binary);

				if (!ifile.is_open()) {
					ofstream ofile;
					ofile.open(file_name[i], ios::binary);
					int empty = 0;
					ofile.write((char*)(&empty), sizeof(int));
					ofile.close();

					index = i;
					break;
				}

				int check = -1;
				
				ifile.read((char*)(&check), sizeof(int));
				if (check == 0) {
					index = i;
					ifile.close();
					break;
				}

				ifile.close();
			}

			// ghi thông tin game vào file rỗng đã tìm được
			if (index != -1) {
				writeGameData(file_name[index], table, nRow, nCol, undo, redo, player, endless);
				cont = false;
				return;
			}

			SetColor3(15);
			gotoxy(0, 44);
			break;
		}
		else if (key_press == 'n') {
			m.lock();
			SetColor3(15);
			clearNoti();
			m.unlock();
			return;
		}
	}

	// game được chơi từ newgame và không còn file trống --> thông báo người chơi chọn 1 file để xóa thông tin game cũ và lưu thông tin game hiện tại
	m.lock();
	SetColor3(15);
	clearNoti();
	SetColor3(10);
	gotoxy(92, 12);		cout << "Please select one of the existing";
	gotoxy(92, 13);		cout << "files to overwrite your game.";

	// hiển thị danh sách game đã lưu lại trò chơi để người chơi chọn
	bool tmp = false;
	int x = 95, y = 15;
	string player_name;
	showResumeFile(x, y);
	chooseResumeFile(x, y, tmp, player_name);
	m.unlock();

	// lưu game hiện tại vào file mà người chơi đã chọn
	writeGameData(file_name[stoi(player_name)], table, nRow, nCol, undo, redo, player, endless);
	
	// kết thúc, quay lại màn hình menu chính
	cont = false;
	SetColor3(15);
}

void clearNoti() {
	for (int i = 11; i <= 25; i++) {
		gotoxy(92, i);
		cout << "                                 ";
	}
}

void doUndo(int xo, int yo, int nRow, int nCol, int width, int height, int** table, myStack& undo, myStack& redo, Player& player, bool& undo_ing, bool& changed, int unre, int best_score) {
	m.lock();
	SetColor3(10);
	if (unre == 0) {
		gotoxy(92, 17);		cout << "The UNDO function is disabled.";
		gotoxy(92, 18);		cout << "Please  go  to  the  Setting";
		gotoxy(92, 19);		cout << "to make changes :(";
	}
	else {
		if (undo.head == NULL) {
			gotoxy(92, 18);	cout << "UNDO is not available :(";
		}
		else {
			redo.pushInt(table, nRow, nCol, player.score);
			undo.top(table, nRow, nCol, player.score);
			undo.pop();

			printNumber(xo, yo, nRow, nCol, width, height, table);
			SetColor3(15);
			gotoxy(109, 34); cout << player.score << "    ";
			if (player.score < best_score) {
				gotoxy(109, 36); cout << best_score << "     ";
			}
			else {
				gotoxy(109, 36); cout << player.score << "     ";
			}

			undo_ing = true;
			changed = false;
		}
	}
	m.unlock();
}

void doRedo(int xo, int yo, int nRow, int nCol, int width, int height, int** table, myStack& undo, myStack& redo, Player& player, bool& changed, int unre, int best_score) {
	m.lock();
	SetColor3(10);
	if (unre == 0 || unre == 1) {
		gotoxy(92, 17);	cout << "The REDO function is disabled.";
		gotoxy(92, 18);	cout << "Please  go  to  the  Setting";
		gotoxy(92, 19);	cout << "to make changes :(";

	}
	else {
		if (redo.head == NULL) {
			gotoxy(92, 18);	cout << "REDO is not available :(";
		}
		else {
			undo.pushInt(table, nRow, nCol, player.score);
			redo.top(table, nRow, nCol, player.score);
			redo.pop();

			printNumber(xo, yo, nRow, nCol, width, height, table);
			SetColor3(15);
			gotoxy(109, 34); cout << player.score << "    ";
			if (player.score < best_score) {
				gotoxy(109, 36); cout << best_score << "     ";
			}
			else {
				gotoxy(109, 36); cout << player.score << "     ";
			}

			changed = false;
		}
	}
	m.unlock();
}

void doWin(bool& endless, bool newgame, string player_name) {
	m.lock();
	SetColor3(3);
	showTitle("text_win.txt", 95, 13);

	SetColor3(10);
	gotoxy(93, 20); cout << "Do you want to continue playing?";
	gotoxy(93, 22); cout << "[y] : switch to Endless Phase";
	gotoxy(93, 23); cout << "[n] : return to the menu";
	m.unlock();

	while (true) {
		char c = _getch();
		if (c == 'y') {
			m.lock();
			clearNoti();
			SetColor(15);
			gotoxy(93, 8);	cout << "----------------- ENDLESS PHASE";
			m.unlock();

			endless = true;
			
			return;
		}
		else if (c == 'n') {
			// nếu game được chơi từ resume thì sau khi thắng phải xóa thông tin trong file
			if (newgame == false) {
				string file_name[] = { "player1.bin", "player2.bin", "player3.bin", "player4.bin", "player5.bin" };

				ofstream ofile;
				ofile.open(file_name[stoi(player_name)], ios::binary | ios::trunc);

				int empty = 0;
				ofile.write((char*)(&empty), sizeof(int));
				ofile.close();
			}

			return;
		}
	}
}

int getRank(PlayerList& list, Player& player) {

	if (list.head == NULL) {
		return 1;
	}

	if (player.score > list.head->player.score || (player.score == list.head->player.score && player.time < list.head->player.time)) {
		return 1;
	}
	else {
		int rank = 2;
		for (PlayerNode* i = list.head; i->next != NULL; i = i->next) {
			if (i->next->player.score < player.score || (i->next->player.score == player.score && i->next->player.time > player.time)) {
				return rank;
			}
			++rank;
		}
		return rank;
	}
}

void doLose(int unre, PlayerList& list, Player& player, bool& lose, bool newgame, string player_name) {
	m.lock();
	SetColor3(12);
	showTitle("text_lose.txt", 92, 12);
	
	SetColor3(10);
	int rank = getRank(list, player);

	if (unre != 0) {
		gotoxy(93, 19); cout << "Your rank is: ";
		if (rank <= 20) cout << rank << " / 20";
		else cout << "20+ / 20";
		gotoxy(93, 21); cout << "Do you want to continue playing?";
		gotoxy(93, 23); cout << "[y] : use undo to continue";
		gotoxy(93, 24); cout << "[n] : return to the menu";
	}
	else {
		gotoxy(93, 19); cout << "Your rank is: ";
		if (rank <= 20) cout << rank << " / 20";
		else cout << "20+ / 20";
		gotoxy(93, 21); cout << "Press [n] to return to the menu";
	}
	m.unlock();

	while (true) {
		char c = _getch();
		if (c == 'y' && unre != 0) {
			clearNoti();
			return;
		}
		else if (c == 'n') {
			lose = true;

			// nếu game được chơi từ resume thì sau khi thua phải xóa thông tin trong file
			if (newgame == false) {
				string file_name[] = { "player1.bin", "player2.bin", "player3.bin", "player4.bin", "player5.bin" };

				ofstream ofile;
				ofile.open(file_name[stoi(player_name)], ios::binary | ios::trunc);

				int empty = 0;
				ofile.write((char*)(&empty), sizeof(int));
				ofile.close();
			}

			return;
		}
	}
}

void doGame(Screen& screen, bool& newgame, bool& pause, bool& out, bool& endless, bool& timeover, int unre, int delay, string player_name, Player& player, int** table, int nRow, int nCol, myStack& undo, myStack& redo) {
	
	system("cls");
	SetColor3(15);
	createBox(0, 0, 130, 42, 14, 0, "");
	ShowCur(0);
	
	// chuẩn bị
	int xo = 5 + ((10 - nRow) * 4), yo = (10 - nRow) * 2 + 1, line = 0;		// tọa độ góc trên bên trái của table
	int width = 9;															// chiều rộng mỗi ô của table
	if (nRow == 4) {
		width = 13;
		xo = 21;
		yo = 9;
	}
	int height = width / 2 + 1;												// chiều dài mỗi cô của table

	// tạo danh sách lưu thông tin top-20 --> để lấy điểm cao nhất và tìm thứ hạng
	PlayerList list;
	list.init();
	readPlayerList("topplayers.bin", list);

	// các biến dùng để đảm bảo tính logic trong trò chơi
	bool changed = false;													// kiểm tra bảng số có thay đổi trạng thái (sau mỗi lượt di chuyển) không
	bool undo_ing = false;													// kiểm tra phím được nhấn gần nhất là undo
	int best_score;															// lưu điểm cao nhất trong top-20 hiện tại
	if (list.head == NULL) best_score = 0;
	else best_score = list.head->player.score;

	// tạo seed cho việc sinh random
	srand(time(0));

	// hiển thị thông tin trò chơi phía bên phải màn hình
	showGameInfo(xo, yo, width, height, nRow, nCol, player, unre, best_score, endless);

	// đếm ngược 3 giây để người chơi sẵn sàng
	countDown1(38, 17);

	// in table trước khi bắt đầu chơi
	m.lock();
	SetColor3(14);
	if (newgame == true) {
		prepare(xo, yo, nRow, nCol, width, height, table);
	}
	else {
		printFrame(xo, yo, nRow, nCol, width, height);
		printNumber(xo, yo, nRow, nCol, width, height, table);
	}
	m.unlock();
	
	// XỬ LÝ KHI NGƯỜI CHƠI THẮNG, bỏ comment từ dòng 769 đến 780 để kiểm tra
	/*
	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nCol; j++) {
			table[i][j] = 0;
		}
	}
	table[0][0] = 1024;
	table[0][1] = 1024;
	m.lock();
	printNumber(xo, yo, nRow, nCol, width, height, table);
	m.unlock();
	*/

	// XỬ LÝ KHI NGƯỜI CHƠI THUA, bỏ comment từ dòng 783 đến 800 để kiểm tra
	/*
	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nCol; j++) {
			if (j != nCol - 1) {
				if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) table[i][j] = 128;
				else table[i][j] = 8;
			}
			else {
				if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) table[i][j] = 16;
				else table[i][j] = 64;
			}
		}
	}
	table[nRow - 1][nCol - 1] = 0;
	m.lock();
	printNumber(xo, yo, nRow, nCol, width, height, table);
	m.unlock();
	*/

	// XỬ LÝ KHI THỜI GIAN CHƠI QUÁ LÂU (60 PHÚT), bỏ comment từ dòng 803 đến 8005 để kiểm tra
	/*
	player.time = 3595;
	*/

	// ghi nhận và xử lý tín hiệu điều khiển trò chơi từ người chơi
	while (timeover == false) {
		if (_kbhit() == true) {
			char key_press = _getch();

			if (key_press == -32) {
				continue;
			}

			if (key_press == 'a' || key_press == 'd' || key_press == 'w' || key_press == 's' || key_press == LEFT || key_press == RIGHT \
				 || key_press == UP || key_press == DOWN || key_press == 'u' || key_press == 'r' || key_press == 'e') {
				m.lock();
				SetColor3(15);
				clearNoti();
				m.unlock();
			}

			if (key_press == 'a' || key_press == 'd' || key_press == 'w' || key_press == 's' \
				|| key_press == LEFT || key_press == RIGHT || key_press == UP || key_press == DOWN) {

				undo.pushInt(table, nRow, nCol, player.score);

				if (undo_ing == true) {
					redo.deleteStack();
					undo_ing = false;
				}

				if (key_press == 'a' || key_press == LEFT) {
					moveLeft(table, nRow, nCol, player.score, changed);
				}
				else if (key_press == 'd' || key_press == RIGHT) {
					moveRight(table, nRow, nCol, player.score, changed);
				}
				else if (key_press == 'w' || key_press == UP) {
					moveUp(table, nRow, nCol, player.score, changed);
				}
				else if (key_press == 's' || key_press == DOWN) {
					moveDown(table, nRow, nCol, player.score, changed);
				}

				if (changed == false) {
					undo.pop();

					m.lock();
					SetColor3(10);
					gotoxy(92, 17);	cout << "No valid moves in that direction.";
					gotoxy(92, 18); cout << "Try another move!";
					m.unlock();
				}
			}

			else if (key_press == 'u') {
				doUndo(xo, yo, nRow, nCol, width, height, table, undo, redo, player, undo_ing, changed, unre, best_score);
			}

			else if (key_press == 'r') {
				doRedo(xo, yo, nRow, nCol, width, height, table, undo, redo, player, changed, unre, best_score);
			}

			else if (key_press == 'e') {
				bool cont = true;
				pause = true;
				doExit(xo, yo, nRow, nCol, width, height, table, undo, redo, player, key_press, cont, endless, newgame);
				if (cont == false) {
					out = true;
					screen = Menu;
					break;
				}
				else {
					pause = false;
				}
			}
		}
		

		if (changed == true) {
			if (delay != 0) {
				m.lock();
				printNumber(xo, yo, nRow, nCol, width, height, table);
				m.unlock();
			}

			randomCell(table, nRow, nCol);

			if (delay != 0) Sleep(delay * 100);

			m.lock();
			printNumber(xo, yo, nRow, nCol, width, height, table);

			SetColor3(15);
			gotoxy(109, 34); cout << player.score;

			if (player.score > best_score) {
				gotoxy(109, 36); cout << player.score;
			}
			m.unlock();

			changed = false;
		}

		if (endless == false && isWin(table, nRow, nCol)) {
			pause = true;

			doWin(endless, newgame, player_name);

			if (endless == false) {
				out = true;
				screen = Menu;
				break;
			}
			else {
				pause = false;
			}
		}

		if (isLose(table, nRow, nCol)) {
			pause = true;
			bool lose = false;
			
			doLose(unre, list, player, lose, newgame, player_name);
						
			if (lose == true) {
				out = true;
				screen = Menu;
				break;
			}
			else {
				doUndo(xo, yo, nRow, nCol, width, height, table, undo, redo, player, undo_ing, changed, unre, best_score);
				pause = false;
			}
		}
	}

	// cập nhật top20
	list.insertPlayer(player);

	writePlayerList("topplayers.bin", list);
	
	// giải phóng vùng nhớ xin cấp phát
	for (int i = 0; i < nRow; i++) {
		delete[] table[i];
	}
	delete[] table;
	table = NULL;

	undo.deleteStack();
	redo.deleteStack();
	list.deleteList();
}

void screenGame(Screen& screen, bool& newgame, string& player_name, int table_size, int unre, int delay) {
	
	// chuẩn bị
	int nRow = table_size + 4, nCol = nRow;			// kích thước của table

	int** table = new int* [nRow];					// cấp phát vùng nhớ cho table
	for (int i = 0; i < nRow; i++) {
		table[i] = new int[nCol];
	}

	for (int i = 0; i < nRow; i++) {				// khởi tạo giá trị ban đầu cho các phần tử của table là 0
		for (int j = 0; j < nCol; j++) {
			table[i][j] = 0;
		}
	}

	myStack undo, redo;								// tạo stack undo, redo
	undo.init(); redo.init();

	bool endless = false;							// kiểm tra trò chơi đã chiến thắng trước đó hay chưa

	// cập nhật thông tin người chơi
	Player player;
	if (newgame == true) {
		player.name = player_name;
		player.score = 0;
		player.time = 0;
	}
	else {
		string file_name[] = { "player1.bin", "player2.bin", "player3.bin", "player4.bin", "player5.bin" };
		readGameData(file_name[stoi(player_name)], table, nRow, nCol, undo, redo, player, endless);
	}

	bool out = false;								// kiểm tra trò chơi có dừng (thoát ra menu) hay không
	bool pause = false;								// kiểm tra trò chơi có đang tạm dừng hay không
	bool timeover = false;							// kiểm tra trò chơi có tốn quá nhiều thời gian hay không (quá 60 phút)

	thread thr1(doGame, ref(screen), ref(newgame), ref(pause), ref(out), ref(endless), ref(timeover), unre, delay, player_name, ref(player), table, nRow, nCol, ref(undo), ref(redo));
	thread thr2(myClock, ref(player.time), ref(pause), ref(out), ref(timeover), ref(screen));
	
	thr1.join();
	thr2.join();
}

// EXTENDED GAME : BATTLE MODE

void myTimer(int& time_battle, bool& end_battle) {
	while (true) {
		if (end_battle == true) {
			return;
		}

		m.lock();
		SetColor3(14);
		gotoxy(63, 14);
		if ((time_battle / 60) % 60 < 10) {
			cout << "0" << (time_battle / 60) % 60 << ":";
		}
		else cout << (time_battle / 60) % 60 << ":";

		gotoxy(66, 14);
		if (time_battle % 60 < 10) {
			cout << "0" << time_battle % 60;
		}
		else cout << time_battle % 60;
		m.unlock();

		if (time_battle == 0) {
			end_battle = true;
			return;
		}

		Sleep(1000);
		--time_battle;
	}
}

void myTimeBar(int& time_battle, bool& end_battle, int time_battle0) {

	int x = 94;

	while (true) {
		if (end_battle == true) {
			return;
		}

		m.lock();
		SetColor3(15);
		if (x > 34) {
			gotoxy(x, 11); cout << " ";
		}
		m.unlock();

		--x;
		if (time_battle0 == 30) Sleep(500);
		else if (time_battle0 == 60) Sleep(1000);
		else if (time_battle0 == 120) Sleep(2000);
	}
}

void countDown2(int x1, int y1, int x2, int y2) {
	m.lock();
	SetColor3(3);
	showTitle("text_3.txt", x1, y1);
	SetColor3(12);
	showTitle("text_3.txt", x2, y2);
	Sleep(1000);

	SetColor3(3);
	showTitle("text_2.txt", x1, y1);
	SetColor3(12);
	showTitle("text_2.txt", x2, y2);
	Sleep(1000);

	SetColor3(3);
	showTitle("text_1.txt", x1, y1);
	SetColor3(12);
	showTitle("text_1.txt", x2, y2);
	Sleep(1000);

	SetColor3(3);
	showTitle("text_0.txt", x1, y1);
	SetColor3(12);
	showTitle("text_0.txt", x2, y2);
	Sleep(1000);

	SetColor(14);
	m.unlock();
}

void clearTable4X4(int xo, int yo, int color) {
	SetColor3(15);
	for (int i = 1; i <= 47; i++) {
		for (int j = 1; j <= 23; j++) {
			gotoxy(xo + i, yo + j);
			cout << " ";
		}
	}
	SetColor3(color);
	gotoxy(xo + 12, yo); cout << (char)205;
	gotoxy(xo + 24, yo); cout << (char)205;
	gotoxy(xo + 36, yo); cout << (char)205;
	gotoxy(xo + 12, yo + 24); cout << (char)205;
	gotoxy(xo + 24, yo + 24); cout << (char)205;
	gotoxy(xo + 36, yo + 24); cout << (char)205;
	gotoxy(xo, yo + 6); cout << (char)186;
	gotoxy(xo, yo + 12); cout << (char)186;
	gotoxy(xo, yo + 18); cout << (char)186;
	gotoxy(xo + 48, yo + 6); cout << (char)186;
	gotoxy(xo + 48, yo + 12); cout << (char)186;
	gotoxy(xo + 48, yo + 18); cout << (char)186;

}

void p1_BattleGame(Player& player1, int** table1, int nRow, int nCol, int x1, int y1, int width, int height, bool& end_battle, bool& p1lose, char key) {
	
	bool changed = false; // kiểm tra bảng số có thay đổi trạng thái (sau mỗi lượt di chuyển) không
	
	if (key == 'a') {
		moveLeft(table1, nRow, nCol, player1.score, changed);
	}
	else if (key == 'd') {
		moveRight(table1, nRow, nCol, player1.score, changed);
	}
	else if (key == 'w') {
		moveUp(table1, nRow, nCol, player1.score, changed);
	}
	else if (key == 's') {
		moveDown(table1, nRow, nCol, player1.score, changed);
	}

	if (changed == true) {

		randomCell(table1, nRow, nCol);

		m.lock();
		printNumber(x1, y1, nRow, nCol, width, height, table1);

		SetColor3(48);
		gotoxy(56, 22); cout << player1.score;
		m.unlock();

		changed = false;
	}

	if (isLose(table1, nRow, nCol)) {
		p1lose = true;
		end_battle = true;
	}
}

void p2_BattleGame(Player& player2, int** table2, int nRow, int nCol, int x2, int y2, int width, int height, bool& end_battle, bool& p2lose, char new_key) {

	bool changed = false;		// kiểm tra bảng số có thay đổi trạng thái (sau mỗi lượt di chuyển) không

	if (new_key == LEFT) {
		moveLeft(table2, nRow, nCol, player2.score, changed);
	}
	else if (new_key == RIGHT) {
		moveRight(table2, nRow, nCol, player2.score, changed);
	}
	else if (new_key == UP) {
		moveUp(table2, nRow, nCol, player2.score, changed);
	}
	else if (new_key == DOWN) {
		moveDown(table2, nRow, nCol, player2.score, changed);
	}
	
	if (changed == true) {

		randomCell(table2, nRow, nCol);

		m.lock();
		printNumber(x2, y2, nRow, nCol, width, height, table2);

		SetColor3(192);
		gotoxy(75 - (to_string(player2.score)).size(), 34); cout << player2.score;
		m.unlock();

		changed = false;
	}

	if (isLose(table2, nRow, nCol)) {
		p2lose = true;
		end_battle = true;
	}
	
}

void doBattleGame(Player& player1, Player& player2, int** table1, int** table2, int nRow, int nCol, int x1, int y1, int x2, int y2, int width, int height, bool& end_battle, bool& p1lose, bool& p2lose, bool& drop) {

	while (end_battle == false) {

		if (_kbhit() == true) {
			char key = _getch();

			if (key == 'a' || key == 'd' || key == 'w' || key == 's') {
				p1_BattleGame(player1, table1, nRow, nCol, x1, y1, width, height, end_battle, p1lose, key);
			}
			else if (key == -32) {
				char new_key = _getch();

				if (new_key == UP || new_key == DOWN || new_key == LEFT || new_key == RIGHT) {
					p2_BattleGame(player2, table2, nRow, nCol, x2, y2, width, height, end_battle, p2lose, new_key);
				}
			}
			else if (key == 'b') {
				end_battle = true;
				drop = true;
				break;
			}
		}
	}
}

void screenBattleGame(Screen& screen, int& time_battle, string& player1_name, string& player2_name) {

	system("cls");
	SetColor3(15);
	ShowCur(0);

	int w_border = 130, h_border = 42;
	createBox(0, 0, w_border, h_border, 14, 0, "");

	showTitle("title_battle.txt", (w_border - 50) / 2, 3);
	showTitle("text_vs.txt", 62, 26);

	string noti = "Press [b] to stop battle immediately";
	gotoxy((w_border - noti.size()) / 2, h_border - 1);
	cout << noti;

	int nRow = 4, nCol = nRow;						// kích thước của table
	int** table1 = new int* [nRow];					// cấp phát vùng nhớ cho các table
	int** table2 = new int* [nRow];
	for (int i = 0; i < nRow; i++) {
		table1[i] = new int[nCol];
		table2[i] = new int[nCol];
	}
	for (int i = 0; i < nRow; i++) {				// khởi tạo giá trị ban đầu cho các phần tử của table là 0
		for (int j = 0; j < nCol; j++) {
			table1[i][j] = 0;
			table2[i][j] = 0;
		}
	}

	int width = 13, height = width / 2 + 1;

	// chuẩn bị cho người chơi 1
	SetColor3(3);
	Player player1 { player1_name, 0, 0 };
	int x1 = 5, y1 = 15;
	
	for (int i = 0; i < 7; i++) {
		SetColor3(3);
		gotoxy(54, 18 + i);
		cout << (char)222;
	}
	gotoxy(56, 18); cout << "PLAYER A";
	gotoxy(56, 21); cout << "SCORE";
	gotoxy(56, 24); cout << "[a][d][w][s]";

	SetColor3(48);
	gotoxy(55, 19); cout << "                 ";
	gotoxy(55, 22); cout << "                 ";
	gotoxy(56, 19); cout << player1.name;
	gotoxy(56, 22); cout << player1.score;

	// chuẩn bị cho người chơi 2
	SetColor3(12);
	Player player2 { player2_name, 0, 0 };
	int x2 = 77, y2 = 15;

	for (int i = 0; i < 7; i++) {
		SetColor3(12);
		gotoxy(76, 30 + i);
		cout << (char)221;
	}
	gotoxy(67, 30); cout << "PLAYER B";
	gotoxy(67, 33); cout << "   SCORE";
	gotoxy(63, 36); cout << "[" << (char)17 << "][" << char(16) << "][" << (char)30 << "][" << (char)31 << "]";
	
	SetColor3(192);
	gotoxy(59, 31); cout << "                 ";
	gotoxy(59, 34); cout << "                 ";
	gotoxy(75 - player2.name.size(), 31); cout << player2.name;
	gotoxy(75 - (to_string(player2.score)).size(), 34); cout << player2.score;

	SetColor3(15);
	createBox(34, 10, 61, 2, 14, 0, "");
	for (int i = 1; i <= 60; i++) {
		gotoxy(34 + i, 11); cout << (char)219;
	}

	int time_battle0 = time_battle;
	bool end_battle = false;
	bool p1lose = false;
	bool p2lose = false;
	bool drop = false;

	// đếm ngược 3 giây để người chơi sẵn sàng
	countDown2(25, 20, 97, 20);

	// chuẩn bị table cho mỗi người chơi
	SetColor3(3);
	prepare(x1, y1, nRow, nCol, width, height, table1);
	SetColor3(12);
	prepare(x2, y2, nRow, nCol, width, height, table2);

	thread thr1(myTimer, ref(time_battle), ref(end_battle));
	thread thr2(myTimeBar, ref(time_battle), ref(end_battle), time_battle0);
	thread thr3(doBattleGame, ref(player1), ref(player2), table1, table2, nRow, nCol, x1, y1, x2, y2, width, height, ref(end_battle), ref(p1lose), ref(p2lose), ref(drop));
		
	thr1.join();
	thr2.join();
	thr3.join();
	
	if (end_battle == true && drop == false) {
		clearTable4X4(x1, y1, 3);
		clearTable4X4(x2, y2, 12);

		if (p1lose == true && p2lose == false) {
			SetColor3(12);
			showTitle("text_win.txt", x2 + 11, y2 + 9);
			gotoxy(86, 31); cout << "Press [Enter] to back to menu";
			SetColor3(8);
			showTitle("text_lose.txt", x1 + 8, y1 + 9);
			gotoxy(14, 31); cout << "Press [Enter] to back to menu";
			
		}
		else if (p2lose == true && p1lose == false) {
			SetColor3(3);
			showTitle("text_win.txt", x1 + 11, y1 + 9);
			gotoxy(14, 31); cout << "Press [Enter] to back to menu";
			SetColor3(8);
			showTitle("text_lose.txt", x2 + 8, y2 + 9);
			gotoxy(86, 31); cout << "Press [Enter] to back to menu";
		}
		else if (p1lose == false && p2lose == false) {
			if (player1.score > player2.score) {
				SetColor3(3);
				showTitle("text_win.txt", x1 + 11, y1 + 9);
				gotoxy(14, 31); cout << "Press [Enter] to back to menu";
				SetColor3(8);
				showTitle("text_lose.txt", x2 + 8, y2 + 9);
				gotoxy(86, 31); cout << "Press [Enter] to back to menu";
			}
			else if (player1.score < player2.score) {
				SetColor3(12);
				showTitle("text_win.txt", x2 + 11, y2 + 9);
				gotoxy(86, 31); cout << "Press [Enter] to back to menu";
				SetColor3(8);
				showTitle("text_lose.txt", x1 + 8, y1 + 9);
				gotoxy(14, 31); cout << "Press [Enter] to back to menu";
			}
			else {
				SetColor3(3);
				showTitle("text_draw.txt", x1 + 8, y1 + 9);
				gotoxy(14, 31); cout << "Press [Enter] to back to menu";
				SetColor3(12);
				showTitle("text_draw.txt", x2 + 8, y2 + 9);
				gotoxy(86, 31); cout << "Press [Enter] to back to menu";
			}
		}

		while(true) {
			char c = _getch();
			if (c == NEWLINE) {
				screen = Menu;
				break;
			}
		}
	}

	if (drop == true) {
		screen = Menu;
	}

	// giải phóng vùng nhớ xin cấp phát
	for (int i = 0; i < nRow; i++) {
		delete[] table1[i];
		delete[] table2[i];
	}
	delete[] table1;
	delete[] table2;
	table1 = NULL;
	table2 = NULL;
}