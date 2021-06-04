#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <cstring>
#include <sstream>
#include <cctype>
using namespace std;

const int maxSize = 1000;
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
class Stack {
public:
	Stack() {};
	virtual void Push(const T& x) = 0;
	virtual bool Pop(T& x) = 0;
	virtual bool getTop(T& x)const = 0;
	virtual bool IsEmpty()const = 0;
	virtual int getSize() const = 0;
};

template <class T>
class LinkedStack :public Stack<T> {		//链式栈类定义
public:
	LinkedStack() :top(NULL) {}				//构造函数，置空栈
	~LinkedStack()							//析构函数
	{
		makeEmpty(); 
	}
	void Push(const T& x);					//进栈
	bool Pop(T& x);							//退栈
	bool getTop(T& x)const;					//读取栈顶元素
	bool IsEmpty()const						//判断是否为空栈
	{
		return (top == NULL) ? true : false;
	}
	int getSize() const;						//求栈的元素个数
	void makeEmpty();						//清空
	friend ostream& operator << (ostream& os, LinkedStack<T>& s);//输出栈元素的重载函数
private:
	LinkNode<T>* top;
};

//清空
template <class T>
void LinkedStack<T>::makeEmpty()
{
	LinkNode<T>* p;
	while (top != NULL)
	{
		p = top;
		top = top->link;
		delete p;
	}
}

//进栈
template <class T>
void LinkedStack<T>::Push(const T& x)
{
	top = new LinkNode<T>(x, top);
	if (top == NULL)
	{
		cout << "申请内存空间失败" << endl;
		exit(-1);
	}
}

//退栈
template <class T>
bool LinkedStack<T>::Pop(T& x)
{
	if (IsEmpty() == true)
		return false;
	LinkNode<T>* p = top;
	top = top->link;
	x = p->data;
	delete p;
	return true;
}

//读取栈顶元素
template <class T>
bool LinkedStack<T>::getTop(T& x)const
{
	if (IsEmpty() == true)
		return false;
	x = top->data;
	return true;
}

//求栈的元素个数
template <class T>
int LinkedStack<T>::getSize() const
{
	LinkNode<T>* p = top;
	int k = 0;
	while (p != NULL)
	{
		p = p->link;
		k++;
	}
	return k;
}

//输出栈元素的重载函数
template <class T>
ostream& operator<<(ostream& os, LinkedStack<T>& s)
{
	os << "栈中元素个数=" << s.getSize() << endl;
	LinkNode* p = s.top;
	int i = 0;
	while (p != NULL)
	{
		os << ++i << ":" << p->data << endl;
		p = p->link;
	}
	return os;
}

//括号匹配
bool Judge(string expression)
{
	LinkedStack<int> s;
	int j, length = expression.length();
	for (int i = 1; i <= length; i++)
	{
		if (expression[i - 1] == '(')
			s.Push(i);
		else if (expression[i - 1] == ')')
			if (s.Pop(j) == false)
				return false;
	}
	if (s.IsEmpty() == false)
		return false;
	return true;
}


int isp(char& ch)
{
	switch (ch)
	{
		case '=':
			return 0;
		case '*':
		case '/':
		case '%':
			return 5;
		case '(':
			return 1;
		case '^':
			return 6;
		case '+':
		case '-':
			return 3;
		case ')':
			return 8;
	}
	return 0;
}
int icp(char& ch)
{
	switch (ch)
	{
		case '=':
			return 0;
		case '*':
		case '/':
		case '%':
			return 4;
		case '(':
			return 8;
		case '^':
			return 7;
		case '+':
		case '-':
			return 2;
		case ')':
			return 1;
	}
	return 0;
}

class arithmetic {
public:
	arithmetic() {}
	bool Run(string s1);
	void Clear();
private:
	LinkedStack<char> OPTR;    //建立运算符栈
	LinkedStack<int> OPND;     //建立操作数栈
	void AddOperand(int value);
	bool getOprands(int& left, int& right);
	bool DoOperator(char op);
	friend int isp(char& ch);
	friend int icp(char& ch);
};

