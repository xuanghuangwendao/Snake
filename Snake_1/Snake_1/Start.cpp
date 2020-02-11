
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cmath>
#include "Map.h"
#include "Snake.h"
using namespace std;

HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;
pair<int, int>food;
int n, m;

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



pair<int, int> random()
{
	unsigned seed = time(0);
	srand(seed);
	pair<int, int> ran_point;
	ran_point.first = rand() % n + 3;
	ran_point.second = rand() % m + 3;
	return ran_point;
}

bool is_food(pair<int,int> now) {
	if (now.first == food.first && now.second == food.second) {
		return true;
	}
	else {
		return false;
	}

}
int main()
{
	hide();
	cin >> n >> m;
	int dir = 3;
	system("cls");
	Snake snake(2 + n / 2, 2 + m / 2, dir);
	Map mp(n, m, 1);
	while (1) {
		food = random();
		if (snake.body_s.count(food) == 0 && mp.wall.count(food) == 0 && food != snake.get_head()) {
			break;
		}
	}
	locate(food.first, food.second);
	cout << "F";
	pair<int, int> now = snake.get_head();

	while (1) {
		locate(n + 4, 1);
		cout << "ÄúµÄµÃ·Ö£º" << snake.get_score() << endl;
		clock_t a, b;
		a = clock();
		char c = ' ';
		while (1) {
			b = clock();
			if (b - a > 500) {
				break;
			}
		}
		while (_kbhit()) {
			c = _getch();
			switch (c)
			{
			case 72:
				dir = 1;
				break;
			case 80:
				dir = 2;
				break;
			case 75:
				dir = 3;
				break;
			case 77:
				dir = 4;
				break;
			default:
				break;
			}

		}
		snake.set_dir(dir);
		
		
		if (is_food(now)) {

			snake.eat_food();
			
			while (1) {
				food = random();
				if (snake.body_s.count(food) == 0 && mp.wall.count(food) == 0 && food != snake.get_head()) {
					break;
				}
			}
			locate(food.first, food.second);
			cout << "F";
			

		}
		
		
		snake.next();
		now = snake.get_head();
		if (!mp.is_correct(now.first, now.second) ||
			!snake.is_correct()) {

			break;
		}

	}
	locate(n+4, m+4);
	system("Pause");
	return 0;

}