#include <iostream>
using namespace std;

int Compare_string(string s, string t);
int Length_string(string Find_length);

int main()
{
	string Main_string;
	string Search_string;
	cout << "请输入主串" << endl;
	cin >> Main_string;
	cout << "请输入搜索串" << endl;
	cin >> Search_string;
	int Return_num = Compare_string(Main_string, Search_string);
	if (Return_num >= 0)
	{
		cout << "匹配位置为第" << Return_num + 1 << "个字符" << endl;
	}
	else if(Return_num == -1)
	{
		cout << "不匹配" << endl;
	}
}

/// <summary>
/// 模式匹配函数
/// </summary>
/// <param name="s">主串s</param>
/// <param name="t">搜索串t</param>
/// <returns>搜索到则返回第几个字符，否则返回-1</returns>
int Compare_string(string s, string t) {
	int s_length = Length_string(s);
	int t_length = Length_string(t);
	int i = 0;
	int j = 0;
	int count = 0;
	while (i < s_length - t_length + 1)
	{
		if (s[i] == t[j])
		{
			count = 1;
			for (size_t k = i; k < t_length + i - 1;)
			{
				k++;
				j++;
				if (s[k] == t[j])
				{
					count++;
				}
			}
			if (count == t_length)
			{
				return i;
			}
			j = 0;
		}
		i++;
	}
	return -1;
}

/// <summary>
/// 求字符串长度
/// </summary>
/// <param name="Find_length">所求字符串</param>
/// <returns>字符串长度</returns>
int Length_string(string Find_length) {
	int i = 0;
	while (Find_length[i] != NULL)
	{
		i++;
	}
	return i;
}