//计算A op B=?
bool arithmetic::DoOperator(char op)
{
	int left, right, value;
	int result;
	result = getOprands(left, right);
	if (result == 1)
		switch (op) {
			case '+':
				value = left + right;
				OPND.Push(value);
				break;
			case '-':
				value = left - right;
				OPND.Push(value);
				break;
			case '*':
				value = left * right;
				OPND.Push(value);
				break;
			case '/':
				if (right == 0) {
					cerr << "除数不能为0，请重新输入" << endl;
					Clear();
					return false;
				}
				else {
					value = left / right;
					OPND.Push(value);
				}
				break;
			case '%':
				if (right == 0) {
					cerr << "除数不能为0，请重新输入" << endl;
					Clear();
					return false;
				}
				else {
					value = left % right;
					OPND.Push(value);
				}
				break;
			case '^':
				value = int(pow(left, right));
				OPND.Push(value);
				break;
		}
	else
	{
		Clear();
		return false;
	}
	return true;
}

bool arithmetic::getOprands(int& left, int& right)
{
	if (OPND.IsEmpty() == true)
	{
		cerr << "缺少右操作数，请重新输入" << endl;
		return false;
	}
	OPND.Pop(right);
	if (OPND.IsEmpty() == true)
	{
		cerr << "缺少左操作数，请重新输入" << endl;
		return false;
	}
	OPND.Pop(left);
	return true;
}

void arithmetic::AddOperand(int value)
{
	OPND.Push(value);
}

bool arithmetic::Run(string s1)
{
	stringstream ss;
	int i, j, temp = 0;
	char ch = '=', ch0, ch1, a;
	int newOperand, flag = 0;
	ss << s1;
	OPTR.Push(ch);
	ss >> ch;
	while (ch != '=' || (OPTR.getTop(a) && a != '='))
	{
		if (isdigit(ch))
		{
			newOperand = ch - '0';
			AddOperand(newOperand);
		}
		else
		{
			OPTR.getTop(ch1);
			i = isp(ch1);
			j = icp(ch);
			if (i < j)
				OPTR.Push(ch);	//栈外运算符优先级高，运算符入栈
			else
			{
				OPTR.Pop(ch1);	//栈内运算符优先级高，运算符出栈
				if (ch1 != '(' && i == j || i > j)
				{
					if (DoOperator(ch1) == false)
					{
						temp = 1;
						break;
					}
					continue;
				}
			}
		}
		ch0 = ch;
		ss >> ch;
		while (isdigit(ch) && isdigit(ch0))
		{
			OPND.Pop(newOperand);
			newOperand = newOperand * 10 + ch - '0';
			OPND.Push(newOperand);
			ch0 = ch;
			ss >> ch;
		}
	}
	if (temp == 1)
		return false;
	int value = 0;
	OPND.Pop(value);
	cout << value << endl;
	return true;
}

void arithmetic::Clear()
{
	OPTR.makeEmpty();
	OPND.makeEmpty();
}

int main()
{
	char expression[maxSize];
	int i, j;
	while (1) {
		int length = 0;
		cout << "输入表达式:" << endl;
		cin >> expression;
		for (i = 0; expression[i]; i++)
			length++;
		if (length - 1 >= 0 && expression[length - 1] != '=')
		{
			cout << "输入错误，请重新输入" << endl;
			cin.ignore(65535, '\n');
			continue;
		}
		for (i = 0; expression[i]; i++)
		{
			if ((expression[i] < '0' || expression[i]>'9') &&
				(expression[i] != '(' && expression[i] != ')' && expression[i] != '=' && expression[i] != '+' && expression[i] != '-' && expression[i] != '*'
					&& expression[i] != '/' && expression[i] != '%' && expression[i] != '^'))
				break;
			if (expression[i] == '=' && i != length - 1)
				break;
			if ((expression[i] == '+' || expression[i] == '-') && (i - 1 < 0 || expression[i - 1] == '('))
			{
				for (j = length + 1; j >= i; j--)
					expression[j + 1] = expression[j];
				length++;
				expression[i] = '0';
			}
		}//处理单目运算符
		if (expression[i] != '\0'||Judge(expression) == false)
		{
			cout << "输入错误，请重新输入" << endl;
			cin.ignore(65535, '\n');
			continue;
		}
		if (expression[0] == '=')
		{
			cout << "表达式为空，请重新输入" << endl;
			cin.ignore(65535, '\n');
			continue;
		}
		arithmetic calculator;
		if (calculator.Run(expression) == false)
			continue;
		
		char ch;
		while (1)
		{
			cout << "是否继续(y,n)?";
			cin >> ch;
			if (ch == 'n')
				break;
			else if (ch != 'y')
				cout << "输入错误，请重新输入" << endl;
			else
				break;
		}
		if (ch == 'n')
			break;
		cin.ignore(65535, '\n');
	}
	return 0;
}