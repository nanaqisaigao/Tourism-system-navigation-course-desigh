#include <iostream>
#include <string>
#include <strstream>
#include <fstream>
// ifstream是从硬盘到内存 以输入的方式打开开文件，ofstream是从内存到硬盘，以输出的方式打开文件
#include "Map.h"

using namespace std;
void ModifyLineData(char * fileName, int lineNum,string lineData); //修改文件第几行的信息
string CharToStr(char * contentChar);
string int_to_string(int i);
void DelLineData(char* fileName, int lineNum); //删除线信息

int main()
{
    int flag;
    char a;
    cout<<"--------------------------------------------------------------------------"<<endl;
    cout<<"-                      请先按任意键读取文件创建图                        -"<<endl;
    cout<<"--------------------------------------------------------------------------"<<endl;
    cin>>a;
	ifstream in;
    cout<<"读取成功"<<endl<<endl;
    cout<<"---------------------------------------------------------------------------"<<endl;
    cout<<"-                      输入1输出邻接矩阵                                  -"<<endl;
    cout<<"-                      输入2查询所在景点以及相邻景点信息                  -"<<endl;
    cout<<"-                      输入3查询从每个景点出发到其他任一景点              -"<<endl;
    cout<<"-                      输入4搜索最短路径                                  -"<<endl;
    cout<<"-                      输入5使用路线推荐功能                              -"<<endl;
    cout<<"-                      输入6编辑景点和路线                                -"<<endl;
    cout<<"-                      输入7退出系统                                      -"<<endl;
    cout<<"---------------------------------------------------------------------------"<<endl;
    cin>>flag;
    while(flag!=7)
    {
    int A;
    int B;
    int line;
    in.open("Vex.txt");
	//读入图的容量
	int capacity;
    in>>capacity;
    //读入点的信息
    int num;//点的编号
    string name;//点的名字
    string introduction;//点的介绍
    Map *jMap= new Map(capacity);//创建一个有capacity容量的图
    Node *jNode[capacity];//创建capacity个点
    for(int i=0;i<capacity;i++)
    {
        in>>num;
        in>>name;
        in>>introduction;
        jNode[i]=new Node(num,name,introduction);
        jMap->addNode(jNode[i]);
    }
    in.close();

    //读入边的信息
    in.open("Edge.txt");
    int NodeAnum;
    int NodeBnum;
    int WeightValue;

    while(!in.eof())//in文件里面还有字符时，in.eof()为true
    {
      in>>NodeAnum;
      in>>NodeBnum;
      in>>WeightValue;
      jMap->setValueToMatrixForUndirectedGraph(NodeAnum,NodeBnum,WeightValue);
    }
    in.close();
//上面为图的创建（包括图中点和边）


//下面为各种功能的实现
    if(flag==1) jMap->printMatrix();//1.输出邻接矩阵
    if(flag==2) {cout<<"你想知道哪个景点周围有啥景点？";cin>>A; jMap->seekNode(A);}//2.查询景点的相邻景点
    if(flag==3) {
    cout<<"输入你在哪儿，给出旅游区每个景点到该景点的最短简单路径及距离."<<endl;
    cin>>A;
for(int i=0;i<capacity;i++){
    if(i!=A) {
    jMap->Dijkstra(i,A);
    cout<<"这是"<<i<<"到"<<A<<"的最佳路线和最短距离。"<<endl;
    }
    }
    }//用户输入任一景点，输出旅游区每个景点到该景点的最短简单路径及距离。
    if(flag==4) {cout<<"输入A景点和B景点，查询他们的最佳路线和最短距离。";cin>>A>>B;jMap->Dijkstra(A,B);}//4.搜索从A到B最短距离
    if(flag==5) {cout<<"输入一个景点给出推荐路线.";cin>>A;jMap->primTree(A);}//5.最佳旅游路线推荐
    if(flag==6)
    {
        int C=0;
        cout<<"---------------------------------------------------------------------------"<<endl;
        cout<<"-                      1.插入景点                                         -"<<endl;
        cout<<"-                      2.修改景点                                         -"<<endl;
        cout<<"-                      3.删除景点                                         -"<<endl;
        cout<<"-                      4.插入道路                                         -"<<endl;
        cout<<"-                      5.删除道路                                         -"<<endl;
        cout<<"-                      6.修改道路                                         -"<<endl;
        cout<<"-                      7.退回上一步                                       -"<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;

    while(C!=7)
   {
     cin>>C;
    //6-1 插入点
     if(C==1)
    {
    ofstream out("Vex.txt",ios::app);//存到文件里ta
//    ios::app：　　　以追加的方式打开文件
//　　ios::in：　　　 文件以输入方式打开(文件数据输入到内存)
//　　ios::out：　　　文件以输出方式打开(内存数据输出到文件)

    cout<<"请输入景区名称："<<endl;
    cin>>name;
    while(jMap->hasNode(name))
    {
        cout<<"已经有该景区了，请重新输入："<<endl;
        cin>>name;
    }
    cout<<"请输入景区介绍"<<endl;
    cin>>introduction;
    out<<capacity<<endl;
    out<<name<<endl;
    out<<introduction<<endl;
    capacity++;
    ModifyLineData("Vex.txt", 1,int_to_string(capacity));
    cout<<"插入景区成功！"<<endl;
    out.close();
     }
    //6-2 修改点
    if(C==2)
    {
    cout<<"请输入需要修改的景点编号："<<endl;
    cin>>num;
    while(num>capacity-1)
    {
        cout<<"没有该编号的景点，请重新输入："<<endl;
        cin>>num;
    }
    cout<<"请修改该点的名称："<<endl;
    cin>>name;
    while(jMap->hasNode(name))
    {
        cout<<"已经有该景区了，请重新输入："<<endl;
        cin>>name;
    }
    cout<<"请修改该点的介绍："<<endl;
    cin>>introduction;
    ModifyLineData("Vex.txt",num*3+3,name);
    ModifyLineData("Vex.txt",num*3+4,introduction);}

    //6-3 删除点
    if(C==3)
    {
    ofstream out("Vex.txt",ios::app);
    num=-1;
    cout<<"请输入你要删除的点的编号：";
    cin>>num;
    while(num>capacity-1)
    {
        cout<<"没有该编号的景点，请重新输入编号："<<endl;
        cin>>num;
    }
    while(num<0||num>capacity-1)
    {
        cout<<"没有该编号的顶点"<<endl;
        cin>>num;
    }
    capacity--;
    DelLineData("Vex.txt",num*3+2);
    DelLineData("Vex.txt",num*3+3);
    DelLineData("Vex.txt",num*3+4);
    ModifyLineData("Vex.txt", 1,int_to_string(capacity));
    cout<<"编号为"<<num<<"的景点已删除"<<endl;

    out.close();
//还要删除点景点周围的边
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
    //6-4 插入边
    if(C==4)
    {
    ofstream out("Edge.txt",ios::app);
    cout<<"请输入需要增加的边的起点编号和终点编号："<<endl;
    cin>>NodeAnum;
    cin>>NodeBnum;
    while(jMap->hasEdge(NodeAnum,NodeBnum))
    {
        cout<<"该边已经存在，请重新输入："<<endl;
        cin>>NodeAnum;
        cin>>NodeBnum;
    }
    cin>>WeightValue;
    out<<NodeAnum<<" "<<NodeBnum<<" "<<WeightValue<<endl;
    cout<<"插入边成功"<<endl;
    out.close();
    }

    //6-5 删除边
    if(C==5)
    {
    ofstream out("Edge.txt",ios::app);
    int hasEdge=0;
    while(hasEdge==0){
    cout<<"请正确输入需要删除的边的起点编号和终点编号："<<endl;
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
          cout<<"该边已经成功删除："<<endl;
          hasEdge=1;
      }
       line++;
    }
    in.close();
    }
    }

    //6-6 修改边
    if(C==6)
    {
    int hasEdge=0;
    ofstream out("Edge.txt",ios::app);
    while(hasEdge==0)
    {
    cout<<"请正确输入需要修改的边的起点和终点以及修改后的距离："<<endl;
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
          cout<<"已成功修改"<<endl;
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
    cout<<"已退回上一步菜单:"<<endl<<endl;
    continue;
    }
   }
  }
  cin>>flag;
 }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModifyLineData(char * fileName, int lineNum, string lineData)//修改线信息
{
	ifstream in;
	in.open(fileName);

	string strFileData = "";
	int line = 1;
	char tmpLineData[1024] = {0};
	while(in.getline(tmpLineData, sizeof(tmpLineData)))//getline可以读取整行
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

	//写入文件
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

void DelLineData(char* fileName, int lineNum) //删除线信息
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
	//写入文件
	ofstream out;
	out.open(fileName);
	out.flush();
	out<<strFileData;
	out.close();
}

