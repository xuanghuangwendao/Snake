#include "Food.h"
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

Food::Food(int max_time)
{
	this->max_time = max_time;
}

Food::~Food()
{
}

void Food::create_food(pii point)
{
	locate(point.first, point.second);
	cout << "F";
	food = point;
	time = max_time;

}

bool Food::is_food(pii now)
{
	locate(2, 23);
	if (now == food) {
		return true;
	}
	else {
		return false;
	}
}

bool Food::update()
{
	time--;
	if (time == 0) {
		locate(food.first, food.second);
		cout << ' ';
		return true;
	}
	else {
		return false;
	}
}

void Food::set_max_time(int time)
{
	max_time = time;
}

pii Food::get_food()
{
	return food;
}

int Food::get_time()
{
	return time;
}
