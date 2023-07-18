#include<iostream>
#include<vector>
#include<memory.h>
//memset //初始化内存
//第一个参数：初始化内存的首地址
//第二个参数：将内存初始化成什么值
//第三个参数：从首地址开始多少个值设置为0
//memcpy //内存拷贝
// 1参：目标空间的首地址
// 2参：源空间的首地址
// 3参：从源空间拷贝多少个字节的数据
//memcmp //内存比较
//第一个参数：参与比较的首地址
//第二个参数：参与比较的首地址
//第三个参数：从首地址开始比较的字节数
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
    //memset是一个初始化函数，作用是将某一块内存中的全部设置为指定的值。

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

void Map::resetNode()//将点重置为未访问过
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
          //用来找跟它相连的点（景区）
    }
}

/*void Map::DFS(int nodeIndex,int beginNum)// 深度优先搜索算法 给mapDFS用
{
  if(m_pNodeArray[nodeIndex].visited==true) ;
    else
    {
        nodeVec.push_back(nodeIndex);
        //在nodeVec的第一个元素（从第0个算起）位置插入数值nodeIndex
        m_pNodeArray[nodeIndex].visited=true;

        for(int i=beginNum;i<m_iCapacity;i++)
        {
            if(m_pMatrix[nodeIndex*m_iCapacity+i]!=0&&m_pNodeArray[i].visited!=true)
                DFS(i,beginNum);
            if((int)nodeVec.size()==m_iCapacity)//满栈时 输出从栈底到栈顶的元素，即为一条路径
            {
               int j;
               for(j=0;j<(int)nodeVec.size();j++)
                    cout<<nodeVec[j]<<" ";
                    cout<<endl;
               //cout<<"**"<<m_pNodeArray[nodeIndex].m_number<<"**";
               m_pNodeArray[nodeIndex].visited=false;//要出栈的数据设置为未访问
               nodeVec.pop_back();//将最后一个数据出栈
               DFS(nodeVec[j-2],nodeVec[j-1]);
               break;
            }
            if(i==(m_iCapacity-1))
               {
                //cout<<"++"<<m_pNodeArray[nodeIndex].m_number<<"++"<<endl;
                m_pNodeArray[nodeIndex].visited=false;//要出栈的数据设置为未访问
                nodeVec.pop_back();//将最后一个数据出栈
               }
        }
    }
}

void Map::mapDFS(int nodeIndex)//旅游景点导航，找出所有能游览整个景区的路线
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
    // 获取最小边失败的情况
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

void Map::primTree(int nodeIndex)//找最小生成树
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
        int temp=nodeVec.back();//返回第一个元素
        for(int i=0;i<m_iCapacity;i++)
        {//把和nodeindex相连的所有点放进 nodeVec里
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
     //从可选边集合中选出最小边
      int edgeIndex=getMinEdge(edgeVec);
      edgeVec[edgeIndex].m_bSelected=true;

      cout<<edgeVec[edgeIndex].m_iNodeIndexA<<"---"<<edgeVec[edgeIndex].m_iNodeIndexB<<" ";
      cout<<edgeVec[edgeIndex].m_iWeightValue<<endl;//输出从开始到结束地 以及他们的长度

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

void Map::Dijkstra(int v0,int v1) //迪斯科算法，找点到点的最短距离
{
    int dist[m_iCapacity];//dist 距离
    int path[m_iCapacity];
    bool final[m_iCapacity];

    dist[v0]=0;
    path[v0]=v0;

    for(int i=0;i<m_iCapacity;i++)
    {//把起始点的所有路径找出来 存储在path数组中
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
		for(int j=0;j<m_iCapacity;j++){//寻找目前的路径距离中最小的一个
			if(!final[j]&&dist[j]<minds){
				minds=dist[j];//minds为理想距离
				ind=j;//ind为当前路径点
			}
		}

		final[ind]=true;
		for(int j=0;j<m_iCapacity;j++)
		 {//更新dist  找到 之前景区到中间站的距离+中间站直接到之后景区内的距离  小于 之前直接到之后的距离
           if(m_pMatrix[ind*m_iCapacity+j]!=0&&!final[j]&&(minds+m_pMatrix[ind*m_iCapacity+j])<dist[j])
            {
              dist[j]=minds+m_pMatrix[ind*m_iCapacity+j];
              path[j]=ind;
            }
		 }//时刻保持距离为已计算过的最小距离
	   }
    //路线规划 倒置的
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

   //转换成正置路线
    int wayNum[ewayNum.capacity()];
    for(int i=0;i<(int)ewayNum.capacity();i++)
    {
        wayNum[i]=ewayNum[ewayNum.capacity()-1-i];
    }

    //输出正置路线
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

