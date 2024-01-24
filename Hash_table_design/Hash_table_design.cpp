#include <iostream>
using namespace std;

typedef struct Hash_table {
	string name = "\0";
} Hash_table;

int Convert_name_to_key(string name);
int Convert_key_to_hash_key(int key);
int Collision_linear_probing(int hash_key);
int Search_collision_linear_probing(int search_name_hash_key, string search_name);

Hash_table hash_table[50];

int main()
{
	string name[30] = {
	"zhanyi","zhaner","zhansan" ,"zhansi" ,"zhanwu" ,"zhanliu" ,"zhanqi" ,"zhanba" ,"zhanjiu" ,"zhanshi"
	,"wangyi","wanger","wangsan","wangsi","wangwu","wangliu","wangqi","wangba","wangjiu","wangshi"
	,"liyi","lier","lisan","lisi","liwu","liliu","liqi","liba","lijiu","lishi"
	};
	for (size_t i = 0; i < 30; i++)
	{
		int key = Convert_name_to_key(name[i]);
		int hash_key = Convert_key_to_hash_key(key);
		if (hash_table[hash_key].name == "\0")
		{
			hash_table[hash_key].name = name[i];
		}
		else
		{
			int collision_hash_key = Collision_linear_probing(hash_key);
			hash_table[collision_hash_key].name = name[i];
		}
	}
	cout << "创建哈希表成功" << endl;
	cout << "请输入要查询的人名" << endl;
	string search_name;
	cin >> search_name;
	int search_name_key = Convert_name_to_key(search_name);
	int search_name_hash_key = Convert_key_to_hash_key(search_name_key);

	if (hash_table[search_name_hash_key].name == search_name)
	{
		cout << "查找成功，查找位置为" << search_name_hash_key << endl;
	}
	else
	{
		int search_name_collision_hash_key = Search_collision_linear_probing(search_name_hash_key, search_name);
		if (search_name_collision_hash_key == -1)
		{
			cout << "查找失败" << endl;
		}
		else
		{
			cout << "查找成功，查找位置为" << search_name_collision_hash_key << endl;
		}
	}
	return 0;
}

/// <summary>
/// 把名字利用ASCII码转化为key
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
int Convert_name_to_key(string name) {
	int temp_key = 0;
	for (size_t i = 0; i < name.length(); i++)
	{
		temp_key = temp_key + name[i];
	}
	return temp_key;
}

/// <summary>
/// 把key转化为hash_key
/// </summary>
/// <param name="key"></param>
/// <returns></returns>
int Convert_key_to_hash_key(int key) {
	return key % 47;	//47是<50的最小质数
}

/// <summary>
/// 通过线性探测来解决碰撞
/// </summary>
/// <param name="hash_key"></param>
/// <returns></returns>
int Collision_linear_probing(int hash_key) {
	for (size_t i = 0; i < 50; i++)
	{
		hash_key++;
		hash_key = hash_key % 50;
		if (hash_table[hash_key].name == "\0")
		{
			return hash_key;
		}
	}
	return -1;
}

/// <summary>
/// 查找时也要通过线性探测来解决碰撞
/// </summary>
/// <param name="search_name_hash_key"></param>
/// <param name="search_name"></param>
/// <returns></returns>
int Search_collision_linear_probing(int search_name_hash_key, string search_name) {
	for (size_t i = 0; i < 50; i++)
	{
		search_name_hash_key++;
		search_name_hash_key = search_name_hash_key % 50;
		if (hash_table[search_name_hash_key].name == search_name)
		{
			return search_name_hash_key;
		}
		else if (hash_table[search_name_hash_key].name == "\0")
		{
			return -1;
		}
	}
}