#ifndef LISTA_H_   
#define LISTA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{
	char word[256];
	int total;
	struct node *next;
}node;

typedef struct list{
	node * first;
	int size;
}list;

void print_list(node * head);
void insert_first(node *node, list *list);
void insert_list(node *node_insert, node *node_list);
node *delete_first(char* word, list *list);
node *delete_list(char* word, node *node);

#endif