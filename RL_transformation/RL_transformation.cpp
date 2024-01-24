#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

typedef struct RL {
public:
	int state_set[100] = { 0,1,2,3,4,5,6,7,8,9 };	//状态集合
	int input_alphabet[2] = { 0,1 };	//输入字母表
	int State_transition_function[200][3];	//状态转移函数
	int initial_state = state_set[0];	//开始状态
	int termination_state_set[100];	//终止状态集合
} RL;

typedef struct RL_num {
public:
	int first_state = -1;
	int last_state = -1;
} RL_num;


void Convert_expression_to_number(string input_string, int& string_index, RL_num rl_num);
void Closure(string input_string, int& string_index, RL_num& rl_num);
void Write_in_RL(int first_num, int input_letter, int second_num, RL_num& rl_num);


static int state_index = 1;	//记录状态输入到第几个

static int state_transition_index = 0;	//状态转移函数输入到第几个

RL rl;

int main()
{
	RL_num rl_num;

	int string_index = 0;
	string input_string;	//记录输入字符串读到第几个
	cin >> input_string;


	while (string_index != input_string.length())
	{
		Convert_expression_to_number(input_string, string_index, rl_num);

	}

	//stack <int> stk;
	//for (int i = 0; i < 10; i++) {
	//	stk.push(i);
	//}
	//cout << stk.size() << endl;
	//cout << stk.top() << endl;
	//stk.pop();
	//cout << stk.empty() << endl;


	return 0;
}

void Convert_expression_to_number(string input_string, int& string_index, RL_num rl_num) {
	if (input_string[string_index] == '(')
	{
		string_index++;
		int begin_string_index = string_index;
		queue <char> string_number;
		int count_left_bracket = 0;
		int count_right_bracket = -1;
		while (true)
		{
			if (input_string[string_index] == '(')
			{
				count_left_bracket++;
			}
			else if (input_string[string_index] == ')')
			{
				count_right_bracket++;
			}
			string_index++;
			if (count_left_bracket == count_right_bracket) {
				break;
			}
			string_number.push(input_string[string_index]);
		}
		if (input_string[string_index] == '*')	//下一个如果是*
		{
			rl_num.first_state = state_index;

			while (begin_string_index != string_index)
			{
				Convert_expression_to_number(input_string, begin_string_index, rl_num);

			}

			rl_num.last_state = state_index;
			Closure(input_string, string_index, rl_num);
			string_index++;
		}





	}
	else if (input_string[string_index] == '+')
	{
		//Or()
	}
	else if (input_string[string_index] == ')')
	{
		string_index++;
	}
	else    //下一个是数字
	{
		Write_in_RL(state_index, input_string[string_index] - '0', state_index + 1, rl_num);
		state_index++;
		string_index++;
		if (input_string[string_index] == '*')	//下一个如果是*
		{
			Closure(input_string, string_index, rl_num);
			string_index++;
		}
	}

}


void Closure(string input_string, int& string_index, RL_num& rl_num) {
	rl.State_transition_function[state_transition_index][0] = rl_num.first_state;
	rl.State_transition_function[state_transition_index][1] = -1;	//ε
	rl.State_transition_function[state_transition_index][2] = rl_num.last_state;
	state_transition_index++;
	rl.State_transition_function[state_transition_index][0] = rl_num.last_state;
	rl.State_transition_function[state_transition_index][1] = -1;	//ε
	rl.State_transition_function[state_transition_index][2] = rl_num.first_state;
	state_transition_index++;
}

void Write_in_RL(int first_num, int input_letter, int second_num, RL_num& rl_num) {
	rl.State_transition_function[state_transition_index][0] = first_num;
	rl.State_transition_function[state_transition_index][1] = input_letter;
	rl.State_transition_function[state_transition_index][2] = second_num;
	rl_num.first_state = first_num;
	rl_num.last_state = second_num;
	state_transition_index++;
}


/*

RL Or(string s, RL& rl, RL& rl1) {
	//rl1 + Convert_expression_to_number()

}
*/