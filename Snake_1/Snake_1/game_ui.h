#pragma once
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <time.h>
#include "Snake.h"
using namespace std;
bool game_default();
bool game_user_define();
bool game_begin_ui();
bool game_begin();
void game_init();
void game_run();
pii random();
pii get_blank();
void print_info();
int game_end();