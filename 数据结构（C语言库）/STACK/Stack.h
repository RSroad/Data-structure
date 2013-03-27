/*
 *名称：栈的引用
 *
 *内容：栈的初始化，创建，入栈，出栈，判空，等一些操作
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
#include <stdio.h>
#include <stdlib.h>
#include "DataElem.h"

#define TRUE_ 0		//正确返回值
#define FALSE_ -1	//错误返回值

#define MAXSIZE 100	//初始化总长度
#define ADDSIZE 10	//追加总长度

//栈的结构
typedef struct Node
{
	DataElem *top;
	DataElem *base;
	int legth;
}Stack;

//栈的初始化
//返回0为成功
//返回-1为申请空间失败
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

//入栈操作
//返回0为成功
//返回-1为申请空间失败
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

//出栈操作
//返回0为成功
//返回-1为空栈，出栈出错
int StackPop(Stack *head, DataElem *e)
{
	if(head->top == head->base){
		return FALSE_;
	}
	head->top--;
	*e = *(head->top);

    return 0;
}

//栈判空操作
//返回0为空栈
//返回-1为非空栈
int StackEmpty(Stack *head)
{

	if(head->top == head->base){

		return TRUE_;
	}
    else

		return FALSE_;
	
}

//求栈长度
//返回值为栈长
int StackLegth(Stack *head)
{
	int i;
	
	i=(head->top - head->base);

	return i;
}

//栈的清空操作
//返回0为成功
//返回-1为失败
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

//栈的销毁
//返回0为销毁成功
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

//得到栈顶元素
//返回0为成功
//返回-1为空栈
int StackGettop(Stack *head, DataElem *e)
{
	if(StackEmpty(head) == 0){
	   return FALSE_;
	}
	*e= *(head->top -1);

    return TRUE_;
}