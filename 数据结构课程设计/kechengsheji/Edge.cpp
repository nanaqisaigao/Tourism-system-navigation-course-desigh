#include "Edge.h"
//û����.h�����Edge�Ķ�������Ҫ��˫ð�ţ�::����ʾ�������
Edge::Edge(int nodeIndexA,int nodeIndexB,int weightValue)
{
     m_iNodeIndexA=nodeIndexA;
     m_iNodeIndexB=nodeIndexB;
     m_iWeightValue=weightValue;
     m_bSelected=false;

}
