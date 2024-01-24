#include <iostream>
#include <string>
using namespace std;

typedef struct Binary_tree_node {
	char data = '\0'; // 数据值
	struct Binary_tree_node* lchild = NULL; // 左子节点指针
	struct Binary_tree_node* rchild = NULL; // 右子节点指针
} Binary_tree_node, * Binary_tree;

int Create_binary_tree(Binary_tree& Tree_node, string Input_tree_string, int length);
int Inorder_traversal_first_right(Binary_tree& Inorder_binary_tree);
void Print_space(int Space_num);

int main()
{
	Binary_tree binary_tree;
	string Input_tree_string;	//AB D  CE F
	getline(cin, Input_tree_string);
	Create_binary_tree(binary_tree, Input_tree_string, Input_tree_string.size());
	Inorder_traversal_first_right(binary_tree);

	return 0;
}

/// <summary>
/// 创建二叉树
/// </summary>
/// <param name="Tree_node">二叉树</param>
/// <param name="Input_tree_string">输入的字符串</param>
/// <param name="length">字符串长度</param>
/// <returns>字符串赋值完毕则返回</returns>
int Create_binary_tree(Binary_tree& Tree_node, string Input_tree_string, int length) {
	static int Position = -1;
	Position++;
	if (length <= Position) return 0;
	else if (Input_tree_string[Position] == ' ') Tree_node = NULL;
	else {
		Tree_node = new Binary_tree_node;
		Tree_node->data = Input_tree_string[Position];
		Create_binary_tree(Tree_node->lchild, Input_tree_string, length);
		Create_binary_tree(Tree_node->rchild, Input_tree_string, length);
	}
}

/// <summary>
/// 中序遍历（右，上，左）
/// </summary>
/// <param name="Inorder_binary_tree">二叉树</param>
/// <returns>遇到空节点则返回</returns>
int Inorder_traversal_first_right(Binary_tree& Inorder_binary_tree) {
	static int count = -1;
	count++;
	if (Inorder_binary_tree == NULL) {
		count--;
		return 0;
	}
	Inorder_traversal_first_right(Inorder_binary_tree->rchild);
	Print_space(count);
	cout << Inorder_binary_tree->data << endl;

	Inorder_traversal_first_right(Inorder_binary_tree->lchild);
	count--;
}

/// <summary>
/// 打印空格
/// </summary>
/// <param name="Space_num">要打印的空格数</param>
void Print_space(int Space_num) {
	for (size_t i = 0; i < Space_num; i++) cout << " ";
}