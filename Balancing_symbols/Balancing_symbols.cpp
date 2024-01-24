#include <iostream>
using namespace std;

typedef struct node {
	char data = '\0';
	struct node* next = NULL;	//这里出现node，所以一开始要声明node
} node, * LinkStack;

bool Parenthesis_matching(string String_parenthesis);
void InitlinkStack(LinkStack& bottom_next);
void push(LinkStack& top, char push_num);
void pop(LinkStack& top, char& pop_num);

LinkStack Parenthesis_stack = new node;

int main()
{
	InitlinkStack(Parenthesis_stack);
	cout << "请输入只包含'('、')'、'['、']'的符号组成的表达式" << endl;
	string Parenthesis_string;
	cin >> Parenthesis_string;
	for (size_t i = 0; i < Parenthesis_string.length(); i++)	//程序健壮性
	{
		if (Parenthesis_string[i] != '(' && Parenthesis_string[i] != ')' && Parenthesis_string[i] != '[' && Parenthesis_string[i] != ']')
		{
			cout << "请输入正确的表达式" << endl;
			cin >> Parenthesis_string;
		}
	}
	bool Bool_result = Parenthesis_matching(Parenthesis_string);
	if (Bool_result)
	{
		cout << "匹配" << endl;
	}
	else if (!Bool_result)
	{
		cout << "此串括号匹配不合法" << endl;
	}
	return 0;
}

/// <summary>
/// 匹配函数
/// </summary>
/// <param name="String_parenthesis">括号字符串</param>
/// <returns>是否匹配</returns>
bool Parenthesis_matching(string String_parenthesis) {
	for (size_t i = 0; i < String_parenthesis.length(); i++)
	{
		if (String_parenthesis[i] == '(' || String_parenthesis[i] == '[')	//如果是(或[，则push到栈中
		{
			push(Parenthesis_stack, String_parenthesis[i]);
		}
		else if (String_parenthesis[i] == ')' || String_parenthesis[i] == ']')	//如果是)或]
		{
			char pop_num;
			if (Parenthesis_stack == NULL)	//如果堆栈为空，则返回false
			{
				return false;
			}
			pop(Parenthesis_stack, pop_num);	//pop栈中元素
			if (!((pop_num == '(' && String_parenthesis[i] == ')') || (pop_num == '[' && String_parenthesis[i] == ']')))
			{
				//如果栈中元素不匹配，则返回false
				return false;
			}
		}
	}
	if (Parenthesis_stack != NULL)	//如果最后栈非空，则返回false
	{
		return false;
	}
	return true;
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
void push(LinkStack& top, char push_num) {
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
void pop(LinkStack& top, char& pop_num) {
	node* p_pop_num = top;	//为top创建一个节点，方便释放
	pop_num = top->data;
	top = top->next;
	delete(p_pop_num);
}
