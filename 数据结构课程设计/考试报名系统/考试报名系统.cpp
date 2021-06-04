#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
using namespace std;
class LinkNode {
public:
	string studentID; //表示学生考号
	string studentName;//表示学生姓名
	string student_sex;//表示学生性别
	string student_age;//表示学生年龄
	string student_category;//表示学生报考种类
	LinkNode* link;//链表结点的指针域
	LinkNode(string sID = "", string sName = "", string sex = "", string age = "", string category = "", LinkNode* ptr = NULL) :
		studentID(sID),
		studentName(sName),
		student_sex(sex),
		student_age(age),
		student_category(category),
		link(ptr)
	{}
};
class List {
public:
	List();							 //构造函数
	List(string sID, string sName, string sex, string age, string category, LinkNode* ptr);				 //带参构造函数
	List(List& L);					 //带对象复制构造函数
	~List();						//析构函数
	void makeEmpty();				//给链表清空
	LinkNode* getHead()const;		//取得头结点
	LinkNode* Search();		//查找考号为ID的考生的地址并返回
	bool findData();		//查找考号为ID的考生
	bool setData();			//修改考号为ID的考生数据
	bool Insert();		//插入
	bool Remove();			//删除考号为ID的考生
	bool check(string ID, LinkNode* temp);					//查重
	void Input(int studentNumber);	//通过后插法建立链表
	void display();					//输出
protected:
	LinkNode* first;
	int Length = 0;
};



