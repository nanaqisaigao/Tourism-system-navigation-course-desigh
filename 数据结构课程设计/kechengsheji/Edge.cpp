#include "Edge.h"
//没有在.h里给出Edge的定义所以要用双冒号（::）表示域操作符
Edge::Edge(int nodeIndexA,int nodeIndexB,int weightValue)
{
     m_iNodeIndexA=nodeIndexA;
     m_iNodeIndexB=nodeIndexB;
     m_iWeightValue=weightValue;
     m_bSelected=false;

}
