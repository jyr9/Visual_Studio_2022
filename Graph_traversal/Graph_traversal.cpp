#include <iostream>
using namespace std;
#define Max_vertex_number 30    //最大顶点数=30

typedef struct Edge_node {
    int Adjacency_vertex = -1;
    struct Edge_node* next = NULL;
} Edge_node;

typedef struct Vertex_node {
    int Vertex_number = -1;
    Edge_node* First_node = NULL;
} Vertex_node, Adjacency_list[Max_vertex_number];

typedef struct Adjacency_list_graph {
    Adjacency_list adjacency_list;
    int vertex_number = 0, edge_number = 0; //顶点数和边数
} Adjacency_list_graph;

typedef struct QNode {
    int data;
    struct QNode* next = NULL;
}QNode, * QueuePtr;

typedef struct LinkQueue {
    QueuePtr front = NULL;
    QueuePtr rear = NULL;
}LinkQueue;

void Initialize_adjacency_list_graph(Adjacency_list_graph& adjacency_list_graph);
void DFS_traverse(Adjacency_list_graph& adjacency_list_graph);
void DFS(Adjacency_list_graph& adjacency_list_graph, int i);
void BFS_traverse(Adjacency_list_graph& adjacency_list_graph);
void BFS(Adjacency_list_graph& adjacency_list_graph, int i);
void InitQueue(LinkQueue& Q);
void EnQueue(LinkQueue& Q, int e);
void DeQueue(LinkQueue& Q, int& e);

bool Visited[Max_vertex_number];
int Print_edge[100];
int count_edge = 0;

int main()
{
    Adjacency_list_graph adjacency_list_graph;
    Initialize_adjacency_list_graph(adjacency_list_graph);
    cout << "DFS输出节点顺序：" << endl;
    DFS_traverse(adjacency_list_graph);
    cout << endl << "BFS输出节点顺序：" << endl;
    BFS_traverse(adjacency_list_graph);
    return 0;
}

/// <summary>
/// 初始化邻接表
/// </summary>
/// <param name="adjacency_list_graph">图</param>
void Initialize_adjacency_list_graph(Adjacency_list_graph& adjacency_list_graph) {
    int vertex_number, edge_number;
    cout << "请输入节点数" << endl;
    cin >> vertex_number;
    cout << "请输入边数" << endl;
    cin >> edge_number;
    adjacency_list_graph.vertex_number = vertex_number;
    adjacency_list_graph.edge_number = edge_number;
    for (size_t i = 0; i < vertex_number; i++)
    {
        adjacency_list_graph.adjacency_list[i].Vertex_number = i + 1;
    }
    for (size_t i = 0; i < edge_number; i++)
    {
        cout << "请输入" << edge_number << "条有向边" << endl;
        cout << "第" << i + 1 << "条：";
        int tail, head; //输入有向边
        cin >> tail >> head;
        if (adjacency_list_graph.adjacency_list[tail].First_node == NULL)   //如果头结点为空，则可以写入
        {
            adjacency_list_graph.adjacency_list[tail].First_node = new Edge_node;
            adjacency_list_graph.adjacency_list[tail].First_node->Adjacency_vertex = head;
        }
        else    //如果头结点不为空，则往下找哪个为空，写入  
        {
            Edge_node* temp_edge_node = adjacency_list_graph.adjacency_list[tail].First_node;
            while (temp_edge_node->next != NULL)
            {
                temp_edge_node = temp_edge_node->next;
            }
            temp_edge_node->next = new Edge_node;
            temp_edge_node->next->Adjacency_vertex = head;
        }
    }
}

/// <summary>
/// DFS遍历所有节点函数
/// </summary>
/// <param name="adjacency_list_graph">图</param>
void DFS_traverse(Adjacency_list_graph& adjacency_list_graph) {
    int j;
    cout << "请输入DFS从哪个节点开始" << endl;
    cin >> j;
    j = j - 1;
    for (size_t i = 0; i < adjacency_list_graph.vertex_number; i++)
    {
        Visited[i] = false;
    }
    for (int i = 0; i < adjacency_list_graph.vertex_number; i++)
    {
        if (Visited[j] == false)
        {
            DFS(adjacency_list_graph, j);
        }
        j++;
        j = j % adjacency_list_graph.vertex_number;
    }
    cout << endl << "DFS的边集为：" << endl;
    for (size_t i = 0; i < count_edge;)
    {
        cout << "(" << Print_edge[i];
        i++;
        cout << "," << Print_edge[i] << ") ";
        i++;
    }
}

