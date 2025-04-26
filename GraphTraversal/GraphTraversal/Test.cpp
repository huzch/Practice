#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

#include "AdjMultilist.h"
#include "AdjList.h"


void TestAdjMultilist()
{
	string v[] = { "����", "���", "֣��", "���ͺ���" , "����" , "����" , "����" , "������" , "����" , "�Ϻ�" , "�ϲ�" , "����" , "����" , "����" , "����" , "�人" , "����" , "����" , "����" , "����" , "�ɶ�" , "����" , "����" , "����" , "��³ľ��" };
	AdjMultilist g(v, 25);
	g.AddEdge("����", "���");
	g.AddEdge("����", "֣��");
	g.AddEdge("����", "���ͺ���");
	g.AddEdge("���", "����");
	g.AddEdge("����", "����");
	g.AddEdge("����", "����");
	g.AddEdge("����", "������");
	g.AddEdge("���", "����");
	g.AddEdge("����", "֣��");
	g.AddEdge("����", "�Ϻ�");
	g.AddEdge("�Ϻ�", "�ϲ�");
	g.AddEdge("�ϲ�", "����");
	g.AddEdge("�ϲ�", "����");
	g.AddEdge("����", "����");
	g.AddEdge("����", "����");
	g.AddEdge("����", "�人");
	g.AddEdge("�人", "֣��");
	g.AddEdge("����", "����");
	g.AddEdge("����", "����");
	g.AddEdge("����", "����");
	g.AddEdge("����", "����");
	g.AddEdge("����", "����");
	g.AddEdge("����", "�ɶ�");
	g.AddEdge("����", "�ɶ�");
	g.AddEdge("�ɶ�", "����");
	g.AddEdge("����", "֣��");
	g.AddEdge("����", "����");
	g.AddEdge("����", "����");
	g.AddEdge("����", "���ͺ���");
	g.AddEdge("����", "��³ľ��");

	
	g.DFS("����");
	cout << endl;
	g.BFS("����");
}

void TestAdjList()
{
	string v[] = { "����", "���", "֣��", "���ͺ���" , "����" , "����" , "����" , "������" , "����" , "�Ϻ�" , "�ϲ�" , "����" , "����" , "����" , "����" , "�人" , "����" , "����" , "����" , "����" , "�ɶ�" , "����" , "����" , "����" , "��³ľ��" };
	AdjList g(v, 25);
	g.AddEdge("����", "���", 137);
	g.AddEdge("����", "֣��", 695);
	g.AddEdge("����", "���ͺ���", 668);
	g.AddEdge("���", "����", 704);
	g.AddEdge("����", "����", 397);
	g.AddEdge("����", "����", 305);
	g.AddEdge("����", "������", 242);
	g.AddEdge("���", "����", 674);
	g.AddEdge("����", "֣��", 349);
	g.AddEdge("����", "�Ϻ�", 651);
	g.AddEdge("�Ϻ�", "�ϲ�", 825);
	g.AddEdge("�ϲ�", "����", 622);
	g.AddEdge("�ϲ�", "����", 367);
	g.AddEdge("����", "����", 675);
	g.AddEdge("����", "����", 140);
	g.AddEdge("����", "�人", 409);
	g.AddEdge("�人", "֣��", 534);
	g.AddEdge("����", "����", 672);
	g.AddEdge("����", "����", 255);
	g.AddEdge("����", "����", 607);
	g.AddEdge("����", "����", 902);
	g.AddEdge("����", "����", 639);
	g.AddEdge("����", "�ɶ�", 1100);
	g.AddEdge("����", "�ɶ�", 967);
	g.AddEdge("�ɶ�", "����", 842);
	g.AddEdge("����", "֣��", 511);
	g.AddEdge("����", "����", 676);
	g.AddEdge("����", "����", 216);
	g.AddEdge("����", "���ͺ���", 1145);
	g.AddEdge("����", "��³ľ��", 1892);


	g.DFS("����");
	cout << endl;
	g.DFSNonR("����");
	cout << endl << endl;
	g.BFS("����");
	cout << endl;
	g.Dijkstra("����");
}

int main()
{
	//TestAdjMultilist();
	TestAdjList();
	return 0;
}