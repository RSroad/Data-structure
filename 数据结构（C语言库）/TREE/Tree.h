/*
 *���ƣ�����Ӧ��
 *
 *���ݣ����ĳ�ʼ�������Ĵ�������������/������ң�Ҷ��������������ȣ���һЩ����
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
#include <string.h>

#define TREE_NODE_MAX 100

//���Ľṹ
typedef struct
{
	int d;	
}TreeDataElem;

typedef struct Tree
{
	TreeDataElem data;
	struct Tree *left;
	struct Tree *right;
}Tree;

//���Ĵ���
int TreeCreat(Tree *root)
{
	Tree *p;
	Tree *q;
	Tree *node[TREE_NODE_MAX];
	char c;
	int leap = 0;
	int k;
	
	q = (Tree *)malloc(sizeof(Tree));
	p = root;
	root->data.d = 0;
	k = root->data.d;
	while(1){
flag:
	printf("%d�Ƿ���������Y/N��\n", k);
	flushall();
	scanf("%c", &c);
	if(c == 'Y'){
		node[leap] = p;
		leap++;
		p->left = (Tree *)malloc(sizeof(Tree));
		p->right = (Tree *)malloc(sizeof(Tree));	//
		memset(p->left, 0, sizeof(Tree));
		memset(p->right, 0, sizeof(Tree));			//
		p = p->left;
		printf("��������Ϣ:\n");
		scanf("%d", &p->data.d);
		k = p->data.d;
		flushall();
	}else if(c == 'N')
	{
		p->left = NULL;
flag2:
		while(1){
			printf("%d�Ƿ���������Y/N��\n", k);
			flushall();
			scanf("%c", &c);
			
			if(c == 'Y'){
				if(p->left == NULL){
					p->right = (Tree *)malloc(sizeof(Tree));
					memset(p->right, 0, sizeof(Tree));
				}
				p = p->right;
				printf("��������Ϣ:\n");
				flushall();
				scanf("%d", &p->data.d);
				k = p->data.d;

				break;
			}else if(c == 'N'){
				p->right = NULL;
				if(leap == 0){
					return 0;
				}
				p = node[leap - 1];
				leap--;
				k = p->data.d;
			}else{
				goto flag2;
			}
		}
	}else{
		goto flag;
	}
	
	}
	return 0;
}

//�����������
int TreeFristFind(Tree *root)
{
	Tree *p;
	Tree *node[TREE_NODE_MAX];
	int leap = 0;

	p = root;
	do{
		while(p != NULL){
			leap++;
			node[leap] = p;
			printf("%d", p->data.d);
			p = p->left;
		}
		if(leap != 0){
			p = node[leap];
			leap--;
			p = p->right;
		}
	}while(p != NULL || leap != 0);
	return 0;
}

//�����������
int TreeMidFind(Tree *root)
{
		Tree *p;
	Tree *node[TREE_NODE_MAX];
	int leap = 0;

	p = root;
	do{
		while(p != NULL){
			leap++;
			node[leap] = p;
			p = p->left;
		}
		if(leap != 0){
			p = node[leap];
			leap--;
			printf("%d", p->data.d);
			p = p->right;
		}
	}while(p != NULL || leap != 0);
	return 0;
}

//����Ҷ�ӽڵ����
int TreeLeavNum(Tree *root)
{
	Tree *p;
	Tree *node[TREE_NODE_MAX];
	int leap = 0;
	int flag = 0;

	p = root;
	do{
		while(p != NULL){
			leap++;
			node[leap] = p;
			p = p->left;
		}
		if(leap != 0){
			p = node[leap];
			leap--;
			if(p->left == NULL && p->right == NULL)
			{
				flag++;
			}
			p = p->right;
		}
	}while(p != NULL || leap != 0);
	return flag;
}

//������Ȳ���
int TreeDeep(Tree *root)
{
	Tree *p;
	Tree *node[TREE_NODE_MAX];
	int leap = 0;
	int min = 0;
	int flag = 0;

	p = root;
	do{
		while(p != NULL){
			leap++;
			min++;
			node[leap] = p;
			p = p->left;
		}
		if(leap != 0){
			p = node[leap];
			leap--;
			if(p->left == NULL && p->right == NULL)
			{
				
			}
			p = p->right;
		}
	}while(p != NULL || leap != 0);
	return flag;
}
