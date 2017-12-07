#include<iostream>
#include<string>
#include<list>
#include<cstdlib>//���Բ��������
#include<windows.h>//���Ի�ÿ���̨������
#include<conio.h>//�����ֵ
using namespace std;

//�����ͼ��
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
	string ma[15];//��ͼ�߽�
	COORD gg;
	list <COORD> snake;//��
	int direction;//���淽��

};

//��ĳ�Ա������ʵʱ���µ�ͼ
void Map::print() {
	for (int i = 0; i<15; i++)
		cout << ma[i] << endl;

}

//����ʳ��
void Map::food() {
	int x = 0 + rand() % 14;
	int y = 0 + rand() % 34;
	ma[x][y] = '*';
}

//��ʼ��Ϸ
void Map::start() {
	print();
	COORD coord;
	coord.X = 13;
	coord.Y = 8;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "���������ʼ";
	while (!_kbhit());
	game();
}

//����ĸ���
void Map::game() {
	food();
	bool flag;
	int ch = 72;//��ʼ����Ϊ��
	while (1) {
		flag = _kbhit();
		if (flag) {
			int direction_;
			ch = _getch();
			switch (ch)
			{
			case 72:
				direction_ = 1;
				break;//��
			case 75:
				direction_ = 3;
				break;//��
			case 80:
				direction_ = 4;
				break;//��
			case 77:
				direction_ = 2;
				break;//��
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
		//����ǽ�ڻ�������
		if (ma[gg.X][gg.Y] == '#' || ma[gg.X][gg.Y] == '@') {
			COORD coord;
			coord.X = 3;
			coord.Y = 8;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			cout << "��Ϸ����";
			Sleep(300);
			break;
		}
		//�Ե�ʳ��
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
		//û�гԵ�ʳ����ƶ�
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

//��Ĺ��캯��,��ʼ����ͼ
Map::Map()
{
	for (int i = 0; i<15; i++)
	{
		if (i == 0 || i == 14)
			ma[i] = "###################################";
		else
			ma[i] = "#                                 #";
	}
	gg.X = 10; gg.Y = 5;//X�ǿ���̨�����ŵķ���Y�ǿ���̨�ĺ��ŵķ���
	snake.push_front(gg);
	direction = 1;
}

Map::~Map()
{
}

//������
void main() {
	Map play;
	play.start();
	system("pause");
}