#include <iostream>
#include <random>
#include <vector>  // 用于存储随机数

#define MAXSIZE 300
using namespace std;

typedef struct {
	int key; //表示排序关键字
} Struct_node;

typedef struct {
	Struct_node struct_array[MAXSIZE + 1]; //存放待排序全体数据元素
	int length; //排序数据元素个数
} Struct_list;

void Insertion_sort(Struct_list struct_list);
void Shell_sort(Struct_list struct_list, int delta[MAXSIZE], int delta_length);
void Shell_insert(Struct_list& struct_list, int increment, int& key_comparison_count, int& element_movement_count);
void Bubble_sort(Struct_list struct_list);
void Call_quick_sort(Struct_list struct_list);
void Quick_sort(Struct_list struct_list, int left, int right, int& key_comparison_count, int& element_movement_count);
int Partition(Struct_list& struct_list, int low, int high, int& key_comparison_count, int& element_movement_count);
void Simple_selection_sort(Struct_list struct_list);
void Heap_sort(Struct_list struct_list);
void Heap_adjust(Struct_list& struct_list, int low, int high, int& key_comparison_count, int& element_movement_count);
void Merge(Struct_list& struct_list, int low, int mid, int high, int& key_comparison_count, int& element_movement_count, int merge_list[]);
void Merge_sort_recursive(Struct_list& struct_list, int low, int high, int& key_comparison_count, int& element_movement_count, int merge_list[]);
void Merge_sort(Struct_list struct_list);
void generateRandomNumbers(int n);

Struct_list struct_list;

int main()
{
	int n;
	cout << "请输入你想生成的随机数数量：";
	cin >> n;
	generateRandomNumbers(n);
	struct_list.length = n;

	Insertion_sort(struct_list);
	int delta[MAXSIZE];
	int d = MAXSIZE;
	int i = 0;
	while (d > 1)
	{
		d = d / 2;
		delta[i] = d;
		i++;
	}
	Shell_sort(struct_list, delta, i);
	Bubble_sort(struct_list);
	Call_quick_sort(struct_list);
	Simple_selection_sort(struct_list);
	Heap_sort(struct_list);
	Merge_sort(struct_list);

	return 0;
}

void Insertion_sort(Struct_list struct_list) {
	int key_comparison_count = 0;
	int element_movement_count = 0;
	for (int i = 2; i < struct_list.length; i++)
	{
		if (struct_list.struct_array[i - 1].key > struct_list.struct_array[i].key)
		{
			key_comparison_count++;
			struct_list.struct_array[0] = struct_list.struct_array[i];
			int j;
			for (j = i - 1; struct_list.struct_array[0].key < struct_list.struct_array[j].key; j--)
			{
				key_comparison_count++;
				struct_list.struct_array[j + 1] = struct_list.struct_array[j];
				element_movement_count++;
			}
			struct_list.struct_array[j + 1] = struct_list.struct_array[0];
		}
	}
	cout << "直接插入排序" << endl;
	cout << "关键字比较次数为" << key_comparison_count << endl;
	cout << "数据元素移动次数为" << element_movement_count << endl;
}

void Shell_sort(Struct_list struct_list, int delta[MAXSIZE], int delta_length) {
	int key_comparison_count = 0;
	int element_movement_count = 0;
	for (int i = 0; i < delta_length; i++)
	{
		Shell_insert(struct_list, delta[i], key_comparison_count, element_movement_count);
	}
	cout << "希尔排序" << endl;
	cout << "关键字比较次数为" << key_comparison_count << endl;
	cout << "数据元素移动次数为" << element_movement_count << endl;
}

