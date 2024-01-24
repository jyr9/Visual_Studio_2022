#include <iostream>
#include <string>
using namespace std;

typedef struct Binary_search_tree_node {
	int key = -1;
	Binary_search_tree_node* lchild = NULL;
	Binary_search_tree_node* rchild = NULL;
} Binary_search_tree_node, * Binary_search_tree;

int Create_binary_search_tree(Binary_search_tree& binary_search_tree, string tree_string, int string_length);
int Find_element_in_binary_serach_tree(Binary_search_tree& binary_search_tree, int find_number);
void Insert_into_binary_search_tree(Binary_search_tree& binary_search_tree, int insert_key);
bool Delete_from_binary_search_tree(Binary_search_tree& binary_search_tree, int delete_key);

int main()
{
	Binary_search_tree binary_search_tree;
	cout << "请输入二叉树序列" << endl;
	string tree_string;
	getline(cin, tree_string);
	Create_binary_search_tree(binary_search_tree, tree_string, tree_string.length());
	cout << "二叉树建立完成" << endl;

	int insert_key;
	cout << "请输入要插入的数：" << endl;
	cin >> insert_key;
	Insert_into_binary_search_tree(binary_search_tree, insert_key);

	int delete_key;
	cout << "请输入要删除的数：" << endl;
	cin >> delete_key;
	if (Delete_from_binary_search_tree(binary_search_tree, delete_key)) {
		cout << "删除成功" << endl;
	}
	else {
		cout << "删除失败" << endl;
	}


	cout << "请输入查找的数" << endl;
	int find_number;
	cin >> find_number;
	int depth = Find_element_in_binary_serach_tree(binary_search_tree, find_number);
	if (depth == -1)
	{
		cout << "查找不成功" << endl;
	}
	else
	{
		cout << "查找成功，查找深度为" << depth << endl;
	}
	return 0;
}

/// <summary>
/// 创建二叉树
/// </summary>
/// <param name="binary_search_tree_node">二叉树节点</param>
/// <param name="tree_string">输入字符串</param>
/// <param name="string_length">字符串长度</param>
/// <returns>找到最后一个就暂停</returns>
int Create_binary_search_tree(Binary_search_tree& binary_search_tree_node, string tree_string, int string_length) {
	static int tree_string_index = -1;
	tree_string_index++;
	binary_search_tree_node = new Binary_search_tree_node;
	binary_search_tree_node->key = tree_string[tree_string_index] - '0';
	if (tree_string_index >= string_length - 1) return 0;
	if (tree_string[tree_string_index] < tree_string[tree_string_index + 1])
	{
		Create_binary_search_tree(binary_search_tree_node->rchild, tree_string, string_length);
	}
	else if (tree_string[tree_string_index] > tree_string[tree_string_index + 1]) {
		Create_binary_search_tree(binary_search_tree_node->lchild, tree_string, string_length);
	}
}

/// <summary>
/// 查找函数
/// </summary>
/// <param name="binary_search_tree">二叉树节点</param>
/// <param name="find_number">要寻找的数</param>
/// <returns>如果寻找成功，返回查找深度，否则返回-1</returns>
int Find_element_in_binary_serach_tree(Binary_search_tree& binary_search_tree, int find_number) {
	static int depth = 0;
	depth++;
	if (binary_search_tree == NULL)
	{
		return -1;
	}
	else if (find_number < binary_search_tree->key)
	{
		Find_element_in_binary_serach_tree(binary_search_tree->lchild, find_number);
	}
	else if (find_number > binary_search_tree->key) {
		Find_element_in_binary_serach_tree(binary_search_tree->rchild, find_number);
	}
	else if (find_number == binary_search_tree->key)
	{
		return depth;
	}
}

/// <summary>
/// 插入函数
/// </summary>
/// <param name="binary_search_tree">二叉树节点</param>
/// <param name="insert_key">插入值</param>
void Insert_into_binary_search_tree(Binary_search_tree& binary_search_tree, int insert_key) {
	if (binary_search_tree == NULL) {
		binary_search_tree = new Binary_search_tree_node;
		binary_search_tree->key = insert_key;
		binary_search_tree->lchild = NULL;
		binary_search_tree->rchild = NULL;
	}
	else if (insert_key < binary_search_tree->key) {
		Insert_into_binary_search_tree(binary_search_tree->lchild, insert_key);
	}
	else if (insert_key > binary_search_tree->key) {
		Insert_into_binary_search_tree(binary_search_tree->rchild, insert_key);
	}
}

/// <summary>
/// 删除函数
/// </summary>
/// <param name="binary_search_tree">二叉树节点</param>
/// <param name="delete_key">删除值</param>
/// <returns>删除成功与否</returns>
bool Delete_from_binary_search_tree(Binary_search_tree& binary_search_tree, int delete_key) {
	if (binary_search_tree == NULL) return false; // 未找到要删除的键

	if (delete_key < binary_search_tree->key) {
		return Delete_from_binary_search_tree(binary_search_tree->lchild, delete_key);
	}
	else if (delete_key > binary_search_tree->key) {
		return Delete_from_binary_search_tree(binary_search_tree->rchild, delete_key);
	}
	else { // 找到了要删除的节点
		if (binary_search_tree->lchild != NULL && binary_search_tree->rchild != NULL) { // 两个子节点
			Binary_search_tree_node* temp = binary_search_tree->rchild;
			while (temp->lchild != NULL) temp = temp->lchild; // 找到右子树的最小节点
			binary_search_tree->key = temp->key;
			return Delete_from_binary_search_tree(binary_search_tree->rchild, temp->key); // 删除替换后的重复节点
		}
		else { // 一个或零个子节点
			Binary_search_tree_node* temp = binary_search_tree;
			if (binary_search_tree->lchild != NULL) binary_search_tree = binary_search_tree->lchild;
			else binary_search_tree = binary_search_tree->rchild;
			delete temp;
			return true;
		}
	}
}
