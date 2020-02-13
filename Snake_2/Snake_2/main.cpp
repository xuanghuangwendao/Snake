#include <iostream>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <queue>
#include <mutex>
using namespace std;
#define pii(a,b) pair<int, int>(a,b)
typedef pair<int, int> pii;
const int maxn = 100;
std::mutex mtx;
/*
线程1：获取键盘信息
线程2：获取时间信息
线程3：监视创建食物
线程3：显示游戏信息
*/

int direction;//方向：1:上 2:下 3:左 4:右
int state;//状态：1:未获得食物 2:获得食物 3:暂停 4: 死亡
queue<pii> snake;//蛇身
pii head;//蛇头
int m_x, m_y;//地图大小
int _time;//时间
int score;//分数
bool need_food;//是否需要创建食物
char mp[maxn][maxn];//地图映射

//光标操作
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;
//隐藏光标
void hide()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);
}
//定位光标
void locate(int x, int y)
{
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(hout, coord);
};

//创建围墙
void create_wall() {
	locate(0, 0);
	for (int i = 0; i <= m_x + 1; i++) {
		locate(i, 0);
		cout << "#";
		mp[i][0] = '#';
		locate(i, m_y + 1);
		cout << "#";
		mp[i][m_y + 1] = '#';
	}
	for (int j = 0; j <= m_y; j++) {
		locate(0, j);
		cout << "#";
		mp[0][j] = '#';
		locate(m_x + 1, j);
		cout << "#";
		mp[m_x + 1][j] = '#';
	}
}
//创建食物
void create_food() {
	int x, y;
	while (1) {
		x = rand() % m_x + 1;
		y = rand() % m_y + 1;
		if (mp[x][y] != 'O' && mp[x][y] != '#' && mp[x][y] != 'A' && mp[x][y] != 'F') {
			mp[x][y] = 'F';
			mtx.lock();
			locate(x, y);
			cout << "F";
			mtx.unlock();
			break;
		}
	}
}

//初始化
void init() {
	hide();
	unsigned seed = time(0);
	srand(seed);
	score = 0;
	direction = 1;
	state = 1;
	m_x = 15;
	m_y = 20;
	create_wall();
	head.first = m_x / 2;
	head.second = m_y / 2;
	locate(head.first, head.second);
	cout << "A";
	mp[head.first][head.second] = 'A';
	pii tmp(m_x / 2 + 1, m_y / 2);
	locate(tmp.first, tmp.second);
	cout << "O";
	snake.push(tmp);
	mp[tmp.first][tmp.second] = 'O';
	create_food();
	need_food = false;
}

void read() {

	char key;
	while (1) {
		if (state == 4) {
			break;
		}
		while (_kbhit()) {
			key = _getch();
			if (key == 72) {
				if(direction != 2)
					direction = 1;
			}
			else if (key == 80) {
				if (direction != 1)
					direction = 2;
			}
			else if (key == 75) {
				if (direction != 4)
					direction = 3;
			}
			else if (key == 77) {
				if (direction != 3)
					direction = 4;
			}
			else if (key == '1') {
				state = 3;
			}
			else if (key == '2') {
				state = 4;
			}
		}
	}
}

void update() {
	clock_t a, b;
	pii next;
	while (1) {
		if (state == 4) {
			break;
		}
		if (state == 3) {
			mtx.lock();
			locate(m_x + 3, 0);
			system("Pause");
			mtx.unlock();
		}
		a = clock();
		while (1) {
			b = clock();
			if (b - a > 500) {
				break;
			}
		}
		next = head;

		if (direction == 1) {
			next.first--;
		}
		else if (direction == 2) {
			next.first++;
		}
		else if (direction == 3) {
			next.second--;
		}
		else if (direction == 4) {
			next.second++;
		}
		if (state == 1) {
			mtx.lock();
			locate(snake.front().first, snake.front().second);
			cout << ' ';
			mtx.unlock();
			mp[snake.front().first][snake.front().second] = ' ';
			snake.pop();
		}
		else if (state == 2) {
			state = 1;
		}
		mtx.lock();
		locate(head.first, head.second);
		cout << 'O';
		mtx.unlock();
		mp[head.first][head.second] = 'O';
		snake.push(head);
		head = next;
		char now_c = mp[next.first][next.second];
		mtx.lock();
		locate(head.first, head.second);
		if (now_c == 'F') {
			state = 2;
			score++;
			need_food = true;
			cout << 'A';
		}
		else if (now_c == 'O' || now_c == '#') {
			state = 4;
			cout << 'X';
		}
		else {
			cout << 'A';
		}
		mtx.unlock();
		_time++;
	}


}
void monitor_food() {
	while (1) {
		if (state == 4) {
			break;
		}
		if (need_food) {
			need_food = false;
			create_food();
		}

	}
}
void info() {
	while (1) {
		if (state == 4) {
			break;
		}
		mtx.lock();
		locate(m_x + 2, 0);
		cout << "分数：" << score << "    |  时间：" << _time << endl;
		mtx.unlock();
	}

}
int main() {
	
	init();
	thread t1(read);
	thread t2(update);
	thread t3(monitor_food);
	thread t4(info);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	locate(m_x + 3, 0);
	system("Pause");
}