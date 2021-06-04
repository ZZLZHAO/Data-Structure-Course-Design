#include<iostream>
#include <string>
#include <time.h>
using namespace std;

#define DefaultSize 1000000
template <class E>
class MaxHeap {
public:
	MaxHeap(long long& compare_times, int sz = DefaultSize);
	MaxHeap(E arr[], int n, long long& compare_times);
	~MaxHeap()
	{
		delete[]heap;
	}
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
	void swap(int m, int n) {
		int temp = heap[m];
		heap[m] = heap[n];
		heap[n] = temp;
	}
	void siftDown(int start, int m, long long& compare_times);
private:
	E* heap;
	int currentSize;
	int MaxHeapSize;
};

template <class E>
MaxHeap<E>::MaxHeap(long long& compare_times, int sz)
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
MaxHeap<E>::MaxHeap(E arr[], int n, long long& compare_times)
{
	MaxHeapSize = n;
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
		siftDown(currentPos, currentSize - 1, compare_times);
		currentPos--;
	}
}

template <class E>
void MaxHeap<E>::siftDown(int start, int m, long long& compare_times)
{
	int i = start, j = 2 * i + 1;
	E temp = heap[i];
	while (j <= m)
	{
		compare_times++;
		if (j < m && heap[j] < heap[j + 1])
			j++;
		compare_times++;
		if (temp >= heap[j])
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

void BubbleSort(int* element, int n, long long& compare_times) {
	int temp;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			compare_times++;
			if (element[j] > element[j + 1])
			{
				temp = element[j];
				element[j] = element[j + 1];
				element[j + 1] = temp;
			}
		}
	}
}

void SelectionSort(int* element, int n, long long& compare_times) {
	int temp;
	for (int i = 0; i < n; i++)
	{
		int min = i;
		for (int j = i + 1; j < n; j++)
		{
			compare_times++;
			if (element[j] < element[min])
				min = j;
		}
		if (min != i)
		{
			temp = element[i];
			element[i] = element[min];
			element[min] = temp;
		}
	}
}

void InsertionSort(int* element, int n, long long& compare_times) 
{
	int temp, i, j = 0;
	for (i = 1; i < n; i++)
	{
		temp = element[i], j = i;
		while (j > 0 && temp < element[j - 1])
		{
			element[j] = element[j - 1];
			compare_times++;
			j--;
		}
		element[j] = temp;
	}
}

void ShellSort(int* element, int n, long long& compare_times) 
{
	int i, j, gap = n;
	int temp;
	do {
		gap = gap / 3 + 1;
		for (i = gap; i <= n; i++)
			if (element[i] < element[i - gap])
			{
				temp = element[i];
				j = i - gap;
				do {
					element[j + gap] = element[j];
					j = j - gap;
					compare_times++;
				} while (j >= 0 && temp < element[j]);
				compare_times++;
				element[j + gap] = temp;
			}
	} while (gap > 1);
}

void QuickSort(int* element, const int left, const int right, long long& compare_times) 
{
	if (left < right)
	{
		int pivotPos = left;
		int pivot = element[left];
		for (int i = left + 1; i <= right; i++)
		{
			compare_times++;
			if (element[i] < pivot)
			{
				pivotPos++;
				if (pivotPos != i)
					swap(element[pivotPos], element[i]);
			}
		}
		element[left] = element[pivotPos];
		element[pivotPos] = pivot;
		QuickSort(element, left, pivotPos - 1, compare_times);
		QuickSort(element, pivotPos + 1, right, compare_times);
	}
}

void HeapSort(int* element, int size, long long& compare_times) {
	MaxHeap<int> maxHeap(element, size, compare_times);
	for (int i = size - 1; i > 0; i--)
	{
		maxHeap.swap(0, i);
		compare_times++;
		maxHeap.siftDown(0, i - 1, compare_times);
	}
}

void merge(int* L1, int* L2, const int left, const int mid, const int right, long long& compare_times) 
{
	for (int i = left; i <= right; i++)
	{
		L2[i] = L1[i];
	}
	int s1 = left;
	int s2 = mid + 1;
	int t = left;
	while (s1 <= mid && s2 <= right)
	{
		compare_times++;
		if (L2[s1] <= L2[s2])
			L1[t++] = L2[s1++];
		else
			L1[t++] = L2[s2++];
	}
	while (s1 <= mid)
		L1[t++] = L2[s1++];
	while (s2 <= right)
		L1[t++] = L2[s2++];
}

void MergeSort(int* L1, int* L2, int left, int right, long long& compare_times) {
	if (left < right) {
		int mid = (left + right) / 2;
		MergeSort(L1, L2, left, mid, compare_times);
		MergeSort(L1, L2, mid + 1, right, compare_times);
		merge(L1, L2, left, mid, right, compare_times);
	}
}


