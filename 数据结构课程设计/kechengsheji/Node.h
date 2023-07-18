#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Node
{
public:
    bool visited;
    Node(int number=-1,string name=" ",string introduction=" ");
    int m_number;
    string m_name;
    string m_introduction;
    //void SeekNode(int number);
};

#endif // NODE_H_INCLUDED

