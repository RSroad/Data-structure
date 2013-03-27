/*
 *名称：链表
 *
 *内容：链表的初始化，插入，判空，销毁，删除等操作
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


/*链表的架构*/
#include <stdio.h>
#include <stdlib.h>

#define TRUE_ 0
#define FALSE_ -1

typedef struct 
{
	int a;
}DataElem;

typedef struct Node
{
	DataElem data;
	struct Node *next;
} List;

//链表初始化
//返回0即为初始化成功
int LinkInit(List *head)
{
	head->next = NULL;
	return TRUE_;
}

//链表尾插法
//返回0代表成功
//返回-1代表申请空间失败
int LinkInsert(List *head,DataElem e)
{
	List *p, *q;
	p = head;
	while( p->next != NULL ){
		p=p->next;//此处为判别p->next是否为空，若为空则从头弹出
	}
	q = (List *)malloc(sizeof(List));
	if(q = NULL){
		return -1;
	}
	q->data = e;
    p->next = q;
	p = q;
    p->next = NULL;

	return TRUE_;		
}

//求链表长度
//返回值为链表长度
int LinkLegth(List *head)//链表的长度运算
{
	List *p;
	int k=0;

	p = head->next;
	while(p !=NULL)
	{
		p = p->next;
		k++;
	
	}

	return k;

}


//链表的判空操作
//返回0为空
//返回-1为非空
int LinkEmpty(List *head)//链表的判空操作
{
	List *p;
	
	p = head;
	if(p->next==NULL){
		printf("List is empty!\n");
		return FALSE_;
	}
	else
	{
		printf("List is not empty!\n");
		return TRUE_;
	
	}
}

//链表的销毁操作
//返回0为销毁成功
//返回
int LinkDestroy(List *head)//链表的销毁操作
{
	List *p,*q,*temp;
	p = head;
	q = p->next;

	if(q == NULL)
	{
		free(head);
		return TRUE_;
	}
	else
	{
      while(q!=NULL)
	  {
		temp=q;
		p->next = q->next;
		q = q->next;
		free(temp);
	  }
        free(head);
        printf("it is destroy!\n");
	}
	return TRUE_;
}

//链表清空操作
//返回0代表清空完毕
//返回-1代表清空失败
int LinkClear(List *head)//链表的清空
{
	List *p,*q,*temp;

	p = head;
	q = p->next;
	if(p == NULL){
		return FALSE_;
	}
	if(q == NULL){
		printf("it is already clear!\n");
		return TRUE_;
	}
	while(q != NULL)
	{
		temp = q;
		p->next = q->next;
		q = q->next;
		free(temp);
	}
	printf("it is clear!\n");
	
	return TRUE_;
}

//链表删除操作
//返回0代表删除节点成功
int LinkDelete(List *head,int i,DataElem *e)//链表的删除操作
{
	List *p,*r;
	int k=0;

	p = head;
	while(p->next!=NULL && k< i-1){
		p = p->next;
		k++;
	}
	if(!(p->next)){
		printf("节点不合理!\n");
		return FALSE_;
	}
	r = p->next;
	p->next = r->next;
	*e = r->data;
	free(r);

	return 0;
}

//返回链表定点插入函数
//返回值为0为表示插入成功
//返回值为-1表示插入位置有误
int LinkIns(List *head, int i, DataElem *e)//链表的插入操作
{
	List *p,*q;	
    int j=0;	
	p = head;

	if(i <= 0){
		printf("it is wrong!\n");
		return FALSE_;
	}
	while(p!=NULL && j<i-1)
	{
		p = p->next;
		j++;
	}
	if(p == NULL){
		printf("it is wrong!\n");
		return FALSE_;
	}
	q = (List *)malloc(sizeof(List));
	q->data = *e;
	q->next = p->next;
	p->next = q;

	return TRUE_;
}

//链表取特定元素
//返回0代表取头成功
//返回-1代表位置错误
int LinkGet(List *head,int i,DataElem *e)//查找节点
{
	List *p,*q;
	int k=0;

	if(i < 1){
		printf("it is wrong!\n");
		return FALSE_;
	}
	p = head;
	while(p->next!=NULL && k < i-1)
	{
		p = p->next;
		k++;
	}
	if(p->next == NULL)
	{
		printf("结点不存在!\n");
		return FALSE_;
	}
	q = p->next;
	*e = q->data;

	return TRUE_;
}

//链表倒序操作
//返回值为0代表倒序成功
//返回值为-1代表空链表
int LinkDxu(List *head)//链表的倒序
{
	List *p,*k,*head1;
   
	p = head->next;
    if(head->next == NULL){
		printf("this is wrong !\n");
		return FALSE_;
	}
    head1 = head;
	head1->next = NULL;
	
	while(p!=NULL)
	{
        k =p;
		p = p->next;
		k->next = head1->next;
		head1->next = k;
	
	
	}

	return TRUE_;
}

/*int LinkPaixu(List *head)//链表的排序操作
{
    List *p,*q,*s;
	if(head->next == NULL){
		printf("this is wrong!\n");
		return FALSE_;
	}
	else
	{
		for(head = head->next;head->next!=NULL;head = head->next)
		{
			for(q = head->next;q!=NULL;q = q->next)
			{
				if((head->data.a)>(q->data.a))
				{
					s = (List *)malloc(sizeof(List));
					p = (List *)malloc(sizeof(List));
					*s = *q;
					*p = *head;
					*head = *q;
					*q = *p;
					head->next = p->next;
					q->next = s->next;
					free(s);
					free(p);
				}
			}
		}
	}

	return TRUE_;
}*/
