#include "Snake.h"
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

Snake::Snake(int x, int y, int dir)
{
	head.x = x;
	head.y = y;
	score = 0;
	length = 1;
	direction = dir;
	state = 0;
	body_s.insert(pair<int,int>(x,y));
}

Snake::~Snake()
{

}

int Snake::get_score()
{
	return score;
}

int Snake::get_len()
{
	return length;
}

int Snake::get_direction()
{
	return direction;
}

int Snake::get_state()
{
	return state;
}

pair<int, int> Snake::get_head()
{
	locate(head.x, head.y);
	cout << "A";
	if (body_s.size() != 0) {
		locate(head_last.x, head_last.y);
		cout << "O";

	}
	return pair<int, int>(head.x, head.y);

}

pair<int, int> Snake::get_tail()
{
	if (!body.empty() && state == 0) {
		pair<int, int> tail = pair<int, int>(body.front().x, body.front().y);
		body_s.erase(tail);
		body.pop();
		return tail;
	}
	else {
		state = 0;
		return pair<int, int>(-1, -1);

	}

}

bool Snake::eat_food()
{
	state = 1;
	length++;
	score++;
	return false;
}

void Snake::next()
{

	Point p_next;
	if (direction == 1) {
		p_next.x = head.x - 1;
		p_next.y = head.y;
	}
	else if (direction == 2) {
		p_next.x = head.x + 1;
		p_next.y = head.y;

	}
	else if (direction == 3) {
		p_next.x = head.x;
		p_next.y = head.y - 1;

	}
	else if (direction == 4) {
		p_next.x = head.x;
		p_next.y = head.y + 1;

	}
	body.push(head);
	head_last = head;
	body_s.insert(pair<int, int>(head.x, head.y));
	head = p_next;

	pair<int, int> tail = get_tail();
	if (tail.first != -1) {
		locate(tail.first, tail.second);
		cout << ' ';
	}
}

bool Snake::set_dir(int dir)
{
	if ((dir+1) / 2 == (this->direction + 1) / 2) {
		return false;
	}
	else {
		this->direction = dir;
		return true;
	}
}

bool Snake::is_correct()
{
	locate(20, 20);
	if (body_s.count(pair<int, int>(head.x, head.y)) == 1) {
		locate(head.x, head.y);
		cout << "X"; 
		return false;
	}

	return true;
}
