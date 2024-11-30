#ifndef _SETTING_H_
#define _SETTING_H_

#include "system.h"

// xử lý khi người chơi thay đổi các lựa chọn trong setting
void changeSetting(int n, int x, int y, int w, int h, string text[4][7], int& table_size, int& unre, bool& set_default, bool& bottom, int& delay);

// xử lý khi người chơi đang chọn defaulut hoặc thoát khỏi màn hình setting
void exitSetting(int x, int y, int w, int h, string text_setting[], bool& menu, bool& set_default, bool& bottom);

// hiển thị màn hình sau khi người chơi nhấn SETTING từ Menu
void screenSetting(Screen& screen, int& table_size, int& unre, int& delay);

#endif // !_SETTING_H_
