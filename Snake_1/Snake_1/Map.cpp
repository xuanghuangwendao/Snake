#include "Map.h"

#include <windows.h>
#include <iostream>
using namespace std;


void static locate(int x, int y)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(hout, coord);
};



Map::Map(int n, int m, int dif)
{
	this->n = n;
	this->m = m;
	this->dif = dif;
	set_border();
	//set_wall();
}

bool Map::set_border()
{
	for (int i = 2; i <= n + 3; i++) {
		locate(i, 2);
		wall.insert(pair<int, int>(i, 2));
		cout << '#'; 
		locate(i, m + 3);
		wall.insert(pair<int, int>(i, m + 3));
		cout << '#';
		
	}
	for (int j = 2; j <= m + 3; j++) {
		locate(2, j);
		wall.insert(pair<int, int>(2, j));
		cout << '#'; 
		locate(n + 3, j);
		wall.insert(pair<int, int>(n+3, j));
		cout << '#';
		}
	return false;
}

bool Map::is_correct(int x, int y)
{
	if (wall.count(pair<int, int>(x, y)) == 1) {
		locate(x, y);
		cout << "X";
		return false;
	}
	else
		return true;
}
