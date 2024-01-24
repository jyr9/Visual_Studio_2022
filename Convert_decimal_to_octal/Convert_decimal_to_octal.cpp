#include <iostream>
using namespace std;

typedef struct node{
	int data = 0;
	struct node* next = NULL;	//这里出现node，所以一开始要声明node
} node, *LinkStack;

void Convert_dec_to_oct(int num_dec);
void InitlinkStack(LinkStack& bottom_next);
void push(LinkStack& top, int push_num);
void pop(LinkStack& top, int& pop_num);

LinkStack oct_stack = new node;

int main()
{
	InitlinkStack(oct_stack);
	int num_dec;
	cout << "请输入十进制正整数" << endl;
	cin >> num_dec;
	while (num_dec < 0)	//程序健壮性
	{
		cout << "输入有误，请重新输入" << endl;
		cin >> num_dec;
	}
	Convert_dec_to_oct(num_dec);
	return 0;
}

/// <summary>
/// 将十进制数转化为八进制数
/// </summary>
/// <param name="num_dec">十进制数</param>
void Convert_dec_to_oct(int num_dec) {
	int mod_num;	//余数
	while (num_dec)	//十进制数为0时就停止push
	{
		mod_num = num_dec % 8;
		num_dec = num_dec / 8;
		push(oct_stack, mod_num);
	}
	cout << "八进制数为" << endl;
	while (!(oct_stack == NULL))	//栈为空时就停止pop
	{
		int pop_num;
		pop(oct_stack, pop_num);
		cout << pop_num;
	}
}

/// <summary>
/// 初始化栈，让bottom指向空
/// </summary>
/// <param name="bottom">bottom_next是bottom的指针，其指向空</param>
void InitlinkStack(LinkStack& bottom_next)
{
	bottom_next = NULL;
}

/// <summary>
/// 插入函数
/// </summary>
/// <param name="top">栈顶指针</param>
/// <param name="push_num">插入的值</param>
void push(LinkStack& top, int push_num) {
	node* p_push_num = new node;	//为插入的值创建一个节点
	p_push_num->data = push_num;
	p_push_num->next = top;
	top = p_push_num;
}

/// <summary>
/// 弹出函数
/// </summary>
/// <param name="top">栈顶指针</param>
/// <param name="pop_num">弹出的值</param>
void pop(LinkStack& top, int& pop_num) {
	node* p_pop_num = top;	//为top创建一个节点，方便释放
	pop_num = top->data;
	top = top->next;
	delete(p_pop_num);
}
