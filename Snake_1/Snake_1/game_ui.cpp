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
	dif_map = 0;
	dif_speed = 0;
	dif_add = true;
	return true;
}

bool game_user_define() {

	system("cls");
	cout << "��������Ϸ������" << endl;
	char dif_add_c;
	cout << "�������ͼ���ȣ�";
	cin >> size_x;
	cout << "�������ͼ��ȣ�";
	cin >> size_y;
	cout << "�������ͼ�Ѷȣ�0-10����";
	cin >> dif_map;
	cout << "��������Ϸ�ٶȣ�0-10����";
	cin >> dif_speed;
	cout << "�Ƿ���õ����Ѷȣ���Y/N����";
	cin >> dif_add_c;
	if (size_x > 10 && size_x < 50 &&
		size_y>10 && size_y < 50 &&
		dif_map >= 0 && dif_map <= 10 &&
		dif_speed >= 0 && dif_speed <= 10 &&
		(dif_add_c == 'Y' || dif_add_c == 'y' ||
			dif_add_c == 'N' || dif_add_c == 'n')) {
		if (dif_add_c == 'Y' || dif_add_c == 'y') {
			dif_add = true;
		}
		else {
			dif_add = false;
		}
		cout << "�������óɹ���" << endl;
		system("Pause");
		return true;
	}
	else {

		cout << "��������ʧ�ܣ�" << endl; 
		system("Pause");
		return false;
	}
	
}
bool game_begin_ui()
{
	system("cls");
	locate(2, 0);
	cout << "**********̰����**********" << endl;
	cout << endl;
	cout << "1:Ĭ����Ϸ" << endl;
	cout << "2:�Զ�����Ϸ" << endl;
	cout << "3:�˳�" << endl;
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
	food = new Food();
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
			now_speed = min(now_speed, 10);
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
	cout << "|̰~��~��|";
	locate(line++, row);
	cout << "��ʼ��Ϸ�ٶ�:" << dif_speed;
	locate(line++, row);
	cout << "��ǰ��Ϸ�ٶ�:" << now_speed;
	locate(line++, row);
	cout << "��ʼ��ͼ�Ѷ�:" << dif_map;
	locate(line++, row);
	cout << "��ǰ��ͼ�Ѷ�:" << game_map->get_dif();
	locate(line++, row);
	locate(line++, row);
	cout << "��ǰ�ߵĳ���" << snake->get_len();
	locate(line++, row);
	cout << "��ǰʱ��" << time_game;
	locate(line++, row);
	locate(line++, row);
	cout << "��ǰ�÷�" << snake->get_score();
	locate(line++, row);
	locate(line++, row);
	cout << "1:��ͣ";
	locate(line++, row);
	cout << "2:����";
	locate(line++, row);
	


}

int game_end()
{
	locate(size_x / 2, size_y / 2 - 2);
	cout << "��Ϸ������";
	locate(size_x / 2 + 1, size_y / 2 - 3);
	cout << "���յ÷֣�" << snake->get_score();
	locate(size_x / 2 + 2, size_y / 2 - 3);
	cout << "1:����������";
	locate(size_x / 2 + 3, size_y / 2 - 3);
	cout << "2:���¿�ʼ";
	locate(size_x / 2 + 4, size_y / 2 - 3);
	cout << "3:�˳�";
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
