#pragma once

#include <vector>
#include <queue>
#include <set>
using namespace std;
struct Point {
	int x, y;
};
class Snake
{
private:
	queue<Point> body;
	Point head;
	Point head_last;
	int score;
	int length;
	int direction;
	int state;

public:
	Snake(int x, int y, int dir);
	~Snake();
	set<pair<int,int>> body_s;
	int get_score();
	int get_len();
	int get_direction();
	int get_state();
	pair<int, int> get_head();
	pair<int, int> get_tail();
	bool eat_food();
	void next();
	bool set_dir(int dir);
	bool is_correct();
};

