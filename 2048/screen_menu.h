#ifndef _MENU_H_
#define _MENU_H_

#include "system.h"
#include "screen_newgame.h"
#include "screen_resume.h"
#include "screen_toplist.h"

// xử lý khi người chơi di chuyển và chọn các nút
void chooseMenu(int n, int x, int y, int w, int h, int text_color, int back_color, bool& resume, string text[], Screen& screen);

// hiển thị menu
void screenMenu(Screen& screen);

#endif // !_MENU_H_