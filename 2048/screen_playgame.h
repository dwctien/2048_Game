#ifndef _PLAYGAME_H_
#define _PLAYGAME_H_

#include "system.h"
#include "mystack.h"
#include "gamelogic.h"
#include "screen_resume.h"

struct Player {
	string name;
	unsigned int score;
	unsigned int time;
};

struct PlayerNode {
	Player player;
	PlayerNode* next;
};

PlayerNode* makeNode(Player player1);

struct PlayerList {
	PlayerNode* head;
	int size;

	void init();							// khởi tạo danh sách người chơi rỗng
	void pushFront(Player player1);			// thêm người chơi vào đầu danh sách
	void pushBack(Player player1);			// thêm người chơi vào cuối danh sách
	void popFront();						// xóa người chơi ở đầu danh sách
	void popBack();							// xóa người chơi ở cuối danh sách
	void insertPlayer(Player player1);		// thêm người chơi vào danh sách mà không làm mất tính tăng dần của điểm
	void deleteList();						// giải phóng vùng nhớ của các node trong danh sách
};

// hiển thị thời gian trôi qua trong quá trình chơi
void myClock(unsigned int& time, bool& pause, bool& out, bool& timeover, Screen& screen);

// đếm ngược 3 giây trước khi bắt đầu chơi
void countDown1(int x, int y);

// ghi danh sách người chơi vào file
void writePlayerList(string filename, PlayerList& list);

// đọc danh sách người chơi từ file
void readPlayerList(string filename, PlayerList& list);

// ghi thông tin 01 người chơi vào file
void writeGameData(string filename, int** table, int nRow, int nCol, myStack& undo, myStack& redo, Player& player, bool endless);

// đọc thông tin 01 người chơi từ file
void readGameData(string filename, int** table, int& nRow, int& nCol, myStack& undo, myStack& redo, Player& player, bool& endless);

// hiển thị thông tin trò chơi bên phải màn hình (tên, điểm,...)
void showGameInfo(int xo, int yo, int width, int height, int row, int col, Player& player, int unre, int best_score, bool endless);

// xử lý khi người chơi nhấn exit
void doExit(int xo, int yo, int nRow, int nCol, int width, int height, int** table, myStack& undo, myStack& redo, Player& player, char& key_press, bool& cont, bool& endless, bool newgame);

// xóa bảng thông báo
void clearNoti();

// xử lý khi người chơi nhấn undo
void doUndo(int xo, int yo, int nRow, int nCol, int width, int height, int** table, myStack& undo, myStack& redo, Player& player, bool& undo_ing, bool& changed, int unre, int best_score);

// xử lý khi người chơi nhấn redo
void doRedo(int xo, int yo, int nRow, int nCol, int width, int height, int** table, myStack& undo, myStack& redo, Player& player, bool& changed, int unre, int best_score);

// xử ký khi người chơi thắng
void doWin(bool& endless, bool newgame, string player_name);

// tính thứ hạng của người chơi trong top 20
int getRank(PlayerList& list, Player& player);

// xử lý khi người chơi thua
void doLose(int unre, PlayerList& list, Player& player, bool& lose, bool newgame, string player_name);

// xử lý trò chơi khi người chơi nhấn các phím điều khiển
void doGame(Screen& screen, bool& newgame, bool& pause, bool& out, bool& endless, bool& timeover, int unre, int delay, string player_name, Player& player, int** table, int nRow, int nCol, myStack& undo, myStack& redo);

// hiển thị trò chơi lên màn hình
void screenGame(Screen& screen, bool& newgame, string& player_name, int table_size, int unre, int delay);

// EXTENDED GAME : BATTLE MODE

// hiển thị thời gian đếm ngược
void myTimer(int& time_battle, bool& end_battle);

// hiển thị thanh thời gian đếm ngược
void myTimeBar(int& time_battle, bool& end_battle, int time_battle0);

// đếm ngược 3 giây trước khi bắt đầu chơi
void countDown2(int x1, int y1, int x2, int y2);

// xóa hiển thị table để in kết quả thắng / thua / hòa
void clearTable4X4(int xo, int yo, int color);

// xử lý trò chơi của người chơi 1
void p1_BattleGame(Player& player1, int** table1, int nRow, int nCol, int x1, int y1, int width, int height, bool& end_battle, bool& p1lose, char key);

// xử lý trò chơi của người chơi 2
void p2_BattleGame(Player& player2, int** table2, int nRow, int nCol, int x2, int y2, int width, int height, bool& end_battle, bool& p2lose, char new_key);

// phân loại phím nhận được từ bàn phím là của người chơi 1 hay 2
void doBattleGame(Player& player1, Player& player2, int** table1, int** table2, int nRow, int nCol, int x1, int y1, int x2, int y2, int width, int height, bool& end_battle, bool& p1lose, bool& p2lose, bool& drop);

// hiển thị trò chơi lên màn hình
void screenBattleGame(Screen& screen, int& time_battle, string& player1_name, string& player2_name);

#endif // !_PLAYGAME_H_