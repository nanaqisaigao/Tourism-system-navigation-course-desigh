#include<iostream>
#include<vector>
#include<memory.h>
//memset //��ʼ���ڴ�
//��һ����������ʼ���ڴ���׵�ַ
//�ڶ������������ڴ��ʼ����ʲôֵ
//���������������׵�ַ��ʼ���ٸ�ֵ����Ϊ0
//memcpy //�ڴ濽��
// 1�Σ�Ŀ��ռ���׵�ַ
// 2�Σ�Դ�ռ���׵�ַ
// 3�Σ���Դ�ռ俽�����ٸ��ֽڵ�����
//memcmp //�ڴ�Ƚ�
//��һ������������Ƚϵ��׵�ַ
//�ڶ�������������Ƚϵ��׵�ַ
//���������������׵�ַ��ʼ�Ƚϵ��ֽ���
#include "Map.h"
using namespace std;
vector <int> nodeVec;

Map::Map(int capacity)
{
    m_iCapacity=capacity;
    m_iNodeCount=0;
    m_pNodeArray=new Node[m_iCapacity];
    m_pMatrix=new int[m_iCapacity*m_iCapacity];
    memset(m_pMatrix,0,m_iCapacity*m_iCapacity*sizeof(int));
    //memset��һ����ʼ�������������ǽ�ĳһ���ڴ��е�ȫ������Ϊָ����ֵ��

    m_pEdge=new Edge[m_iCapacity-1];
}
Map::~Map()
{
    delete []m_pNodeArray;
    delete []m_pMatrix;
    delete []m_pEdge;
}

bool Map::addNode(Node *pNode)
{
    m_pNodeArray[m_iNodeCount].m_number=pNode->m_number;
    m_pNodeArray[m_iNodeCount].m_name=pNode->m_name;
    m_pNodeArray[m_iNodeCount].m_introduction=pNode->m_introduction;
    m_iNodeCount++;
    return true;
}

void Map::resetNode()//��������Ϊδ���ʹ�
{
    for(int i=0;i<m_iNodeCount;i++)
    {
        m_pNodeArray[i].visited=false;
    }
}

bool Map::setValueToMatrixForUndirectedGraph(int row,int col,int val)
{
    m_pMatrix[row*m_iCapacity+col]=val;
    m_pMatrix[col*m_iCapacity+row]=val;
    return true;
}

