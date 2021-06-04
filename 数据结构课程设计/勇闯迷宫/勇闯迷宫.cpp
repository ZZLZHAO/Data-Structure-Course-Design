#include <iostream>
#include <iomanip>
#include <time.h>
#include <Windows.h>
using namespace std;
int m = 50, p = 50;
struct offsets {
	int a, b;
	char* dir;
};
struct rec{
	int a, b;
	struct rec* link;
};
char a[4][2] = { "N","E","S","W" };
offsets movedir[8] = { {-1,0,a[0]}, {0,1,a[1]},{1,0,a[2]},{0,-1,a[3]} };
rec record, * current;
int** Maze = new int* [m + 2];
int** mark = new int* [m + 2];
int SeekPath(int x, int y)
{
	int i, g, h;
	char* dir;
	if (x == m && y ==p)
		return 1;
	for (i = 0; i < 8; i++)
	{
		g = x + movedir[i].a;
		h = y + movedir[i].b;
		dir = movedir[i].dir;
		if (Maze[g][h] == 0 && mark[g][h] == 0)
		{
			mark[g][h] = 1;
			if (SeekPath(g, h))
			{
				Maze[g][h] = 2;
				rec* newNode = new rec;
				if (newNode == NULL)
				{
					cout << "申请内存失败" << endl;
					exit(-1);
				}
				newNode->a = g;
				newNode->b = h;
				newNode->link = NULL;
				current->link = newNode;
				current = current->link;
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	if (Maze == NULL || mark == NULL)
	{
		cout << "申请内存失败" << endl;
		exit(-1);
	}
	int i, j;
	for (i = 0; i < m + 2; i++)
	{
		Maze[i] = new int[p + 2];
		if (Maze[i] == NULL)
		{
			cout << "申请内存失败" << endl;
			exit(-1);
		}
		mark[i] = new int[p + 2];
		if (mark[i] == NULL)
		{
			cout << "申请内存失败" << endl;
			exit(-1);
		}
	}
	record.link = NULL;
	current = &record;
	while (1)
	{
		cout << "请输入迷宫的行数和列数：";
		cin >> m >> p;
		if (!cin.good())
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	cout << "请输入迷宫，1代表墙壁，0代表通路" << endl;
	for (i = 0; i < m + 2; i++)
		for (j = 0; j < p + 2; j++)
		{

			while (1)
			{
				cin >> Maze[i][j];
				if (!cin.good() || Maze[i][j] > 1 || Maze[i][j] < 0)
				{
					cout << "输入错误，请错误位置重新开始输入" << endl;
					cin.clear();
					cin.ignore(65535, '\n');
				}
				else
					break;
			}
		}
	for (i = 0; i < m + 2; i++)
		for (j = 0; j < p + 2; j++)
			mark[i][j] = 0;
	mark[1][1] = 1;



	double run_time;
	LARGE_INTEGER time_start;	//开始时间
	LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始


	if (SeekPath(1, 1))
		Maze[1][1] = 2;


	QueryPerformanceCounter(&time_over);	//计时结束
	run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000000/（cpu主频）微秒
	Maze[0][1] = Maze[m][p + 1] = 1;
	cout << "所用时间：      " << run_time << endl;
	// □表示未经过的节点， █表示障碍物， ☆表示可行节点 
	string s[3] = { "□", "█", "☆" };
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= p; j++)
			cout << s[Maze[i][j]];
		cout << endl;
	}
	cout << "迷宫地图：" << endl << endl;
	cout << "        ";
	cout << setiosflags(ios::left);
	for (i = 0; i < p + 2; i++) {
		cout << i << setw(int(7 - int(i / 10))) << "列";
	}
	cout << endl;
	for (i = 0; i < m + 2; i++)
	{
		cout << i << setw(int(7 - int(i / 10))) << "行";
		for (j = 0; j < p + 2; j++)
		{
			switch (Maze[i][j]) {
				case 1:
					cout << "#       ";
					break;
				case 2:
					cout << "×      ";
					break;
				case 0:
					cout << "0       ";
					break;
			}
		}
		cout << endl;
	}
	if (Maze[1][1] == 2)
	{
		cout << endl << "迷宫路径：" << endl << endl;
		current = &record;
		cout << "<1,1>";
		while (current->link != NULL) {
			rec* tmp = &record;
			if (current->link != NULL && current->link->link == NULL)
				tmp = current;
			while (current->link != NULL)
			{
				current = current->link;
				if (current->link != NULL && current->link->link == NULL)
					tmp = current;
			}
			cout << " ---> " << "<" << current->a << "," << current->b << ">";
			tmp->link = NULL;
			delete current;
			current = &record;
		}
	}
	else
		cout << "迷宫中没有入口到出口的通路" << endl;
	cout << endl;
	delete[] Maze;
	delete[] mark;
	return 0;
}