void Shell_insert(Struct_list& struct_list, int increment, int& key_comparison_count, int& element_movement_count) {
	for (int i = 1 + increment; i < struct_list.length; i++)
	{
		if (struct_list.struct_array[i - increment].key > struct_list.struct_array[i].key)
		{
			key_comparison_count++;
			struct_list.struct_array[0] = struct_list.struct_array[i];
			int j;
			for (j = i - increment; j > 0 && struct_list.struct_array[0].key < struct_list.struct_array[j].key; j = j - increment)
			{
				key_comparison_count++;
				struct_list.struct_array[j + increment] = struct_list.struct_array[j];
				element_movement_count++;
			}
			struct_list.struct_array[j + increment] = struct_list.struct_array[0];
		}
	}
}

void Bubble_sort(Struct_list struct_list) {
	int key_comparison_count = 0;
	int element_movement_count = 0;
	bool change = true;
	for (int i = struct_list.length; i > 1 && change; i--)
	{
		change = false;
		for (int j = 1; j < i; j++)
		{
			if (struct_list.struct_array[j].key > struct_list.struct_array[j + 1].key)
			{
				key_comparison_count++;
				Struct_node temp = struct_list.struct_array[j];
				struct_list.struct_array[j] = struct_list.struct_array[j + 1];
				struct_list.struct_array[j + 1] = temp;
				element_movement_count = element_movement_count + 3;
				change = true;
			}
		}
	}
	cout << "冒泡排序" << endl;
	cout << "关键字比较次数为" << key_comparison_count << endl;
	cout << "数据元素移动次数为" << element_movement_count << endl;
}

void Call_quick_sort(Struct_list struct_list) {
	int key_comparison_count = 0;
	int element_movement_count = 0;
	Quick_sort(struct_list, 1, struct_list.length, key_comparison_count, element_movement_count);
	cout << "快速排序" << endl;
	cout << "关键字比较次数为" << key_comparison_count << endl;
	cout << "数据元素移动次数为" << element_movement_count << endl;
}

void Quick_sort(Struct_list struct_list, int left, int right, int& key_comparison_count, int& element_movement_count) {
	if (left < right)
	{
		int pivot_location = Partition(struct_list, left, right, key_comparison_count, element_movement_count);
		Quick_sort(struct_list, left, pivot_location - 1, key_comparison_count, element_movement_count);
		Quick_sort(struct_list, pivot_location + 1, right, key_comparison_count, element_movement_count);
	}
}

int Partition(Struct_list& struct_list, int low, int high, int& key_comparison_count, int& element_movement_count) {
	struct_list.struct_array[0] = struct_list.struct_array[low];
	int pivot_key = struct_list.struct_array[0].key;
	while (low < high)
	{
		while (low < high && pivot_key <= struct_list.struct_array[high].key)
		{
			key_comparison_count++;
			high--;
		}
		struct_list.struct_array[low] = struct_list.struct_array[high];
		element_movement_count++;
		while (low < high && pivot_key > struct_list.struct_array[low].key)
		{
			key_comparison_count++;
			low++;
		}
		struct_list.struct_array[high] = struct_list.struct_array[low];
		element_movement_count++;
	}
	struct_list.struct_array[low] = struct_list.struct_array[0];
	element_movement_count++;
	return low;
}

void Simple_selection_sort(Struct_list struct_list) {
	int key_comparison_count = 0;
	int element_movement_count = 0;
	for (int i = 0; i < struct_list.length; i++)
	{
		int j = struct_list.length;
		int min = j;
		while (j > i)
		{
			key_comparison_count++;
			if (struct_list.struct_array[j - 1].key < struct_list.struct_array[min].key)
			{
				key_comparison_count++;
				min = j - 1;
			}
			j--;
		}
		Struct_node temp = struct_list.struct_array[min];
		struct_list.struct_array[min] = struct_list.struct_array[i];
		struct_list.struct_array[i] = temp;
		element_movement_count = element_movement_count + 3;
	}
	cout << "简单选择排序" << endl;
	cout << "关键字比较次数为" << key_comparison_count << endl;
	cout << "数据元素移动次数为" << element_movement_count << endl;
}

