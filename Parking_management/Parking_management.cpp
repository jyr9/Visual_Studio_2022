#include <iostream>
using namespace std;

typedef struct Snode {
	int Car_registration_num = 0;
	int In_or_out_time = 0;
	struct Snode* next = NULL;
} Snode, * LinkStack;

typedef struct QNode {
	int Car_registration_num = 0;
	int In_or_out_time = 0;
	struct QNode* next = NULL;
} QNode, * QueuePtr;

typedef struct {
	QueuePtr front;	// front指针
	QueuePtr rear;	// rear指针
}LinkQueue;

void Push_in_parking_lot(int Car_registration_num, int In_time);
void Pop_out_parking_lot(int Car_registration_num, int Out_time);
void Enqueue_waiting_line(int Car_registration_num, int In_time);
void Initialize_stack_and_queue(LinkStack& S, LinkQueue& Q);
bool Parking_lot_full(void);
int Find_car_registration_num_same(int Car_registration_num);
void Output_parking_lot_and_waiting_line(void);
void Charge_base_on_time(int Parking_time);

LinkStack Parking_lot_stack;
LinkQueue Waiting_line_queue;

static int Parking_lot_size_n = 0;

int main()
{
	Parking_lot_size_n = 2;	//可停放n辆汽车
	Initialize_stack_and_queue(Parking_lot_stack, Waiting_line_queue);
	char In_or_out_information = '\0';	//判断作何操作
	int Car_registration_num, In_or_out_time;	//车牌号和进入/出去的时刻
	while (In_or_out_information != 'E')
	{
		cout << "请输入" << endl;
		cin >> In_or_out_information >> Car_registration_num >> In_or_out_time;
		if (In_or_out_information == 'A')
		{
			Push_in_parking_lot(Car_registration_num, In_or_out_time);
			Output_parking_lot_and_waiting_line();
		}
		else if (In_or_out_information == 'D')
		{
			Pop_out_parking_lot(Car_registration_num, In_or_out_time);
			Output_parking_lot_and_waiting_line();
		}
		else if (In_or_out_information == 'E')
		{

		}
		else
		{
			cout << "输入有误，请重新输入" << endl;
		}
	}
	cout << "已退出" << endl;
	return 0;
}

/// <summary>
/// 初始化栈和队列
/// </summary>
/// <param name="S">停车场stack</param>
/// <param name="Q">停车外排队便道queue</param>
void Initialize_stack_and_queue(LinkStack& S, LinkQueue& Q) {
	S = new Snode;
	S->next = NULL;
	Q.rear = new QNode;
	Q.front = Q.rear;
	Q.front->next = NULL;
}

/// <summary>
/// 将元素push到栈中
/// </summary>
/// <param name="Car_registration_num">车牌号</param>
/// <param name="In_time">进入时间</param>
void Push_in_parking_lot(int Car_registration_num, int In_time) {
	if (!Parking_lot_full())
	{
		Snode* p_push_node = new Snode;	//创建一个插入的节点
		p_push_node->Car_registration_num = Car_registration_num;
		p_push_node->In_or_out_time = In_time;
		p_push_node->next = Parking_lot_stack;
		Parking_lot_stack = p_push_node;
	}
	else
	{
		Enqueue_waiting_line(Car_registration_num, In_time);
	}
}

/// <summary>
/// 将元素pop出栈
/// </summary>
/// <param name="Car_registration_num">车牌号</param>
/// <param name="Out_time">出去时间</param>
void Pop_out_parking_lot(int Car_registration_num, int Out_time) {
	int i = Find_car_registration_num_same(Car_registration_num);
	LinkStack Temp_stack = Parking_lot_stack;
	LinkStack Temp_stack_save_data = Parking_lot_stack;
	if (i >= 0) {
		for (size_t j = 0; j < i; j++)
		{
			Temp_stack = Temp_stack->next;
		}
		Charge_base_on_time(Out_time - Temp_stack->In_or_out_time);
		if (i == 1)
		{
			Parking_lot_stack->next->Car_registration_num = Temp_stack_save_data->Car_registration_num;
			Parking_lot_stack->next->In_or_out_time = Temp_stack_save_data->In_or_out_time;
			Parking_lot_stack = Parking_lot_stack->next;
		}
		else
		{
			Parking_lot_stack = Parking_lot_stack->next;
		}
		for (size_t j = 0; j < i; j++)
		{
			if (Waiting_line_queue.rear->next != NULL)
			{
				Snode* Enter_node = new Snode;
				Enter_node->Car_registration_num = Waiting_line_queue.rear->Car_registration_num;
				Enter_node->In_or_out_time = Waiting_line_queue.rear->In_or_out_time;
				Enter_node->next = Parking_lot_stack;
				Parking_lot_stack = Enter_node;
				Waiting_line_queue.rear = Waiting_line_queue.rear->next;
				Waiting_line_queue.rear->Car_registration_num = 0;
				Waiting_line_queue.rear->In_or_out_time = 0;
			}
		}
	}
}

