#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXBUFF		1024
#define MAXBUFF_SZ	"1023"

/* ---------------------------------------------------------------------------------------
Funcao Client:	Executa no processo PAI
		Envia o nome do arquivo para o FILHO
		Recebe os dados do FILHO e apresenta no terminal de texto
------------------------------------------------------------------------------------------ */
void client(int readfd, int writefd) {
    char buff[MAXBUFF] = {};
    int n = 0;
    
	printf("Arquivo? ");
	scanf("%s", buff);
	n = strlen(buff);
	write(writefd, buff, n);

    return;
}		

/* ---------------------------------------------------------------------------------------
Funcao Server:	Executa no processo FILHO
		Abre o arquivo solicitado e envia seu conteudo para o PAI
------------------------------------------------------------------------------------------ */
void server(int readfd, int writefd) {
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