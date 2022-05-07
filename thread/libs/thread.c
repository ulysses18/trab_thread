#include <stdio.h>

void get_file_name(char *file_name[100]) {
    printf("Arquivo? ");
    scanf("%s", file_name);
}

void read_file(char *file_name[100]) {
	FILE *arq;
    int n = 0;
	char c;

	arq = fopen(file_name, "r");
	do
	{
		c = fgetc(arq);
		
		printf("%c" , c);    
    
	}while (c != EOF);
}