#include "adbook.h"

int create_book(PBNode *book)
{
    if (NULL == book)
	{
		return FAIL;
	}

	*book = (PBNode)malloc(sizeof(BNode));
	if (NULL == *book)
	{
		return M_FAIL;
	}

	(*book)->next = (*book)->pre = *book;

    return OK;
}

int create_bnode(PBNode *bnode)
{
	if (NULL == bnode)
	{
        return FAIL;
	}

	*bnode = (PBNode)malloc(sizeof(BNode));
	if (NULL == *bnode)
	{
		return M_FAIL;
	}

	return OK;
}

int create_dnode(PDNode *dnode)
{
    if (NULL == dnode)
	{
		return FAIL;
	}

    *dnode = (PDNode)malloc(sizeof(DNode));
	if (NULL == *dnode)
	{
		return M_FAIL;
	}

	return OK;
}

int assign_value(PDNode dnode, char * name, char * hometel, int number, char * addr)
{
	if (NULL == dnode)
	{
		return FAIL;
	}

	strcpy(dnode->name, name);
	strcpy(dnode->hometel, hometel);
	dnode->number = number;
	strcpy(dnode->addr, addr);

    return OK;	
}

int is_conflict_data(PBNode book, PDNode dnode)
{
    if (NULL == book || NULL == dnode)
	{
		return FAIL;
	}

	PBNode pNode = book->next;
    while (book != pNode)
	{
        if (0 == strcmp(dnode->name, pNode->data->name) 
		    || 0 == strcmp(dnode->hometel, pNode->data->hometel))
		{
			return FAIL;
		}

		pNode = pNode->next;
	}

    return OK;
}

int insert_bnode(PBNode book, PDNode dnode)
{
    if (NULL == book || NULL == dnode)
	{
		return FAIL;
	}
    
	if (FAIL == is_conflict_data(book, dnode))
	{
		return FAIL;
	}

    PBNode pIns = NULL;
	if (OK == create_bnode(&pIns))
	{
		pIns->data = dnode;
       
        pIns->next = book;
		pIns->pre = book->pre;
		book->pre->next = pIns;
		book->pre = pIns;
	}

	return OK;
}

int is_correct_format(char * name, char * hometel, int number, char * addr)
{
	int len = strlen(hometel);
	int i;

	if (len != 11)
	{
		return FAIL;
	}

	for (i = 0; i < len; i++)
	{
		if (hometel[i] < '0' || hometel[i] > '9')
		{
			return FAIL;
		}
	}
	
	return OK;
}

int input_value(PBNode book)
{
    char name[MAX_SIZE];
	char hometel[MAX_SIZE];
	int number;
	char addr[MAX_SIZE];

	scanf("%s%s%d%s", name, hometel, &number, addr);

	if (FAIL == is_correct_format(name, hometel, number, addr))
	{
		return FAIL;
	}

    PDNode pVal = NULL;
    create_dnode(&pVal);
	assign_value(pVal, name, hometel, number, addr);

	if (FAIL == insert_bnode(book, pVal))
	{
        return FAIL;
	}

	return OK;       
}

int display_book(PBNode book)
{
    if (NULL == book)
	{
		return FAIL;
	}

	PBNode pNode = book->next;

    printf("book:\n");
	while (book != pNode)
	{
		printf("| Name:%s\t| Hometel:%s\t| Number:%d\t| Addr:%s\t |\n"
		        ,pNode->data->name, pNode->data->hometel, pNode->data->number, pNode->data->addr);
		
		pNode = pNode->next;
	}

    return OK;
}

int display_bnode(PBNode pName)
{
    if (NULL == pName)
	{
		return FAIL;
	}

    printf("Find:\n");
	printf("| Name:%s\t| Hometel:%s\t| Number:%d\t| Addr:%s\t |\n"
			,pName->data->name, pName->data->hometel, pName->data->number, pName->data->addr);
		
    return OK;
}

PBNode find_name(PBNode book, char * name)
{
    if (NULL == book || NULL == name)
	{
		return NULL;
	}

	PBNode pNode = book->next;
	while (book != pNode)
	{
        if (0 == strcmp(pNode->data->name, name))
		{
			return pNode;
		}

		pNode = pNode->next;
	}

    return NULL;
}

PBNode find_hometel(PBNode book, char * hometel)
{
    if (NULL == book || NULL == hometel)
	{
		return NULL;
	}

	PBNode pNode = book->next;
	while (book != pNode)
	{
        if (0 == strcmp(pNode->data->hometel, hometel))
		{
			return pNode;
		}

		pNode = pNode->next;
	}

    return NULL;
}

PBNode find_number(PBNode book, int f_num)
{
	if (NULL == book)
	{
		return NULL;
	}

	PBNode pNode = book->next;
	while (book != pNode)
	{
        if (f_num == pNode->data->number)
		{
			return pNode;
		}

		pNode = pNode->next;
	}

    return NULL;
}

