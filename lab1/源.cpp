#include <iostream>
#include <string>
#include <cmath>
using namespace std;

typedef struct node {	//�����ʼ��
	string name{ "null" };
	int x_coordinate = 0;
	int y_coordinate = 0;
	struct node* next{ NULL };
} node, *CITY;
CITY head = new node;

int City_num = 5;	//һ��ʼ����5������

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
	bool Decide_continue = true;	//�ж��Ƿ����
	while (Decide_continue)
	{
		cout << "������Ҫ���еĲ�����" << endl;
		cout << "��0���˳�" << endl;
		cout << "��1�����ӳ�����Ϣ" << endl;
		cout << "��2��ɾ��������Ϣ" << endl;
		cout << "��3�����ĳ�����Ϣ" << endl;
		cout << "��4����ѯ������Ϣ" << endl;
		cout << "��5����������������������" << endl;
		cout << "��6��������������룬����С�ھ���ĳ���" << endl;

		int Selected_num;	//ѡ�����
		cin >> Selected_num;

		if (Selected_num == 0)
		{
			cout << "���˳�" << endl;
			Decide_continue = false;
		}

		else if (Selected_num == 1)	// ��
		{
			cout << "��������Ҫ���ӳ��е�λ��" << endl;
			int Create_number = Input_legal();
			Create_city(Create_number);
		}

		else if (Selected_num == 2)	// ɾ
		{
			cout << "��������Ҫɾ���ĳ���λ��" << endl;
			int Delete_number = Input_legal();
			Delete_city(Delete_number);
		}

		else if (Selected_num == 3)	// ��
		{
			cout << "��������Ҫ���ĵĳ���λ��" << endl;
			int Update_number = Input_legal();
			Update_city(Update_number);
		}

		else if (Selected_num == 4)	// ��
		{
			cout << "��������Ҫ��ѯ�ĳ���λ��" << endl;
			int Read_number = Input_legal();
			Read_city(Read_number);
		}

		else if (Selected_num == 5)	//��������������������
		{
			cout << "��������Ҫ��ѯ�ĳ�������" << endl;
			string City_name;
			cin >> City_name;
			CITY p_city_name = Judge_city_name(City_name);
			if (p_city_name == NULL) {
				cout << "δ��ѯ�����������������������" << endl;
			}
			else {
				cout << "����" << City_name << "��x����Ϊ" << p_city_name->x_coordinate << "��y����Ϊ" << p_city_name->y_coordinate << endl;
			}
		}

		else if (Selected_num == 6)	//������������룬����С�ھ���ĳ���
		{
			int x_coordinate;
			int y_coordinate;
			int distance;
			cout << "��������Ҫ��ѯ��x����λ��" << endl;
			cin >> x_coordinate;
			cout << "��������Ҫ��ѯ��y����λ��" << endl;
			cin >> y_coordinate;
			cout << "��������Ҫ��ѯ�ľ���" << endl;
			cin >> distance;
			Return_city(x_coordinate, y_coordinate, distance);
		}

		else
		{
			cout << "�밴Ҫ������" << endl;	//����׳��
		}
	}
}

