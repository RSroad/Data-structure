
/*
 *名称：图——邻接表形式
 *
 *内容：迪杰斯特拉算法，图的所有路径，图的深度优先搜索，查找，以及用函数指针实现了一些功能。
 *
 *作者：刘丹阳
 *
 *完成时间：11月20日
 *
 *	第一次修改：2月1日
	修改人：刘丹阳
	修改内容：针对一些小bug，及备注进行修改
 *
*/



#include <stdio.h>
#include <stdlib.h>
#include "DataElem.h"
#include "Stack.h"
#include "Queue.h"
#include "List.h"

#define MAX_VERTEX_NUM 50

typedef enum{DG, DN, UDG, UDN}GraphKind;

//节点数据类型
typedef struct
{
	int a;
}VertexData;

//边信息
typedef struct
{
	char b;
}OtherInfo;

//图节点链表
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	OtherInfo test;
}ArcNode;

//邻接表节点
typedef struct VertexNode
{
	VertexData data;
	ArcNode *fristarc;
}VertexNode;

//整个图的主数据结构
typedef struct 
{
	VertexNode vertex[MAX_VERTEX_NUM];
	int vexnum, arcnum;
	GraphKind kind;
}AdjList;

//为求树深度单设的节点信息（可以取消用别的代替）
typedef struct ListNode
{
	int deep;		//求树的深度
}ListNode;

//从文件中将图读出
int GraphRead(AdjList *graph, int a[][MAX_VERTEX_NUM])
{
	FILE *f;
	int i;
	int j;

	f = fopen("邻接矩阵(网)", "r");
	for(i = 0 ; i < graph->vexnum ; i++){
		for(j = 0 ; j < graph->vexnum ; j++){
			fscanf(f, "%d", &a[i][j]);
		}
	}

	return 0;
}

//图的初始化（自带的为14个节点）
int GraphInit(AdjList *graph)
{

	printf("请输入有多少个点？\n");
	scanf("%d", &graph->vexnum);
	graph->vexnum = graph->vexnum;

	return 0;
}

//图的创建函数
int GraphListCreat(AdjList *graph)
{
	int i, j;
	int leap = 0;
	int a[MAX_VERTEX_NUM ][MAX_VERTEX_NUM ];
	ArcNode *p;
	
	GraphRead(graph, a);
	for(i = 0 ; i < graph->vexnum ; i++){
		for(j = 0 ; j < graph->vexnum ; j++){
			if(i == j){
				continue;
			}
			if(leap == 0){
				graph->vertex[i].fristarc = NULL;
			}
			if(a[i][j] != 32768 && leap == 0){
				graph->vertex[i].fristarc = (ArcNode *) malloc (sizeof(ArcNode));
				graph->vertex[i].fristarc->adjvex = j;
				graph->vertex[i].fristarc->nextarc = NULL;
				leap = 1;
				continue;
			}
			if(a[i][j] != 32768){
				p = (ArcNode *) malloc (sizeof(ArcNode));
				p->adjvex = j;
				p->nextarc = graph->vertex[i].fristarc->nextarc;
				graph->vertex[i].fristarc->nextarc = p;
			}
		}
		leap = 0;
	}

	return 0;
}

//深度优先搜索
int GraphListDepthSearch(AdjList *graph, int v)
{
	int visited [MAX_VERTEX_NUM] = {0};
	int i = 0;
	ArcNode *p;
	StackNode *stack;
	StackDataElem e;

	stack = (StackNode *)malloc(sizeof(StackNode));
	StackInit(stack);
	e.a = v;
	StackPush(stack, e);
	while(StackEmpty(stack)){
		StackPop(stack, &e);
		i = e.a;
		if(!visited[i]){
			printf("%d", i);
			visited[i] = 1;
		}
		p = graph->vertex[i].fristarc;
		while(p != NULL){
			if(!visited[p->adjvex]){
				e.a = p->adjvex;
				StackPush(stack, e);
			}
			p = p->nextarc;
		}
	}
	return 0;
}


//查找
int GraphListDepthFind(AdjList *graph, int v, int t)
{
	int visited [MAX_VERTEX_NUM] = {0};
	int i = 0;
	ArcNode *p;
	StackNode *stack;
	StackDataElem e;

	stack = (StackNode *)malloc(sizeof(StackNode));
	StackInit(stack);
	e.a = v;
	StackPush(stack, e);
	while(StackEmpty(stack)){
		StackPop(stack, &e);
		i = e.a;
		if(!visited[i]){
			printf("%d", i);
			visited[i] = 1;
		}
		if(i == t){
			return 0;
		}
		p = graph->vertex[i].fristarc;
		while(p != NULL){
			if(!visited[p->adjvex]){
				e.a = p->adjvex;
				StackPush(stack, e);
			}
			p = p->nextarc;
		}
	}
	return 0;
}


