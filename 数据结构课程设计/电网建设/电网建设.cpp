#include <iostream>
#include <cstring>
using namespace std;

const int DefaultSize = 1000;
const int DefaultVertics = 500;
const float maxWeight = 65535;

template <class T, class E>
class Graphmtx{
	friend istream& operator >>(istream& in, Graphmtx<T, E>& G);
	friend ostream& operator<<(ostream& out, Graphmtx<T, E>& G);
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
	E getWeight(int v1, int v2)
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
		if (numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2)
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
	bool insertEdge(int v1, int v2, E cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
private:
	int maxVertices;
	int numEdges;
	int numVertices;
	T* VerticesList;
	E** Edge;
};

template <class T, class E>
Graphmtx<T, E>::Graphmtx(int sz)
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	int i, j;
	VerticesList = new T[maxVertices];
	Edge = (E**)new E * [maxVertices];
	for (i = 0; i < maxVertices; i++)
		Edge[i] = new E[maxVertices];
	for (i = 0; i < maxVertices; i++)
		for (j = 0; j < maxVertices; j++)
			Edge[i][j] = (i == j) ? 0 : maxWeight;
}
template <class T, class E>
int Graphmtx<T, E>::getFirstNeighbor(int v)
{
	if (v != -1)
	{
		for (int col = 0; col < numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
				return col;
	}
	return -1;
}

template<class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w)		 //给出顶点v的某邻接顶点w的下一个邻接顶点
{
	if (v != -1 && w != -1)
	{
		for (int col = w + 1; col < numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
				return col;
	}
	return -1;
}

template <class T, class E>
bool Graphmtx<T, E>::insertVertex(const T& vertex)	//插人顶点 vertex
{

	if (numVertices == maxVertices) 	// 顶点表满, 不插入
		return false;
	VerticesList[numVertices++] = vertex;
	return true;
}
template <class T, class E>
bool Graphmtx<T, E>::removeVertex(int v)		//删去顶点v和所有与它相关联的边
{
	if(v < 0 || v >= numVertices)//v不在图中, 不删除
		return false;
	if (numVertices == 1)//只剩一个顶点, 不删除
		return false;
	int i, j;
	VerticesList[v] = VerticesList[numVertices - 1];//顶点表中删除该结点
	for (i = 0; i < numVertices; i++)// 减去与v相关联边数
		if (Edge[i][v] > 0 && Edge[i][v] < maxWeight)//用最后一列填补第v列
			numEdges--;
	for (i = 0; i < numVertices; i++)
		Edge[i][v] = Edge[i][numVertices - 1];
	numVertices--;		//顶点数减1
	for (j = 0; j < numVertices; j++)//用最后行填补第v行
		Edge[v][j] = Edge[numVertices][j];
	return true;
}
template <class T, class E >
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost)
{
	if (v1 > -1 && v1< numVertices && v2>-1 && v2 < numVertices && Edge[v1][v2] == maxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = cost;
		numEdges++;
		return true;
	}
	else
		return false;
}

template <class T, class E>
bool Graphmtx<T, E>::removeEdge(int v1, int v2)	//在图中删去边(v1,v2)
{
	if (v1 > -1 && v1 < numVertices && v2> -1 && v2 < numVertices && Edge[v1][v2]> 0 && Edge[v1][v2] < maxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = maxWeight;
		numEdges--;
		return true;
	}
	else
		return false;
}

//通过从输人流对象in输入n个顶点信息和e条无向边的信息建立用邻接矩阵表示的图G,邻接矩阵初始化的工作已经在构造函数中完成。
template <class T, class E>
istream& operator>> (istream& in, Graphmtx<T, E>& G)
{
	int i, j, k, n, m;
	T e1, e2;
	E weight;
	in >> n >> m;
	for (i = 0; i < n; i++) //建立顶点表数据
	{
		in >> e1;
		G.insertVertex(e1);
	}
	i = 0;
	while (i < m)
	{
		in >> e1 >> e2 >> weight;
		j = G.getVertexPos(e1);
		k = G.getVertexPos(e2);
		if (j == -1 || k == -1)
			cout << "边两端点信息有误，重新输人!" << endl;
		else
		{
			G.insertEdge(j, k, weight);
			i++;
		}
	}
	return in;
}

