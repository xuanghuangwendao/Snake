#include "Snake.h"
#include <Windows.h>
using namespace std;
void static locate(int x, int y)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(hout, coord);
};
void Snake::init_body(int len)
{
	pii tmp_body;
	for(int i=len-1;i>0;i--)
	{
		tmp_body.first = head.first + i;
		tmp_body.second = head.second;
		body.insert(tmp_body);
		if (i == 1) {
			head_last = tmp_body;
		}
		body_q.push(tmp_body);
		locate(tmp_body.first, tmp_body.second);
		cout << "O";
	}
}

Snake::Snake(int x, int y, int len, int dir)
{
	head.first = x;
	head.second = y;
	init_body(len);
	body_q.push(head);
	this->length = len;
	this->direction = dir;
	this->score = 0;
	this->state = 2;
	locate(x, y);
	cout << "A";
}

bool Snake::move()
{
	pii new_head = head;
	if (direction == 1) {
		new_head.first--;
	}
	else if (direction == 2) {
		new_head.first++;
	}
	else if (direction == 3) {
		new_head.second--;
	}
	else if (direction == 4) {
		new_head.second++;
	}
	head_last = head;
	body.insert(head);
	if (state == 1) {
		length++;
		state = 2;
	}
	else if (state == 2) {
		pii tail = body_q.front();
		body.erase(tail);
		body_q.pop();
		locate(tail.first, tail.second);
		cout << " ";
	}
	else {
		return false;
	}
	locate(head.first, head.second);
	cout << "O";
	head = new_head;
	locate(head.first, head.second);
	cout << "A";
	body_q.push(head);
	if (check()) {
		return true;
	}
	else {
		
		locate(head.first, head.second);
		cout << "X";
		return false;
		
	}
}

bool Snake::check()
{
	if (body.count(head) == 1) {
		state = 3;
		return false;
	}
	return true;
}


void Snake::set_dir(int dir)
{
	this->direction = dir;
	
}

void Snake::set_dir(char dir)
{	
	int new_dir = direction;
	if (dir == 72) {
		new_dir = 1;
	}
	else if (dir == 80) {
		new_dir = 2;
	}
	else if (dir == 75) {
		new_dir = 3;
	}
	else if (dir == 77) {
		new_dir = 4;
	}
	if ((new_dir + 1) / 2 != (direction + 1) / 2) {
		direction = new_dir;
	}
}


int Snake::get_score()
{
	return score;
}

int Snake::get_len()
{
	return length;
}

void Snake::eat_food()
{
	this->state = 1;
}

pii Snake::get_head()
{
	return head;
}

bool Snake::is_blank(pii point)
{
	if (body.count(point) == 1 || point == head) {
		return false;
	}
	return true;
}

void Snake::add_score(int score)
{
	this->score += score;
}

Snake::~Snake()
{
}

