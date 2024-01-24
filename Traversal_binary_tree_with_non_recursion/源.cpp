#include <iostream>
#include <string>
#include <stack>
using namespace std;

typedef struct Binary_tree_node {
	char data = '\0'; // 数据值
	struct Binary_tree_node* lchild = NULL; // 左子节点指针
	struct Binary_tree_node* rchild = NULL; // 右子节点指针
} Binary_tree_node, * Binary_tree;

int Create_binary_tree(Binary_tree& Tree_node, string Input_tree_string, int length);
void Preorder_traversal(Binary_tree& Preorder_binary_tree);
void Inorder_traversal(Binary_tree& Inorder_binary_tree);
void Postorder_traversal(Binary_tree& Postorder_binary_tree);

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
void Preorder_traversal(Binary_tree& Preorder_binary_tree) {
	stack<Binary_tree_node*> s;
	Binary_tree_node* current = Preorder_binary_tree;
	while (current != NULL || !s.empty()) {
		while (current != NULL) {
			cout << current->data; // 访问根节点
			s.push(current);
			current = current->lchild; // 访问左子树
		}
		if (!s.empty()) {
			current = s.top();
			s.pop();
			current = current->rchild; // 访问右子树
		}
	}
}


/// <summary>
/// 中序遍历（左，上，右）
/// </summary>
/// <param name="Inorder_binary_tree">二叉树</param>
void Inorder_traversal(Binary_tree& Inorder_binary_tree) {
	stack<Binary_tree_node*> s;
	Binary_tree_node* current = Inorder_binary_tree;
	while (current != NULL || !s.empty()) {
		while (current != NULL) {
			s.push(current);
			current = current->lchild;
		}
		if (!s.empty()) {
			current = s.top();
			s.pop();
			cout << current->data; // 访问根节点
			current = current->rchild;
		}
	}
}


/// <summary>
/// 后序遍历（左，右，上）
/// </summary>
/// <param name="Postorder_binary_tree">二叉树</param>
void Postorder_traversal(Binary_tree& Postorder_binary_tree) {
	stack<Binary_tree_node*> s1, s2;
	Binary_tree_node* current = Postorder_binary_tree;
	s1.push(current);
	while (!s1.empty()) {
		current = s1.top();
		s1.pop();
		s2.push(current);
		if (current->lchild)
			s1.push(current->lchild);
		if (current->rchild)
			s1.push(current->rchild);
	}
	while (!s2.empty()) {
		cout << s2.top()->data;
		s2.pop();
	}
}