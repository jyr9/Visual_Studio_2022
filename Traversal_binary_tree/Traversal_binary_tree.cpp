#include <iostream>
#include <string>
using namespace std;

typedef struct Binary_tree_node {
	char data = '\0'; // 数据值
	struct Binary_tree_node* lchild = NULL; // 左子节点指针
	struct Binary_tree_node* rchild = NULL; // 右子节点指针
} Binary_tree_node, * Binary_tree;

int Create_binary_tree(Binary_tree& Tree_node, string Input_tree_string, int length);
int Preorder_traversal(Binary_tree& Preorder_binary_tree);
int Inorder_traversal(Binary_tree& Inorder_binary_tree);
int Postorder_traversal(Binary_tree& Postorder_binary_tree);

int main()
{
	Binary_tree binary_tree;
	string Input_tree_string;
	getline(cin, Input_tree_string);
	Create_binary_tree(binary_tree, Input_tree_string, Input_tree_string.size());
	cout << "先序：";
	Preorder_traversal(binary_tree);
	cout << endl << "中序：";
	Inorder_traversal(binary_tree);
	cout << endl << "后序：";
	Postorder_traversal(binary_tree);
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
/// 先序遍历（上，左，右）
/// </summary>
/// <param name="Preorder_binary_tree">二叉树</param>
/// <returns>遇到空节点则返回</returns>
int Preorder_traversal(Binary_tree& Preorder_binary_tree) {
	if (Preorder_binary_tree == NULL) return 0;
	cout << Preorder_binary_tree->data;
	Preorder_traversal(Preorder_binary_tree->lchild);
	Preorder_traversal(Preorder_binary_tree->rchild);
}

/// <summary>
/// 中序遍历（左，上，右）
/// </summary>
/// <param name="Inorder_binary_tree">二叉树</param>
/// <returns>遇到空节点则返回</returns>
int Inorder_traversal(Binary_tree& Inorder_binary_tree) {
	if (Inorder_binary_tree == NULL) return 0;
	Inorder_traversal(Inorder_binary_tree->lchild);
	cout << Inorder_binary_tree->data;
	Inorder_traversal(Inorder_binary_tree->rchild);
}

/// <summary>
/// 后序遍历（左，右，上）
/// </summary>
/// <param name="Postorder_binary_tree">二叉树</param>
/// <returns>遇到空节点则返回</returns>
int Postorder_traversal(Binary_tree& Postorder_binary_tree) {
	if (Postorder_binary_tree == NULL) return 0;
	Postorder_traversal(Postorder_binary_tree->lchild);
	Postorder_traversal(Postorder_binary_tree->rchild);
	cout << Postorder_binary_tree->data;
}