#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

const int DefaultSize = 200;
const int DefaultVertics = 100;

template <class T>
class LinkNode {
public:
	T data;
	LinkNode<T>* link;
	LinkNode(LinkNode<T>* ptr = NULL)
	{
		link = ptr;
	}
	LinkNode(const T& item, LinkNode<T>* ptr = NULL)
	{
		data = item;
		link = ptr;
	}
};

template <class T>
class LinkedQueue {
public:
	LinkedQueue() :rear(NULL), front(NULL) {}	//构造函数，建立空队列
	~LinkedQueue()								//析构函数
	{
		makeEmpty();
	}
	bool EnQueue(const T& x);					//将x加入到队列中
	bool DeQueue(T& x);							//删除队头元素,x返回其值
	bool getFront(T& x)const;					//查看队头元素的值
	void makeEmpty();							//置空队列
	bool IsEmpty()const							//判队列空否
	{
		return(front == NULL) ? true : false;
	}
	int getSize()const;							//求队列元素个数
	friend ostream& operator<<(ostream& os, LinkedQueue<T>& Q);//重载输出
protected:
	LinkNode<T>* front, * rear;
};

template <class T>
void LinkedQueue<T>::makeEmpty()
{
	LinkNode<T>* p;
	while (front != NULL)
	{
		p = front;
		front = front->link;
		delete p;
	}
}

template <class T>
bool LinkedQueue<T>::EnQueue(const T& x)
{
	if (front == NULL)
	{
		front = rear = new LinkNode<T>(x);
		if (front == NULL)
			return false;
	}
	else
	{
		rear->link = new LinkNode<T>(x);
		if (rear->link == NULL)
			return false;
		rear = rear->link;
	}
	return true;
}

template <class T>
bool LinkedQueue<T>::DeQueue(T& x)
{
	if (IsEmpty() == true)
		return false;
	LinkNode<T>* p = front;
	x = front->data;
	front = front->link;
	delete p;
	return true;
}

template <class T>
bool LinkedQueue<T>::getFront(T& x)const
{
	if (IsEmpty() == true)
		return false;
	x = front->data;
	return true;
}

template <class T>
int LinkedQueue<T>::getSize()const
{
	LinkNode<T>* p = front;
	int k = 0;
	while (p != NULL)
	{
		p = p->link;
		k++;
	}
	return k;
}

template <class T>
ostream& operator <<(ostream& os, LinkedQueue<T>& Q)
{
	os << "队列中的元素个数为" << Q.getSize() << endl;
	LinkNode<T>* p = Q.front;
	int i = 0;
	while (p != NULL)
	{
		os << ++i << ":" << p->data << endl;
		p = p->link;
	}
	return os;
}

template <class T>
class Graphmtx {
	friend istream& operator >>(istream& in, Graphmtx<T>& G);
	friend ostream& operator<<(ostream& out, Graphmtx<T>& G);
public:
	Graphmtx(int sz = DefaultVertics);
	~Graphmtx()
	{
		delete[]VerticesList;
		delete[]Edge;
	}
	T getValue(int i)
	{
		return VerticesList[i];
	}
	int getWeight(int v1, int v2)
	{

		return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;
	}
	bool GraphEmpty()const
	{
		if (numEdges == 0)
			return true;
		else
			return false;
	}
	bool GraphFull()const
	{
		if (numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1))
			return true;
		else
			return false;
	}
	int NumberOfVertices()
	{
		return numVertices;
	}
	int NumberOfEdges()
	{
		return numEdges;
	}
	int getVertexPos(T vertex)
	{
		for (int i = 0; i < numVertices; i++)
			if (VerticesList[i] == vertex)
				return i;
		return -1;
	}
	bool check(T vertex)
	{
		for (int i = 0; i < numVertices; i++)
			if (VerticesList[i] == vertex)
				return true;
		return false;
	}
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	bool insertVertex(const T& vertex);
	bool insertEdge(int v1, int v2);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
private:
	int maxVertices;
	int numEdges;
	int numVertices;
	T* VerticesList;
	int** Edge;
};