template <class T,class E>
ostream& operator <<(ostream& out, Graphmtx<T, E>& G)
{
	int i, j, n, m;
	T e1, e2;
	E w;
	n = G.NumberOfVertices();
	m = G.NumberOfEdges();
	out << n << "," << m << endl;
	for (int i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
		{
			w = G.getWeight(i, j);
			if (w > 0 && w < maxWeight)
			{
				e1 = G.getValue(i);
				e2 = G.getValue(j);
				out << "(" << e1 << "," << e2 << "," << w << ")" << endl;
			}
		}
	return out;
}



struct MSTEdgeNode {
	int tail, head;
	float key;
	bool operator<=(MSTEdgeNode& R)
	{
		return key <= R.key;
	}
	bool operator >(MSTEdgeNode& R)
	{
		return key > R.key;
	}
};


class MinSpanTree {
protected:
	MSTEdgeNode* edgevalue;
	int maxSize, n;
public:
	MinSpanTree(int sz = DefaultSize - 1) :maxSize(sz), n(0)
	{
		edgevalue = new MSTEdgeNode[sz];
		if (edgevalue == NULL)
		{
			cout << "申请内存失败" << endl;
			exit(-1);
		}
	}
	int Insert(MSTEdgeNode& item);
	void display(Graphmtx<string, float>& G)
	{
		cout << "最小生成树的顶点及边为：" << endl << endl;
		for (int i = 0; i < n; i++)
			cout << G.getValue(edgevalue[i].tail) << "-<" << edgevalue[i].key << ">-" << G.getValue(edgevalue[i].head) << "        ";
		cout << endl;
	}
};


int MinSpanTree::Insert(MSTEdgeNode& item)
{
	if (n < maxSize)
	{
		edgevalue[n].tail = item.tail;
		edgevalue[n].head = item.head;
		edgevalue[n].key = item.key;
		n++;
		return 1;
	}
	else
		return 0;
}

template <class E>
class MinHeap {
public:
	MinHeap(int sz = DefaultSize);
	MinHeap(E arr[], int n);
	~MinHeap()
	{
		delete[]heap;
	}
	bool Insert(const E& x);
	bool RemoveMin(E& x);
	bool IsEmpty()const
	{
		return (currentSize == 0) ? true : false;
	}
	bool IsFull()const
	{
		return (currentSize == MaxHeapSize) ? true : false;
	}
	void makeEmpty()
	{
		currentSize = 0;
	}
private:
	E* heap;
	int currentSize;
	int MaxHeapSize;
	void siftDown(int start, int m);
	void siftUp(int start);
};

template <class E>
MinHeap<E>::MinHeap(int sz)
{
	MaxHeapSize = (DefaultSize < sz) ? sz : DefaultSize;
	heap = new E[MaxHeapSize];
	if (heap == NULL)
	{
		cerr << "申请内存失败" << endl;
		exit(-1);
	}
	currentSize = 0;
}

template <class E>
MinHeap<E>::MinHeap(E arr[], int n)
{
	MaxHeapSize = (DefaultSize < n) ? n : DefaultSize;
	heap = new E[MaxHeapSize];
	if (heap == NULL)
	{
		cerr << "申请内存失败" << endl;
		exit(-1);
	}
	for (int i = 0; i < n; i++)
		heap[i] = arr[i];
	currentSize = n;
	int currentPos = (currentSize - 2) / 2;
	while (currentPos >= 0)
	{
		siftDown(currentPos, currentSize - 1);
		currentPos--;
	}
}

template <class E>
void MinHeap<E>::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;
	E temp = heap[i];
	while (j <= m)
	{
		if (j<m && heap[j]>heap[j + 1])
			j++;
		if (temp <= heap[j])
			break;
		else
		{
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}

template <class E>
void MinHeap<E>::siftUp(int start)
{
	int j = start, i = (j - 1) / 2;
	E temp = heap[j];
	while (j > 0)
	{
		if (heap[i] <= temp)
			break;
		else
		{
			heap[j] = heap[i];
			j = i; i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

template <class E>
bool MinHeap<E>::Insert(const E& x)
{
	if (currentSize == MaxHeapSize)
	{
		cerr << "存储空间已满" << endl;
		return false;
	}
	heap[currentSize] = x;
	siftUp(currentSize);
	currentSize++;
	return true;
}

template <class E>
bool MinHeap<E>::RemoveMin(E& x)
{
	if (!currentSize)
	{
		cout << "无元素可供删除" << endl;
		return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return true;
}


template <class T,class E>
void Prim( Graphmtx<T, E>& G, MinSpanTree& MST)			//最小生成树Prim算法
{
	T u0;
	cout << "请输入起始顶点";
	while (1)
	{
		cin >> u0;
		if (G.check(u0) == false)
			cout << "顶点不存在，请重新输入" << endl;
		else
			break;
	}
	MSTEdgeNode ed;
	int i, u, v, count;
	int n = G.NumberOfVertices();
	int m = G.NumberOfEdges();
	u = G.getVertexPos(u0);
	MinHeap<MSTEdgeNode> H(m);
	bool* Vmst = new bool[n];
	for (i = 0; i < n; i++)
		Vmst[i] = false;
	Vmst[u] = true;
	count = 1;
	do {
		v = G.getFirstNeighbor(u);
		while (v != -1)
		{
			if (Vmst[v] == false)
			{
				ed.tail = u;
				ed.head = v;
				ed.key = G.getWeight(u, v);
				H.Insert(ed);
			}
			v = G.getNextNeighbor(u, v);
		}
		while (H.IsEmpty() == false && count < n)
		{
			H.RemoveMin(ed);
			if (Vmst[ed.head] == false)
			{
				MST.Insert(ed);
				u = ed.head;
				Vmst[u] = true;
				count++;
				break;
			}
		}
	} while (count < n);
	cout << "生成Prim最小树！" << endl;
}

void createpoint(Graphmtx<string, float>& G, int& n)
{
	string name;
	int i;
	cout << "请输入顶点的个数：";
	while (1)
	{
		cin >> n;
		if (!cin.good())
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	cout << "请依次输入各顶顶点的名称" << endl;
	for (i = 0; i < n; i++) //建立顶点表数据
	{
		while (1)
		{
			cin >> name;
			if (G.check(name) == true)
				cout << "顶点名称重复，请从重复顶点后重新输入" << endl;
			else
				break;
		}
		G.insertVertex(name);
	}
}

void createedge(Graphmtx<string, float>& G)
{
	string name1,name2;
	int i = 0, j, k;
	float weight;
	cout << "（当输入\"? ? 0\"时输入结束）" << endl;
	while(1)
	{
		cout << "请输入两个顶点及边：";
		cin >> name1 >> name2 >> weight;
		if (name1 == "?" && name2 == "?" && weight == 0)
			break;
		j = G.getVertexPos(name1);
		k = G.getVertexPos(name2);
		if (j == -1 || k == -1)
			cout << "边两端点信息有误，重新输人!" << endl;
		else
		{
			if (G.insertEdge(j, k, weight) == false)
				cout << "已输入此边，请重新输入" << endl;
		}
	}
}

int main()
{
	cout << "**                     电网造价模拟系统                     **" << endl;
	cout << "==============================================================" << endl;
	cout << "**                     A---创建电网顶点                     **" << endl;
	cout << "**                     B---添加电网的边                     **" << endl;
	cout << "**                     C---构造最小生成树                   **" << endl;
	cout << "**                     D---显示最小生成树                   **" << endl;
	cout << "**                     E---退出   程序                      **" << endl;
	cout << "==============================================================" << endl << endl;
	char ch;
	Graphmtx<string, float> tree;
	MinSpanTree MST;
	int flag = 1, n;
	while (flag)
	{
		cout << "请选择操作：";
		cin >> ch;
		switch (ch)
		{
			case 'A':
				createpoint(tree, n);
				break;
			case 'B':
				createedge(tree);
				break;
			case 'C':
				Prim(tree, MST);
				break;
			case 'D':
				MST.display(tree);
				break;
			case 'E':
				flag = 0;
				break;
			default:
				cout << "输入错误，请重新输入";
				break;
		}
		cout << endl;
	}
	return 0;
}