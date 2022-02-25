#include <stdio.h>
#include <stdlib.h>

#define NULLKY '?'
#define MAX_NODE 50

typedef struct BTNode
{
	char data;

    int lflag;
	int rflag;
    struct BTNode *Lchild, *Rchild;
}BTNode;

BTNode * Create_BTree(void)
{
	BTNode *T;
	BTNode *p;
	BTNode *s[MAX_NODE];

	char ch;
	int i, j;

	while (1)
	{
        scanf("%d",&i);
		if (0 ==  i)
		{
			break;
		}
        else
		{
			ch = getchar();
			p = (BTNode *)malloc(sizeof(BTNode));
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
	}
	else
	{
	    *T = (BTNode *)malloc(sizeof(BTNode));
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
	BTNode *stack[MAX_NODE];
	BTNode *p = T;
	BTNode *q;

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
				top--;
			}


		} while(p != NULL);
	}
}

void InorderTraverse(BTNode *T)
{
    BTNode *stack[MAX_NODE];
	BTNode *p = T;

	int top = 0;
	int bool = 1;

    if (T == NULL)
	{
		printf("Binary Tree is Empty!\n");
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
			if (0 == top)
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
    BTNode *s1[MAX_NODE];
	BTNode *p = T;
	int s2[MAX_NODE];
	int top = 0;
	int bool = 1;

	if (T == NULL)
	{
		printf("Binary Tree is Empty!\n");
	}
	else
	{
		do
		{
			while (p != NULL)
			{
				s1[++top] = p;
				s2[top] = 0;
				p = p->Lchild;
			}
			if (top == 0)
			{
				bool = 0;
			}
			else if(s2[top] == 0)
			{
				p = s1[top]->Rchild;
				s2[top] = 1;
			}
			else
			{
				p = s1[top];
				top--;
				visit(p->data);
				p = NULL;
			}
			
			
		} while (bool != 0);
		
	}
}

void LevelTraverse(BTNode *T)
{
	BTNode *Queue[MAX_NODE];
	BTNode *p = T;
    
	int front = 0;
	int rear = 0;

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

int search_leaves(BTNode *T)
{
	BTNode *stack[MAX_NODE];
	BTNode *p = T;
	int top = 0;
	int num = 0;
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
			{
				stack[++top] = p->Rchild;
			}
			if (p->Lchild != NULL)
			{
				stack[++top] = p->Lchild;
			}
		}
	}
	return num;
}

int search_depth(BTNode *T)
{
	BTNode *Queue[MAX_NODE];
	BTNode *p = T;

    int front = 0, rear = 0;
	int depth = 0, level = 0;

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

	return depth;
}

BTNode *in_pre = NULL;
void in_thread(BTNode **root)
{
	if (*root != NULL)
	{
		in_thread(&(*root)->Lchild);

		if ((*root)->Lchild == NULL)
		{
			(*root)->Lchild = in_pre;
			(*root)->lflag  = 1;
		}
        
		if (in_pre != NULL && in_pre->Rchild == NULL)
		{
            in_pre->Rchild = *root;
			in_pre->rflag = 1;
		}

		in_pre = *root;

		in_thread(&(*root)->Rchild);
	}
}

BTNode * in_first_node(BTNode *root)
{
	if (root == NULL)
	{
		return NULL;
	}

	BTNode *p = root;
	while (p->lflag == 0)
	{
		p = p->Lchild;
	}

	return p;
}

BTNode * in_next_node(BTNode *root)
{
    if (root == NULL)
	{
		return NULL;
	}

	if (root->rflag == 0)
	{
		return in_first_node(root->Rchild);
	}
	else
	{
		return root->Rchild;
	}
}

void thread_traverse(BTNode *root)
{
	BTNode *first = root;
	first = in_first_node(first);
    while (first)
	{
		printf("%c ", first->data);

        first = in_next_node(first);
	}
}

int main()
{
    BTNode * head;

	//输入A B D ? ? E ? G ? ? C F ? ? ?
	Preorder_Create_BTree(&head); 

	in_thread(&head);
	if (in_pre != NULL)
	{
		in_pre->Rchild = NULL;
		in_pre->rflag = 1;
	}

    thread_traverse(head);

	// BTNode *p = in_first_node(head);
	// for (; p != NULL ; p =in_next_node(p))
	// {
	// 	printf("%c\n",p->data);
	// }




    // printf("leafs:%d\n",search_leaves(head));

	// printf("depths:%d\n",search_depth(head));

        //PreorderTraverse(head);
	//InorderTraverse(head);
        //PostorderTraverse(head);
	//LevelTraverse(head);

	return 0;

	
}