template <class T>
Graphmtx<T>::Graphmtx(int sz)
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	int i, j;
	VerticesList = new T[maxVertices];
	Edge = (int**)new int * [maxVertices];
	for (i = 0; i < maxVertices; i++)
		Edge[i] = new int[maxVertices];
	for (i = 0; i < maxVertices; i++)
		for (j = 0; j < maxVertices; j++)
			Edge[i][j] = 0;
}
template <class T>
int Graphmtx<T>::getFirstNeighbor(int v)
{
	if (v != -1)
	{
		for (int col = 0; col < numVertices; col++)
			if (Edge[v][col] != 0)
				return col;
	}
	return -1;
}

template<class T>
int Graphmtx<T>::getNextNeighbor(int v, int w)		 //给出顶点v的某邻接顶点w的下一个邻接顶点
{
	if (v != -1 && w != -1)
	{
		for (int col = w + 1; col < numVertices; col++)
			if (Edge[v][col] != 0)
				return col;
	}
	return -1;
}

template <class T>
bool Graphmtx<T>::insertVertex(const T& vertex)	//插人顶点 vertex
{

	if (numVertices == maxVertices) 	// 顶点表满, 不插入
		return false;
	VerticesList[numVertices++] = vertex;
	return true;
}
template <class T>
bool Graphmtx<T>::removeVertex(int v)		//删去顶点v和所有与它相关联的边
{
	if (v < 0 || v >= numVertices)//v不在图中, 不删除
		return false;
	if (numVertices == 1)//只剩一个顶点, 不删除
		return false;
	int i, j;
	VerticesList[v] = VerticesList[numVertices - 1];//顶点表中删除该结点
	for (i = 0; i < numVertices; i++)// 减去与v相关联边数
		if (Edge[i][v] != 0)//用最后一列填补第v列
			numEdges--;
	for (i = 0; i < numVertices; i++)
		Edge[i][v] = Edge[i][numVertices - 1];
	numVertices--;		//顶点数减1
	for (j = 0; j < numVertices; j++)//用最后行填补第v行
		Edge[v][j] = Edge[numVertices][j];
	return true;
}
template <class T>
bool Graphmtx<T>::insertEdge(int v1, int v2)
{
	if (v1 > -1 && v1< numVertices && v2>-1 && v2 < numVertices && Edge[v1][v2] == 0)
	{
		Edge[v1][v2] = 1;
		numEdges++;
		return true;
	}
	else
		return false;
}

template <class T>
bool Graphmtx<T>::removeEdge(int v1, int v2)	//在图中删去边(v1,v2)
{
	if (v1 > -1 && v1 < numVertices && v2> -1 && v2 < numVertices && Edge[v1][v2] != 0)
	{
		Edge[v1][v2] = 0;
		numEdges--;
		return true;
	}
	else
		return false;
}

//通过从输人流对象in输入n个顶点信息和e条无向边的信息建立用邻接矩阵表示的图G,邻接矩阵初始化的工作已经在构造函数中完成。
template <class T>
istream& operator>> (istream& in, Graphmtx<T>& G)
{
	int i, j, k, n, m;
	T e1, e2;
	in >> n >> m;
	for (i = 0; i < n; i++) //建立顶点表数据
	{
		in >> e1;
		G.insertVertex(e1);
	}
	i = 0;
	while (i < m)
	{
		in >> e1 >> e2;
		j = G.getVertexPos(e1);
		k = G.getVertexPos(e2);
		if (j == -1 || k == -1)
			cout << "边两端点信息有误，重新输人!" << endl;
		else
		{
			G.insertEdge(j, k);
			i++;
		}
	}
	return in;
}

