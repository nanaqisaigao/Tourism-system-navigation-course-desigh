#ifndef EDGE_H_INCLUDED
//#ifndef ��"if not defined"�ļ�д
//ָ���EDGE_H_INCLUDEDû�ж�����ִ��#define EDGE_H_INCLUDED
#define EDGE_H_INCLUDED
#include <iostream>

class Edge
{

public:
    Edge(int nodeIndexA=0,int nodeIndexB=0,int weightValue=0);
    int m_iNodeIndexA;
    int m_iNodeIndexB;
    int m_iWeightValue;
    bool m_bSelected;

};

#endif // EDGE_H_INCLUDED