int maxdigit(int* element, int n)
{
	int max = element[0];
	for (int i = 1; i < n; i++) {
		if (max < element[i]) {
			max = element[i];
		}
	}
	int d = 1;
	int p = 10;
	while (max >= p) {
		max = max / 10;
		d++;
	}
	return d;
}


void RadixSort(int* element, int n, long long& compare_times)
{
	int d = maxdigit(element, n);
	int* temp = new int[n];
	int count[10];
	int radix = 1;
	for (int i = 1; i <= d; i++)
	{
		for (int j = 0; j < 10; j++)
			count[j] = 0;
		for (int j = 0; j < n; j++)
		{
			int k = (element[j] / radix) % 10;
			count[k]++;
		}
		for (int j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j];
		for (int j = n - 1; j >= 0; j--)
		{
			int k = (element[j] / radix) % 10;
			temp[count[k] - 1] = element[j];
			count[k]--;
		}
		for (int j = 0; j < n; j++)
			element[j] = temp[j];
		radix *= 10;
	}
}




int main()
{
	cout << "**            排序算法比较             **" << endl;
	cout << "=========================================" << endl;
	cout << "**            1 --- 冒泡排序             **" << endl;
	cout << "**            2 --- 选择排序             **" << endl;
	cout << "**            3 --- 直接插入排序         **" << endl;
	cout << "**            4 --- 希尔排序             **" << endl;
	cout << "**            5 --- 快速排序             **" << endl;
	cout << "**            6 --- 堆排序               **" << endl;
	cout << "**            7 --- 归并排序             **" << endl;
	cout << "**            8 --- 基数排序             **" << endl;
	cout << "**            9 --- 退出程序             **" << endl;
	cout << "=========================================" << endl << endl;



	int a;
	long long exchangeTime = 0;
	long long times;
	cout << "请输入要产生的随机数的个数：";
	int n;
	while (1)
	{
		cin >> n;
		if (!cin.good())
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		else
			break;
	}
	cout << endl;
	int* element = new int[n + 1];
	int* element_backup = new int[n + 1];
	int* L = new int[n + 1];
		srand(int(time(NULL)));
	for (int i = 0; i < n; i++)
		element[i] = rand() % 2147483647;
	while (1)
	{
		double time_start, time_end;
		times = 0;
		while (1)
		{
			cout << "请选择排序算法：        ";
			cin >> a;
			if (!cin.good() || a <= 0 || a > 9)
			{
				cout << "输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
				continue;
			}
			else
				break;
		}
		if (a == 9)
			break;
		for (int i = 0; i < n; i++)
			element_backup[i]=element[i];
		switch (a)
		{
			case 1:
				time_start = clock();
				BubbleSort(element_backup, n, times);
				time_end = clock();
				cout << "冒泡排序所用时间：      " << double(time_end - time_start) / 1000 << endl;
				cout << "冒泡排序交换次数：      " << times << endl;
				break;
			case 2:
				time_start = clock();
				SelectionSort(element_backup, n, times);
				time_end = clock();
				cout << "选择排序所用时间：      " << double(time_end - time_start) / 1000 << endl;
				cout << "选择排序交换次数：      " << times << endl;
				break;
			case 3:
				time_start = clock();
				InsertionSort(element_backup, n, times);
				time_end = clock();
				cout << "直接插入排序所用时间：  " << double(time_end - time_start) / 1000 << endl;
				cout << "直接插入排序交换次数：  " << times << endl;
				break;
			case 4:
				time_start = clock();
				ShellSort(element_backup, n, times);
				time_end = clock();
				cout << "希尔排序所用时间：      " << double(time_end - time_start) / 1000 << endl;
				cout << "希尔排序交换次数：      " << times << endl;
				break;
			case 5:
				time_start = clock();
				QuickSort(element_backup, 0, n - 1, times);
				time_end = clock();
				cout << "快速排序所用时间：      " << double(time_end - time_start) / 1000 << endl;
				cout << "快速排序交换次数：      " << times << endl;
				break;
			case 6:
				time_start = clock();
				HeapSort(element_backup, n, times);
				time_end = clock();
				cout << "堆排序所用时间：        " << double(time_end - time_start) / 1000 << endl;
				cout << "堆排序交换次数：        " << times << endl;
				break;
			case 7:
				time_start = clock();
				MergeSort(element_backup, L, 0, n - 1, times);
				time_end = clock();
				cout << "归并排序所用时间：      " << double(time_end - time_start) / 1000 << endl;
				cout << "归并排序比较次数：      " << times << endl;
				break;
			case 8:
				time_start = clock();
				RadixSort(element_backup, n, times);
				time_end = clock();
				cout << "基数排序所用时间：      " << double(time_end - time_start) / 1000 << endl;
				cout << "基数排序交换次数：      " << times << endl;
				break;
		}
		cout << endl;
	}
	delete[]L;
	delete[]element;
	return 0;
}