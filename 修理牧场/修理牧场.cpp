#include <iostream>
using namespace std;
#define DefaultSize 1000
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
		cerr << "ÉêÇëÄÚ´æÊ§°Ü" << endl;
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
		cerr << "ÉêÇëÄÚ´æÊ§°Ü" << endl;
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
			j = i; 
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

template <class E>
bool MinHeap<E>::Insert(const E& x)
{
	if (currentSize == MaxHeapSize)
	{
		cerr << "´æ´¢¿Õ¼äÒÑÂú" << endl;
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
		cout << "ÎÞÔªËØ¿É¹©É¾³ý" << endl;
		return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return true;
}

struct HuffmanNode {
	int data = 0;
	HuffmanNode* leftChild, * rightChild, * parent;
	HuffmanNode() :leftChild(NULL), rightChild(NULL), parent(NULL) {}
	HuffmanNode(int elem, HuffmanNode* left = NULL, HuffmanNode* right = NULL, HuffmanNode* pr = NULL)
		:data(elem), leftChild(left), rightChild(right), parent(pr) {}
	bool operator<=(HuffmanNode& R)
	{
		return data <= R.data;
	}
	bool operator>(HuffmanNode& R)
	{
		return data > R.data;
	}
};

class HuffmanTree {
public:
	HuffmanTree(int w[], int n);
	~HuffmanTree()
	{
		deleteTree(root);
	}
	int getData()
	{
		return cost;
	}
protected:
	HuffmanNode* root;
	int cost = 0;
	void deleteTree(HuffmanNode* t);
	void mergeTree(HuffmanNode& ht1, HuffmanNode& ht2, HuffmanNode*& parent);
};

HuffmanTree::HuffmanTree(int w[], int n)
{
	int i;
	MinHeap<HuffmanNode> hp;
	HuffmanNode* parent = NULL, * first, * second, work;
	for (i = 0; i < n; i++)
	{
		work.data = w[i];
		work.leftChild = NULL;
		work.parent = NULL;
		hp.Insert(work);
	}
	for (i = 0; i < n - 1; i++)
	{
		first = new HuffmanNode;
		if (first == NULL)
		{
			cerr << "ÉêÇëÄÚ´æÊ§°Ü" << endl;
			exit(-1);
		}
		second = new HuffmanNode;
		if (second == NULL)
		{
			cerr << "ÉêÇëÄÚ´æÊ§°Ü" << endl;
			exit(-1);
		}
		hp.RemoveMin(*first);
		hp.RemoveMin(*second);
		mergeTree(*first, *second, parent);
		hp.Insert(*parent);
		cost += parent->data;
	}
	root = parent;
}

void HuffmanTree::mergeTree(HuffmanNode& bt1, HuffmanNode& bt2, HuffmanNode*& parent)
{
	parent = new HuffmanNode;
	if (parent == NULL)
	{
		cerr << "ÉêÇëÄÚ´æÊ§°Ü" << endl;
		exit(-1);
	}
	parent->leftChild = &bt1;
	parent->rightChild = &bt2;
	parent->data = bt1.data + bt2.data;
	bt1.parent = bt2.parent = parent;
}

void HuffmanTree::deleteTree(HuffmanNode* t)
{
	if (t != NULL)
	{
		deleteTree(t->leftChild);
		deleteTree(t->rightChild);
		delete t;
	}
}

int main()
{
	int n, farmer[DefaultSize];
	while (1)
	{
		cin >> n;
		if (!cin.good())
		{
			cout << "ÊäÈë´íÎó£¬ÇëÖØÐÂÊäÈë" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	for (int i = 0; i < n; i++)
	{
		while (1)
		{
			cin >> farmer[i];
			if (!cin.good())
			{
				cout << "ÊäÈë´íÎó£¬ÇëÖØÐÂÊäÈë" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else
				break;
		}
	}
	HuffmanTree cost(farmer, n);
	cout << cost.getData() << endl;
	return 0;
}