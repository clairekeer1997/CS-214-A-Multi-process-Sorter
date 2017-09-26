#define BUF_SIZE 1025
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

typedef struct{
	char **row;	
}row;

int main (int argc, char* argv[]){
	FILE *fp;
	fp = stdin;
	char *first_line;
	first_line = (char*) malloc (sizeof(char) * BUF_SIZE);
	char *rest_line;
	rest_line = (char*) malloc (sizeof(char) * BUF_SIZE);
	char *token;
	char ** first_line_token;
	char ** rest_line_token;
	size_t line_size;
	size_t num_col = 1;

	fgets(first_line, BUF_SIZE-1, fp);
	line_size = strlen(first_line);
	first_line_token = (char**) malloc(sizeof(char *) * line_size);
	token = strtok(first_line, ",");
	first_line_token[0] = token;
	
	while(token = strtok(NULL, ",")){
		//printf("%d token is: %s\n",num_col, token);
		first_line_token[num_col++] = token;
		//printf("inside %d token is: %s\n",num_col, first_line_token[num_col - 1]);
	}

	free(first_line);

	//fgets(rest_line, BUF_SIZE-1, fp);
	while(fgets(rest_line, BUF_SIZE-1, fp) != NULL){
		num_col = 1;
		line_size = strlen(rest_line);
		rest_line_token = (char**) malloc(sizeof(char *) * line_size);
		token = strtok(rest_line, ",");
		rest_line_token[0] = token;
		printf("%d token is: %s\n",num_col, token);
		
		while(token = strtok(NULL, ",")){
			printf("%d token is: %s\n",num_col, token);
			rest_line_token[num_col++] = token;
			printf("inside %d token is: %s\n",num_col, rest_line_token[num_col - 1]);
		}
	}

	//printf("%d", first_line_size);
	printf("%s", rest_line_token[0]);
}

