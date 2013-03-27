/*����ļܹ�*/
#include <stdio.h>
#include <stdlib.h>

#define TRUE_ 0
#define FALSE_ -1

/*typedef struct 
{
	int a;
}QueueDataElem;*/

typedef struct LinkNode
{
	QueueDataElem data;
	struct LinkNode *next;
} List;

int ListInit(List *head)
{
	head->next = NULL;
	return TRUE_;
}

int ListInsert(List *head,QueueDataElem e)
{
	List *p, *q;
	p = head;
	while( p->next != NULL ){
		p=p->next;//�˴�Ϊ�б�p->next�Ƿ�Ϊ�գ���Ϊ�����ͷ����
	}
	q = (List *)malloc(sizeof(List));
	q->data = e;
    p->next = q;
	p = q;
    p->next = NULL;

	return TRUE_;		
}

int ListLegth(List *head)//����ĳ�������
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

int ListEmpty(List *head)//������пղ���
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

int ListDestroy(List *head)//��������ٲ���
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

int ListClear(List *head)//��������
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

int ListDelete(List *head,int i,QueueDataElem *e)//�����ɾ������
{
	List *p,*r;
	int k=0;

	p = head;
	while(p->next!=NULL && k< i-1){
		p = p->next;
		k++;
	}
	if(!(p->next)){
		printf("�ڵ㲻����!\n");
		return FALSE_;
	}
	r = p->next;
	p->next = r->next;
	*e = r->data;
	free(r);

	return 0;
}

int ListIns(List *head, int i, QueueDataElem e)//����Ĳ������
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
	q->data = e;
	q->next = p->next;
	p->next = q;

	return TRUE_;
}

int ListGet(List *head,int i,QueueDataElem *e)//���ҽڵ�
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
		printf("��㲻����!\n");
		return FALSE_;
	}
	q = p->next;
	*e = q->data;

	return TRUE_;
}

int ListDxu(List *head)//����ĵ���
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

/*int ListPaixu(List *head)//������������
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
