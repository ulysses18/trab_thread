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

#define MAXBUFF		1024	// numero de caracteres do buffer
#define MAXBUFF_SZ	"1023"

void client(int, int);
void server(int, int);

int main() {
   int	descritor,		// usado para criar o processo filho pelo fork()
	pipe1[2] = {},		// comunicacao pai -> filho
	pipe2[2] = {};		// comunicacao filho -> pai

   if ((pipe(pipe1) < 0) || (pipe(pipe2) < 0)) {
	printf("Erro na chamada pipe!\n");
	exit(0);
   }

   // Fork para criar o processo filho
   if ((descritor = fork()) < 0) {
        printf("Erro na chamada fork!\n");
	exit(0);
   } else if (descritor > 0) {		// Processo PAI
	close(pipe1[0]);		// fecha leitura no pipe1
	close(pipe2[1]);		// fecha escrita no pipe2

	// Chama CLIENTE no PAI
	client(pipe2[0], pipe1[1]);

	close(pipe1[1]);		// fecha pipe1
	close(pipe2[0]);		// fecha pipe2
	exit(0);			// Fim do Processo PAI
   } else {				// Processo FILHO
	close(pipe1[1]);		// fecha escrita no pipe1
	close(pipe2[0]);		// fecha leitura no pipe2

	// Chama SERVIDOR no FILHO
	server(pipe1[0], pipe2[1]);

	close(pipe1[0]);		// fecha leitura no pipe1
	close(pipe2[1]);		// fecha escrita no pipe2
	exit(0);
   }					// Fim do Processo FILHO
   return(0);
}					// Fim do MAIN

/* ---------------------------------------------------------------------------------------
Funcao Client:	Executa no processo PAI
		Envia o nome do arquivo para o FILHO
		Recebe os dados do FILHO e apresenta no terminal de texto
------------------------------------------------------------------------------------------ */
void client(int readfd, int writefd) {	// leitura do pipe2[0] e escrita no pipe1[1]
    char buff[MAXBUFF] = {};
    int n = 0;
    
	printf("Arquivo? ");
	scanf("%s", buff);
	n = strlen(buff);
	write(writefd, buff, n);

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