#include "Map.h"

void static locate(int x, int y)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(hout, coord);
};
Map::Map(int x, int y, bool has_border, int dif)
{
	this->x = x;
	this->y = y;
	this->dif = dif;
	this->number_wall = 0;
	if (has_border) {
		init_border();
	}
}

Map::~Map()
{

}

void Map::init_border()
{
	locate(0, 0);
	for (int i = 0; i <= x+1; i++) {
		locate(i, 0);
		border.insert(pii(i,0));
		cout << "#";
		locate(i, y+1);
		border.insert(pii(i, y + 1));
		cout << "#";
	}
	for (int j = 0; j <= y; j++) {
		locate(0, j);
		border.insert(pii(0, j));
		cout << "#";
		locate(x+1, j);
		border.insert(pii(x + 1, j));
		cout << "#";
	}

}

void Map::create_wall(pii point)
{
	locate(point.first, point.second);
	cout << "#";
	wall[point] = time;
	number_wall++;
}

bool Map::check(pii now)
{
	if (border.count(now) == 1 || wall.count(now) == 1) {
		locate(now.first, now.second);
		cout<<"X";
		return false;
	}
	else {
		return true;
	}
}

bool Map::is_blank(pii point)
{
	if (border.count(point) == 1 || wall.count(point) == 1) {
		
		return false;
	}
	else {
		return true;
	}
}

bool Map::complete_wall()
{
	double now_dif = 50.0 * number_wall / (x * y);
	if (now_dif < dif) {
		return false;
	}
	else{
		return true;
	}
}

void Map::add_dif()
{
	dif = min(dif + 1, 10);
}

int Map::get_dif()
{

	return dif;
}