template <class T>
ostream& operator <<(ostream& out, Graphmtx<T>& G)
{
	int i, j, n, m;
	T e1, e2;
	int w;
	n = G.NumberOfVertices();
	m = G.NumberOfEdges();
	out << n << "," << m << endl;
	for (int i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
		{
			w = G.getWeight(i, j);
			if (w != 0)
			{
				e1 = G.getValue(i);
				e2 = G.getValue(j);
				out << "(" << e1 << "," << e2 << endl;
			}
		}
	return out;
}

class Timetable {
public:
	string courseID;
	string coursename;
	short times;
	short term;
	bool flag = false;
	short pre = 0;
	string Prerequisite[DefaultVertics];
	Timetable(string ID = "", string name = "", short ti = 0, short te = 0) :courseID(ID), coursename(name), times(ti), term(te)
	{
		for (int i = 0; i < DefaultVertics; i++)
			Prerequisite[i] = "";
	}
};

struct table {
	string name;
	short cost = 0;
	bool flag = false;
};

Timetable list[DefaultVertics];
table stu_table[10][5];

void initialize()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
		{
			stu_table[i][j].name = "";
			stu_table[i][j].cost = 1;
			stu_table[i][j].flag = false;
		}
}

void print(const int& term, ofstream& out)
{
	out << "第" << term << "学期课表：" << endl;
	out << "            星期一              星期二              星期三              星期四              星期五" << endl;
	for (int i = 0; i < 9; i++)
	{
		out << "第" << i + 1 << "节" << "     ";
		for (int j = 0; j < 5; j++)
			out << setw(20) << setiosflags(ios::left) << stu_table[i][j].name;
		out << endl;
	}
	out << "第" << 10 << "节" << "    ";
	for (int j = 0; j < 5; j++)
		out << setw(20) << setiosflags(ios::left) << stu_table[9][j].name;
	out << endl;
	out << endl << endl;
}

bool loopjudge(int* count,int n)
{
	int i;
	for (i = 0; i < n; i++)
		if (count[i] == 0)
			break;
	if (i >= n)
	{
		cout << "课程中有回路" << endl;
		return false;
	}
	return true;
}

int lasttime()
{
	int count = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 5; j++)
			if (stu_table[i][j].flag == false)
				count++;
	return count;
}

void insertcourse(int n)
{
	int weekday = 0, i, j, judge = 0;
	for (j = 0; j < 5;)
	{
		if (list[n].times == 0 || list[n].times < 3 || list[n].times == 4)
			break;
		judge = 0;
		for (i = 2; i < 10 && list[n].times != 0;)
		{
			if (stu_table[i][j].flag == false && stu_table[i + 1][j].flag == false && stu_table[i + 2][j].flag == false)
			{
				stu_table[i][j].name = list[n].coursename;
				stu_table[i + 1][j].name = list[n].coursename;
				stu_table[i + 2][j].name = list[n].coursename;
				stu_table[i][j].flag = true;
				stu_table[i + 1][j].flag = true;
				stu_table[i + 2][j].flag = true;
				list[n].times -= 3;
				judge = 1;
				if (list[n].times > 0)
				{
					j = (j - 3 > 0) ? (j - 3) : (j + 2);
					break;
				}
				if (list[n].times == 0 || list[n].times < 3)
					break;
			}
			i += 5;
		}
		if (judge == 0)
			j++;
	}
	for (; j < 5;)
	{
		if (list[n].times == 0)
			break;
		judge = 0;
		for (i = 0; i < 10 && list[n].times != 0;)
		{
			if (stu_table[i][j].flag == false && stu_table[i + 1][j].flag == false)
			{
				stu_table[i][j].name = list[n].coursename;
				stu_table[i + 1][j].name = list[n].coursename;
				stu_table[i][j].flag = true;
				stu_table[i + 1][j].flag = true;
				list[n].times -= 2;
				judge = 1;
				if (list[n].times > 0)
				{
					j = (j - 3 > 0) ? (j - 3) : (j + 2);
					break;
				}
			}
			i += 5;
		}
		if (judge == 0)
			j++;
	}
	if (list[n].times != 0)
	{
		for (; j < 5; j++)
		{
			if (list[n].times == 0)
				break;
			judge = 0;
			for (i = 0; i < 10; i++)
			{
				if (stu_table[i][j].flag == false)
				{
					stu_table[i][j].name = list[n].coursename;
					stu_table[i][j].flag = true;
					list[n].times--;
					judge = 1;
					if (list[n].times > 0)
					{
						j = (j - 3 > 0) ? (j - 3) : (j + 2);
						break;
					}
				}
			}
			if (judge == 0)
				j++;
		}
	}
}

