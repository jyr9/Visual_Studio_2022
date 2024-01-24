#include <iostream>
#include <string>
#include <cmath>
using namespace std;

typedef struct node {	//链表初始化
	string name{ "null" };
	int x_coordinate = 0;
	int y_coordinate = 0;
	struct node* next{ NULL };
} node, *CITY;
CITY head = new node;

int City_num = 5;	//一开始共有5个数据

void City_data(void);
CITY Find_element(int number);
CITY Judge_city_name(string City_name);
void Create_city(int Create_number);
void Delete_city(int Delete_number);
void Update_city(int Update_number);
void Read_city(int Read_number);
void Return_city(int x_coordinate, int y_coordinate, int distance);
int Input_legal();

int main(void) {
	City_data();
	bool Decide_continue = true;	//判断是否继续
	while (Decide_continue)
	{
		cout << "请输入要进行的操作：" << endl;
		cout << "【0】退出" << endl;
		cout << "【1】增加城市信息" << endl;
		cout << "【2】删除城市信息" << endl;
		cout << "【3】更改城市信息" << endl;
		cout << "【4】查询城市信息" << endl;
		cout << "【5】给定城市名，返回坐标" << endl;
		cout << "【6】给定坐标与距离，返回小于距离的城市" << endl;

		int Selected_num;	//选择的数
		cin >> Selected_num;

		if (Selected_num == 0)
		{
			cout << "已退出" << endl;
			Decide_continue = false;
		}

		else if (Selected_num == 1)	// 增
		{
			cout << "请输入想要增加城市的位置" << endl;
			int Create_number = Input_legal();
			Create_city(Create_number);
		}

		else if (Selected_num == 2)	// 删
		{
			cout << "请输入想要删除的城市位置" << endl;
			int Delete_number = Input_legal();
			Delete_city(Delete_number);
		}

		else if (Selected_num == 3)	// 改
		{
			cout << "请输入想要更改的城市位置" << endl;
			int Update_number = Input_legal();
			Update_city(Update_number);
		}

		else if (Selected_num == 4)	// 查
		{
			cout << "请输入想要查询的城市位置" << endl;
			int Read_number = Input_legal();
			Read_city(Read_number);
		}

		else if (Selected_num == 5)	//给定城市名，返回坐标
		{
			cout << "请输入想要查询的城市名称" << endl;
			string City_name;
			cin >> City_name;
			CITY p_city_name = Judge_city_name(City_name);
			if (p_city_name == NULL) {
				cout << "未查询到所输入城市名，请检查输入" << endl;
			}
			else {
				cout << "城市" << City_name << "的x坐标为" << p_city_name->x_coordinate << "，y坐标为" << p_city_name->y_coordinate << endl;
			}
		}

		else if (Selected_num == 6)	//给定坐标与距离，返回小于距离的城市
		{
			int x_coordinate;
			int y_coordinate;
			int distance;
			cout << "请输入想要查询的x坐标位置" << endl;
			cin >> x_coordinate;
			cout << "请输入想要查询的y坐标位置" << endl;
			cin >> y_coordinate;
			cout << "请输入想要查询的距离" << endl;
			cin >> distance;
			Return_city(x_coordinate, y_coordinate, distance);
		}

		else
		{
			cout << "请按要求输入" << endl;	//程序健壮性
		}
	}
}

/// <summary>
/// City数据值函数
/// </summary>
void City_data(void) {
	CITY p = head;

	for (size_t i = 0; i < City_num; i++)	// 构造空链表
	{
		CITY New_node = new node;
		p->next = New_node;
		p = p->next;
	}

	Find_element(1)->name = "beijing";	//链表赋值
	Find_element(2)->name = "shanghai";
	Find_element(3)->name = "guangzhou";
	Find_element(4)->name = "shenzhen";
	Find_element(5)->name = "tongxian";

	Find_element(1)->x_coordinate = 100;
	Find_element(2)->x_coordinate = 200;
	Find_element(3)->x_coordinate = 300;
	Find_element(4)->x_coordinate = 400;
	Find_element(5)->x_coordinate = 500;

	Find_element(1)->y_coordinate = 100;
	Find_element(2)->y_coordinate = 200;
	Find_element(3)->y_coordinate = 300;
	Find_element(4)->y_coordinate = 400;
	Find_element(5)->y_coordinate = 500;
}


/// <summary>
/// 找到第i个元素的地址
/// </summary>
/// <param name="number">要找的第i个元素</param>
/// <returns>第i个元素的地址</returns>
CITY Find_element(int number) {
	CITY p_location;
	p_location = head;
	for (size_t i = 0; i < number; i++)
	{
		p_location = p_location->next;
	}
	return p_location;
}

