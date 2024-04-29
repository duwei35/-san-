#include<stdio.h>
#include<iostream>
using namespace std;
#define MAXweight 999// 权值
#define MAXNUM 100//最大点数
typedef char top;//顶点
typedef  int weight;//边权
typedef struct
{
	top vexs[MAXNUM];//顶点表
	weight arcs[MAXNUM][MAXNUM];//邻接矩阵
	int vexum, arcnum;//当前点数和边数
}AMGraph;
struct Primtree
{
	char adjvex;//最小边在U中的那个顶点
	int lowcost;//最小边上的权值
};
struct Primtree closedge[MAXNUM];
struct
{
	char Head;//头节点
	char Tail;//尾节点
	int lowcost;//两点之间权重
}Edge[MAXNUM];
//转换
int locat(AMGraph G, char v)
{
	int i = 0;
	for (i = 0; i < G.vexum; i++)
	{
		if (G.vexs[i] == v)
			return i;
	}
	return -1;
}
void Createudn(AMGraph& G)
{
	char v1, v2;
	int i, j, w;
	cout << "请输入点数和边数:";
	cin >> G.vexum >> G.arcnum;
	cout << "输入各顶点的名称:";
	for (i = 0; i < G.vexum; ++i)
	{
		cin >> G.vexs[i];
	}
	for (i = 0; i < G.arcnum; i++)
	{
		for (j = 0; j < G.arcnum; j++)
		{
			G.arcs[i][j] = MAXweight;
		}
	}
	cout << "输入边与权值" << endl;
	for (int k = 0; k < G.arcnum; k++)
	{
		cin >> v1 >> v2 >> w;
		i = locat(G, v1);
		j = locat(G, v2);
		G.arcs[i][j] = w;
		G.arcs[j][i] = w;
		Edge[k].Head = v1;
		Edge[k].Tail = v2;
		Edge[k].lowcost = w;
	}
}
int Min(AMGraph G, Primtree closedge[])
{
	int min = 999;
	int index = -1;
	for (int i = 0; i < G.vexum; i++)
	{
		if (closedge[i].lowcost < min && closedge[i].lowcost != 0)
		{
			min = closedge[i].lowcost;
			index = i;
		}
	}
	return index;
}

void Prim(AMGraph G)
{
	char u = 'B';
	char u0, v0;
	int sum = 0;
	int k, i, j;
	k = locat(G, u);
	for (j = 0; j < G.vexum; ++j)
		if (j != k)
		{
			closedge[j].adjvex = u;
			closedge[j].lowcost = G.arcs[k][j];
		}
	closedge[k].lowcost = 0;
	for (i = 1; i < G.vexum; ++i)
	{
		k = Min(G, closedge);
		u0 = closedge[k].adjvex;
		v0 = G.vexs[k];
		cout << u0 << "—" << v0 << " 边权为 " << closedge[k].lowcost << endl;
		sum += closedge[k].lowcost;
		closedge[k].lowcost = 0;
		for (j = 0; j < G.vexum; ++j)
		{
			if (G.arcs[k][j] < closedge[j].lowcost)
			{
				closedge[j].adjvex = G.vexs[k];
				closedge[j].lowcost = G.arcs[k][j];
			}
		}
	}
	cout << "边权总值为 :" << sum << endl;
}
void show(AMGraph& G)
{
	for (int i = 0; i < G.vexum; i++)
	{
		for (int j = 0; j < G.vexum; j++)
		{
			if (G.arcs[i][j] == 999)
				printf("∞ ");
			else
				printf("%02d ", G.arcs[i][j]);
		}
		printf("\n");
	}
}
void Kruskal(AMGraph& G)
{
	int Vexset[MAXNUM];
	int i, j;
	int sum = 0;
	char v1, v2;
	int vs1, vs2;
	for (i = 0; i < G.vexum; i++) Vexset[i] = i;
	for (i = 0; i < G.arcnum - 1; i++)
	{
		for (j = i + 1; j < G.arcnum; j++)
		{
			if (Edge[j].lowcost < Edge[i].lowcost)
			{
				Edge[G.arcnum].Head = Edge[j].Head;
				Edge[G.arcnum].Tail = Edge[j].Tail;
				Edge[G.arcnum].lowcost = Edge[j].lowcost;
				Edge[j].Head = Edge[i].Head;
				Edge[j].Tail = Edge[i].Tail;
				Edge[j].lowcost = Edge[i].lowcost;
				Edge[i].Head = Edge[G.arcnum].Head;
				Edge[i].Tail = Edge[G.arcnum].Tail;
				Edge[i].lowcost = Edge[G.arcnum].lowcost;
			}
		}
	}
	for (i = 0; i < G.arcnum; i++)
	{
		v1 = locat(G, Edge[i].Head);
		v2 = locat(G, Edge[i].Tail);
		vs1 = Vexset[v1];
		vs2 = Vexset[v2];
		if (vs1 != vs2)
		{
			cout << Edge[i].Head << "—" << Edge[i].Tail << "  边权为 " << Edge[i].lowcost << endl;
			sum += Edge[i].lowcost;
			for (j = 0; j < G.vexum; j++) if (Vexset[j] == vs2) Vexset[j] = vs1;
		}
	}
	cout << "边权总值为 :" << sum << endl;
}
int main()
{
	int x;
	AMGraph G;
	Createudn(G);
	show(G);
	printf("1、普里姆（Prim）算法构造最小生成树\n");
	printf("2、克鲁斯卡尔（Kruskal）算法构造最小生成树\n");
	printf("请选择使用的算法:");
	scanf("%d", &x);
	switch (x)
	{
	case 1:
		Prim(G);
		break;
	case 2:
		Kruskal(G);
		break;
	case 0:
		break;
	default:
		printf("输入异常\n");
		break;
	}
}


