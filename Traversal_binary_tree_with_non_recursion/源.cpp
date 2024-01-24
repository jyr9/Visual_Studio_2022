#include <iostream>
#include <string>
#include <stack>
using namespace std;

typedef struct Binary_tree_node {
	char data = '\0'; // ����ֵ
	struct Binary_tree_node* lchild = NULL; // ���ӽڵ�ָ��
	struct Binary_tree_node* rchild = NULL; // ���ӽڵ�ָ��
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
	cout << "����";
	Preorder_traversal(binary_tree);
	cout << endl << "����";
	Inorder_traversal(binary_tree);
	cout << endl << "����";
	Postorder_traversal(binary_tree);
	return 0;
}

/// <summary>
/// ����������
/// </summary>
/// <param name="Tree_node">������</param>
/// <param name="Input_tree_string">������ַ���</param>
/// <param name="length">�ַ�������</param>
/// <returns>�ַ�����ֵ����򷵻�</returns>
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
/// ����������ϣ����ң�
/// </summary>
/// <param name="Preorder_binary_tree">������</param>
void Preorder_traversal(Binary_tree& Preorder_binary_tree) {
	stack<Binary_tree_node*> s;
	Binary_tree_node* current = Preorder_binary_tree;
	while (current != NULL || !s.empty()) {
		while (current != NULL) {
			cout << current->data; // ���ʸ��ڵ�
			s.push(current);
			current = current->lchild; // ����������
		}
		if (!s.empty()) {
			current = s.top();
			s.pop();
			current = current->rchild; // ����������
		}
	}
}


/// <summary>
/// ������������ϣ��ң�
/// </summary>
/// <param name="Inorder_binary_tree">������</param>
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
			cout << current->data; // ���ʸ��ڵ�
			current = current->rchild;
		}
	}
}


/// <summary>
/// ������������ң��ϣ�
/// </summary>
/// <param name="Postorder_binary_tree">������</param>
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