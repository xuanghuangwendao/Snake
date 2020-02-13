#include "game_ui.h"
#include "config.h"
#include "Map.h"
#include "Food.h"
Snake* snake;
Map* game_map;
Food* food;
clock_t time_begin = clock();
clock_t time_now = clock();
const int time_inv = 500;
int now_speed;
int level;
int time_game;

//Map* map;
bool game_default() {
	size_x = 20;
	size_y = 20;
	dif_map = 1;
	dif_speed = 1;
	dif_add = true;
	return true;
}

bool game_user_define() {

	char dif_add_c;
	string s;
	system("cls");
	std::cout << "请设置游戏参数：" << endl;
	cout << "请输入地图长度(10-50)：";
	cin >> s;
	size_x = atoi(s.c_str());
	if (size_x < 10 || size_x > 50) {
		cout<<"参数配置失败！";
		system("pause");
		return false;
	}
	cout << "请输入地图宽度(10-100)：";
	cin >> s;
	size_y = atoi(s.c_str());
	if (size_y < 10 || size_y > 100) {
		cout << "参数配置失败！";
		system("pause");
		return false;
	}
	cout << "请输入地图难度（1-10）：";
	cin >> s;
	dif_map = atoi(s.c_str());
	if (dif_map < 1 || dif_map > 10) {
		cout << "参数配置失败！";
		system("pause");
		return false;
	}
	cout << "请输入游戏速度（1-10）：";
	cin >> s;
	dif_speed = atoi(s.c_str());
	if (dif_speed < 1 || dif_speed > 10) {
		cout << "参数配置失败！";
		system("pause");
		return false;
	}
	cout << "是否采用递增难度？（Y/N）：";
	cin >> dif_add_c;
	if (dif_add_c == 'Y' || dif_add_c == 'y') {
		dif_add = true;
	}
	else if (dif_add_c == 'N' || dif_add_c == 'n') {
		dif_add = false;
	}
	else {
		cout << "参数配置失败！";
		system("pause");
		return false;
	}

	cout << "参数配置成功！";
	system("pause");
	return true;

}
bool game_begin_ui()
{
	system("cls");
	locate(2, 0);
	cout << "**********贪吃蛇**********" << endl;
	cout << endl;
	cout << "1:默认游戏" << endl;
	cout << "2:自定义游戏" << endl;
	cout << "3:退出" << endl;
	return true;
}

bool game_begin()
{
	hide();
	while (1) {
		game_begin_ui();
		char c = _getch();
		if (c == '1') {
			game_default();
			break;
		}
		else if (c == '2') {
			if (!game_user_define()) {
				return false;
			}
			break;
		}
		else if (c == '3') {
			return false;
		}
		else {
			continue;
		}
	}
	
	return true;
}

void game_init() {
	snake = new Snake(size_x / 2, size_y / 2,2);
	game_map = new Map(size_x, size_y, true, dif_map);
	food = new Food(size_x + size_y);
	while (!game_map->complete_wall() ) {
		game_map->create_wall(get_blank());
	}
	food->create_food(get_blank());

}

void game_run() {
	system("cls");
	level = 0;
	time_game = 0;
	unsigned seed = time(0);
	srand(seed);
	game_init();
	time_begin = clock();
	now_speed = dif_speed;
	clock_t a, b;
	while (1) {
		print_info();
		a = clock();
		time_now = clock();
		
		if (dif_add && (time_now - time_begin) / 20000 > level) {
			level++;
			now_speed = min(now_speed +1, 10);
			game_map->add_dif();
			while (!game_map->complete_wall()) {
				game_map->create_wall(get_blank());
			}
		}
		char c = ' ';
		while (1) {
			b = clock();
			if ((b - a) > time_inv/(1.0+ now_speed /5.0)) {
				break;
			}
		}
		while (_kbhit()) {
			c = _getch();
			if (c == '1') {
				locate(size_x + 3, 0);
				system("Pause");
			}
			else if (c == '2' ) {
				locate(size_x + 3, 0);
				return;
			}
			snake->set_dir(c);
		}
		if (!snake->move()) {
			break;
		}

		pii head = snake->get_head();
		locate(1, 23);
		if (food->is_food(head)) {
			snake->eat_food();
			snake->add_score(now_speed * game_map->get_dif() * 10);
			food->create_food(get_blank());
		}
		if (food->update()) {
			food->create_food(get_blank());
		}
		if (!game_map->check(head)) {
			break;
		}
		snake->add_score(now_speed* game_map->get_dif());
		time_game++;
		locate(size_x + 3, 0);
		cout << "                                   ";

	}


}

pii random()
{
	pii ran_point;
	ran_point.first = rand() % size_x + 1;
	ran_point.second = rand() % size_y + 1;
	return ran_point;
}

pii get_blank()
{
	pii tmp;
	while (1) {
		tmp = random();
		if (snake->is_blank(tmp) && game_map->is_blank(tmp) && !food->is_food(tmp)) {
			break;
		}
	}
	return tmp;
}

void print_info()
{
	int line = 1;
	int row = size_y + 3;
	locate(line++, row);
	cout << "      |贪~吃~蛇|";
	locate(line++, row);
	cout << "---------------------";
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "初始游戏速度:" << dif_speed;
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "当前游戏速度:" << now_speed;
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "初始地图难度:" << dif_map;
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "当前地图难度:" << game_map->get_dif();
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "---------------------";
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "当前蛇的长度:" << snake->get_len();
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "当前游戏时间:" << time_game;
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "当前蛇的位置:(" << snake->get_head().first << "," << snake->get_head().second << ")";
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "当前食物位置:(" << food->get_food().first << "," << food->get_food().second << ")";
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "当前食物剩余时间:" << food->get_time();

	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "---------------------";
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "当前得分" << snake->get_score();
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "---------------------";
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "1:暂停";
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "2:结束";
	locate(line++, row);
	cout << "                     |";
	locate(line - 1, row);
	cout << "---------------------";
	


}

int game_end()
{
	locate(size_x / 2, size_y / 2 - 2);
	cout << "游戏结束！";
	locate(size_x / 2 + 1, size_y / 2 - 3);
	cout << "最终得分：" << snake->get_score();
	locate(size_x / 2 + 2, size_y / 2 - 3);
	cout << "1:返回主界面";
	locate(size_x / 2 + 3, size_y / 2 - 3);
	cout << "2:重新开始";
	locate(size_x / 2 + 4, size_y / 2 - 3);
	cout << "3:退出";
	locate(size_x + 3, 0);
	char c;
	while (1) {
		c = _getch();
		if (c == '1') {
			return 1;
		}
		else if (c == '2') {
			return 2;
		}
		else if (c == '3') {
			return 3;
		}
		else {

		}
	}

}