/// <summary>
/// DFS主函数
/// </summary>
/// <param name="adjacency_list_graph">图</param>
/// <param name="i">数组i</param>
void DFS(Adjacency_list_graph& adjacency_list_graph, int i) {
    Visited[i] = true;
    cout << adjacency_list_graph.adjacency_list[i].Vertex_number << " ";
    Edge_node* temp_edge_node = adjacency_list_graph.adjacency_list[i].First_node;
    while (temp_edge_node != NULL)
    {
        if (Visited[temp_edge_node->Adjacency_vertex] == false)
        {
            Print_edge[count_edge] = i + 1;
            count_edge++;
            Print_edge[count_edge] = temp_edge_node->Adjacency_vertex + 1;
            count_edge++;
            DFS(adjacency_list_graph, temp_edge_node->Adjacency_vertex);
        }
        else
        {
            temp_edge_node = temp_edge_node->next;
        }
    }
}

/// <summary>
/// BFS遍历所有节点函数
/// </summary>
/// <param name="adjacency_list_graph">图</param>
void BFS_traverse(Adjacency_list_graph& adjacency_list_graph) {
    int j;
    cout << "请输入BFS从哪个节点开始" << endl;
    cin >> j;
    j = j - 1;
    count_edge = 0;
    for (size_t i = 0; i < adjacency_list_graph.vertex_number; i++)
    {
        Visited[i] = false;
    }
    for (size_t i = 0; i < adjacency_list_graph.vertex_number; i++)
    {
        if (Visited[j] == false)
        {
            BFS(adjacency_list_graph, j);
        }
        j++;
        j = j % adjacency_list_graph.vertex_number;
    }
    cout << endl << "BFS的边集为：" << endl;
    for (size_t i = 0; i < count_edge;)
    {
        cout << "(" << Print_edge[i];
        i++;
        cout << "," << Print_edge[i] << ") ";
        i++;
    }
}

/// <summary>
/// BFS主函数
/// </summary>
/// <param name="adjacency_list_graph">图</param>
/// <param name="i">数组i</param>
void BFS(Adjacency_list_graph& adjacency_list_graph, int i) {
    LinkQueue vertex_queue;
    InitQueue(vertex_queue);
    Visited[i] = true;
    cout << adjacency_list_graph.adjacency_list[i].Vertex_number << " ";
    Edge_node* enqueue_temp_edge_node = adjacency_list_graph.adjacency_list[i].First_node;
    while (enqueue_temp_edge_node != NULL)
    {
        if (Visited[enqueue_temp_edge_node->Adjacency_vertex] == false)
        {
            Visited[enqueue_temp_edge_node->Adjacency_vertex] = true;
            cout << adjacency_list_graph.adjacency_list[enqueue_temp_edge_node->Adjacency_vertex].Vertex_number << " ";
            Print_edge[count_edge] = i + 1;
            count_edge++;
            Print_edge[count_edge] = adjacency_list_graph.adjacency_list[enqueue_temp_edge_node->Adjacency_vertex].Vertex_number;
            count_edge++;
            EnQueue(vertex_queue, enqueue_temp_edge_node->Adjacency_vertex);
        }
        enqueue_temp_edge_node = enqueue_temp_edge_node->next;
    }
    while (!(vertex_queue.front == vertex_queue.rear))
    {
        int dequeue_temp_edge_num;
        DeQueue(vertex_queue, dequeue_temp_edge_num);
        Edge_node* temp_edge_node = adjacency_list_graph.adjacency_list[dequeue_temp_edge_num].First_node;
        while (temp_edge_node != NULL)// 应该是他对应的数组的下一个不是空
        {
            if (Visited[temp_edge_node->Adjacency_vertex] == false)
            {
                Visited[temp_edge_node->Adjacency_vertex] = true;
                cout << adjacency_list_graph.adjacency_list[temp_edge_node->Adjacency_vertex].Vertex_number << " ";
                Print_edge[count_edge] = adjacency_list_graph.adjacency_list[dequeue_temp_edge_num].Vertex_number;
                count_edge++;
                Print_edge[count_edge] = adjacency_list_graph.adjacency_list[temp_edge_node->Adjacency_vertex].Vertex_number;
                count_edge++;
                EnQueue(vertex_queue, temp_edge_node->Adjacency_vertex);
            }
            temp_edge_node = temp_edge_node->next;
        }
    }
}

/// <summary>
/// 初始化队列
/// </summary>
/// <param name="Q"></param>
void InitQueue(LinkQueue& Q) {
    Q.rear = new QNode;
    Q.front = Q.rear;	//如果出现这种情况，则队列为空
    Q.front->next = NULL;
}

/// <summary>
/// 入队
/// </summary>
/// <param name="Q"></param>
/// <param name="e"></param>
void EnQueue(LinkQueue& Q, int e) {
    QNode* p = new QNode;
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
}

/// <summary>
/// 出队
/// </summary>
/// <param name="Q"></param>
/// <param name="e"></param>
void DeQueue(LinkQueue& Q, int& e) {
    QNode* p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p) Q.rear = Q.front;	//判断删除后的线性表是不是空队列
    delete p;
}

/*测试数据：
8
9
0 1
1 3
3 7
4 1
4 7
0 2
2 5
5 6
2 6
*/