void readData(string& sID, string& sName, string& sex, string& age, string& category)
{
	while (1)
	{
		cin >> sID >> sName >> sex >> age >> category;
		if (!cin.good())
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
}
void print(string sID, string sName, string sex, string age, string category)
{
	cout << setw(10) << setfill(' ') << sID;
	cout << setw(10) << setfill(' ') << sName;
	cout << setw(8) << setfill(' ') << sex;
	cout << setw(6) << setfill(' ') << age;
	cout << setw(20) << setfill(' ') << category << endl;
}
void readData(string& sID, string& sName, string& sex, string& age, string& category);
//构造函数
List::List()
{
	first = new LinkNode;
	if (first == NULL)
	{
		cout << "申请内存失败" << endl;
		exit(-1);
	}
}

//带参构造函数
List::List(string sID, string sName, string sex, string age, string category, LinkNode* ptr)
{
	first = new LinkNode(sID, sName, sex, age, category, ptr);
	if (first == NULL)
	{
		cout << "申请内存失败" << endl;
		exit(-1);
	}
}

//析构函数
List::~List()
{
	LinkNode* q;
	while (first->link != NULL)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
	Length = 0;
}

//带对象复制构造函数
List::List(List& L)
{
	string sID, sName, sex, age, category;
	LinkNode* srcptr = L.getHead();
	LinkNode* destptr = first = new LinkNode;
	while (srcptr->link != NULL)
	{
		sID = srcptr->link->studentID;
		sName = srcptr->link->studentName;
		sex = srcptr->link->student_sex;
		age = srcptr->link->student_age;
		category = srcptr->link->student_category;
		destptr->link = new LinkNode(sID, sName, sex, age, category);
		if (destptr->link == NULL)
		{
			cout << "申请内存失败" << endl;
			exit(-1);
		}
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;
}

//给链表清空
void List::makeEmpty()
{
	LinkNode* q;
	while (first->link != NULL)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
	Length = 0;
}

//取得头结点
LinkNode* List::getHead()const
{
	return first;
}

//查找考号为ID的考生的结点地址并返回
LinkNode* List::Search()
{
	string ID;
	while (1)
	{
		cin >> ID;
		if (!cin.good())
		{
			cout << "输入错误，请重新输入：";
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	LinkNode* current = first->link;
	while (current != NULL)
	{
		if (current->studentID == ID)
			break;
		else
			current = current->link;
	}
	return current;
}

//查找考号为ID的考生
bool List::findData()
{
	LinkNode* current = Search();
	if (current == NULL)
	{
		cout << "您要查找的考生不存在" << endl;
		return false;
	}
	else
	{
		cout << setw(10) << setfill(' ') << "考号";
		cout << setw(10) << setfill(' ') << "姓名";
		cout << setw(8) << setfill(' ') << "性别";
		cout << setw(6) << setfill(' ') << "年龄";
		cout << setw(20) << setfill(' ') << "报考种类" << endl;
		cout << setw(10) << setfill(' ') << current->studentID;
		cout << setw(10) << setfill(' ') << current->studentName;
		cout << setw(8) << setfill(' ') << current->student_sex;
		cout << setw(6) << setfill(' ') << current->student_age;
		cout << setw(20) << setfill(' ') << current->student_category << endl;
	}
	return true;
}

//修改考号为ID的考生数据
bool List::setData()
{
	string ID, sID, sName, sex, age, category;
	LinkNode* current = Search();
	if (current != NULL)
	{
		while (1)
		{
			cout << "请输入要修改的考生的考号，姓名，性别，年龄，报考类别！" << endl;
			readData(sID, sName, sex, age, category);
			if (check(sID, current) == true)
				break;
			else
				cout << "修改考号与已有考生重复，请重新输入" << endl;
		}
		current->studentID = sID;
		current->studentName = sName;
		current->student_sex = sex;
		current->student_age = age;
		current->student_category = category;
		display();
	}
	else
	{
		cout << "您要修改的考生不存在" << endl;
		return false;
	}
	return true;
}

//插入
bool List::Insert()
{
	int studentnumber;
	string sID, sName, sex, age, category;
	LinkNode* current = first;
	while (1)
	{
		cout << "请输入要插入的考生位置[1-" << Length + 1 << "]：";
		cin >> studentnumber;
		if (!cin.good() || studentnumber > Length + 1 || studentnumber <= 0)
		{
			cout << "您输入的位置不合法，请重新输入！" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	for (int i = 0; i < studentnumber - 1; i++)
		current = current->link;
	while (1)
	{
		cout << "请输入要插入考生的考号，姓名，性别，年龄，报考类别！" << endl;
		readData(sID, sName, sex, age, category);
		if (check(sID, current) == true)
			break;
		else
			cout << "插入考号与已有考生重复，请重新输入" << endl;
	}
	LinkNode* newNode = new LinkNode(sID, sName, sex, age, category);
	if (newNode == NULL)
	{
		cerr << "申请空间失败" << endl;
		exit(-1);
	}
	Length++;
	newNode->link = current->link;
	current->link = newNode;
	display();
	return true;
}

//删除
bool List::Remove()
{
	string ID, sID, sName, sex, age, category;
	LinkNode* current = first;
	while (1)
	{
		cin >> ID;
		if (!cin.good())
		{
			cout << "输入错误，请重新输入：";
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	while (current->link != NULL)
	{
		if (current->link->studentID == ID)
			break;
		else
			current = current->link;
	}
	if (current == NULL || current->link == NULL)
	{
		cout << "您要删除的学生不存在" << endl;
		return false;
	}
	LinkNode* del = current->link;
	current->link = del->link;
	sID = del->studentID;
	sName = del->studentName;
	sex = del->student_sex;
	age = del->student_age;
	category = del->student_category;
	cout << "您删除的考生的信息是：";
	print(sID, sName, sex, age, category);
	display();
	Length--;
	delete del;
	return true;
}

//输出
void List::display()
{
	LinkNode* current = first->link;
	cout << setw(10) << setfill(' ') << "考号";
	cout << setw(10) << setfill(' ') << "姓名";
	cout << setw(8) << setfill(' ') << "性别";
	cout << setw(6) << setfill(' ') << "年龄";
	cout << setw(20) << setfill(' ') << "报考种类" << endl;
	while (current != NULL)
	{
		cout << setw(10) << setfill(' ') << current->studentID;
		cout << setw(10) << setfill(' ') << current->studentName;
		cout << setw(8) << setfill(' ') << current->student_sex;
		cout << setw(6) << setfill(' ') << current->student_age;
		cout << setw(20) << setfill(' ') << current->student_category << endl;
		current = current->link;
	}
}

//采用后插法建立链表
void List::Input(int studentnumber)
{
	LinkNode* newNode, * last = NULL;
	string sID, sName, sex, age, category;
	makeEmpty();
	cout << "请依次输入考生的考号，姓名，性别，年龄，报考类别！" << endl;
	last = first;
	for (int i = 0; i < studentnumber; i++)
	{
		while (1)
		{
			readData(sID, sName, sex, age, category);
			if (check(sID, last) == true)
				break;
			else
				cout << "输入考号与已有考生重复，请重新输入" << endl;
		}
		newNode = new LinkNode(sID, sName, sex, age, category);
		if (newNode == NULL)
		{
			cerr << "申请空间失败" << endl;
			exit(-1);
		}
		Length++;
		last->link = newNode;
		last = newNode;
	}
	last->link = NULL;
}

//考号查重
bool List::check(string ID, LinkNode* temp)
{
	LinkNode* current = first->link;
	while (current != NULL)
	{
		if (current->studentID == ID && current != temp)
			return false;
		current = current->link;
	}
	return true;
}

int main()
{
	int studentNumber, flag = -1;
	cout << setiosflags(ios::left);
	cout << "首先请建立考生信息系统！" << endl;
	while (1)
	{
		cout << "请输入考生人数：";
		cin >> studentNumber;
		if (!cin.good() || studentNumber <= 0)
		{
			cout << "请输入一个正整数" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	List stuTest;
	stuTest.Input(studentNumber);
	while (flag != 0)
	{
		cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为退出）" << endl;
		while (1)
		{
			cout << "请选择您要进行的操作：" << endl;
			cin >> flag;
			if (!cin.good() || flag > 5 || flag < 0)
			{
				cout << "抱歉，您想要的操作不存在，请重新输入！" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else
				break;
		}
		switch (flag)
		{
			case 1:
				stuTest.Insert();
				break;
			case 2:
				cout << "请输入您要删除的考生的考号：";
				stuTest.Remove();
				break;
			case 3:
				cout << "请输入您要查找的考生的考号：";
				stuTest.findData();
				break;
			case 4:
				cout << "请输入您要修改的考生的考号：";
				stuTest.setData();
				break;
			case 5:
				stuTest.display();
				break;
			case 0:
				break;
		}
		if (flag == 0)
			break;
	}
	return 0;
}