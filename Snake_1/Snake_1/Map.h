#pragma once
#include <set>
#include <map>
#include <windows.h>
#include <iostream>
#include <time.h>
using namespace std;
typedef pair<int, int> pii;
#define pii(x,y) pair<int,int>(x,y)
class Map
{
private:
	int x, y;
	int dif;
	int number_wall;
	set<pii> border;
	map<pii, int> wall;
	int time;


public:
	Map(int x,int y,bool has_border = true, int dif = 0);
	~Map();
	void init_border();
	void create_wall(pii point);
	bool check(pii now);
	bool is_blank(pii point);
	bool complete_wall();
	void add_dif();
	int get_dif();
};

