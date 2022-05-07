/*
Jean Martins
Lucas Paiva
Ulysses Ferreira
*/

#include "../includes/pipes.h"

int main() {
   int	descritor,
	pipe1[2] = {},
	pipe2[2] = {};

   if ((pipe(pipe1) < 0) || (pipe(pipe2) < 0)) {
	printf("Erro na chamada pipe!\n");
	exit(0);
   }

   if ((descritor = fork()) < 0) {
        printf("Erro na chamada fork!\n");
	exit(0);
   } else if (descritor > 0) {		
	close(pipe1[0]);
	close(pipe2[1]);


	client(pipe2[0], pipe1[1]);

	close(pipe1[1]);
	close(pipe2[0]);
	exit(0);		
   } else {			
	close(pipe1[1]);
	close(pipe2[0]);

	
	server(pipe1[0], pipe2[1]);

	close(pipe1[0]);
	close(pipe2[1]);
	exit(0);
   }				
   return(0);
}					

