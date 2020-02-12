#pragma once

#include <Windows.h>
#include <iostream>
#include <set>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
#define pii(x,y) pair<int,int>(x,y)
class Snake
{
private:
	set<pii> body;
	queue<pii> body_q;
	pii head;
	pii head_last;
	int score;
	int length;
	int direction;//1���� 2���� 3���� 4����
	int state;//1:�Ե�ʳ�� 2��û�гԵ�ʳ�� 3:����
	void init_body(int len);

public:
	Snake(int x, int y, int len = 2, int dir = 1);

	bool move();
	bool check();
	void set_dir(int dir);
	void set_dir(char dir);
	int get_score();
	int get_len();
	void eat_food();
	pii get_head();
	bool is_blank(pii point);
	void add_score(int score);
	~Snake();
	
};
