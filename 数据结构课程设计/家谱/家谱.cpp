#include <iostream>
#include <cstring>
using namespace std;

template <class T>
struct TreeNode {
	T data;
	TreeNode<T>* firstChild, * nextBrother;
	TreeNode(T value = 0, TreeNode<T>* fc = NULL, TreeNode<T>* nb = NULL) :data(value), firstChild(fc), nextBrother(nb) {}
};

template <class T>
class Tree {
private:
	TreeNode<T>* root, * current;
	void destroy(TreeNode<T>* p);						//删除以p为根的子树
public:
	Tree()
	{
		root = current = NULL;
	}
	Tree(T value)
	{
		root = new TreeNode<T>(value);
		if (root == NULL)
		{
			cout << "申请空间失败" << endl;
			exit(-1);
		}
		current = root;
	}
	~Tree()
	{
		destroy(root);
	}
	bool Root();										//寻找根，使其成为当前节点
	bool IsEmpty()										//判空
	{
		return root == NULL;
	}
	T getData()
	{
		return current->data;
	}
	bool FirstChild();									//寻找current的第一个子女，并使其成为当前节点
	bool NextBrother();									//寻找current的下一个兄弟，并使其成为当前节点
	bool Parent();										//寻找current的父节点，并使其成为当前节点
	bool Find(TreeNode<T>* p, T value);					//在以p为根的树搜索value，并使其成为当前节点
	bool FindParent(TreeNode<T>* t, TreeNode<T>* p);	//在根为*t的树中找*p的父节点，并使其成为当前节点
	void InsertFamilyMember();							//添加家庭成员
	void RemovesubTree();								//解散家庭
	void CompleteFamilyTree();							//完善家谱
	void changeName();									//更改家庭成员姓名
	void MemberMessage();								//查找资料
	void printfirstChildren();							//打印第一代子女

};

template <class T>
bool Tree<T>::Root()									//寻找根，使其成为当前节点
{
	if (root == NULL)
	{
		current = NULL;
		return false;
	}
	else
	{
		current = root;
		return true;
	}
}

template <class T>
bool Tree<T>::Parent()									//寻找current的父节点，并使其成为当前节点
{
	TreeNode<T>* p = current;
	if (current == NULL || current == root)
	{
		current = NULL;
		return false;
	}
	return FindParent(root, p);
}

template <class T>
bool Tree<T>::FindParent(TreeNode<T>* t, TreeNode<T>* p)//在根为*t的树中找*p的父节点，并使其成为当前节点
{
	TreeNode<T>* q = t->firstChild;
	bool succ;
	while (q != NULL && q != p)
	{
		if ((succ = FindParent(q, p)) == true)
			return succ;
		q = q->nextBrother;
	}
	if (q != NULL && q == p)
	{
		current = t;
		return true;
	}
	else
	{
		current = NULL;
		return false;
	}
}

template <class T>
bool Tree<T>::FirstChild()								//寻找current的第一个子女，并使其成为当前节点
{
	if (current != NULL && current->firstChild != NULL)
	{
		current = current->firstChild;
		return true;
	}
	current = NULL;
	return false;
}

template <class T>
bool Tree<T>::NextBrother()								//寻找current的下一个兄弟，并使其成为当前节点
{
	if (current != NULL && current->nextBrother != NULL)
	{
		current = current->nextBrother;
		return true;
	}
	current = NULL;
	return false;
}

template <class T>
bool Tree<T>::Find(TreeNode<T>* p, T value)				//在以p为根的树搜索value，并使其成为当前节点
{
	bool result = false;
	if (p->data == value)
	{
		result = true;
		current = p;
	}
	else
	{
		TreeNode<T>* q = p->firstChild;
		while (q != NULL && !(result = Find(q, value)))
			q = q->nextBrother;
	}
	return result;
}

template <class T>
void Tree<T>::destroy(TreeNode<T>* p)					//删除以p为根的子树
{
	if (p != NULL)
	{
		destroy(p->firstChild);
		destroy(p->nextBrother);
		delete p;
	}
}

template <class T>
void Tree<T>::InsertFamilyMember()						//添加家庭成员
{
	T name;
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	while (1)
	{
		cin >> name;
		if (!cin.good())
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		break;
	}
	if (Find(root, name) == false)
		cout << "查无此人" << endl;
	else
	{
		cout << "请输入" << current->data << "新添加的儿子（或女儿）的姓名：";
		string s;
		while (1)
		{
			cin >> s;
			if (!cin.good())
			{
				cout << "输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
				continue;
			}
			break;
		}
		TreeNode<T>* newNode = new TreeNode<T>(s);
		if (newNode == NULL)
		{
			cout << "申请空间失败" << endl;
			exit(-1);
		}
		if (current->firstChild == NULL)
			current->firstChild = newNode;
		else
		{
			TreeNode<T>* temp = current->firstChild;
			while (temp->nextBrother)
				temp = temp->nextBrother;
			temp->nextBrother = newNode;
		}
		printfirstChildren();
	}
}

template <class T>
void Tree<T>::RemovesubTree()							//删除以p为根的子树,保留根节点
{
	T name;
	cout << "请输入要解散家庭的人的姓名：";
	while (1)
	{
		cin >> name;
		if (!cin.good())
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		break;
	}
	if (Find(root, name) == false)
		cout << "查无此人" << endl;
	else
	{
		cout << "要解散家庭的人是：" << current->data << endl;
		printfirstChildren();
		destroy(current->firstChild);
		current->firstChild = NULL;
	}
}