/// <summary>
/// City����ֵ����
/// </summary>
void City_data(void) {
	CITY p = head;

	for (size_t i = 0; i < City_num; i++)	// ���������
	{
		CITY New_node = new node;
		p->next = New_node;
		p = p->next;
	}

	Find_element(1)->name = "beijing";	//����ֵ
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
/// �ҵ���i��Ԫ�صĵ�ַ
/// </summary>
/// <param name="number">Ҫ�ҵĵ�i��Ԫ��</param>
/// <returns>��i��Ԫ�صĵ�ַ</returns>
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
/// �жϳ�����������������
/// </summary>
/// <param name="City_name">������</param>
/// <returns>��������Ӧ��������</returns>
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
/// ���Ӻ���
/// p_prior_location��ǰһ��Ԫ�صĵ�ַ
/// Create_element��Ҫ�ӵ�Ԫ�صĵ�ַ
/// </summary>
/// <param name="Create_number">Ҫ�ӵ��ڼ���Ԫ��ǰ</param>
void Create_city(int Create_number) {
	CITY p_prior_location = Find_element(Create_number - 1);
	CITY Create_element = new node;
	string New_name;
	int New_x_coordinate, New_y_coordinate;
	cout << "���������ӵĳ�������" << endl;
	cin >> New_name;
	cout << "���������ӳ��е�x����" << endl;
	cin >> New_x_coordinate;
	cout << "���������ӳ��е�y����" << endl;
	cin >> New_y_coordinate;
	Create_element->name = New_name;
	Create_element->x_coordinate = New_x_coordinate;
	Create_element->y_coordinate = New_y_coordinate;
	Create_element->next = p_prior_location->next;
	p_prior_location->next = Create_element;
	City_num++;
	cout << "���ڵ�" << Create_number << "������ǰ" << "���ӳ���" << New_name << endl;
}

/// <summary>
/// ɾ��Ԫ��
/// p_prior_location��ǰһ��Ԫ�صĵ�ַ
/// p_location�Ǵ�Ԫ�صĵ�ַ
/// </summary>
/// <param name="Delete_number">Ҫɾ���ڼ���Ԫ��</param>
void Delete_city(int Delete_number) {
	CITY p_prior_location = Find_element(Delete_number - 1);
	CITY p_location = p_prior_location->next;
	p_prior_location->next = p_location->next;
	free(p_location);
	City_num--;
	cout << "��ɾ����" << Delete_number << "������" << endl;
}

/// <summary>
/// �޸ĺ���
/// p_location�Ǵ�Ԫ�صĵ�ַ
/// </summary>
/// <param name="Update_number">Ҫ��ĵڼ���Ԫ��</param>
void Update_city(int Update_number) {
	CITY p_location = Find_element(Update_number);
	string New_name;
	int New_x_coordinate, New_y_coordinate;
	cout << "�������޸ĵĳ�������" << endl;
	cin >> New_name;
	cout << "�������޸ĳ��е�x����" << endl;
	cin >> New_x_coordinate;
	cout << "�������޸ĳ��е�y����" << endl;
	cin >> New_y_coordinate;
	p_location->name = New_name;
	p_location->x_coordinate = New_x_coordinate;
	p_location->y_coordinate = New_y_coordinate;
	cout << "���޸ĵ�" << Update_number << "������Ϊ����" << New_name << endl;
}

/// <summary>
/// ��ѯ����
/// p_location�Ǵ�Ԫ�صĵ�ַ
/// </summary>
/// <param name="Read_number">Ҫ���ѯ�ڼ���Ԫ��</param>
void Read_city(int Read_number) {
	CITY p_location = Find_element(Read_number);
	cout << "��" << Read_number << "����������Ϊ" << p_location->name << endl;
	cout << "x����Ϊ" << p_location->x_coordinate << endl;
	cout << "y����Ϊ" << p_location->y_coordinate << endl;
}

/// <summary>
/// ������������룬����С�ھ���ĳ���
/// </summary>
/// <param name="x_coordinate">������x����</param>
/// <param name="y_coordinate">������y����</param>
/// <param name="distance">�����ľ���</param>
void Return_city(int x_coordinate, int y_coordinate, int distance) {
	CITY p_location;
	p_location = head;
	bool judge = true;
	for (size_t i = 0; i < City_num; i++)
	{
		p_location = p_location->next;
		int Relative_distance = sqrt(pow(x_coordinate - p_location->x_coordinate, 2) + pow(y_coordinate - p_location->y_coordinate, 2));
		// ������Ծ���
		if (Relative_distance <= distance) {
			cout << p_location->name << endl;
			judge = false;
		}
	}
	if (judge)	//�ж��Ƿ��ҵ�Ҫ��ĳ���
	{
		cout << "û�ҵ�Ҫ��ĳ���" << endl;
	}
}

/// <summary>
/// �������ݣ�����Ҫ�ǺϷ���
/// </summary>
/// <returns>�Ϸ�������</returns>
int Input_legal() {
	int number;
	cin >> number;
	while (!(0 < number && number <= City_num)) {
		cout << "�������󣬻򳬳����и��������ֵ������������Ϸ�����" << endl;
		cin.clear();	// ���ʧ��״̬
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// ���Դ�������ֱ����һ�����з���EOF
		cin >> number;
	}
	return number;
}