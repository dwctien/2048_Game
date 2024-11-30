#ifndef _NEWGAME_H_
#define _NEWGAME_H_

#include "system.h"
#include "screen_playgame.h"

// chuẩn hóa tên (xóa dấu cách ở đầu và cuối)
void formatName(string& name);

// kiểm tra trùng tên trong top-20 và 5 game resume
bool isDuplicated(string name, PlayerList& list);

// lấy tên được nhập từ bàn phím
string getName(string noti, int x_body, int y_body, PlayerList& list);

// (chế độ PVP) lấy tên được nhập từ bàn phím
string getNamePVP(string noti, int x_body, int y_body, string other_name);

// xử lý khi người chơi chọn bắt đầu chơi hoặc trở lại menu
void chooseNewgameMenu(int x, int y, int w, int h, string text_newgame[], string& player1_name, string& player2_name, bool& newgame, Screen& screen);

// (chế độ PVP) xử lý khi người chơi chọn khoảng thời gian chơi
void chooseTime(int x, int y, int& time_battle);

// hiển thị màn hình sau khi người chơi nhấn NEW GAME từ Menu
void screenNewGame(Screen& screen, bool& newgame, string& player_name);

// hiển thị màn hình sau khi người chơi nhấn PVP MODE từ Menu
void screenNewGamePVP(Screen& screen, string& player1_name, string& player2_name, int& time_battle);

#endif // !_NEWGAME_H_