bool Inserttable(Graphmtx<string>& G, const int n, ofstream &out)
{
	int i, j, w, v, a, b, term = 1;;
	int finishjudge;
	int* count = new int[n];
	LinkedQueue<int> que;
	for (i = 0; i < n; i++)
		count[i] = 0;
	for (i = 0; i < n; i++)					//构建课程有向图
	{
		if (list[i].flag == true)
		{
			b = G.getVertexPos(list[i].courseID);
			for (j = 0; j < list[i].pre; j++)
			{
				a = G.getVertexPos(list[i].Prerequisite[j]);
				G.insertEdge(a, b);
				count[i]++;
			}
		}
	}

	while (1)
	{
		initialize();
		for (i = 0; i < n; i++)				//安排固定学期课程
			if (list[i].term == term)
			{
				if (lasttime() < list[i].times)
				{
					cout << "课程过多，课表已满" << endl;
					return false;
				}
				else
				{
					insertcourse(i);
					count[i] = -1;
				}
			}
		int full_or_not = 0;
		while (que.DeQueue(v))
		{
			if (lasttime() < list[i].times)
			{
				full_or_not = 1;
				break;
			}
			else
				insertcourse(v);
			count[v] = -1;
			w = G.getFirstNeighbor(v);
			while (w != -1)
			{
				count[w]--;
				w = G.getNextNeighbor(v, w);
			}
		}
		if (full_or_not == 1)
		{
			print(term, out);
			term++;
			continue;
		}
		finishjudge = 1;
		for (i = 0; i < n; i++)
			if (count[i] != -1)
				finishjudge = 0;
		if (finishjudge)
		{
			print(term, out);
			break;
		}
		//判断是否有回路
		if (loopjudge(count, n) == false)
			return false;
		for (i = 0; i < n; i++)
			if (count[i] == 0 && list[i].term == 0)
				que.EnQueue(i);
		while (que.DeQueue(v))
		{

			if (lasttime() < list[i].times)
			{
				full_or_not = 1;
				break;
			}
			else
			{
				insertcourse(v);
				count[v] = -1;
				w = G.getFirstNeighbor(v);
				while (w != -1)
				{
					count[w]--;
					w = G.getNextNeighbor(v, w);
				}
			}
		}
		if (full_or_not == 1)
		{
			print(term, out);
			term++;
			continue;
		}
		print(term, out);
		finishjudge = 1;
		for (i = 0; i < n; i++)
			if (count[i] != -1)
				finishjudge = 0;
		if (finishjudge)
			break;
		term++;
	}
	return true;
}
int main()
{
	ifstream in;
	in.open("timetable.txt", ios::in);
	if (!in.is_open())
	{
		cout << "打开文件失败" << endl;
		exit(-1);
	}
	ofstream out;
	out.open("student.txt", ios::out);
	if (!out.is_open())
	{
		cout << "打开文件失败" << endl;
		exit(-1);
	}

	Graphmtx<string> G;
	char temp[DefaultSize];
	int i = 0, n;
	while (!in.eof())
	{
		int j = 0;
		stringstream ss;
		in.getline(temp,DefaultSize,'\n');
		if (strlen(temp) < 1)
			break;
		ss << temp;
		ss >> list[i].courseID >> list[i].coursename;
		ss >> list[i].times;
		if (!ss.good())
		{
			cout << "输入错误，注意课程名不能有空格" << endl;
			in.close();
			out.close();
			exit(-1);
		}
		ss >> list[i].term;
		if (!ss.eof())
			list[i].flag = true;
		if (list[i].flag == true && list[i].term != 0)
		{
			cout << "指定课程学期课程不应安排先修课" << endl;
			in.close();
			out.close();
			exit(-1);
		}
		while (!ss.eof())
		{
			ss >> list[i].Prerequisite[j];
			j++;
			list[i].pre++;
		}
		i++;
	}
	n = i;
	for (i = 0; i < n; i++)
		G.insertVertex(list[i].courseID);
	if (Inserttable(G, n,out) == false)
	{
		in.close();
		out.close();
		exit(-1);
	}






	in.close();
	out.close();
	return 0;
}