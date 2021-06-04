#include<iostream>
using namespace std;
const int MAX = 100;
template <typename T>
class Stack                 //模板类:栈
{
public:
    Stack();                //默认构造函数
    Stack(int n);           //构造函数,调用函数createStack(int n),创建长度为n的栈
    ~Stack();               //虚构函数
    int createStack(int n); //创建长度为n的栈
    int empty();            //判断栈是否为空
    int full();             //判断栈是否为满
    int push(T e);          //将元素e压栈
    int pop(T& e);          //元素出栈，保存在e中
    T get_top();            //得到栈顶元素
    friend int isoperator(char& e);//判断字符e是否为运算符
    friend int isp(char& e);//返回栈中运算符的优先级
    friend int icp(char& e);//返回栈外运算符的优先级
    friend int compute(int x, char a, int y);//求值函数
private:
    T* elem;                //建立长度为n的数组
    int n;                  //栈中元素的最大个数
    int top;                //栈顶指针
};
template<typename T>
Stack<T>::Stack()
{
    top = -1;
}
template<typename T>
Stack<T>::Stack(int n)
{
    createStack(n);
}
template<typename T>
Stack<T>::~Stack()
{
    n = 0;
    top = -1;
    delete[]elem;
}
template<typename T>
int Stack<T>::createStack(int n)
{
    if (n <= 0)
        return 0;
    this->n = n;
    top = -1;
    elem = new T[n];
    if (!elem)
        return 0;
    return 1;
}
template<typename T>
int Stack<T>::empty()
{
    return top == -1;
}
template<typename T>
int Stack<T>::full()
{
    return top >= n - 1;
}
template<typename T>
int Stack<T>::push(T e)
{
    if (top >= n - 1)
        return 0;
    elem[++top] = e;
    return 1;
}
template<typename T>
int Stack<T>::pop(T& e)
{
    if (top == -1)
        return 0;
    e = elem[top--];
    return 1;
}
template<typename T>
T Stack<T>::get_top()
{
    return elem[top];
};
int isoperator(char& e)        //判断是否为运算符
{
    if (e == '+' || e == '-' || e == '*' || e == '/' || e == '(' || e == ')' || e == '#' || e == 'P' || e == 'N')
        return 1;      //是运算符返回1
    else
        return 0;      //不是运算符返回0
}
int isp(char& e)               //返回栈中运算符的优先级
{
    switch (e)
    {
        case '#':
            return 0; break;
        case '(':
            return 1; break;
        case '+':
        case '-':
            return 2; break;
        case '*':
        case '/':
            return 3; break;
        case 'P':
        case 'N':
            return 4; break;
        case ')':
            return 5; break;
        default:
            return -1; break;
    }
}
int icp(char& e)                 //返回栈外运算符的优先级
{
    switch (e)
    {
        case '#':
            return 0; break;
        case ')':
            return 1; break;
        case '+':
        case '-':
            return 2; break;
        case '*':
        case '/':
            return 3; break;
        case 'P':
        case 'N':
            return 4; break;
        case '(':
            return 5; break;
        default:
            return -1; break;
    }
}
int compute(int x, char a, int y)
{
    switch (a)
    {
        case '+':                //计算加法
            return x + y; break;
        case '-':                //计算减法
            return x - y; break;
        case '*':                //计算乘法
            return x * y; break;
        case '/':                //计算除法
            return x / y; break;
        default:
            return -1; break;
    }
}
int g1()
{
    char a, b, c;
    int i, j, f, value, firstOpnd, secondOpnd, m;
    Stack<char> OPTR(MAX);    //建立运算符栈
    Stack<int> OPND(MAX);     //建立操作数栈
    OPTR.push('#');           //'#'压栈
    cout << "请输入中缀表达式： ";
    a = getchar();
    while (a != '#' || OPTR.get_top() != '#')
    {
        if (!isoperator(a))   //不是运算符，即为操作数，操作数入栈
            OPND.push(a - 48);//将字符型转化为整型数字
        else                  //是运算符，与栈顶运算符比较优先级大小
        {
            b = OPTR.get_top();//得到运算符栈顶元素
            i = isp(b);       //栈顶运算符的优先级
            j = icp(a);       //栈外运算符的优先级
            if (i < j)        //栈外运算符优先级高，运算符入栈
                OPTR.push(a);
            else
            {
                OPTR.pop(b);
                if (b != '(' && i == j || i > j)
                {
                    c = OPTR.get_top();
                    if ((c == '(' || c == '#') && (b == 'P' || b == 'N'))    /*c为一元运
                                                                            算符：正负号*/
                    {
                        OPND.pop(firstOpnd); //得到操作数
                        switch (b)
                        {
                            case 'P':            //正号
                                f = firstOpnd * 1;
                                break;
                            case 'N':            //负号
                                f = firstOpnd * (-1);
                                break;
                        }
                    }
                    else                     //c为二元运算符
                    {
                        OPND.pop(secondOpnd); //得到第二操作数
                        OPND.pop(firstOpnd);  //得到第一操作数
                        f = compute(firstOpnd, b, secondOpnd); //计算求值
                    }
                    OPND.push(f);             //求值结果压栈
                    continue;
                }
            }
        }
        c = a;
        a = getchar();                         //继续读取字符
        while (!isoperator(a) && !isoperator(c))  /*若连续读取字符均为数字，则乘以位权
                                                  得到多位数*/
        {
            OPND.pop(m);
            m = m * 10 + a - 48;
            OPND.push(m);
            c = a;
            a = getchar();
        }

    }
    OPND.pop(value);
    return value;      //返回表达式的结果
}
int main()
{
    int a;
    a = g1();
    cout << "运算结果为:  " << a << endl;
    return 0;
}