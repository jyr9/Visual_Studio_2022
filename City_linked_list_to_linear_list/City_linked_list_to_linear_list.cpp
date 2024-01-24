#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

struct City {
    string name = "null";
    int x_coordinate = 0;
    int y_coordinate = 0;
};

vector<City> cities;

void City_data();
City* Judge_city_name(const string& City_name);
void Create_city(int Create_number);
void Delete_city(int Delete_number);
void Update_city(int Update_number);
void Read_city(int Read_number);
void Return_city(int x_coordinate, int y_coordinate, int distance);
int Input_legal();

int main(void) {
    City_data();
    bool Decide_continue = true;    //判断是否继续
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
			City* p_city_name = Judge_city_name(City_name);
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

void City_data() {
    cities = {
        {"beijing", 100, 100},
        {"shanghai", 200, 200},
        {"guangzhou", 300, 300},
        {"shenzhen", 400, 400},
        {"tongxian", 500, 500}
    };
}

City* Judge_city_name(const string& City_name) {
    for (auto& city : cities) {
        if (city.name == City_name) {
            return &city;
        }
    }
    return nullptr;
}

void Create_city(int Create_number) {
    string New_name;
    int New_x_coordinate, New_y_coordinate;
    cout << "请输入增加的城市名称" << endl;
    cin >> New_name;
    cout << "请输入增加城市的x坐标" << endl;
    cin >> New_x_coordinate;
    cout << "请输入增加城市的y坐标" << endl;
    cin >> New_y_coordinate;

    City newCity = { New_name, New_x_coordinate, New_y_coordinate };
    cities.insert(cities.begin() + Create_number - 1, newCity);

    cout << "已在第" << Create_number << "个城市前" << "增加城市" << New_name << endl;
}

void Delete_city(int Delete_number) {
    cities.erase(cities.begin() + Delete_number - 1);
    cout << "已删除第" << Delete_number << "个城市" << endl;
}

void Update_city(int Update_number) {
    string New_name;
    int New_x_coordinate, New_y_coordinate;
    cout << "请输入修改的城市名称" << endl;
    cin >> New_name;
    cout << "请输入修改城市的x坐标" << endl;
    cin >> New_x_coordinate;
    cout << "请输入修改城市的y坐标" << endl;
    cin >> New_y_coordinate;

    cities[Update_number - 1] = { New_name, New_x_coordinate, New_y_coordinate };

    cout << "已修改第" << Update_number << "个城市为城市" << New_name << endl;
}

void Read_city(int Read_number) {
    cout << "第" << Read_number << "个城市名称为" << cities[Read_number - 1].name << endl;
    cout << "x坐标为" << cities[Read_number - 1].x_coordinate << endl;
    cout << "y坐标为" << cities[Read_number - 1].y_coordinate << endl;
}

void Return_city(int x_coordinate, int y_coordinate, int distance) {
    bool judge = true;
    for (const auto& city : cities) {
        int Relative_distance = sqrt(pow(x_coordinate - city.x_coordinate, 2) + pow(y_coordinate - city.y_coordinate, 2));
        if (Relative_distance <= distance) {
            cout << city.name << endl;
            judge = false;
        }
    }
    if (judge) {
        cout << "没找到要求的城市" << endl;
    }
}

int Input_legal() {
    int number;
    cin >> number;
    while (!(0 < number && number <= cities.size())) {
        cout << "输入有误，或超出城市个数的最大值，请重新输入合法数据" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> number;
    }
    return number;
}
