/*¶ÓÁÐµÄ³õÊŒ»¯*/
#include<stdio.h>
#include<stdlib.h>
//#include "DataElem.h"

#define TRUE_ 0
#define FALSE_ -1


typedef struct QueueDataElem
{
	DataElem d;	
	int l;	//长度
	int vn;	//节点号
	struct QueueDataElem *datanext;
}QueueDataElem;

typedef struct Mid
{
	QueueDataElem s;
	struct Mid *next;
}MidNode;

typedef struct
{
	MidNode *front;
	MidNode *rear;
	int legth;
}Queue;

int QueueInit(Queue *head)
{
	head->front = (MidNode *)malloc(sizeof(MidNode));
	head->rear = head->front;
	head->front->next = NULL;
	head->legth = 0;

	return 0;
}

int QueueEnter(Queue *head, QueueDataElem m)
{

	MidNode *p;

	p = (MidNode *)malloc(sizeof(MidNode));
	p->s = m;
	p->next = NULL;
	head->rear->next = p;
	head->rear = p;
	head->legth++;
	return 0;
}

int QueueDelete(Queue *head, QueueDataElem *p)
{
	MidNode *e;
	if(head->front == head->rear){
	   return FALSE_;
	}
	e = (MidNode *)malloc(sizeof(MidNode));

	e = head->front->next;
   	head->front->next = e->next;
	if(head->rear == e){
        	head->rear = head->front;	
	}
   	*p= e->s;
	free(e);
	head->legth--;
	return 0;
}

int QueueEmpty(Queue *head)
{
	if(head->front != head->rear){
		return FALSE_;
	
	}
	else{
        	return TRUE_;
	}
}

int QueueClear(Queue *head)
{
    	MidNode *p;

	while(head->front!=head->rear){ 
		p = (MidNode *)malloc(sizeof(MidNode));
       		p = head->front->next; 
       	 	head->front->next = p->next;
		if(head->rear == p){
			head->rear = head->front;
		}
		free(p);
	 }
	 return TRUE_;

}

int QueueDestroy(Queue *head)
{
	MidNode *p;
	while(head->front != head->rear){
		p = (MidNode *)malloc(sizeof(MidNode));
		p = head->front->next;
		head->front->next = p->next;
	        if(head->rear == p){
		  head->rear = head->front;
		}
		free(p);
	}
	free(head);
	
	return 0;

}

