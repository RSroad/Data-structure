/*
 *���ƣ����е�Ӧ��
 *
 *���ݣ����еĳ�ʼ������������ӣ����ӣ��пգ���һЩ����
 *
 *���ߣ����֣�������
 *
 *���ʱ�䣺11��20��
 *
 *	��һ���޸ģ�2��1��
	�޸��ˣ�������
	�޸����ݣ����һЩСbug������ע�����޸�
 *
*/


#include<stdio.h>
#include<stdlib.h>
#include "DataElem.h"

#define TRUE_ 0
#define FALSE_ -1


//���нṹ
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

//���г�ʼ������
//����ֵΪ0��ʾ�ɹ�
//����ֵΪ-1��ʾ����ռ�ʧ��
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

//���в��뺯��
//����ֵΪ0��ʾ�ɹ�
//����ֵΪ-1��ʾ����ռ�ʧ��
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

//���Ӻ���
//����ֵΪ0��ʾ�ɹ�
//����ֵΪ-1�˽ڶ���Ϊ�ն���
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

//�����пղ���
//����ֵΪ0��ʾ����Ϊ��
//����ֵΪ-1��ʾ���зǿ�
int QueueEmpty(Queue *head)
{
	if(head->front != head->rear){
		return FALSE_;
	
	}
	else{
        return TRUE_;
	}
}

//�����������
//����ֵΪ0��ʾ�ɹ�
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

//�������ٺ���
//����ֵΪ0��ʾ���ٳɹ�
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

