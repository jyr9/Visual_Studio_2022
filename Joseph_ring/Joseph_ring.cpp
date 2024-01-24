#include <iostream>
using namespace std;

typedef struct node {	//链表初始化
	int number = 0;
	int password = 0;
	struct node* next{ NULL };
} node, * CITY;
CITY head = new node;

int People_number = 7;	//总人数
int m = 20;

void People_data(void);
CITY Find_element(int number);

int main()
{
	People_data();
	while (People_number != 0)
	{
		static CITY p_location = head;	//第一次运行时，p_location为head
		for (size_t i = 0; i < m - 1; i++)
		{
			p_location = p_location->next;
		}	//p_location现在是要删除的前一个

		CITY Delete_people = p_location->next;
		p_location->next = Delete_people->next;
		m = Delete_people->password;	//更改m为passoword
		cout << Delete_people->number;	//输出number
		free(Delete_people);			//free删除的节点
		People_number--;				//人数-1，用于辅助判断
	}
}

void People_data(void) {
	CITY p = head;

	for (size_t i = 0; i < People_number; i++)	// 构造空链表
	{
		CITY New_node = new node;
		p->next = New_node;
		p = p->next;
	}
	Find_element(People_number)->next = head->next;	//构成循环

	Find_element(1)->number = 1;	//链表赋值
	Find_element(2)->number = 2;
	Find_element(3)->number = 3;
	Find_element(4)->number = 4;
	Find_element(5)->number = 5;
	Find_element(6)->number = 6;
	Find_element(7)->number = 7;

	Find_element(1)->password = 3;
	Find_element(2)->password = 1;
	Find_element(3)->password = 7;
	Find_element(4)->password = 2;
	Find_element(5)->password = 4;
	Find_element(6)->password = 8;
	Find_element(7)->password = 4;
}

CITY Find_element(int number) {
	CITY p_location;
	p_location = head;
	for (size_t i = 0; i < number; i++)
	{
		p_location = p_location->next;
	}
	return p_location;
}