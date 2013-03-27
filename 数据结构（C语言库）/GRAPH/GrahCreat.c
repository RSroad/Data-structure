
/*
 *���ƣ�ͼ�����ڽӱ���ʽ
 *
 *���ݣ��Ͻ�˹�����㷨��ͼ������·����ͼ������������������ң��Լ��ú���ָ��ʵ����һЩ���ܡ�
 *
 *���ߣ�������
 *
 *���ʱ�䣺11��20��
 *
 *	��һ���޸ģ�2��1��
	�޸��ˣ�������
	�޸����ݣ����һЩСbug������ע�����޸�
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

//�ڵ���������
typedef struct
{
	int a;
}VertexData;

//����Ϣ
typedef struct
{
	char b;
}OtherInfo;

//ͼ�ڵ�����
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	OtherInfo test;
}ArcNode;

//�ڽӱ�ڵ�
typedef struct VertexNode
{
	VertexData data;
	ArcNode *fristarc;
}VertexNode;

//����ͼ�������ݽṹ
typedef struct 
{
	VertexNode vertex[MAX_VERTEX_NUM];
	int vexnum, arcnum;
	GraphKind kind;
}AdjList;

//Ϊ������ȵ���Ľڵ���Ϣ������ȡ���ñ�Ĵ��棩
typedef struct ListNode
{
	int deep;		//���������
}ListNode;

//���ļ��н�ͼ����
int GraphRead(AdjList *graph, int a[][MAX_VERTEX_NUM])
{
	FILE *f;
	int i;
	int j;

	f = fopen("�ڽӾ���(��)", "r");
	for(i = 0 ; i < graph->vexnum ; i++){
		for(j = 0 ; j < graph->vexnum ; j++){
			fscanf(f, "%d", &a[i][j]);
		}
	}

	return 0;
}

//ͼ�ĳ�ʼ�����Դ���Ϊ14���ڵ㣩
int GraphInit(AdjList *graph)
{

	printf("�������ж��ٸ��㣿\n");
	scanf("%d", &graph->vexnum);
	graph->vexnum = graph->vexnum;

	return 0;
}

//ͼ�Ĵ�������
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

//�����������
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


//����
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


//�Ͻ�˹���������·��
int GraphListPath_DJS(AdjList *graph, int f, int t)
{
	Queue *path;					//�������
	QueueDataElem *node, *p;			//�������Ԫ�ؽڵ�
	MidNode *head, *mid;				//������ת�ڵ�
	int min = 0, num = 0;				//��¼�ڵ����ֵ
	int i = 0;
	int weigth[MAX_VERTEX_NUM][MAX_VERTEX_NUM];	//����ٽӾ���
	int donevex[MAX_VERTEX_NUM] = {0};		//����Ѿ��߹��Ľڵ�
	ListNode LiNo[MAX_VERTEX_NUM];			//���������Ϣ
	ArcNode *GrNo;					//����ĩβ�ڵ�
	List *h;

	GraphRead(graph, weigth);			//��ȡ�ٽӾ���
	path = (Queue *) malloc (sizeof(Queue));
	p = (QueueDataElem *) malloc (sizeof(QueueDataElem));
	GrNo = (ArcNode *) malloc (sizeof(ArcNode));
	node = (QueueDataElem *) malloc (sizeof(QueueDataElem));	//��ʼ��
	donevex[f] = 1;					//�ó�ʼ����·��
	QueueInit(path);				//��ʼ������
	node->l = 0;					
	node->vn = f;
	node->datanext = NULL;				//�ó�ʼ�ڵ��nextΪNULL
	QueueEnter(path, *node);			//��ʼ�ڵ����
	while(i < graph->vexnum - 1){			//����ѭ��
		min = 32768;
		mid = path->front->next;		
		node = &(mid->s);			//ȥ����ͷԪ��
		while(1){
			GrNo = graph->vertex[node->vn].fristarc;	//�õ��ٽӱ���̬��ͷָ��
			while(GrNo != NULL){				
				if((weigth[node->vn][GrNo->adjvex] + node->l) < min && donevex[GrNo->adjvex] != 1){
					min = weigth[node->vn][GrNo->adjvex] + node->l;
					num = GrNo->adjvex;
					LiNo[GrNo->adjvex].deep = node->vn;
				}
				GrNo = GrNo->nextarc;	//�ڽӱ����һ��
			}
			mid = mid->next;		//�ж϶����Ƿ�Ϊ��
			if(mid == NULL){
				break;
			}
			node = &(mid->s);
		}
		node = (QueueDataElem *) malloc (sizeof(QueueDataElem));
		node->l = min;
		node->vn = num;
		donevex[num] = 1;
		mid = path->front->next;				//ָ���ʼ·��
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
		QueueEnter(path, *node);				//��·�����
		i++;
	}
	head = path->front;
	while(head != NULL){						//ͷ�����������ҽڵ�
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

//�����õ�ָ�뺯��
int weizhi(int a)
{
	FILE *f;
	int i = 0;
	static leap = 0;
	static	char name[MAX_VERTEX_NUM][20];

	if (leap == 0){
		f = fopen("����", "r");
		while(!feof(f)){
			fscanf(f, "%s", name[i]);
			i++;
		}
		leap++;
	}
	printf("%s ", name[a]);
	return 0;
}

//������·��֮��ľ���
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

//������
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
