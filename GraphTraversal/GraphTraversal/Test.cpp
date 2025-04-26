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
	string v[] = { "北京", "天津", "郑州", "呼和浩特" , "沈阳" , "大连" , "长春" , "哈尔滨" , "徐州" , "上海" , "南昌" , "福州" , "株洲" , "广州" , "深圳" , "武汉" , "柳州" , "南宁" , "贵阳" , "昆明" , "成都" , "西安" , "兰州" , "西宁" , "乌鲁木齐" };
	AdjMultilist g(v, 25);
	g.AddEdge("北京", "天津");
	g.AddEdge("北京", "郑州");
	g.AddEdge("北京", "呼和浩特");
	g.AddEdge("天津", "沈阳");
	g.AddEdge("沈阳", "大连");
	g.AddEdge("沈阳", "长春");
	g.AddEdge("长春", "哈尔滨");
	g.AddEdge("天津", "徐州");
	g.AddEdge("徐州", "郑州");
	g.AddEdge("徐州", "上海");
	g.AddEdge("上海", "南昌");
	g.AddEdge("南昌", "福州");
	g.AddEdge("南昌", "株洲");
	g.AddEdge("株洲", "广州");
	g.AddEdge("广州", "深圳");
	g.AddEdge("株洲", "武汉");
	g.AddEdge("武汉", "郑州");
	g.AddEdge("株洲", "柳州");
	g.AddEdge("柳州", "南宁");
	g.AddEdge("柳州", "贵阳");
	g.AddEdge("株洲", "贵阳");
	g.AddEdge("贵阳", "昆明");
	g.AddEdge("昆明", "成都");
	g.AddEdge("贵阳", "成都");
	g.AddEdge("成都", "西安");
	g.AddEdge("西安", "郑州");
	g.AddEdge("西安", "兰州");
	g.AddEdge("兰州", "西宁");
	g.AddEdge("兰州", "呼和浩特");
	g.AddEdge("兰州", "乌鲁木齐");

	
	g.DFS("北京");
	cout << endl;
	g.BFS("北京");
}

void TestAdjList()
{
	string v[] = { "北京", "天津", "郑州", "呼和浩特" , "沈阳" , "大连" , "长春" , "哈尔滨" , "徐州" , "上海" , "南昌" , "福州" , "株洲" , "广州" , "深圳" , "武汉" , "柳州" , "南宁" , "贵阳" , "昆明" , "成都" , "西安" , "兰州" , "西宁" , "乌鲁木齐" };
	AdjList g(v, 25);
	g.AddEdge("北京", "天津", 137);
	g.AddEdge("北京", "郑州", 695);
	g.AddEdge("北京", "呼和浩特", 668);
	g.AddEdge("天津", "沈阳", 704);
	g.AddEdge("沈阳", "大连", 397);
	g.AddEdge("沈阳", "长春", 305);
	g.AddEdge("长春", "哈尔滨", 242);
	g.AddEdge("天津", "徐州", 674);
	g.AddEdge("徐州", "郑州", 349);
	g.AddEdge("徐州", "上海", 651);
	g.AddEdge("上海", "南昌", 825);
	g.AddEdge("南昌", "福州", 622);
	g.AddEdge("南昌", "株洲", 367);
	g.AddEdge("株洲", "广州", 675);
	g.AddEdge("广州", "深圳", 140);
	g.AddEdge("株洲", "武汉", 409);
	g.AddEdge("武汉", "郑州", 534);
	g.AddEdge("株洲", "柳州", 672);
	g.AddEdge("柳州", "南宁", 255);
	g.AddEdge("柳州", "贵阳", 607);
	g.AddEdge("株洲", "贵阳", 902);
	g.AddEdge("贵阳", "昆明", 639);
	g.AddEdge("昆明", "成都", 1100);
	g.AddEdge("贵阳", "成都", 967);
	g.AddEdge("成都", "西安", 842);
	g.AddEdge("西安", "郑州", 511);
	g.AddEdge("西安", "兰州", 676);
	g.AddEdge("兰州", "西宁", 216);
	g.AddEdge("兰州", "呼和浩特", 1145);
	g.AddEdge("兰州", "乌鲁木齐", 1892);


	g.DFS("北京");
	cout << endl;
	g.DFSNonR("北京");
	cout << endl << endl;
	g.BFS("北京");
	cout << endl;
	g.Dijkstra("北京");
}

int main()
{
	//TestAdjMultilist();
	TestAdjList();
	return 0;
}