/*
Jean Martins
Lucas Paiva
Ulysses Ferreira
*/
#include <stdio.h>
#include <pthread.h>
#include "../includes/thread.h"

int main(void) {
    char nome_arquivo[100] = "";
    pthread_t thread1, thread2;

    puts("\n");
    pthread_create(&thread1, NULL, (void *)get_file_name, (char *)&nome_arquivo);
    pthread_join(thread1, NULL);
    pthread_create(&thread2, NULL, (void *)read_file, (char *)&nome_arquivo);
    pthread_join(thread2, NULL);
    puts("\n");
    return(0);
}

