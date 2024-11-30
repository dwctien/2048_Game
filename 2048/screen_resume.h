#ifndef _RESUME_H_
#define _RESUME_H_

#include "system.h"
#include "screen_playgame.h"

// hiển thị danh sách file resume TRONG MÀN HÌNH TRÒ CHƠI khi người chơi thoát game và 5 file đã đầy nên cần chọn file để thay thế
void showResumeFile(int x, int y);

// hiển thị danh sách file resume TRONG MÀN HÌNH RESUME
void showResumeFile2(int x, int y);

// tắt hiển thị các file trên màn hình resume
void clearResumeFile(int x, int y);

// xử lý khi người chơi đang chọn file
void chooseResumeFile(int x, int y, bool& bottom, string& player_name);

// xóa thông tin game lưu trong file --> trở thành file rỗng
void deleteResumeFile(int x, int y, string player_name);

// kiểm tra file rỗng
bool isEmptyFile(string player_name);

// xử lý khi người chơi chọn chơi game / xóa game / trở về menu
void chooseMenuResume(int x, int y, int x1, int y1, int w, int h, bool& bottom, bool& newgame, string& player_name, string text_resume[], Screen& screen);

// hiển thị màn hình sau khi người chơi nhấn RESUME từ Menu
void screenResume(Screen& screen, bool& newgame, string& player_name);

#endif // !_RESUME_H_