#include "system.h"

int whereX() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}

int whereY() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

void gotoxy(int x, int y) {
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void SetColor(WORD color) {
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void SetColor2(int backgound_color, int text_color) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int color_code = backgound_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}

void SetColor3(int color) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, color);
}

void ShowCur(bool CursorVisibility) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void SetWindowSize(SHORT width, SHORT height) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT WindowSize;
	WindowSize.Top = 0;
	WindowSize.Left = 0;
	WindowSize.Right = width;
	WindowSize.Bottom = height;

	SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void SetScreenBufferSize(SHORT width, SHORT height) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD NewSize;
	NewSize.X = width;
	NewSize.Y = height;

	SetConsoleScreenBufferSize(hStdout, NewSize);
}

void DisableResizeWindow() {
	HWND hWnd = GetConsoleWindow();
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void DisableCtrButton(bool Close, bool Min, bool Max) {
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);

	if (Close == 1) {
		DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
	}
	if (Min == 1) {
		DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	}
	if (Max == 1) {
		DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	}
}

void createBox(int x, int y, int w, int h, int text_color, int back_color, string text) {
	SetColor(text_color);

	if (h <= 1 || w <= 1) return;

	int y_text = y + 1;
	int x_text = x + (w - text.size() - 1) / 2 + 1;
	gotoxy(x_text, y_text);
	cout << text;

	for (int ix = x; ix <= x + w; ix++) {
		gotoxy(ix, y); cout << (char)196;
		gotoxy(ix, y + h); cout << (char)196;
	}

	for (int iy = y; iy <= y + h; iy++) {
		gotoxy(x, iy); cout << (char)179;
		gotoxy(x + w, iy); cout << (char)179;
	}

	gotoxy(x, y); cout << (char)218;
	gotoxy(x + w, y); cout << (char)191;
	gotoxy(x, y + h); cout << (char)192;
	gotoxy(x + w, y + h); cout << (char)217;
}

void createTextBar(int x, int y, int w, int h, int text_color, int back_color, string text) {
	SetColor2(back_color, text_color);
	int y_text = y + 1;
	int x_text = x + (w - text.size() - 1) / 2 + 1;
	gotoxy(x_text, y_text);
	cout << text;
}

void createHighlightBar(int x, int y, int w, int h, int color, string text) {
	SetColor3(color);
	string new_text = "";
	for (int i = 1; i <= (w - text.size() - 1) / 2; i++) {
		new_text += " ";
	}
	new_text += text;
	for (int i = 1; i <= (w - text.size()) / 2; i++) {
		new_text += " ";
	}
	int y_text = y;
	int x_text = x + 1;
	gotoxy(x_text, y_text);
	cout << new_text;
}

void showTitle(string filename, int x, int y) {
	SetConsoleOutputCP(65001);

	fstream ifile;
	ifile.open(filename, ios::in);

	if (!ifile.is_open()) {
		cout << "Cannot open the text file!\n";
		return;
	}

	int i = 0;
	while (!ifile.eof()) {
		string line;
		getline(ifile, line);
		gotoxy(x, y + i);
		cout << line;
		++i;
	}

	ifile.close();
	SetConsoleOutputCP(437);
}