/// <summary>
/// 判断城市名，并返回坐标
/// </summary>
/// <param name="City_name">城市名</param>
/// <returns>城市名对应的坐标或空</returns>
CITY Judge_city_name(string City_name) {
	CITY p_location;
	p_location = head;
	for (size_t i = 0; i < City_num; i++)
	{
		p_location = p_location->next;
		if (p_location->name == City_name) {
			return p_location;
		}
	}
	return NULL;
}

/// <summary>
/// 增加函数
/// p_prior_location是前一个元素的地址
/// Create_element是要加的元素的地址
/// </summary>
/// <param name="Create_number">要加到第几个元素前</param>
void Create_city(int Create_number) {
	CITY p_prior_location = Find_element(Create_number - 1);
	CITY Create_element = new node;
	string New_name;
	int New_x_coordinate, New_y_coordinate;
	cout << "请输入增加的城市名称" << endl;
	cin >> New_name;
	cout << "请输入增加城市的x坐标" << endl;
	cin >> New_x_coordinate;
	cout << "请输入增加城市的y坐标" << endl;
	cin >> New_y_coordinate;
	Create_element->name = New_name;
	Create_element->x_coordinate = New_x_coordinate;
	Create_element->y_coordinate = New_y_coordinate;
	Create_element->next = p_prior_location->next;
	p_prior_location->next = Create_element;
	City_num++;
	cout << "已在第" << Create_number << "个城市前" << "增加城市" << New_name << endl;
}

/// <summary>
/// 删除元素
/// p_prior_location是前一个元素的地址
/// p_location是此元素的地址
/// </summary>
/// <param name="Delete_number">要删除第几个元素</param>
void Delete_city(int Delete_number) {
	CITY p_prior_location = Find_element(Delete_number - 1);
	CITY p_location = p_prior_location->next;
	p_prior_location->next = p_location->next;
	free(p_location);
	City_num--;
	cout << "已删除第" << Delete_number << "个城市" << endl;
}

/// <summary>
/// 修改函数
/// p_location是此元素的地址
/// </summary>
/// <param name="Update_number">要求改第几个元素</param>
void Update_city(int Update_number) {
	CITY p_location = Find_element(Update_number);
	string New_name;
	int New_x_coordinate, New_y_coordinate;
	cout << "请输入修改的城市名称" << endl;
	cin >> New_name;
	cout << "请输入修改城市的x坐标" << endl;
	cin >> New_x_coordinate;
	cout << "请输入修改城市的y坐标" << endl;
	cin >> New_y_coordinate;
	p_location->name = New_name;
	p_location->x_coordinate = New_x_coordinate;
	p_location->y_coordinate = New_y_coordinate;
	cout << "已修改第" << Update_number << "个城市为城市" << New_name << endl;
}

/// <summary>
/// 查询函数
/// p_location是此元素的地址
/// </summary>
/// <param name="Read_number">要求查询第几个元素</param>
void Read_city(int Read_number) {
	CITY p_location = Find_element(Read_number);
	cout << "第" << Read_number << "个城市名称为" << p_location->name << endl;
	cout << "x坐标为" << p_location->x_coordinate << endl;
	cout << "y坐标为" << p_location->y_coordinate << endl;
}

/// <summary>
/// 给定坐标与距离，返回小于距离的城市
/// </summary>
/// <param name="x_coordinate">给定的x坐标</param>
/// <param name="y_coordinate">给定的y坐标</param>
/// <param name="distance">给定的距离</param>
void Return_city(int x_coordinate, int y_coordinate, int distance) {
	CITY p_location;
	p_location = head;
	bool judge = true;
	for (size_t i = 0; i < City_num; i++)
	{
		p_location = p_location->next;
		int Relative_distance = sqrt(pow(x_coordinate - p_location->x_coordinate, 2) + pow(y_coordinate - p_location->y_coordinate, 2));
		// 计算相对距离
		if (Relative_distance <= distance) {
			cout << p_location->name << endl;
			judge = false;
		}
	}
	if (judge)	//判断是否找到要求的城市
	{
		cout << "没找到要求的城市" << endl;
	}
}

/// <summary>
/// 输入数据，且需要是合法的
/// </summary>
/// <returns>合法的数据</returns>
int Input_legal() {
	int number;
	cin >> number;
	while (!(0 < number && number <= City_num)) {
		cout << "输入有误，或超出城市个数的最大值，请重新输入合法数据" << endl;
		cin.clear();	// 清除失败状态
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// 忽略错误输入直到下一个换行符或EOF
		cin >> number;
	}
	return number;
}