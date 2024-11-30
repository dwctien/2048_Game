#include "system.h"
#include "screen_menu.h"
#include "screen_newgame.h"
#include "screen_playgame.h"
#include "screen_resume.h"
#include "screen_setting.h"
#include "screen_toplist.h"

int main() {

	// cài đặt màn hình console
	SetScreenBufferSize(150, 43);
	SetWindowSize(150, 70);

	Screen screen = Menu;						// xác định màn hình cần hiển thị
	bool newgame = true;						// kiểm tra đây trò chơi mới hay trò chơi đã được lưu trong resume
	string player_name = "test";				// lưu tên người chơi nếu trò chơi mới, lưu tên file nếu trò chơi resume

	int table_size = 0;							// lưu kích thước bảng số (table), 0,1,...,6 ứng với 4x4,5x5,...,10x10
	int unre = 0;								// lưu chế độ undo/redo, 0 : tắt, 1 : bật undo, 2 : bật cả undo và redo
	int delay = 0;								// lưu thời gian chờ để một ô random xuất hiện sau khi di chuyển

	string player1_name, player2_name;			// (PVP MODE) lưu tên 2 người chơi
	bool pvp = false;							// (PVP MODE) kiểm tra chế độ PVP được chọn		
	int time_battle = 0;						// (PVP MODE) lưu thời gian được chọn để đếm ngược

	while (true) {
		if (screen == Menu) {
			screenMenu(screen);
		}
		else if (screen == NewGame) {
			screenNewGame(screen, newgame, player_name);
		}
		else if (screen == Setting) {
			screenSetting(screen, table_size, unre, delay);
		}
		else if (screen == TopList) {
			screenTopList(screen);
		}
		else if (screen == Resume) {
			screenResume(screen, newgame, player_name);
		}
		else if (screen == PVPGame) {
			pvp = true;
			screenNewGamePVP(screen, player1_name, player2_name, time_battle);
		}
		else if (screen == PlayGame) {
			if (pvp == false) {
				screenGame(screen, newgame, player_name, table_size, unre, delay);
			}
			else {
				screenBattleGame(screen, time_battle, player1_name, player2_name);
				pvp = false;
			}
		}
		else if (screen == Quit) {
			break;
		}
	}

	gotoxy(0, 35);
	return 0;
}