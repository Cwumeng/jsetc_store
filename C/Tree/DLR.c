#include <stdio.h>
#include <stdlib.h>

#define NULLKY '?'
#define MAX_NODE 50

typedef struct BTNode
{
	char data;
	struct BTNode *Lchild,*Rchild;
}BTNode;

BTNode *Create_BTree(void)
{
	BTNode *T, *p, *s[MAX_NODE];
        char ch;
	int i,j;

	while(1)
	{
		scanf("%d",&i);
		if (0 == i)
		{
			break;
		}
		else
		{
			ch = getchar();
			p = (BTNode*)malloc(sizeof(BTNode));
			p->data = ch;
			p->Lchild = p->Rchild = NULL;
			s[i] = p;
			if (1 == i)
			{
				T = p;
			}
			else
			{
                                j = i / 2;
				if (i % 2 == 0)
				{
					s[j]->Lchild = p;
				}
				else
				{
					s[j]->Rchild = p;
				}
			 
			}
		}
	}
    return T;
}

BTNode *Preorder_Create_BTree(BTNode **T)
{
	char ch;
	ch = getchar(); 
	getchar();
	if (ch == NULLKY)
	{
                *T = NULL;
		return *T;
	}
	else
	{
                (*T) = (BTNode *)malloc(sizeof(BTNode));
		(*T)->data = ch;
		Preorder_Create_BTree(&(*T)->Lchild);
		Preorder_Create_BTree(&(*T)->Rchild);
		return *T;
	}
}

void visit(char data)
{
	printf("%c\n",data);
}

void PreorderTraverse(BTNode *T)
{
	BTNode *stack[MAX_NODE], *p = T, *q;
	int top = 0;
	stack[top] = NULL;

	if (T == NULL)
	{
		printf("Binary Tree is Empty!\n");
	}
	else
	{
                do
		{
                        visit(p->data);

			q = p->Rchild;
			if (q != NULL)
			{
				stack[++top] = q;
			}

			p = p->Lchild;
			if (p == NULL)
			{
                                p = stack[top];

				//stack[0]会被访问到，赋初始NULL
				top--;
			}
		}
		while(p != NULL);
	}
}

void InorderTraverse(BTNode *T)
{
	BTNode *stack[MAX_NODE], *p = T;
	int top = 0, bool = 1;

	if (T == NULL)
	{
		printf("Binart Tree is Empty!\n");
	}
	else
	{
        do
		{
			while (p != NULL)
			{
				stack[++top] = p;
				p = p->Lchild;
			}
			if (top == 0)
			{
				bool = 0;
			}
			else 
			{
				p = stack[top];
				top--;
				visit(p->data);
				p = p->Rchild;
			}
		} while (bool != 0);
	}
}

void PostorderTraverse(BTNode *T)
{
	BTNode *s1[MAX_NODE], *p = T;
	int s2[MAX_NODE], top = 0, bool = 1;

	if (T == NULL)
	{
		printf("Binary Tree is Empty !\n");
	}
	else
	{
        do
		{
			while(p != NULL)
			{
				s1[++top] = p;
				s2[top] = 0;
				p = p->Lchild;
			}
			if (top == 0)
			{
				bool = 0;
			}
			else if (s2[top] == 0)
			{
				p = s1[top]->Rchild;
				s2[top] = 1;
			}
			else
			{
                                p = s1[top];
				top--;
				visit(p->data);
				p = NULL;// 使循环将继续进行而不死循环
			}
		} while (bool != 0);
		
	}
}

void LevelTraverse(BTNode *T)
{
	BTNode *Queue[MAX_NODE], *p = T;
	int front = 0, rear = 0;

	if (p != NULL)
	{
		Queue[++rear] = p;
		while (front < rear)
		{
			p = Queue[++front];
			visit(p->data);
			if (p->Lchild != NULL)
			{
				Queue[++rear] = p->Lchild;
			}
			if (p->Rchild != NULL)
			{
				Queue[++rear] = p->Rchild;
			}
		}
	}
}

//段错误，无法运行
int search_leaves(BTNode *T)
{
	BTNode *stack[MAX_NODE], *p = T;
	int top = 0, num = 0;
	stack[top] = NULL;

	if (T != NULL)
	{
		stack[++top] = p;
		while (top > 0)
		{
			p = stack[top--];
			if (p->Lchild == NULL && p->Rchild == NULL)
		        {
				num++;
			}
                        if (p->Rchild != NULL)
			    stack[++top] = p->Rchild;
			if (p->Lchild != NULL)
			    stack[++top] == p->Lchild;	
		}
	}
	return num;
}

//层数不对
int search_depth(BTNode *T)
{
	BTNode *Queue[MAX_NODE], *p = T;
	int front = 0, rear = 0, depth = 0, level = 0;

	if (T != NULL)
	{
		Queue[++rear] = p;
		level = rear;
		while (front < rear)
		{
			p = Queue[++front];
			if (p->Lchild != NULL)
			{
				Queue[++rear] = p->Lchild;
			}
			if (p->Rchild != NULL)
			{
				Queue[++rear] = p->Rchild;
			}
			if (front == level)
			{
				depth++;
				level = rear;
			}
		}
	}
}
int main()
{
        BTNode * head;

	//输入A B D ? ? E ? G ? ? C F ? ? ?
	Preorder_Create_BTree(&head);  

        printf("leafs:%d\n",search_leaves(head));

	printf("depths:%d\n",search_depth(head));

        //PreorderTraverse(head);
	//InorderTraverse(head);
        //PostorderTraverse(head);
	//LevelTraverse(head);

	return 0;
}
