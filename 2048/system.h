#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <iostream>			// i/o cơ bản
#include <fstream>			// xử lý tệp tin
#include <string>			// xử lý chuỗi
#include <math.h>			// chứa các hàm toán học
#include <stdio.h>			// cung cấp các hàm i/o
#include <conio.h>			// xử lý input từ bàn phím: _getch() _kbhit()
#include <cstdlib>			// dùng hàm srand() để khởi tạo bộ sinh số ngẫu nhiên
#include <time.h>			// làm việc với thời gian
#include <thread>			// tạo và quản lý đa luồng
#include <mutex>			// tránh xung đột giữa các luồng
#include <Windows.h>		// hỗ trợ liên quan đến hệ điều hành windows

#define NEWLINE 0x0D
#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

using namespace std;

enum Screen { Menu, NewGame, Setting, TopList, Resume, PVPGame, PlayGame, Quit };

int whereX();																					// lấy tọa độ x của con trỏ hiện tại

int whereY();																					// lấy tọa độ y của con trỏ hiện tại

void gotoxy(int x, int y);																		// dịch con trỏ hiện tại đến điểm có tọa độ (x,y)

void SetColor(WORD color);																		// cài đặt màu

void SetColor2(int backgound_color, int text_color);											// cài đặt màu

void SetColor3(int color);																		// cài đặt màu

void ShowCur(bool CursorVisibility);															// ẩn trỏ chuột

void SetWindowSize(SHORT width, SHORT height);													// thiết lập kích thước màn hình windows

void SetScreenBufferSize(SHORT width, SHORT height);											// thiết lập kích thước màn hình buffer

void DisableResizeWindow();																		// vô hiệu hóa thay đổi kích thước màn hình

void DisableCtrButton(bool Close, bool Min, bool Max);											// vô hiệu hóa các phím điều khiển màn hình

void createBox(int x, int y, int w, int h, int text_color, int back_color, string text);		// tạo ô

void createTextBar(int x, int y, int w, int h, int text_color, int back_color, string text);	// tạo thanh chữ màu

void createHighlightBar(int x, int y, int w, int h, int color, string text);					// tạo thanh chữ highlight

void showTitle(string filename, int x, int y);													// hiển thị chữ kiểu (được lưu sẵn trong file)

#endif // !_SYSTEM_H_