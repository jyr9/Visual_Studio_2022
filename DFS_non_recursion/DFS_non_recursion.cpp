#include<iostream>
using namespace std;

//实现栈类型
#define INITSIZE 100
#define INCREASIZE 10
typedef struct stack_ {
    int* top;//栈顶指针
    int* bottom;//栈底指针
    int sSize;//栈当前可使用的最大容量
}SqStack;

//实现图
#define MaxVerNum 100
bool visited[MaxVerNum];//用于标识结点是否已被访问过
//邻接表边结点类型
typedef struct ArcNode {
    int adjvex;//邻接点域
    struct ArcNode* next;//指针域
}ArcNode;
//表头结点类型
typedef struct Vnode {
    char vertex; //顶点域
    ArcNode* firstedge; //边表头指针
} Vnode, AdjList[MaxVerNum];
//图的类型(以邻接表方式存储)
typedef struct ALGraph {
    AdjList vertices; /*邻接表*/
    int vexnum, arcnum; /*顶点数和边数*/
} ALGraph;

//栈函数
void initS(SqStack& pare);//初始化堆栈
void pushS(SqStack& pare, int x);//在栈顶加入一个元素
bool popS(SqStack& pare, int& x);//从栈顶弹出一个元素
int topS(SqStack& pare);//从栈顶读取一个元素
bool sEmpty(SqStack pare);//判断堆栈是否为空
int sLength(SqStack pare);//计算堆栈长度
//图函数
void creat(ALGraph& theGraph);//初始化图
int loca(ALGraph theGraph, char temp);//找顶点所在的位置
void ListCout(ALGraph theGraph);//输出邻接表
void DFSTravers(ALGraph theGraph);//深度优先遍历


int main()
{
    //创建图
    ALGraph theGraph;
    creat(theGraph);
    //输出邻接表
    ListCout(theGraph);
    //接受用户输入，指定的节点为起点
    cout << endl << "深度优先遍历:" << endl;
    //深度优先遍历
    DFSTravers(theGraph);
}


