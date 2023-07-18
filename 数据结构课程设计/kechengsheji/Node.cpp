#include "Node.h"
#include<iostream>
Node::Node(int number,string name,string introduction)
{
    m_number=number;
    m_name=name;
    m_introduction=introduction;
    visited=false;
}
