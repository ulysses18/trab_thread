/* Source: chat_pobre.c
   Compilar: clang -Wall -static chat_pobre.c -o chat
             gcc -Wall -static chat_pobre.c -o chat
             -Wall (todas as advertencias de compilacao)
   Hearders: man pipe (SYNOPSIS: #include <unistd.h>)
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