void initS(SqStack& pare)//初始化堆栈
{
    pare.bottom = (int*)malloc(sizeof(int) * INITSIZE);//分配空间
    if (!pare.bottom) exit(OVERFLOW);//若没有分配到空间则报错并退出
    pare.top = pare.bottom;//若无异常，栈顶与栈底指向起始位置
    pare.sSize = INITSIZE;//初始化栈的大小
}
void pushS(SqStack& pare, int x) {//在栈顶加入一个元素
    if (sLength(pare) >= pare.sSize) {
        pare.bottom = (int*)realloc(pare.bottom, (pare.sSize + INCREASIZE * sizeof(int)));//如果内存不够则重新分配内存
        if (!pare.bottom) exit(OVERFLOW);//若没有分配到空间则报错并退出
        pare.top = pare.bottom + INCREASIZE;//若无异常，栈顶指针指向栈底指针+原栈长度的大小（即比原来多了1）
        pare.sSize += INCREASIZE;//栈的大小增加
    }
    *pare.top++ = x;//把x赋给当前栈顶指针指向的空间后，栈顶指针再向上挪动一位
}
bool popS(SqStack& pare, int& x) {//从栈顶弹出一个元素
    if (sEmpty(pare)) return false;//先判断是否为空
    else {
        x = *--pare.top;//栈顶指针再向下挪动一位后，把当前栈顶指针指向的空间赋给X
    }
    return true;
}
int topS(SqStack& pare) {//从栈顶读取一个元素
    int x{ 0 };
    if (sEmpty(pare)) cout << "当前无可读取元素" << endl;//先判断是否为空
    else {
        x = *pare.top;//把当前栈顶指针指向的空间赋给X
        return x;
    }
}
bool sEmpty(SqStack pare) {//判断堆栈是否为空
    if (pare.top == pare.bottom) return true;
    else return false;
}
int sLength(SqStack pare) {//计算堆栈长度
    return pare.top - pare.bottom;
}
//初始化图
void creat(ALGraph& theGraph) {
    cout << "请分别输入顶点数和边数：" << endl;
    cin >> theGraph.vexnum >> theGraph.arcnum;
    cout << "请输入顶点信息：" << endl;
    //读入顶点
    for (int i = 0; i < theGraph.vexnum; i++) {
        cout << "请输入第" << i + 1 << "个结点的值（字符）:" << endl;
        cin >> theGraph.vertices[i].vertex;
        theGraph.vertices[i].firstedge = NULL;
    }
    //读入边
    for (int i = 0; i < theGraph.arcnum; i++) {
        cout << "请输入边(vi,vj)的顶点信息：" << endl;
        char v1, v2;
        cin >> v1 >> v2;
        int x = loca(theGraph, v1);
        int y = loca(theGraph, v2);

        ArcNode* e = new ArcNode;
        //添加到vi的邻接表
        ArcNode* p = theGraph.vertices[x].firstedge;
        if (p == NULL) {//如果边表头指针为空，则设置e为头指针
            theGraph.vertices[x].firstedge = e;
        }
        else {
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = e;//如果边表头指针不为空，则指针指向e
        }
        e->adjvex = y;
        e->next = NULL;
        //同理,添加到vj的邻接表
        ArcNode* e2 = new ArcNode;
        ArcNode* p2 = theGraph.vertices[y].firstedge;
        if (p2 == NULL) {
            theGraph.vertices[y].firstedge = e2;
        }
        else {
            while (p2->next != NULL) {
                p2 = p2->next;
            }
            p2->next = e2;
        }
        e2->adjvex = x;
        e2->next = NULL;
    }
}
//找顶点所在的位置,即adjvex,方便创建邻接表
int loca(ALGraph theGraph, char temp) {
    for (int i = 0; i < theGraph.vexnum; i++) {
        if (temp == theGraph.vertices[i].vertex) {
            return i;
        }
    }
    return -1;
}
//输出邻接表
void ListCout(ALGraph theGraph) {
    cout << "图创建完成，其邻接表如下所示：" << endl;
    for (int i = 0; i < theGraph.vexnum; i++) {//循环邻接表
        cout << theGraph.vertices[i].vertex;//输出顶点域
        //循环输出邻接点域
        ArcNode* p = theGraph.vertices[i].firstedge;
        while (p) {
            cout << "-->" << p->adjvex;
            p = p->next;
        }
        cout << endl;
    }
}

//深度优先遍历
void DFSTravers(ALGraph theGraph) {
    //声明并初始化一个栈
    SqStack stc;
    initS(stc);
    //初始化每个结点都未被访问过
    for (int i = 0; i < theGraph.vexnum; i++) {
        visited[i] = false;
    }
    //从给出的初始结点开始顶点入栈,遍历，输出结点访问序列
    int i = 0, j = 0;
    int num = 0;//统计一共访问过多少结点
    pushS(stc, i);
    cout << "输出结点访问序列:" << endl;
    while (num != theGraph.vexnum) {//没有把所有的节点都访问一遍
        while (!sEmpty(stc)) {//如果栈不为空，且没被访问过，就弹出最顶上的元素并输出
            popS(stc, i);
            if (!visited[i]) {
                visited[i] = true;//标志为已被访问过
                cout << theGraph.vertices[i].vertex << " ";
                num++;
            }
            ArcNode* p = theGraph.vertices[i].firstedge;
            while (p) {
                j = p->adjvex;
                if (!visited[j]) {
                    visited[j] = true;//标志为已被访问过
                    cout << theGraph.vertices[j].vertex << " ";
                    num++;
                    pushS(stc, j);
                    if (theGraph.vertices[j].firstedge) p = theGraph.vertices[j].firstedge;
                }
                else p = p->next;
            }
            popS(stc, i);
        }
        for (int k = 0; k < theGraph.vexnum; k++) {
            if (visited[k] = false) {
                pushS(stc, k);
                break;
            }
        }
    }
}