int input_n(PBNode book)
{
    if (NULL == book)
	{
        return FAIL;
	}

    int n;
	printf("Enter the number of elements!\n");
	printf("n = ");
	scanf("%d",&n);

    int Cur_elem = n;
	while (n--)
	{
		printf("Please enter the %d element!\n", (Cur_elem - n));
		if (FAIL == input_value(book))
        {
            printf("Entry error!\n");
			n++;
			continue;
		}
	} 

    return OK;
}

PBNode how_to_find(PBNode book)
{
	if (NULL == book)
	{
		return NULL;
	}

	printf("Choose how to find an element of your address book!\n");
	printf("1:by name\t 2:by number\t 3:by hometel\n");

    int n;
	printf("n = ");
	scanf("%d",&n);

    while (1 > n && 3 < n)
	{
		printf("Please enter the correct n!\n");
		printf("n = ");
	    scanf("%d",&n);
	}

    PBNode pFind = NULL;
	if (1 == n)
	{
		char f_name[MAX_SIZE];
        printf("Find name = ");
		scanf("%s", f_name);
        
		pFind = find_name(book, f_name);
	}
	else if (2 == n)
	{
	    int f_num;
	    printf("Find number = ");
		scanf("%d", &f_num);

		pFind = find_number(book, f_num);
	}
	else
	{
		char f_hometel[MAX_SIZE];
        printf("Find hometel = ");
		scanf("%s", f_hometel);
        
		pFind = find_hometel(book, f_hometel);
	}
	
	
	if (NULL == pFind)
	{
		printf("There is no such person!\n");
	}

	return pFind;
}

int delete_bnode(PBNode book, PBNode pFind)
{
	if (NULL == book || NULL == pFind)
	{
		return FAIL;
	}

	PBNode pNode = book->next;
	while (pNode != book)
	{
        if (pFind == pNode)
		{
			pNode->next->pre = pNode->pre;
			pNode->pre->next = pNode->next;

			if (pNode != NULL)
			{
				free(pNode);
				pNode = NULL;
			}
            
			return OK;
		}

		pNode = pNode->next;
	}

    return FAIL;
}

int destroy_book(PBNode *book)
{
    if (NULL == book || NULL == *book)
	{
		return FAIL;
	}

    PBNode pNode = (*book)->next;
	PBNode pDel;
    while (*book != pNode)
	{
		pDel = pNode;
		pNode = pNode->next;

		pDel->next->pre = *book;
		(*book)->next = pDel->next;

		if (pDel != NULL)
		{
			free(pDel);
			pDel = NULL;
		}
	}

	free(*book);
	*book = NULL;

    return OK;
}

int modify_inf(PBNode book, PBNode pFind)
{
    if (NULL == book)
	{
		return FAIL;
	}

    if (NULL != pFind)
	{
	    scanf("%s%s%d%s", name, hometel, &number, addr);
        
		strcpy(pFind->data->name, name);
		strcpy(pFind->data->hometel, hometel);
        pFind->data->number = number;
		strcpy(pFind->data->addr, addr);
	}
    
    return FAIL;
}

int print_interface()
{
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("* * * * * * * *                            * * * * * * * * * * * \n");
	printf("* * * * * * * *         weclome            * * * * * * * * * * * \n");
	printf("* * * * * * * *                            * * * * * * * * * * * \n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n\n");

	printf("****    1 Add Information!       2 List Information!      ****\n");
	printf("****    3 Information Query      4 Delete Information!    ****\n");
	printf("****    5 Modify Information!    6 Destroy Book!          ****\n");
	printf("****    7 Print Interface!       8 Clear!                 ****\n");
	printf("****               Press other key to exit!               ****\n\n");

    printf("  **          hello, sir! what can I do for you ?          **\n\n");

	return OK;
}

int interface_book()
{
	print_interface();

    do
	{
	    scanf("%d",&choose);
		
		switch(choose)
		{
			case 1 :
				if (NULL == book)
				{
					create_book(&book);
				}

				input_n(book);

				printf("success!\n");
				break;

			case 2 :
				display_book(book);

				printf("success!\n");
				break;

			case 3 :
				pFind = how_to_find(book);
				display_bnode(pFind);

				printf("success!\n");
				break;

			case 4 :
				pFind = how_to_find(book);
				display_bnode(pFind);
				delete_bnode(book, pFind);

				printf("success!\n");
				break;

			case 5 :
				pFind = how_to_find(book);
				display_bnode(pFind);
				modify_inf(book, pFind);

				printf("success!\n");
				break;

			case 6 :
				destroy_book(&book);

				printf("success!\n");
				break;
			
			case 7 :
				print_interface();

				printf("success!\n");
				break;

			case 8 :
			    system("clear"); 

				printf("success!\n");
				break;

			default:
			
			    printf("success!\n");
				return OK;
		}
	} while (1);
	
    return FAIL;
}