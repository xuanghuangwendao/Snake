#pragma once

#include <Windows.h>
using namespace std;
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;
//隐藏光标
void hide()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);
}
//光标定位
void locate(int x, int y)
{
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(hout, coord);
};

#define ERROR_CONFIG cout<<"参数配置错误！"<<endl;
#define EXIT_WAIT_Q cout<<"请输入Q退出。"<<endl;
#define REDO_WAIT_R cout<<"请输入R重试。"<<endl;
#define REDO_WAIT_ELSE cout<<"请输入其他键重试。"<<endl;
#define pii(x,y) pair<int,int>(x,y)

//初始参数
int size_x;
int size_y;
int dif_map, dif_speed;
int dif;
bool dif_add;


