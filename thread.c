/* Source: chat_pobre.c
   Compilar: clang -Wall -static chat_pobre.c -o chat
             gcc -Wall -static chat_pobre.c -o chat
             -Wall (todas as advertencias de compilacao)
   Hearders: man pipe (SYNOPSIS: #include <unistd.h>)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#define MAXBUFF		1024	
#define MAXBUFF_SZ	"1023"

typedef struct canos {
    int pipe1[2];
    int pipe2[2];
} canos;

void *client(void *tubo);
void *server(void *tubo);

int main() {
	
    pthread_t thread1, thread2;
    canos pipe_str;

	if ((pipe(pipe_str.pipe1) < 0) || (pipe(pipe_str.pipe2) < 0)) {
		printf("Erro na chamada pipe!\n");
		exit(0);
	}
   
	pthread_create(&thread1, NULL, client, &pipe_str);
	pthread_create(&thread2, NULL, server, &pipe_str);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
   				
	return(0);
}					
void *client(void *tubo) {	
	//printf("\nfuncao client");
	canos *cano = (canos*) tubo;
    char buff[MAXBUFF] = {""};
	char c[2] = {};
	char d;
    int n = 0;

	printf("Arquivo? ");
	scanf("%s", buff);
	n = strlen(buff);
	//printf("\n>>%s *\n", buff);
	write(cano->pipe1[1], buff, n);
	
	do{
		read(cano->pipe2[0], c, 2);
		
		if(c[1] != 1){
			printf("%c", c[0]);
		}
	}while (c[1] != 1);
	printf("\n");
}		

void *server(void *tubo) {	
	//printf("\nfuncao server\n\n");
    char buff[MAXBUFF] = {};
	FILE *arq;
	canos *cano = (canos*) tubo;

	read(cano->pipe1[0], buff, MAXBUFF);
	//printf("\n\n>>%s", buff);
	arq = fopen(buff, "r");

	char c[2] = {""};
	do
	{
		c[0] = fgetc(arq);
		if(c[0] != EOF){
			c[1] = 0;
		}else{
			c[1] = 1;
		}
		write(cano->pipe2[1], c, 2);
	}while (c[0] != EOF);
}
