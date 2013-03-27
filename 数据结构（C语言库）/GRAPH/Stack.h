#include <stdio.h>
#include <stdlib.h>
//#include "DataElem.h"

#define TRUE_ 0		//��ȷ����ֵ
#define FALSE_ -1	//���󷵻�ֵ

#define MAXSIZE 100	//��ʼ���ܳ���
#define ADDSIZE 10	//׷���ܳ���


typedef struct 
{
	DataElem d;
	int a;
}StackDataElem;

typedef struct Node
{
	StackDataElem *top;
	StackDataElem *base;
	int legth;
}StackNode;

//ջ�ĳ�ʼ��
//����0Ϊ�ɹ�
//����-1Ϊ����ռ�ʧ��
int StackInit(StackNode *head)
{
	head->base = (StackDataElem *)malloc(MAXSIZE * sizeof(StackDataElem));
	if(head->base == NULL){
		printf("StackInit malloc error!\n");
		return FALSE_;
	}
	head->top = head->base;
	head->legth = MAXSIZE;

	return 0;
}

//��ջ����
//����0Ϊ�ɹ�
//����-1Ϊ����ռ�ʧ��
int  StackPush(StackNode *head, StackDataElem e)
{
	if(head->top - head->base == head->legth){
		head->base = (StackDataElem *)realloc(head->base, ADDSIZE * sizeof(StackDataElem));
		if(head->base == NULL){
			printf("StackPush realloc error!\n");
			return FALSE_;
		}
		head->legth = head->legth + ADDSIZE;
	}
    *(head->top) = e;
	head->top++;

	return TRUE_;
}

//��ջ����
//����0Ϊ�ɹ�
//����-1Ϊ��ջ����ջ����
int StackPop(StackNode *head, StackDataElem *e)
{
	if(head->top == head->base){
		return FALSE_;
	}
	head->top--;
	*e = *(head->top);

    return TRUE_;
}

//ջ�пղ���
//����0Ϊ��ջ
//����-1Ϊ�ǿ�ջ
int StackEmpty(StackNode *head)
{

	if(head->top == head->base){
		return TRUE_;
	}else{
		return FALSE_;
	}
}

//��ջ����
//����ֵΪջ��
int StackLegth(StackNode *head)
{
	int i;
	
	i=(head->top - head->base);

	return i;
}

//ջ����ղ���
//����0Ϊ�ɹ�
//����-1Ϊʧ��
int StackClear(StackNode *head)
{
	head->top = head->base;
	head->legth = 0;
	if(head->top - head->base!=0){
	     return FALSE_;
	}
	else
		return TRUE_;

	return 0;
}

//ջ������
//����0Ϊ���ٳɹ�
int StackDestory(StackNode *head)
{
	StackDataElem *p;

	if(head->top - head->base == 0){
		free(head->base);
		return TRUE_;
	}
	else
		head->top--;
		while(head->top != head->base){
			p = head->top;
			head->top--;
			free(p);
		}
	free(head->base);
	
	return TRUE_;
}

//�õ�ջ��Ԫ��
//����0Ϊ�ɹ�
//����-1Ϊ��ջ
int StackGettop(StackNode *head, StackDataElem *e)
{
	if(StackEmpty(head) == 0){
	   return FALSE_;
	}
	*e= *(head->top -1);

    return TRUE_;
}
