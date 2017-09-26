#define BUF_SIZE 1025
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>


typedef struct{
    char** row_token;
    char * row_text;
    size_t row_size;
    size_t num_col;
}row;

int main (int argc, char* argv[]){
	/*start declare variable*/
	FILE *fp;
	fp = stdin;

	row first_row;
	first_row.row_text = (char*) malloc (sizeof(char) * BUF_SIZE);
	row rest_row;
	rest_row.row_text = (char*) malloc (sizeof(char) * BUF_SIZE);


	char *token;
	size_t num_col = 1;
	/*end of declare variable*/

	/*deal with the first row which contains all titles.*/
	fgets(first_row.row_text, BUF_SIZE-1, fp);
	first_row.row_size = strlen(first_row.row_text);
	first_row.row_token = (char**) malloc(sizeof(char *) * first_row.row_size);
	token = strtok(first_row.row_text, ",");
	first_row.row_token[0] = token;
	
	while(token = strtok(NULL, ",")){
		//printf("%d token is: %s\n",num_col, token);//debug
		first_row.row_token[num_col++] = token;
		//printf("inside %d token is: %s\n",num_col, first_row.row_token[num_col - 1]);//debug
	}

	/*deal with the rest rows which contain all data.*/
	while(fgets(rest_row.row_text, BUF_SIZE-1, fp) != NULL){
		num_col = 1;
		rest_row.row_size = strlen(rest_row.row_text);
		rest_row.row_token = (char**) malloc(sizeof(char *) * rest_row.row_size);
		token = strtok(rest_row.row_text, ",");
		rest_row.row_token[0] = token;
		printf("%d token is: %s\n",num_col, token);
		
		while(token = strtok(NULL, ",")){
			//printf("%d token is: %s\n",num_col, token);//debug
			rest_row.row_token[num_col++] = token;
			//printf("inside %d token is: %s\n",num_col, rest_row.row_token[num_col - 1]);//debug
		}
	}

	//printf("%d", first_line_size);
	//printf("%s", rest_row.row_token[0]);
}