//迪杰斯特拉求最短路径
int GraphListPath_DJS(AdjList *graph, int f, int t)
{
	Queue *path;					//申请队列
	QueueDataElem *node, *p;			//申请队列元素节点
	MidNode *head, *mid;				//申请中转节点
	int min = 0, num = 0;				//记录节点的数值
	int i = 0;
	int weigth[MAX_VERTEX_NUM][MAX_VERTEX_NUM];	//存放临接矩阵
	int donevex[MAX_VERTEX_NUM] = {0};		//存放已经走过的节点
	ListNode LiNo[MAX_VERTEX_NUM];			//存放数字信息
	ArcNode *GrNo;					//申请末尾节点
	List *h;

	GraphRead(graph, weigth);			//读取临接矩阵
	path = (Queue *) malloc (sizeof(Queue));
	p = (QueueDataElem *) malloc (sizeof(QueueDataElem));
	GrNo = (ArcNode *) malloc (sizeof(ArcNode));
	node = (QueueDataElem *) malloc (sizeof(QueueDataElem));	//初始化
	donevex[f] = 1;					//置初始访问路径
	QueueInit(path);				//初始化队列
	node->l = 0;					
	node->vn = f;
	node->datanext = NULL;				//置初始节点的next为NULL
	QueueEnter(path, *node);			//初始节点入队
	while(i < graph->vexnum - 1){			//进入循环
		min = 32768;
		mid = path->front->next;		
		node = &(mid->s);			//去队列头元素
		while(1){
			GrNo = graph->vertex[node->vn].fristarc;	//得到临接表形态的头指针
			while(GrNo != NULL){				
				if((weigth[node->vn][GrNo->adjvex] + node->l) < min && donevex[GrNo->adjvex] != 1){
					min = weigth[node->vn][GrNo->adjvex] + node->l;
					num = GrNo->adjvex;
					LiNo[GrNo->adjvex].deep = node->vn;
				}
				GrNo = GrNo->nextarc;	//邻接表的下一项
			}
			mid = mid->next;		//判断队列是否为空
			if(mid == NULL){
				break;
			}
			node = &(mid->s);
		}
		node = (QueueDataElem *) malloc (sizeof(QueueDataElem));
		node->l = min;
		node->vn = num;
		donevex[num] = 1;
		mid = path->front->next;				//指向初始路径
		p = &(mid->s);
		while(1){
			if(p->vn == LiNo[node->vn].deep){
				break;
			}
			mid = mid->next;
			if(mid == NULL){
				break;
			}
			p = &(mid->s);
		}
		node->datanext = p;
		QueueEnter(path, *node);				//新路径入队
		i++;
	}
	head = path->front;
	while(head != NULL){						//头不空则往下找节点
		if(head->s.vn == t){
			break;
		}
		head = head->next;
	}
	*node = head->s;
	h = (List *)malloc(sizeof(List));
	ListInit(h);
	while(node != NULL){						
//		printf("%d\t", node->vn + 1);
//		node = node->datanext;
		ListInsert(h, *node);
		node = node->datanext;
	}
	ListDxu(h);
	h = h->next;
	while(h != NULL){
		printf("%d\t", h->data.vn);
		h = h->next;
	}
	printf("\n");
	return 0;
}

//测试用的指针函数
int weizhi(int a)
{
	FILE *f;
	int i = 0;
	static leap = 0;
	static	char name[MAX_VERTEX_NUM][20];

	if (leap == 0){
		f = fopen("名称", "r");
		while(!feof(f)){
			fscanf(f, "%s", name[i]);
			i++;
		}
		leap++;
	}
	printf("%s ", name[a]);
	return 0;
}

//求所有路径之间的距离
int GrapgAllWay(AdjList *graph, int f, int t, void (*weizhi)(int))
{
	int done[MAX_VERTEX_NUM] = {0};
	Queue *que;
	QueueDataElem *p, *q;
	ArcNode *x;
	List * head;
	int i;
	int leap = 0;

	que = (Queue *)malloc(sizeof(Queue));
	p = (QueueDataElem *)malloc(sizeof(QueueDataElem));
	x = (ArcNode *)malloc(sizeof(ArcNode));
	QueueInit(que);
	p->l = 0;
	p->vn = f;
	p->datanext = NULL;
	done[p->vn] = 1;
	QueueEnter(que, *p);
	do{
		QueueDelete(que, p);
		q = p;
		while(p != NULL){
			done[p->vn] = 1;
			p = p->datanext;
			continue;
		}
		p = q;
		if(p->vn == t){
			leap++;
			head = (List *)malloc(sizeof(List));
			ListInit(head);
			while(p != NULL){
//				printf("%d\t", p->vn + 1);
//				p = p->datanext;
				ListInsert(head, *p);
				p = p->datanext;
			}
			ListDxu(head);
			head = head->next;
			while(head != NULL){
//				printf("%d\t\t", head->data.vn);
				weizhi(head->data.vn);
				head = head->next;
			}
			printf("\n");
			printf("%d", leap);
			printf("\n");
		}
		p = q;
		x = graph->vertex[p->vn].fristarc;
		while(x != NULL){
			if(done[x->adjvex] == 1){
				x = x->nextarc;
				continue;
			}
			p = (QueueDataElem *)malloc(sizeof(QueueDataElem));
			p->vn = x->adjvex;
			p->datanext = q;
			QueueEnter(que, *p);
			x = x->nextarc;
		}
		for(i = 0 ; i < graph->vexnum ; i++){
			done[i] = 0;
		}
	}while(QueueEmpty(que));

	return 0;
}

//主函数
int main(void)
{
	AdjList *graph;
//	int a[30][30];
	int i = 0;


	graph = (AdjList *)malloc(sizeof(AdjList));
	GraphInit(graph);
//	GraphRead(graph, a);
	GraphListCreat(graph);
//	GraphListDepthSearch(graph, 0);
//	GraphListDepthFind(graph, 1, 4);
/*	while(i < 14){
		GraphListPath_DJS(graph, 0, i);
		i++;
	}*/
	
	GrapgAllWay(graph, 1, 13, weizhi);

	return 0;
}
