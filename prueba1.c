#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"

int main() {
	/* Declaramos variables para la entrada */
	char *string = malloc(256);
	char *palabra1 = malloc(256);
	char delim[] = " ";
	int archivos;
	FILE* file;
	node * nodo = NULL;
	list *lista = NULL;
	lista = malloc(sizeof(list));
	if (lista == NULL) {exit(4);}
	lista->size = 0;
	/* Obtenemos el comando de entrada */
	fgets(string, 256, stdin);
	/* Cambiamos el /n de la entrada */
    if ((strlen(string) > 0) && (string[strlen (string) - 1] == '\n'))
        string[strlen (string) - 1] = '\0';

	printf("%s\n", string);
	char *word = strtok(string, delim);
	printf("%s\n", string);
/*chequeamos sintaxis correcta*/
	if( !strcmp(word, "frecpal")){
		printf("yei el comando tiene el esquema apropiado \n");
		word = strtok(NULL, delim);
		printf(" word %s\n", word);
		printf(" string %s\n", string);
		/*conseguimos el numero de archivos */
		archivos = atoi(word);
		if(archivos <= 0){
			printf("comando incorrecto 2\n");
		} else{
			printf("%d\n", archivos);
			while(archivos >0){
				word = strtok(NULL, delim);
				printf(" word archivo %d %s\n",archivos, word);
				file = fopen(word, "r"); 
				if (file == NULL) { printf("error de apertura de archivo\n"); archivos = 0;}
				else{
					printf("pos si existe\n");
					while(fscanf(file, "%s", palabra1) == 1){
						printf("palabra: %s\n", palabra1);
						nodo = malloc(sizeof(node));
						nodo = delete_first(palabra1,lista);
						if(nodo == NULL){
							memcpy(nodo->word, palabra1, sizeof(palabra1));
							nodo->total= 1;
							nodo->next = NULL;
							printf("palabra nodo 1 %s \n", nodo->word);
							insert_first(nodo, lista);
							printf("%d\n",lista-> size);
							print_list(lista->first);
							sleep(1);
						}else{
							nodo-> total += 1;
							printf("palabra nodo 2 %s \n", nodo->word);
							insert_first(nodo, lista);
							printf("%d\n",lista-> size);
							print_list(lista->first);
							sleep(1);
						}
					}
					archivos -= 1;
				}
			}
		}

	} else{
		printf("comando incorrecto 1");
		exit(2);
	}
}