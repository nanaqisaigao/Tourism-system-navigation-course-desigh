#include <iostream>
#include <string>
#include <strstream>
#include <fstream>
// ifstream�Ǵ�Ӳ�̵��ڴ� ������ķ�ʽ�򿪿��ļ���ofstream�Ǵ��ڴ浽Ӳ�̣�������ķ�ʽ���ļ�
#include "Map.h"

using namespace std;
void ModifyLineData(char * fileName, int lineNum,string lineData); //�޸��ļ��ڼ��е���Ϣ
string CharToStr(char * contentChar);
string int_to_string(int i);
void DelLineData(char* fileName, int lineNum); //ɾ������Ϣ

int main()
{
    int flag;
    char a;
    cout<<"--------------------------------------------------------------------------"<<endl;
    cout<<"-                      ���Ȱ��������ȡ�ļ�����ͼ                        -"<<endl;
    cout<<"--------------------------------------------------------------------------"<<endl;
    cin>>a;
	ifstream in;
    cout<<"��ȡ�ɹ�"<<endl<<endl;
    cout<<"---------------------------------------------------------------------------"<<endl;
    cout<<"-                      ����1����ڽӾ���                                  -"<<endl;
    cout<<"-                      ����2��ѯ���ھ����Լ����ھ�����Ϣ                  -"<<endl;
    cout<<"-                      ����3��ѯ��ÿ�����������������һ����              -"<<endl;
    cout<<"-                      ����4�������·��                                  -"<<endl;
    cout<<"-                      ����5ʹ��·���Ƽ�����                              -"<<endl;
    cout<<"-                      ����6�༭�����·��                                -"<<endl;
    cout<<"-                      ����7�˳�ϵͳ                                      -"<<endl;
    cout<<"---------------------------------------------------------------------------"<<endl;
    cin>>flag;
    while(flag!=7)
    {
    int A;
    int B;
    int line;
    in.open("Vex.txt");
	//����ͼ������
	int capacity;
    in>>capacity;
    //��������Ϣ
    int num;//��ı��
    string name;//�������
    string introduction;//��Ľ���
    Map *jMap= new Map(capacity);//����һ����capacity������ͼ
    Node *jNode[capacity];//����capacity����
    for(int i=0;i<capacity;i++)
    {
        in>>num;
        in>>name;
        in>>introduction;
        jNode[i]=new Node(num,name,introduction);
        jMap->addNode(jNode[i]);
    }
    in.close();

    //����ߵ���Ϣ
    in.open("Edge.txt");
    int NodeAnum;
    int NodeBnum;
    int WeightValue;

    while(!in.eof())//in�ļ����滹���ַ�ʱ��in.eof()Ϊtrue
    {
      in>>NodeAnum;
      in>>NodeBnum;
      in>>WeightValue;
      jMap->setValueToMatrixForUndirectedGraph(NodeAnum,NodeBnum,WeightValue);
    }
    in.close();
//����Ϊͼ�Ĵ���������ͼ�е�ͱߣ�


//����Ϊ���ֹ��ܵ�ʵ��
    if(flag==1) jMap->printMatrix();//1.����ڽӾ���
    if(flag==2) {cout<<"����֪���ĸ�������Χ��ɶ���㣿";cin>>A; jMap->seekNode(A);}//2.��ѯ��������ھ���
    if(flag==3) {
    cout<<"���������Ķ�������������ÿ�����㵽�þ������̼�·��������."<<endl;
    cin>>A;
for(int i=0;i<capacity;i++){
    if(i!=A) {
    jMap->Dijkstra(i,A);
    cout<<"����"<<i<<"��"<<A<<"�����·�ߺ���̾��롣"<<endl;
    }
    }
    }//�û�������һ���㣬���������ÿ�����㵽�þ������̼�·�������롣
    if(flag==4) {cout<<"����A�����B���㣬��ѯ���ǵ����·�ߺ���̾��롣";cin>>A>>B;jMap->Dijkstra(A,B);}//4.������A��B��̾���
    if(flag==5) {cout<<"����һ����������Ƽ�·��.";cin>>A;jMap->primTree(A);}//5.�������·���Ƽ�
    if(flag==6)
    {
        int C=0;
        cout<<"---------------------------------------------------------------------------"<<endl;
        cout<<"-                      1.���뾰��                                         -"<<endl;
        cout<<"-                      2.�޸ľ���                                         -"<<endl;
        cout<<"-                      3.ɾ������                                         -"<<endl;
        cout<<"-                      4.�����·                                         -"<<endl;
        cout<<"-                      5.ɾ����·                                         -"<<endl;
        cout<<"-                      6.�޸ĵ�·                                         -"<<endl;
        cout<<"-                      7.�˻���һ��                                       -"<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;

    while(C!=7)
   {
     cin>>C;
    //6-1 �����
     if(C==1)
    {
    ofstream out("Vex.txt",ios::app);//�浽�ļ���ta
//    ios::app����������׷�ӵķ�ʽ���ļ�
//����ios::in�������� �ļ������뷽ʽ��(�ļ��������뵽�ڴ�)
//����ios::out���������ļ��������ʽ��(�ڴ�����������ļ�)

    cout<<"�����뾰�����ƣ�"<<endl;
    cin>>name;
    while(jMap->hasNode(name))
    {
        cout<<"�Ѿ��иþ����ˣ����������룺"<<endl;
        cin>>name;
    }
    cout<<"�����뾰������"<<endl;
    cin>>introduction;
    out<<capacity<<endl;
    out<<name<<endl;
    out<<introduction<<endl;
    capacity++;
    ModifyLineData("Vex.txt", 1,int_to_string(capacity));
    cout<<"���뾰���ɹ���"<<endl;
    out.close();
     }
    //6-2 �޸ĵ�
    if(C==2)
    {
    cout<<"��������Ҫ�޸ĵľ����ţ�"<<endl;
    cin>>num;
    while(num>capacity-1)
    {
        cout<<"û�иñ�ŵľ��㣬���������룺"<<endl;
        cin>>num;
    }
    cout<<"���޸ĸõ�����ƣ�"<<endl;
    cin>>name;
    while(jMap->hasNode(name))
    {
        cout<<"�Ѿ��иþ����ˣ����������룺"<<endl;
        cin>>name;
    }
    cout<<"���޸ĸõ�Ľ��ܣ�"<<endl;
    cin>>introduction;
    ModifyLineData("Vex.txt",num*3+3,name);
    ModifyLineData("Vex.txt",num*3+4,introduction);}

    //6-3 ɾ����
    if(C==3)
    {
    ofstream out("Vex.txt",ios::app);
    num=-1;
    cout<<"��������Ҫɾ���ĵ�ı�ţ�";
    cin>>num;
    while(num>capacity-1)
    {
        cout<<"û�иñ�ŵľ��㣬�����������ţ�"<<endl;
        cin>>num;
    }
    while(num<0||num>capacity-1)
    {
        cout<<"û�иñ�ŵĶ���"<<endl;
        cin>>num;
    }
    capacity--;
    DelLineData("Vex.txt",num*3+2);
    DelLineData("Vex.txt",num*3+3);
    DelLineData("Vex.txt",num*3+4);
    ModifyLineData("Vex.txt", 1,int_to_string(capacity));
    cout<<"���Ϊ"<<num<<"�ľ�����ɾ��"<<endl;

    out.close();
//��Ҫɾ���㾰����Χ�ı�
	in.open("Edge.txt");
	line=1;
	while(!in.eof())
    {
      in>>NodeAnum;
      in>>NodeBnum;
      in>>WeightValue;
      if(NodeAnum==num||NodeBnum==num)
      {
          DelLineData("Edge.txt", line);
      }
       line++;
    }
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //6-4 �����
    if(C==4)
    {
    ofstream out("Edge.txt",ios::app);
    cout<<"��������Ҫ���ӵıߵ�����ź��յ��ţ�"<<endl;
    cin>>NodeAnum;
    cin>>NodeBnum;
    while(jMap->hasEdge(NodeAnum,NodeBnum))
    {
        cout<<"�ñ��Ѿ����ڣ����������룺"<<endl;
        cin>>NodeAnum;
        cin>>NodeBnum;
    }
    cin>>WeightValue;
    out<<NodeAnum<<" "<<NodeBnum<<" "<<WeightValue<<endl;
    cout<<"����߳ɹ�"<<endl;
    out.close();
    }

    //6-5 ɾ����
    if(C==5)
    {
    ofstream out("Edge.txt",ios::app);
    int hasEdge=0;
    while(hasEdge==0){
    cout<<"����ȷ������Ҫɾ���ıߵ�����ź��յ��ţ�"<<endl;
    cin>>NodeAnum;
    cin>>NodeBnum;
    in.open("Edge.txt");
    out.open("Edge.txt",ios::app);
	line=1;
	while(!in.eof())
    {
      in>>A;
      in>>B;
      in>>WeightValue;
      if((NodeAnum==A&&NodeBnum==B)||(NodeBnum==A&&NodeAnum==B))
      {
          DelLineData("Edge.txt", line);
          cout<<"�ñ��Ѿ��ɹ�ɾ����"<<endl;
          hasEdge=1;
      }
       line++;
    }
    in.close();
    }
    }

    //6-6 �޸ı�
    if(C==6)
    {
    int hasEdge=0;
    ofstream out("Edge.txt",ios::app);
    while(hasEdge==0)
    {
    cout<<"����ȷ������Ҫ�޸ĵıߵ������յ��Լ��޸ĺ�ľ��룺"<<endl;
    cin>>NodeAnum;
    cin>>NodeBnum;
    cin>>WeightValue;
    in.open("Edge.txt");
	line=1;
	while(!in.eof())
    {
      in>>A;
      in>>B;
      if((NodeAnum==A&&NodeBnum==B)||(NodeBnum==A&&NodeAnum==B))
      {
          DelLineData("Edge.txt", line);
          out<<NodeAnum<<" "<<NodeBnum<<" "<<WeightValue<<endl;
          cout<<"�ѳɹ��޸�"<<endl;
          hasEdge=1;
      }
       line++;
    }
    out.close();
    in.close();
    }
    }

    if(C==7)
    {
    cout<<"���˻���һ���˵�:"<<endl<<endl;
    continue;
    }
   }
  }
  cin>>flag;
 }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModifyLineData(char * fileName, int lineNum, string lineData)//�޸�����Ϣ
{
	ifstream in;
	in.open(fileName);

	string strFileData = "";
	int line = 1;
	char tmpLineData[1024] = {0};
	while(in.getline(tmpLineData, sizeof(tmpLineData)))//getline���Զ�ȡ����
	{
		if (line == lineNum)
		{
			strFileData += lineData;
			strFileData += "\n";
		}
		else
		{
			strFileData += CharToStr(tmpLineData);
			strFileData += "\n";
		}
		line++;
	}
	in.close();

	//д���ļ�
	ofstream out;
	out.open(fileName);
	out.flush();
	out<<strFileData;
	out.close();
}

string CharToStr(char * contentChar)
{
	string tempStr;
	for (int i=0;contentChar[i]!='\0';i++)
	{
		tempStr+=contentChar[i];
	}
	return tempStr;
}

string int_to_string(int i)
{
    string s;
    strstream ss;
    ss<<i;
    ss>>s;

    return s;
}

void DelLineData(char* fileName, int lineNum) //ɾ������Ϣ
{
	ifstream in;
	in.open(fileName);

	string strFileData = "";
	int line = 1;
	char lineData[1024] = {0};
	while(in.getline(lineData, sizeof(lineData)))
	{
		if (line == lineNum)
		{
		    strFileData += "\n";
		}
		else
		{
			strFileData += CharToStr(lineData);
			strFileData += "\n";
		}
		line++;
	}
	in.close();
	//д���ļ�
	ofstream out;
	out.open(fileName);
	out.flush();
	out<<strFileData;
	out.close();
}

