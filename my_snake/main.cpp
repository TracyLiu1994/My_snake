#include<iostream>
#include<string>
#include<list>
#include<cstdlib>//可以产生随机数
#include<windows.h>//可以获得控制台的坐标
#include<conio.h>//输入键值
using namespace std;

//定义地图类
class Map
{
public:
	Map();
	void food();
	void print();
	void start();
	void game();
	~Map();

private:
	string ma[15];//地图边界
	COORD gg;
	list <COORD> snake;//蛇
	int direction;//保存方向

};

//类的成员函数，实时更新地图
void Map::print() {
	for (int i = 0; i<15; i++)
		cout << ma[i] << endl;

}

//产生食物
void Map::food() {
	int x = 0 + rand() % 14;
	int y = 0 + rand() % 34;
	ma[x][y] = '*';
}

//开始游戏
void Map::start() {
	print();
	COORD coord;
	coord.X = 13;
	coord.Y = 8;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "按任意键开始";
	while (!_kbhit());
	game();
}

//蛇体的更新
void Map::game() {
	food();
	bool flag;
	int ch = 72;//起始方向为上
	while (1) {
		flag = _kbhit();
		if (flag) {
			int direction_;
			ch = _getch();
			switch (ch)
			{
			case 72:
				direction_ = 1;
				break;//上
			case 75:
				direction_ = 3;
				break;//左
			case 80:
				direction_ = 4;
				break;//下
			case 77:
				direction_ = 2;
				break;//右
			default:
				direction_ = 0;
			}
			if (direction_ != 0)
				direction = direction_;
		}
		switch (direction)
		{
		case 1:gg.X = snake.front().X - 1; gg.Y = snake.front().Y; break;
		case 2:gg.X = snake.front().X; gg.Y = snake.front().Y + 1; break;
		case 3:gg.X = snake.front().X; gg.Y = snake.front().Y - 1; break;
		case 4:gg.X = snake.front().X + 1; gg.Y = snake.front().Y; break;
		}
		//碰到墙壁或者蛇身
		if (ma[gg.X][gg.Y] == '#' || ma[gg.X][gg.Y] == '@') {
			COORD coord;
			coord.X = 3;
			coord.Y = 8;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			cout << "游戏结束";
			Sleep(300);
			break;
		}
		//吃到食物
		else if (ma[gg.X][gg.Y] == '*') {
			ma[snake.front().X][snake.front().Y] = '@';
			snake.push_front(gg);
			ma[snake.front().X][snake.front().Y] = '@';
			if (snake.size() == 50)
			{
				COORD coord; coord.X = 3; coord.Y = 8;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				cout << "YOU SUCCESS !";
				Sleep(300);
				break;
			}
			food();
		}
		//没有吃到食物的移动
		else
		{
			ma[snake.front().X][snake.front().Y] = '@';
			snake.push_front(gg);
			ma[snake.front().X][snake.front().Y] = '@';
			ma[snake.back().X][snake.back().Y] = ' ';
			snake.pop_back();
			Sleep(300);
		}
		system("cls");
		print();
	}
}

//类的构造函数,初始化地图
Map::Map()
{
	for (int i = 0; i<15; i++)
	{
		if (i == 0 || i == 14)
			ma[i] = "###################################";
		else
			ma[i] = "#                                 #";
	}
	gg.X = 10; gg.Y = 5;//X是控制台的竖着的方向，Y是控制台的横着的方向。
	snake.push_front(gg);
	direction = 1;
}

Map::~Map()
{
}

//主函数
void main() {
	Map play;
	play.start();
	system("pause");
}