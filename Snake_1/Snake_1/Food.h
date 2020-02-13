#pragma once
#include <windows.h>
#include <iostream>
#include <time.h>
using namespace std;
typedef pair<int, int> pii;
#define pii(x,y) pair<int,int>(x,y)
class Food
{
private:
	pii food;
	int time;
	int max_time;

public:
	Food(int max_time = -1);
	~Food();
	void create_food(pii point);
	bool is_food(pii now);
	bool update();
	void set_max_time(int time);
	pii get_food();
	int get_time();
};

