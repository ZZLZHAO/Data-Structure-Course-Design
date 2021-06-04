#include <iostream>
using namespace std;
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
	bool getFront(T & x)const;					//查看队头元素的值
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

int main()
{
	LinkedQueue<int> A, B;
	int n, m, i, flag = 0;
	while (1)
	{
		while (1)
		{
			cin >> n;
			if (!cin.good() || n <= 0 || n > 1000)
			{
				cin.clear();
				cin.ignore(65535, '\n');
				cout << "输入错误，请重新输入" << endl;
				continue;
			}
			else
				break;
		}
		for ( i = 0; i < n; i++) 
		{
			cin >> m;
			if (!cin.good())
			{
				cin.clear();
				cin.ignore(65535, '\n');
				cout << "输入错误，请重新输入" << endl;
				A.makeEmpty();
				B.makeEmpty();
				break;
			}
			if (m % 2 == 0)
			{
				if (B.EnQueue(m) == false)
				{
					cout << "申请内存失败" << endl;
					A.makeEmpty();
					B.makeEmpty();
					exit(-1);
				}
			}
			else
			{
				if (A.EnQueue(m) == false)
				{
					cout << "申请内存失败" << endl;
					A.makeEmpty();
					B.makeEmpty();
					exit(-1);
				}
			}
		}
		if (i >= n)
			break;
	}
	int a, b, temp;
	while (A.IsEmpty() != true && B.IsEmpty() != true) {//当他们都不为空
		if (flag == 0) {
			A.getFront(a);
			cout << a;
			flag++;
		}
		else {
			A.getFront(a);
			cout << " " << a;
		}
		A.DeQueue(temp);
		if (A.IsEmpty() != 1) {
			A.getFront(a);
			cout << " " << a;
			A.DeQueue(temp);
		}
		B.getFront(b);
		cout << " " << b;
		B.DeQueue(temp);
	}
	while (A.IsEmpty() == true && B.IsEmpty() != true) {
		if (flag == 0) {
			B.getFront(b);
			cout << b;
			flag++;
		}
		else {
			B.getFront(b);
			cout << " " << b;
		}
		B.DeQueue(temp);
	}
	while (A.IsEmpty() != true && B.IsEmpty() == true) {
		if (flag == 0) {
			A.getFront(a);
			cout << a;
			flag++;
		}
		else {
			A.getFront(a);
			cout << " " << a;
		}
		A.DeQueue(temp);
	}
	return 0;
}
