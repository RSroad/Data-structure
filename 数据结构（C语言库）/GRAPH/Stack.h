#include <stdio.h>
#include <stdlib.h>
//#include "DataElem.h"

#define TRUE_ 0		//正确返回值
#define FALSE_ -1	//错误返回值

#define MAXSIZE 100	//初始化总长度
#define ADDSIZE 10	//追加总长度


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

//栈的初始化
//返回0为成功
//返回-1为申请空间失败
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

//入栈操作
//返回0为成功
//返回-1为申请空间失败
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

//出栈操作
//返回0为成功
//返回-1为空栈，出栈出错
int StackPop(StackNode *head, StackDataElem *e)
{
	if(head->top == head->base){
		return FALSE_;
	}
	head->top--;
	*e = *(head->top);

    return TRUE_;
}

//栈判空操作
//返回0为空栈
//返回-1为非空栈
int StackEmpty(StackNode *head)
{

	if(head->top == head->base){
		return TRUE_;
	}else{
		return FALSE_;
	}
}

//求栈长度
//返回值为栈长
int StackLegth(StackNode *head)
{
	int i;
	
	i=(head->top - head->base);

	return i;
}

//栈的清空操作
//返回0为成功
//返回-1为失败
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

//栈的销毁
//返回0为销毁成功
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

//得到栈顶元素
//返回0为成功
//返回-1为空栈
int StackGettop(StackNode *head, StackDataElem *e)
{
	if(StackEmpty(head) == 0){
	   return FALSE_;
	}
	*e= *(head->top -1);

    return TRUE_;
}
