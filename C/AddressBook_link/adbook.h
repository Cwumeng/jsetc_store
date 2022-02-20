#ifndef _ADBOOK_H_
#define _ADBOOK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 30

typedef struct DNode
{
	char name[MAX_SIZE];
	char hometel[MAX_SIZE];
	int number;
	char addr[MAX_SIZE];
}DNode, * PDNode;

typedef struct BNode 
{
    DNode * data;

	struct BNode *pre;
	struct BNode *next;
}BNode, * PBNode;

enum ret {B_OK = 100, B_FAIL, M_OK, M_FAIL, OK, FAIL};

PBNode bnode;
PDNode dnode;

char name[MAX_SIZE];
char hometel[MAX_SIZE];
int number;
char addr[MAX_SIZE];

static PBNode book = NULL;
static PBNode pFind;
static int choose;

int create_book(PBNode *book);

int create_bnode(PBNode *bnode);

int create_dnode(PDNode *dnode);

int assign_value(PDNode dnode, char * name, char * hometel, int number, char * addr);

int is_conflict_data(PBNode book, PDNode dnode);

int insert_bnode(PBNode book, PDNode dnode);

int is_correct_format(char * name, char * hometel, int number, char * addr);

int input_value(PBNode book);

int display_book(PBNode book);

PBNode find_name(PBNode book, char * name);

PBNode find_hometel(PBNode book, char * hometel);

int display_bnode(PBNode pName);

int input_n(PBNode book);

PBNode find_number(PBNode book, int f_num);

PBNode how_to_find(PBNode book);

int delete_bnode(PBNode book, PBNode pFind);

int destroy_book(PBNode *book);

int modify_inf(PBNode book, PBNode pFind);

int print_interface();

int interface_book();

#endif