/// <summary>
/// 判断停车场是否满
/// </summary>
/// <param name=""></param>
/// <returns>true为满，false为未满</returns>
bool Parking_lot_full(void) {
	LinkStack Temp_stack = Parking_lot_stack;
	for (size_t i = 0; i < Parking_lot_size_n; i++)
	{
		Temp_stack = Temp_stack->next;
		if (Temp_stack == NULL)
		{
			return false;
		}
	}
	return true;
}

/// <summary>
/// 元素入便道的队
/// </summary>
/// <param name="Car_registration_num">车牌号</param>
/// <param name="In_time">进入时间</param>
void Enqueue_waiting_line(int Car_registration_num, int In_time) {
	QNode* p_push_node = new QNode;
	p_push_node->Car_registration_num = Car_registration_num;
	p_push_node->In_or_out_time = In_time;
	Waiting_line_queue.rear->next = p_push_node;
	p_push_node = Waiting_line_queue.rear;
}

/// <summary>
/// 判断是否车牌相同
/// </summary>
/// <param name="Car_registration_num">车牌号</param>
/// <returns>相同的车牌在栈的第几个</returns>
int Find_car_registration_num_same(int Car_registration_num) {
	LinkStack Temp_stack = Parking_lot_stack;
	for (size_t i = 0; i < Parking_lot_size_n; i++)
	{
		if (Car_registration_num == Temp_stack->Car_registration_num)
		{
			return i;
		}
		Temp_stack = Temp_stack->next;
	}
	return -1;
}

/// <summary>
/// 输出现在停车场与便道的信息
/// </summary>
/// <param name=""></param>
void Output_parking_lot_and_waiting_line(void) {
	Snode* Temp_parking_lot = Parking_lot_stack;
	LinkQueue Temp_waiting_line = Waiting_line_queue;
	int count_parking_lot = 0;
	cout << "停车场车辆信息：" << endl;
	while (Temp_parking_lot != NULL)
	{
		if (Temp_parking_lot->Car_registration_num != 0)
		{
			cout << "车牌号为" << Temp_parking_lot->Car_registration_num;
			cout << ",停入时间为" << Temp_parking_lot->In_or_out_time << endl;
		}
		Temp_parking_lot = Temp_parking_lot->next;
		count_parking_lot++;
	}
	if (Parking_lot_size_n - count_parking_lot > 0)
	{
		cout << "没有第";
		for (size_t i = 0; i < Parking_lot_size_n - count_parking_lot; i++)
		{
			cout << count_parking_lot + 1 << " ";
			count_parking_lot++;
		}
		cout << "位车" << endl;
	}
	int count_waiting_line = 0;
	if (Temp_waiting_line.rear->next != NULL)
	{
		cout << "便道车辆信息：" << endl;
		while (Temp_waiting_line.rear->next != NULL)
		{
			cout << "车牌号为" << Temp_waiting_line.rear->next->Car_registration_num;
			cout << ",停入时间为" << Temp_waiting_line.rear->next->In_or_out_time << endl;
			Temp_waiting_line.rear = Temp_waiting_line.rear->next;
			count_waiting_line++;
		}
	}
	else
	{
		cout << "便道中没有车" << endl;
	}
}

/// <summary>
/// 依据时间收费
/// </summary>
/// <param name="Parking_time">停车时长</param>
void Charge_base_on_time(int Parking_time) {
	cout << "收费标准：1分钟1元,收" << Parking_time * 1 << "元" << endl;
}