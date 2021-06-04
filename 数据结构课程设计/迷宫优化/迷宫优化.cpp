#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cmath>
#include<queue>
#include <Windows.h>
#include <time.h>
#include <iomanip>
#define N 40 // 棋盘/迷宫 的阶数 
#define M 20 // 棋盘/迷宫 的阶数 
using namespace std;

class Node
{
public:
	int x, y; // 节点所在位置	
	int F, G, H; // G:从起点开始，沿着产的路径，移动到网格上指定方格的移动耗费。
				 // H:从网格上那个方格移动到终点B的预估移动耗费，使用曼哈顿距离。 
				 // F = G + H 
	Node(int a, int b) :x(a), y(b) {}

	// 重载操作符，使优先队列以F值大小为标准维持堆 
	bool operator < (const Node& a) const
	{
		return F > a.F;
	}
};

// 定义八个方向 
int dir[4][2] = { {-1, 0},  {0, -1},
		 {0, 1},   {1, 0} };
// 优先队列，就相当于open表 
priority_queue<Node>que;
// 棋盘
int qp[N][M] = { {0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1} ,
			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
			{0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1},
			{0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
			{1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1},
			{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1},
			{0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1},
			{1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
			{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1},
			{0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0},
			{0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1},
			{0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
			{0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1},
			{1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			{0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
			{0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0},
			{0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1} ,
			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
			{0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1},
			{0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
			{1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1},
			{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1},
			{0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1},
			{1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
			{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1},
			{0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0},
			{0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1},
			{0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
			{0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1},
			{1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			{0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
			{0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0} };
bool visit[N][M]; // 访问情况记录，close表 
int valF[N][M];   // 记录每个节点对应的F值
int path[N][M][2]; // 存储每个节点的父节点

int Manhuattan(int x, int y, int x1, int y1); // 计算曼哈顿距离 
bool NodeIsLegal(int x, int y, int xx, int yy); // 判断位置合法性
void A_start(int x0, int y0, int x1, int y1); // A*算法 
void PrintPath(int x1, int y1); // 打印路径

/* ----------------主函数------------------- */
int main()
{
	fill(visit[0], visit[0] + N * M, false); // 将visit数组赋初值false
	fill(valF[0], valF[0] + N * M, 0); // 初始化F全为0 
	fill(path[0][0], path[0][0] + N * M * 2, -1); // 路径同样赋初值-1 

	//  // 起点 // 终点
	int x0, y0, x1, y1;
	cout << "输入起点：";
	cin >> x0 >> y0;
	cout << "输入终点：";
	cin >> x1 >> y1;
	x0--; y0--; x1--; y1--;

	if (!NodeIsLegal(x0, y0, x0, y0))
	{
		cout << "非法起点！" << endl;
		return 0;
	}

	double run_time;
	LARGE_INTEGER time_start;	//开始时间
	LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始


	A_start(x0, y0, x1, y1);  // A*算法 


	QueryPerformanceCounter(&time_over);	//计时结束
	run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000000/（cpu主频）微秒
	cout << "所用时间：      " << run_time << endl;



	PrintPath(x1, y1);        // 打印路径 
}

/* ----------------自定义函数------------------ */
void A_start(int x0, int y0, int x1, int y1)
{
	// 初始化起点 
	Node node(x0, y0);
	node.G = 0;
	node.H = Manhuattan(x0, y0, x1, y1);
	node.F = node.G + node.H;
	valF[x0][y0] = node.F;
	// 起点加入open表 
	que.push(node);

	while (!que.empty())
	{
		Node node_top = que.top(); que.pop();
		visit[node_top.x][node_top.y] = true; // 访问该点，加入closed表 
		if (node_top.x == x1 && node_top.y == y1) // 到达终点 
			break;

		// 遍历node_top周围的8个位置 
		for (int i = 0; i < 4; i++)
		{
			Node node_next(node_top.x + dir[i][0], node_top.y + dir[i][1]); // 创建一个node_top周围的节点 
			// 该节点坐标合法 且 未加入close表 
			if (NodeIsLegal(node_next.x, node_next.y, node_top.x, node_top.y) && !visit[node_next.x][node_next.y])
			{
				// 计算从起点并经过node_top节点到达该节点所花费的代价 
				node_next.G =  int(abs(node_next.x - x0) + abs(node_next.y - y0));
				// 计算该节点到终点的曼哈顿距离
				node_next.H = Manhuattan(node_next.x, node_next.y, x1, y1);
				// 从起点经过node_top和该节点到达终点的估计代价
				node_next.F = node_next.G + node_next.H;

				// node_next.F < valF[node_next.x][node_next.y] 说明找到了更优的路径，则进行更新
				// valF[node_next.x][node_next.y] == 0 说明该节点还未加入open表中，则加入 
				if (node_next.F < valF[node_next.x][node_next.y] || valF[node_next.x][node_next.y] == 0)
				{
					// 保存该节点的父节点 
					path[node_next.x][node_next.y][0] = node_top.x;
					path[node_next.x][node_next.y][1] = node_top.y;
					valF[node_next.x][node_next.y] = node_next.F; // 修改该节点对应的valF值 
					que.push(node_next); // 加入open表
				}
			}
		}
	}
}

void PrintPath(int x1, int y1)
{
	if (path[x1][y1][0] == -1 || path[x1][y1][1] == -1)
	{
		cout << "没有可行路径！" << endl;
		return;
	}
	int x = x1, y = y1;
	int a, b;
	while (x != -1 || y != -1)
	{
		qp[x][y] = 2; // 将可行路径上的节点赋值为2 
		a = path[x][y][0];
		b = path[x][y][1];
		x = a;
		y = b;
	}
	// □表示未经过的节点， █表示障碍物， ☆表示可行节点 
	string s[3] = { "□", "█", "☆" };
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cout << s[qp[i][j]];
		cout << endl;
	}
}

int Manhuattan(int x, int y, int x1, int y1)
{
	//return (abs(x - x1) + abs(y - y1)) * 10;
	return pow(x - x1, 2) + pow(y - y1, 2);
}

bool NodeIsLegal(int x, int y, int xx, int yy)
{
	if (x < 0 || x >= N || y < 0 || y >= M) return false; // 判断边界 
	if (qp[x][y] == 1) return false; // 判断障碍物 
	// 两节点成对角型且它们的公共相邻节点存在障碍物 
	if (x != xx && y != yy && (qp[x][yy] == 1 || qp[xx][y] == 1)) return false;
	return true;
}

