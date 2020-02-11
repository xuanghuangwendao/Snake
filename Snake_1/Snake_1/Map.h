#pragma once
#include <set>
#include <Windows.h>
#include <iostream>
#include <ctime>


using namespace std;

class Map
{
private:
	int n, m;
	int dif;
public:
	set<pair<int, int>> wall;
	Map(int n,int m, int dif);
	bool set_border();
	bool set_wall();
	bool is_correct(int x, int y);
};

