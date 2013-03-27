/*
 *���ƣ�ջ������
 *
 *���ݣ�ջ�ĳ�ʼ������������ջ����ջ���пգ���һЩ����
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
#include <stdio.h>
#include <stdlib.h>
#include "DataElem.h"

#define TRUE_ 0		//��ȷ����ֵ
#define FALSE_ -1	//���󷵻�ֵ

#define MAXSIZE 100	//��ʼ���ܳ���
#define ADDSIZE 10	//׷���ܳ���

//ջ�Ľṹ
typedef struct Node
{
	DataElem *top;
	DataElem *base;
	int legth;
}Stack;

//ջ�ĳ�ʼ��
//����0Ϊ�ɹ�
//����-1Ϊ����ռ�ʧ��
int StackInit(Stack *head)
{
	head->base = (DataElem *)malloc(MAXSIZE * sizeof(DataElem));
	if(head->base == NULL){
		printf("StackInit malloc error!\n");
		return FALSE_;
	}
	head->top = head->base;
	head->legth = MAXSIZE;

	return TRUE_;
}

//��ջ����
//����0Ϊ�ɹ�
//����-1Ϊ����ռ�ʧ��
int  StackPush(Stack *head, DataElem e)
{
	if(head->top - head->base == head->legth){
		head->base = (DataElem *)realloc(head->base, ADDSIZE * sizeof(DataElem));
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
int StackPop(Stack *head, DataElem *e)
{
	if(head->top == head->base){
		return FALSE_;
	}
	head->top--;
	*e = *(head->top);

    return 0;
}

//ջ�пղ���
//����0Ϊ��ջ
//����-1Ϊ�ǿ�ջ
int StackEmpty(Stack *head)
{

	if(head->top == head->base){

		return TRUE_;
	}
    else

		return FALSE_;
	
}

//��ջ����
//����ֵΪջ��
int StackLegth(Stack *head)
{
	int i;
	
	i=(head->top - head->base);

	return i;
}

//ջ����ղ���
//����0Ϊ�ɹ�
//����-1Ϊʧ��
int StackClear(Stack *head)
{
	head->top = head->base;
	head->legth = 0;
	if(head->top - head->base!=0){
	     return FALSE_;
	}
	else
		return TRUE_;
}

//ջ������
//����0Ϊ���ٳɹ�
int StackDestory(Stack *head)
{
	DataElem *p;

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
int StackGettop(Stack *head, DataElem *e)
{
	if(StackEmpty(head) == 0){
	   return FALSE_;
	}
	*e= *(head->top -1);

    return TRUE_;
}