template <class T>
void Tree<T>::CompleteFamilyTree()						//完善家谱
{
	T name;
	cout << "请输入要建立家庭的人的姓名:";
	while (1)
	{
		cin >> name;
		if (!cin.good())
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		break;
	}
	if (Find(root, name) == false)
		cout << "查无此人" << endl;
	else
	{
		if (current->firstChild)
			cout << "已建立家庭，无法再建立" << endl;
		else
		{
			cout << "请输入" << current->data << "的儿女人数：";
			int n;
			while (1)
			{
				cin >> n;
				if (!cin.good() || n < 0)
				{
					cout << "输入错误，请重新输入" << endl;
					cin.clear();
					cin.ignore(65535, '\n');
					continue;
				}
				break;
			}
			if (n != 0)
			{
				cout << "请依次输入" << current->data << "的儿女的姓名：";
				string s;
				while (1)
				{
					cin >> s;
					if (!cin.good())
					{
						cout << "输入错误，请重新输入" << endl;
						cin.clear();
						cin.ignore(65535, '\n');
						continue;
					}
					break;
				}
				TreeNode<T>* newNode = new TreeNode<T>(s);
				if (newNode == NULL)
				{
					cout << "申请空间失败" << endl;
					exit(-1);
				}
				current->firstChild = newNode;
				TreeNode<T>* temp = current->firstChild;
				for (int i = 1; i < n; i++)
				{
					string s;
					while (1)
					{
						cin >> s;
						if (!cin.good())
						{
							cout << "输入错误，请重新输入" << endl;
							cin.clear();
							cin.ignore(65535, '\n');
							continue;
						}
						break;
					}
					TreeNode<T>* newNode = new TreeNode<T>(s);
					if (newNode == NULL)
					{
						cout << "申请空间失败" << endl;
						exit(-1);
					}
					while (temp->nextBrother)
						temp = temp->nextBrother;
					temp->nextBrother = newNode;
				}
				printfirstChildren();
			}
		}
	}
}

template <class T>
void Tree<T>::changeName()								//更改家庭成员姓名
{
	T name;
	cout << "请输入要更改姓名的人的姓名:";
	while (1)
	{
		cin >> name;
		if (!cin.good())
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		break;
	}
	if (Find(root, name) == false)
		cout << "查无此人" << endl;
	else
	{
		cout << "请输入更改后的姓名:";
		while (1)
		{
			cin >> current->data;
			if (!cin.good())
			{
				cout << "输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
				continue;
			}
			break;
		}
		cout << name << "已更名为" << current->data << endl;
	}
}

template <class T>
void Tree<T>::MemberMessage()							//查找资料
{
	T name;
	cout << "请输入要查看人的姓名:";
	while (1)
	{
		cin >> name;
		if (!cin.good())
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		break;
	}
	if (Find(root, name) == false)
		cout << "查无此人" << endl;
	else
	{
		cout << "姓名：" << current->data << endl;
		if (Parent()) 
		{
			cout << "父亲：" << current->data << endl;
			if (current->firstChild->nextBrother != NULL) 
			{
				TreeNode<T>* temp = current->firstChild;
				cout << "兄弟：";
				while(temp)
				{
					if (temp->data != name)
						cout << temp->data << "    ";
					temp = temp->nextBrother;
				}
				cout << endl;
			}
		}
		Find(root, name);
		printfirstChildren();
	}
}

template <class T>
void Tree<T>::printfirstChildren()						//打印第一代子女
{
	if (!current->firstChild)
		cout << current->data << "目前尚未有后代";
	else
	{
		cout << current->data << "的第一代子孙是:";
		TreeNode<T>* temp = current->firstChild;
		while(temp) {
			cout << temp->data << "   ";
			temp = temp->nextBrother;
		}
	}
}

int main() {
	char ch;
	cout << "**                         家谱管理系统                         **" << endl;
	cout << "==================================================================" << endl;
	cout << "**                     请选择要执行的操作：                     **" << endl;
	cout << "**                     A --- 完善家庭                           **" << endl;
	cout << "**                     B --- 添加家庭成员                       **" << endl;
	cout << "**                     C --- 解散局部成员                       **" << endl;
	cout << "**                     D --- 更改家庭成员姓名                   **" << endl;
	cout << "**                     E --- 查看个人信息                       **" << endl;
	cout << "**                     F --- 退出系统                           **" << endl;
	cout << "==================================================================" << endl;
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";

	string name;
	while (1)
	{
		cin >> name;
		if (!cin.good())
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		break;
	}
	Tree<string> Family(name);
	cout << "此家谱的祖先是：" << Family.getData() << endl << endl;
	cout << "请选择要执行的操作:";
	cin >> ch;
	while (ch != 'F') {
		switch (ch) {
			case 'A':
				Family.CompleteFamilyTree();
				break;
			case 'B':
				Family.InsertFamilyMember();
				break;
			case 'C':
				Family.RemovesubTree();
				break;
			case 'D':
				Family.changeName();
				break;
			case 'E':
				Family.MemberMessage();
				break;
			default:
				cout << "输入错误，请重新输入";
				break;
		}
		cout << endl << endl;
		cout << "请选择要执行的操作:";
		cin>>ch;
	}
	return 0;
}