void Map::printMatrix()
{
    for(int i=0;i<m_iCapacity;i++)
    {
        for(int k=0;k<m_iCapacity;k++)
        {
            cout<<m_pMatrix[i*m_iCapacity+k]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
bool Map::getValueFromMatricx(int row,int col,int &val)
{
    if(row<0||row>=m_iCapacity)
    {
        return false;
    }
    if(col<0||col>=m_iCapacity)
    {
        return false;
    }
    val=m_pMatrix[row*m_iCapacity+col];
    return true;
}

void Map::seekNode(int number)
{
    cout<<m_pNodeArray[number].m_number<<endl;
    cout<<m_pNodeArray[number].m_name<<endl;
    cout<<m_pNodeArray[number].m_introduction<<endl;
    for(int i=0;i<m_iCapacity;i++)
    {
        if(m_pMatrix[number*m_iCapacity+i]!=0)
            cout<<" "<<m_pNodeArray[i].m_name<<" "<<m_pMatrix[number*m_iCapacity+i]<<endl;
          //�����Ҹ��������ĵ㣨������
    }
}

/*void Map::DFS(int nodeIndex,int beginNum)// ������������㷨 ��mapDFS��
{
  if(m_pNodeArray[nodeIndex].visited==true) ;
    else
    {
        nodeVec.push_back(nodeIndex);
        //��nodeVec�ĵ�һ��Ԫ�أ��ӵ�0������λ�ò�����ֵnodeIndex
        m_pNodeArray[nodeIndex].visited=true;

        for(int i=beginNum;i<m_iCapacity;i++)
        {
            if(m_pMatrix[nodeIndex*m_iCapacity+i]!=0&&m_pNodeArray[i].visited!=true)
                DFS(i,beginNum);
            if((int)nodeVec.size()==m_iCapacity)//��ջʱ �����ջ�׵�ջ����Ԫ�أ���Ϊһ��·��
            {
               int j;
               for(j=0;j<(int)nodeVec.size();j++)
                    cout<<nodeVec[j]<<" ";
                    cout<<endl;
               //cout<<"**"<<m_pNodeArray[nodeIndex].m_number<<"**";
               m_pNodeArray[nodeIndex].visited=false;//Ҫ��ջ����������Ϊδ����
               nodeVec.pop_back();//�����һ�����ݳ�ջ
               DFS(nodeVec[j-2],nodeVec[j-1]);
               break;
            }
            if(i==(m_iCapacity-1))
               {
                //cout<<"++"<<m_pNodeArray[nodeIndex].m_number<<"++"<<endl;
                m_pNodeArray[nodeIndex].visited=false;//Ҫ��ջ����������Ϊδ����
                nodeVec.pop_back();//�����һ�����ݳ�ջ
               }
        }
    }
}

void Map::mapDFS(int nodeIndex)//���ξ��㵼�����ҳ���������������������·��
{
    cout<<"ways:"<<endl;
    nodeVec.push_back(nodeIndex);
    m_pNodeArray[nodeIndex].visited=true;

    for(int i=0;i<m_iCapacity;i++)
        {
         if(m_pMatrix[nodeIndex*m_iCapacity+i]!=0)
            DFS(i,0);
        }
}
*/
int Map::getMinEdge(vector<Edge> edgeVec)
{
    int minWeight=0;
    int edgeIndex=0;
    int i=0;
    for(;i<(int)edgeVec.size();i++)
    {
         if(edgeVec[i].m_bSelected)
        {
            continue;
        }
        else
        {
            minWeight=edgeVec[i].m_iWeightValue;
            edgeIndex=i;
        }
    }
    // ��ȡ��С��ʧ�ܵ����
    if(minWeight==0)
    {
        return -1;
    }
    for(;i<(int)edgeVec.size();i++)
    {
        if(minWeight>edgeVec[i].m_iWeightValue)
        {
            minWeight=edgeVec[i].m_iWeightValue;
            edgeIndex=i;
        }
    }
    return edgeIndex;
}

void Map::primTree(int nodeIndex)//����С������
{
    int AllWeightValue=0;
    int value=0;
    int edgeCount=0;
    vector <int> nodeVec;
    vector <Edge> edgeVec;
    //cout<<m_pNodeArray[nodeIndex].m_name<<endl;
    nodeVec.push_back(nodeIndex);
    m_pNodeArray[nodeIndex].visited=true;

    while(edgeCount<m_iCapacity-1)
    {
        int temp=nodeVec.back();//���ص�һ��Ԫ��
        for(int i=0;i<m_iCapacity;i++)
        {//�Ѻ�nodeindex���������е�Ž� nodeVec��
            getValueFromMatricx(temp,i,value);
            if(value!=0)
            {
                if(m_pNodeArray[i].visited)
                {
                    continue;
                }
                else
                {
                    Edge edge(temp,i,value);
                    edgeVec.push_back(edge);
                }
            }
        }
     //�ӿ�ѡ�߼�����ѡ����С��
      int edgeIndex=getMinEdge(edgeVec);
      edgeVec[edgeIndex].m_bSelected=true;

      cout<<edgeVec[edgeIndex].m_iNodeIndexA<<"---"<<edgeVec[edgeIndex].m_iNodeIndexB<<" ";
      cout<<edgeVec[edgeIndex].m_iWeightValue<<endl;//����ӿ�ʼ�������� �Լ����ǵĳ���

      AllWeightValue+=edgeVec[edgeIndex].m_iWeightValue;
      m_pEdge[edgeCount]=edgeVec[edgeIndex];
      edgeCount++;

      int nextNodeIndex=edgeVec[edgeIndex].m_iNodeIndexB;

      nodeVec.push_back(nextNodeIndex);
      m_pNodeArray[nextNodeIndex].visited=true;
     // cout<<m_pNodeArray[nextNodeIndex].m_introduction<<endl;
    }


    cout<<AllWeightValue<<endl;
    for(int j=0;j<m_iCapacity-1;j++)
    {
        m_pNodeArray[j].visited=false;
    }
}

void Map::Dijkstra(int v0,int v1) //��˹���㷨���ҵ㵽�����̾���
{
    int dist[m_iCapacity];//dist ����
    int path[m_iCapacity];
    bool final[m_iCapacity];

    dist[v0]=0;
    path[v0]=v0;

    for(int i=0;i<m_iCapacity;i++)
    {//����ʼ�������·���ҳ��� �洢��path������
      if(m_pMatrix[v0*m_iCapacity+i]!=0)
      {
      dist[i]=m_pMatrix[v0*m_iCapacity+i];
      }
      else
      {
      dist[i]=100000;
      }
      path[i]=v0;
      final[i]=false;
    }

	for(int i=0;i<m_iCapacity;i++)
        {
		int minds=100000;
		int ind=10000;
		for(int j=0;j<m_iCapacity;j++){//Ѱ��Ŀǰ��·����������С��һ��
			if(!final[j]&&dist[j]<minds){
				minds=dist[j];//mindsΪ�������
				ind=j;//indΪ��ǰ·����
			}
		}

		final[ind]=true;
		for(int j=0;j<m_iCapacity;j++)
		 {//����dist  �ҵ� ֮ǰ�������м�վ�ľ���+�м�վֱ�ӵ�֮�����ڵľ���  С�� ֮ǰֱ�ӵ�֮��ľ���
           if(m_pMatrix[ind*m_iCapacity+j]!=0&&!final[j]&&(minds+m_pMatrix[ind*m_iCapacity+j])<dist[j])
            {
              dist[j]=minds+m_pMatrix[ind*m_iCapacity+j];
              path[j]=ind;
            }
		 }//ʱ�̱��־���Ϊ�Ѽ��������С����
	   }
    //·�߹滮 ���õ�
    int endNum=v1;
    vector <int> ewayNum;

   while(1)
    {
      if(path[endNum]!=v0)
        {
         ewayNum.push_back(endNum);
         endNum=path[endNum];

        }
      if(path[endNum]==v0)
      {
          ewayNum.push_back(endNum);
          break;
      }
    }

   //ת��������·��
    int wayNum[ewayNum.capacity()];
    for(int i=0;i<(int)ewayNum.capacity();i++)
    {
        wayNum[i]=ewayNum[ewayNum.capacity()-1-i];
    }

    //�������·��
    cout<<v0<<endl;
    for(int i=0;i<(int)ewayNum.capacity();i++)
    {
        cout<<wayNum[i]<<endl;
    }

    cout<<dist[v1]<<endl;
}

bool Map::hasNode(string nodeName)
{
    for(int i=0;i<m_iCapacity;i++)
    {
        if(nodeName==m_pNodeArray[i].m_name)
            return true;
    }
    return false;
}

bool Map::hasEdge(int NodeAnum,int NodeBnum)
{
    if(m_pMatrix[NodeAnum*m_iCapacity+NodeBnum])
        return true;
    else
        return false;
}

