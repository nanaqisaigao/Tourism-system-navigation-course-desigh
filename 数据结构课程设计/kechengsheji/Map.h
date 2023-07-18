#ifndef MAP_H_INCLUDED
//#ifndef ��"if not defined"�ļ�д
//ָ���EDGE_H_INCLUDEDû�ж�����ִ��#define EDGE_H_INCLUDED
#define MAP_H_INCLUDED
#include <vector>
//Vector ��һ����ģ�塣����һ���������͡� Vector<int>��һ���������͡�
//vector���������ͣ���������������͵����ݣ����Ҳ����Ϊ����(�������Ϊ��̬���飬�Ƿ�װ���˵��ࣩ
#include "Node.h"
#include "Edge.h"
using namespace std;

class Map
{
public:
    Map(int capacity);
    ~Map();
    bool addNode(Node *pNode);// ��ͼ����Ӷ���

    void resetNode();//���ö���
    bool setValueToMatrixForUndirectedGraph(int row,int cli,int val=1);//�����ڽӾ���

    void printMatrix();//��ӡ�ڽӾ���
    void DFS(int nodeIndex,int beginNum);//������ȱ���

    void seekNode(int number);//��ѯ����
    void mapDFS(int nodeIndex);//���ξ��㵼��
    void primTree(int nodeIndex);//����ķ�㷨������  ����С������
    void Dijkstra(int v0,int v1);//�Ͻ�˹�����㷨   ���ڲ���ͼ��ĳ�����㵽�������ж�������·��
    bool hasNode(string nodeName);
    bool hasEdge(int NodeAnum,int NodeBnum);

private:
    bool getValueFromMatricx(int row,int col,int &val);//�Ӿ����л�ȡȨֵ
    void breadthFirstTraverseImpl(vector <int> preVec);//������ȱ���ʵ�ֺ���

    int getMinEdge(vector<Edge> edgeVec);
private:
    int m_iCapacity;//���������ɵĶ�����
    int m_iNodeCount; //�Ѿ���ӵĶ������
    Node *m_pNodeArray;//������Ŷ�������
    int *m_pMatrix; //��������ڽӾ���
    Edge *m_pEdge;//������ű�����


};

#endif // MAP_H_INCLUDED
