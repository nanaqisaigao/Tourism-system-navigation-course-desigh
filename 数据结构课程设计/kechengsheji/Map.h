#ifndef MAP_H_INCLUDED
//#ifndef 是"if not defined"的简写
//指如果EDGE_H_INCLUDED没有定义则执行#define EDGE_H_INCLUDED
#define MAP_H_INCLUDED
#include <vector>
//Vector 是一个类模板。不是一种数据类型。 Vector<int>是一种数据类型。
//vector是向量类型，可以容纳许多类型的数据，因此也被称为容器(可以理解为动态数组，是封装好了的类）
#include "Node.h"
#include "Edge.h"
using namespace std;

class Map
{
public:
    Map(int capacity);
    ~Map();
    bool addNode(Node *pNode);// 向图中添加顶点

    void resetNode();//重置顶点
    bool setValueToMatrixForUndirectedGraph(int row,int cli,int val=1);//设置邻接矩阵

    void printMatrix();//打印邻接矩阵
    void DFS(int nodeIndex,int beginNum);//深度优先遍历

    void seekNode(int number);//查询景点
    void mapDFS(int nodeIndex);//旅游景点导航
    void primTree(int nodeIndex);//普利姆算法生成树  找最小生成树
    void Dijkstra(int v0,int v1);//迪杰斯特拉算法   用于查找图中某个顶点到其它所有顶点的最短路径
    bool hasNode(string nodeName);
    bool hasEdge(int NodeAnum,int NodeBnum);

private:
    bool getValueFromMatricx(int row,int col,int &val);//从矩阵中获取权值
    void breadthFirstTraverseImpl(vector <int> preVec);//广度优先遍历实现函数

    int getMinEdge(vector<Edge> edgeVec);
private:
    int m_iCapacity;//最多可以容纳的顶点数
    int m_iNodeCount; //已经添加的顶点个数
    Node *m_pNodeArray;//用来存放顶点数组
    int *m_pMatrix; //用来存放邻接矩阵
    Edge *m_pEdge;//用来存放边数组


};

#endif // MAP_H_INCLUDED
