/*
 *名称：队列的应用
 *
 *内容：队列的初始化，创建，入队，出队，判空，等一些操作
 *
 *作者：李乐，刘丹阳
 *
 *完成时间：11月20日
 *
 *	第一次修改：2月1日
	修改人：刘丹阳
	修改内容：针对一些小bug，及备注进行修改
 *
*/


#include<stdio.h>
#include<stdlib.h>
#include "DataElem.h"

#define TRUE_ 0
#define FALSE_ -1


//队列结构
typedef struct Mid
{
	DataElem s;
	struct Mid *next;
}MidNode;

typedef struct Node
{
	MidNode *front;
	MidNode *rear;
	int legth;
}Queue;

//队列初始化函数
//返回值为0表示成功
//返回值为-1表示申请空间失败
int QueueInit(Queue *head)
{
	head->front = (MidNode *)malloc(sizeof(MidNode));
	if(head->front == NULL){
		return FALSE_;
	}
	head->rear = head->front;
	head->front->next = NULL;
	head->legth = 0;

	return TRUE_;
}

//队列插入函数
//返回值为0表示成功
//返回值为-1表示申请空间失败
int QueueEnter(Queue *head, DataElem m)
{

	MidNode *p;

	p = (MidNode *)malloc(sizeof(MidNode));
	if(p == NULL){
		return FALSE_;
	}
	p->s = m;
	p->next = NULL;
	head->rear->next = p;
	head->rear = p;

	return TRUE_;
}

//出队函数
//返回值为0表示成功
//返回值为-1此节队列为空队列
int QueueDelete(Queue *head, DataElem *p)
{
	MidNode *e;
	if(head->front == head->rear){
	   return FALSE_;
	}
	e = (MidNode *)malloc(sizeof(MidNode));

	e = head->front->next;
   	head->front->next = e->next;
	if(head->rear == e)
        head->front = head->rear;	
   	*p= e->s;
	free(e);

	return TRUE_;
}

//队列判空操作
//返回值为0表示队列为空
//返回值为-1表示队列非空
int QueueEmpty(Queue *head)
{
	if(head->front != head->rear){
		return FALSE_;
	
	}
	else{
        return TRUE_;
	}
}

//队列清除函数
//返回值为0表示成功
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

//队列销毁函数
//返回值为0表示销毁成功
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
	
	return TRUE_;

}

