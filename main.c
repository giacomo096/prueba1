#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <semaphore.h>
#include "main.h"
#include <dirent.h>



sem_t sem1;
sem_t sem2;
int ocupados[];
char* directorios[];
sem_t semaforos[];
int hilos;


int main(int argc, char *argv[]){
	char *string = malloc(256);
	char delim[] = " ";
	int i = 0;

	printf("argc %d \n", argc);
	if(argc != 3){
		printf("numero erroneo de argumentos de entrada \n");
		return -1;
	}else{
		if(strcmp(argv[0], "./frecpalhilo" ) != 0){
			printf("comando desconocido \n");
			return -2;
		}else{
			if(atoi(argv[1]) < 0){
				printf("numero de hilos no puede ser negativo \n");
				return -3;
			}
		}
	}
	hilos = atoi(argv[1]);
	pthread_t arrayhilos[hilos];
	sem_t semaforos[hilos];
	char* directorios[hilos];
	int ocupados[hilos];
	printf("%d \n", hilos);
	printf("%s\n %s\n %s\n",argv[0],argv[1],argv[2]);
	sem_init(&sem1, 0,0);
	sem_init(&sem2, 0,hilos);
	while(i < hilos){
		sem_init(&semaforos[i], 0,0);
		i++;
	}

	i = 0;

	while(i < hilos){
		ocupados[i]= 0;
		i++;
	}
	i = 0;

	while(i< hilos){
		pthread_create(&arrayhilos[i] ,NULL ,funcion, &i);
		sem_wait(&sem1);
		i++;
	}

	abrirdir(argv[2]);

	i= 0;
	while(i < hilos){
		pthread_join(arrayhilos[i], NULL);
		i++;
	}


	return 1;
}

void *funcion(void * i){
	int identificador = *((int*)i);
	sem_post(&sem1);
	printf("Hola, soy el hilo %d \n", identificador);
	sem_wait(&semaforos[identificador]);
	sem_post(&sem2);
	ocupados[identificador] = 1;
	printf("%s \n", directorios[identificador]);
	ocupados[identificador] = 0;

}

void abrirdir(char* name){
	struct stat estru;
 	struct dirent *dt;
	DIR* directorio; 
	printf("abriendo el directorio %s\n",name);
	directorio = opendir(name);
	while((dt = readdir(directorio))!=NULL){
		if((strcmp(dt->d_name,".")!=0)&&(strcmp(dt->d_name,"..")!=0)){
 			stat(dt->d_name,&estru);
 			if(S_ISDIR(estru.st_mode)){
 				int j =0;
 				sem_wait(&sem2);
 				while((ocupados[j] == 1) && (j<hilos)){
 					j++;
 				}
 				directorios[j] = malloc(256);
 				strcpy(directorios[j],"aqui va el nombre del dir");
 				sem_post(&semaforos[j]);
 				abrirdir(dt->d_name);
 			}
 		}
 	}
 	closedir(directorio);
}