void Heap_sort(Struct_list struct_list) {
	int key_comparison_count = 0;
	int element_movement_count = 0;
	for (int i = struct_list.length / 2; i > 0; i--)	//堆创建
	{
		Heap_adjust(struct_list, i, struct_list.length, key_comparison_count, element_movement_count);
	}
	for (int i = struct_list.length; i > 0; i--)
	{
		Struct_node temp = struct_list.struct_array[1];
		struct_list.struct_array[1] = struct_list.struct_array[i];
		struct_list.struct_array[i] = temp;
		element_movement_count = element_movement_count + 3;
		Heap_adjust(struct_list, 1, i - 1, key_comparison_count, element_movement_count);
	}
	cout << "堆排序" << endl;
	cout << "关键字比较次数为" << key_comparison_count << endl;
	cout << "数据元素移动次数为" << element_movement_count << endl;
}

void Heap_adjust(Struct_list& struct_list, int low, int high, int& key_comparison_count, int& element_movement_count) {
	Struct_node temp = struct_list.struct_array[low];
	for (int i = 2 * low; i <= high; i = i * 2)
	{
		key_comparison_count++;
		if (i < high && struct_list.struct_array[i].key <= struct_list.struct_array[i + 1].key)
		{
			key_comparison_count++;
			i++;
		}
		key_comparison_count++;
		if (temp.key >= struct_list.struct_array[i].key)
		{
			key_comparison_count++;
			break;
		}
		struct_list.struct_array[low] = struct_list.struct_array[i];
		element_movement_count++;
		low = i;
	}
	struct_list.struct_array[low] = temp;
}

void Merge(Struct_list& struct_list, int low, int mid, int high, int& key_comparison_count, int& element_movement_count) {
	Struct_node merge_list[MAXSIZE + 1];  // 临时数组
	int i = low, j = mid + 1, k = low;
	while (i <= mid && j <= high) {
		key_comparison_count++;
		if (struct_list.struct_array[i].key <= struct_list.struct_array[j].key) {
			merge_list[k++] = struct_list.struct_array[i++];
		}
		else {
			merge_list[k++] = struct_list.struct_array[j++];
		}
		element_movement_count++;
	}

	while (i <= mid) {
		merge_list[k++] = struct_list.struct_array[i++];
		element_movement_count++;
	}

	while (j <= high) {
		merge_list[k++] = struct_list.struct_array[j++];
		element_movement_count++;
	}

	for (int l = low; l <= high; l++) {
		struct_list.struct_array[l] = merge_list[l];
	}
}

void Merge_sort_recursive(Struct_list& struct_list, int low, int high, int& key_comparison_count, int& element_movement_count) {
	if (low < high) {
		int mid = (low + high) / 2;
		Merge_sort_recursive(struct_list, low, mid, key_comparison_count, element_movement_count);
		Merge_sort_recursive(struct_list, mid + 1, high, key_comparison_count, element_movement_count);
		Merge(struct_list, low, mid, high, key_comparison_count, element_movement_count);
	}
}

void Merge_sort(Struct_list struct_list) {
	int key_comparison_count = 0;
	int element_movement_count = 0;

	Merge_sort_recursive(struct_list, 1, struct_list.length, key_comparison_count, element_movement_count);

	cout << "二路归并排序" << endl;
	cout << "关键字比较次数为" << key_comparison_count << endl;
	cout << "数据元素移动次数为" << element_movement_count << endl;
}

void generateRandomNumbers(int n) {
	int randomNumbers;
	random_device rd;  // 用于获得随机数的种子
	mt19937 gen(rd()); // 以随机数种子初始化Mersenne Twister生成器
	uniform_int_distribution<> distrib(1, 1000); // 定义一个分布范围在1到1000之间的均匀分布
	for (int i = 0; i < n; i++) {
		struct_list.struct_array[i].key = distrib(gen); // 生成随机数并添加到向量中
	}
}