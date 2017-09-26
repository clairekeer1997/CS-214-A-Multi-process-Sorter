#define BUF_SIZE 1025
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


Stypedef struct{
    char** row_token;
    char * row_text;
    size_t row_size;
    size_t num_col;
}row;


char** tokenizer(char* line){
    
    int i, j, k;
    i = 0;
    j = 0;
    k = 0;
    
    char** result = (char**)malloc(sizeof(char*) * strlen(line)); //return value;
    char* temp = (char*)malloc(500);//store each word;
    
    //go through each character;
    while(i < strlen(line)){
    
        //split by ',' or reach the end of line;
        if(line[i] == ',' || i == strlen(line) - 1){
    
            //if there is no character; (eg: ,,)
            if(!temp){
                temp[0] = '\0';
            }
            //store value to result;
            result[k] = (char*)malloc((j+1) * sizeof(char));
            strcpy(result[k], temp);
            memset(&temp[0], 0, sizeof(temp));
            j = 0;
            k++;
        }else{
            //copy value from line to temp;
            temp[j] = line[i];
            j++;
        }
        i++;
    }
    free(temp);
    return result;
}

int main (int argc, char* argv[]){
	/*start to declare variable*/
	FILE *fp;
	fp = stdin;

	row first_row;
	first_row.row_text = (char*) malloc (sizeof(char) * BUF_SIZE);
	row rest_row;
	rest_row.row_text = (char*) malloc (sizeof(char) * BUF_SIZE);


	char *token;
	size_t num_col = 1;
	/*end of declaring variable*/

	/*deal with the first row which contains all titles.*/

		/*split the first token*/
	fgets(first_row.row_text, BUF_SIZE-1, fp);

	first_row.row_size = strlen(first_row.row_text);
	first_row.row_token = (char**) malloc(sizeof(char *) * first_row.row_size);

	token = strtok(first_row.row_text, ",");
	first_row.row_token[0] = token;
	
	/*split the rest of token in the first row repeatedly*/
	while(token = strtok(NULL, ",")){
		//printf("%d token is: %s\n",num_col, token);//debug
		first_row.row_token[num_col++] = token;
		//printf("inside %d token is: %s\n",num_col, first_row.row_token[num_col - 1]);//debug
	}

	/*deal with the rest rows which contain all data.*/
	while(fgets(rest_row.row_text, BUF_SIZE-1, fp) != NULL){
		
		/*split the first token*/

		num_col = 1;//reset num of col to make sure element store in the right position

		rest_row.row_size = strlen(rest_row.row_text);
		rest_row.row_token = (char**) malloc(sizeof(char *) * rest_row.row_size);

		token = strtok(rest_row.row_text, ",");
		rest_row.row_token[0] = token;
		//printf("%d token is: %s\n",num_col, token);//debug
		
		/*split the rest of token repeatedly*/
		while(token = strtok(NULL, ",")){
			//printf("%d token is: %s\n",num_col, token);//debug
			rest_row.row_token[num_col++] = token;
			//printf("inside %d token is: %s\n",num_col, rest_row.row_token[num_col - 1]);//debug
		}
	}

	return 0；
	//printf("%d", first_line_size);
	//printf("%s", rest_row.row_token[0]);
}


