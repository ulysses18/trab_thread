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

#define MAXBUFF		1024	// numero de caracteres do buffer
#define MAXBUFF_SZ	"1023"

typedef struct canos {
    int pipe1[2];
    int pipe2[2];
} canos;

// void client(canos);
// void server(int, int);

void client(canos *cano) {	// leitura do pipe2[0] e escrita no pipe1[1]
    char buff[MAXBUFF] = {};
    int n = 0;
    
	printf("Arquivo? ");
	scanf("%s", buff);
	n = strlen(buff);
	write(cano->pipe2, buff, n);

    return;
}		// Fim da funcao client

/* ---------------------------------------------------------------------------------------
Funcao Server:	Executa no processo FILHO
		Abre o arquivo solicitado e envia seu conteudo para o PAI
------------------------------------------------------------------------------------------ */
void server(int readfd, int writefd) {	// leitura do pipe1[0] e escrita no pipe2[1]
    char buff[MAXBUFF] = {};
	FILE *arq;
    int n = 0;
	char c;

	read(readfd, buff, MAXBUFF);
	arq = fopen(buff, "r");
	do
	{
		c = fgetc(arq);
		
		printf("%c" , c);    
    
	}while (c != EOF);
	
    return;
}

int main() {
   int	descritor;		// usado para criar o processo filho pelo fork()
	// pipe1[2] = {},		// comunicacao pai -> filho
	// pipe2[2] = {};		// comunicacao filho -> pai
    
    pthread_t thread1, thread2;
    canos claudio;

   if ((pipe(claudio.pipe1) < 0) || (pipe(claudio.pipe2) < 0)) {
	printf("Erro na chamada pipe!\n");
	exit(0);
   }

   // Fork para criar o processo filho
   descritor = pthread_create(&thread1, NULL, client, &claudio);
   if(descritor != 0) {
        printf("Erro na chamada fork!\n");
	exit(0);
   } else if (descritor > 0) {		// Processo PAI
	close(claudio.pipe1[0]);		// fecha leitura no pipe1
	close(claudio.pipe2[1]);		// fecha escrita no pipe2

	// Chama CLIENTE no PAI
	// client(pipe2[0], pipe1[1]);

	close(claudio.pipe1[1]);		// fecha pipe1
	close(claudio.pipe2[0]);		// fecha pipe2
	exit(0);			// Fim do Processo PAI
   } else {				// Processo FILHO
	close(claudio.pipe1[1]);		// fecha escrita no pipe1
	close(claudio.pipe2[0]);		// fecha leitura no pipe2

	// Chama SERVIDOR no FILHO
	server(claudio.pipe1[0], claudio.pipe2[1]);

	close(claudio.pipe1[0]);		// fecha leitura no pipe1
	close(claudio.pipe2[1]);		// fecha escrita no pipe2
	exit(0);
   }					// Fim do Processo FILHO
   return(0);
}					// Fim do MAIN

/* ---------------------------------------------------------------------------------------
Funcao Client:	Executa no processo PAI
		Envia o nome do arquivo para o FILHO
		Recebe os dados do FILHO e apresenta no terminal de texto
------------------------------------------------------------------------------------------ */
