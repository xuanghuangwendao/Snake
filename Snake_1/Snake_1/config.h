#pragma once
#include <windows.h>
#include <iostream>
using namespace std;


HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

void hide()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);
}


void locate(int x, int y)
{
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(hout, coord);
};

