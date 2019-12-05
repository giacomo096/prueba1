#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"



void print_list(node * head){

	printf(" en la lista %s, %d\n", head->word, head->total);
	if(head-> next != NULL){
	print_list(head->next);
	}
}

void insert_first(node *node, list *list){
	if(list->size == 0){
		list->first = node;
		list->size =1;
	}else{
		if(list->first->total <= node->total){
			node->next = list-> first;
			list->first = node;
			list->size += 1;
		}else{
			if(list->first->next == NULL){
				list->first->next = node;
				list->size +=1;
			}else{
				insert_list(node, list->first);
				list->size += 1;
			}
		}
	}
}

void insert_list(node *node_insert, node *node_list){
	if(node_list->next == NULL){
		node_list->next = node_insert;	
	}else{
		if(node_list->next->total <= node_insert->total){
		node_insert->next = node_list->next;
		node_list->next = node_insert;
		}else{
			insert_list(node_insert, node_list->next);
		}
	}
}


node *delete_first(char* word, list *list){
	if(strcmp(list->first-> word, word) != 0){
		if(list->first->next != NULL){
			return delete_list(word,list->first);
		}else{
			return NULL;
		}
	}else{
		node *node =NULL;
		node = malloc(sizeof(node));
		node = list-> first;
		list->first = list->first->next;
		node->next = NULL;
		return node;
	}
}

node *delete_list(char* word, node *nodo){
	if(nodo->next != NULL){
		if(strcmp(nodo->next->word, word) != 0){
			return delete_list(word, nodo->next);
		}else{
			node *nodew = NULL;
			nodew = malloc(sizeof(node));
			nodew = nodo->next;
			nodo->next = nodo->next->next;
			nodew->next = NULL;
			return nodew;
		}
	}else{
		return NULL;
	}
}