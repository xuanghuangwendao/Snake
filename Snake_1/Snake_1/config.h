#pragma once

#include <Windows.h>
using namespace std;
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;
//���ع��
void hide()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);
}
//��궨λ
void locate(int x, int y)
{
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(hout, coord);
};

#define ERROR_CONFIG cout<<"�������ô���"<<endl;
#define EXIT_WAIT_Q cout<<"������Q�˳���"<<endl;
#define REDO_WAIT_R cout<<"������R���ԡ�"<<endl;
#define REDO_WAIT_ELSE cout<<"���������������ԡ�"<<endl;
#define pii(x,y) pair<int,int>(x,y)

//��ʼ����
int size_x;
int size_y;
int dif_map, dif_speed;
int dif;
bool dif_add;


