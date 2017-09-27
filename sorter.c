#define BUF_SIZE 1025
#define TRUE 1
#define FALSE 0
#include "Sorter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*typedef struct{
    char** row_token;
    char * row_text;
    size_t row_size;
    size_t num_col;
}row;*/
char* trim(char* word, int index){
	while(index >= 0){
		if(word[index]){
			break;
		}
		index--;
	}
	word[index+1] = '\0';
	return word;
}

char** tokenizer(char* line, size_t num_col){
    
    int i, j, k;
    i = 0;//current position in line;
    j = 0;//current position in tmp;
    k = 0;//current position in result;
    
    char** result = (char**)malloc(sizeof(char*) * (num_col + 1)); //return value;
    char* temp = (char*)malloc(500);//store each word;
	size_t start_quote = FALSE;//1 quote start, 0 quote end;
	
    //go through each character;
    while(i < strlen(line)){
		
		/*reach the start '"' */
		if(line[i] == '"' && start_quote == FALSE){
			start_quote = TRUE;
		}
		
		
		else if(line[i] == '"' && start_quote == TRUE){
			//store value in result
			result[k] = (char*) malloc((j + 1) * sizeof(char));
			temp = trim(temp, j);
			strcpy(result[k], temp);
			memset(&temp[0], 0, strlen(temp));
			j = 0;
			k++;
			i++;
		}

        //split by ',' or reach the end of line;
        else if((line[i] == ',' || i == strlen(line) - 1 ) && start_quote != TRUE){
    
            //if there is no character; (eg: ,,)
            if(!temp){
                temp[0] = '\0';
			}
			
            //store value to result;
			result[k] = (char*)malloc((j+1) * sizeof(char));
			temp = trim(temp, j);			
            strcpy(result[k], temp);
            j = 0;
            k++;
        }else{
			//copy character from line to temp;
			if(j == 0){
				memset(&temp[0], 0, strlen(temp));
				if(line[i] == ' '){
					i++;
					continue;
				}				
			}
			
            temp[j] = line[i];
			j++;
		}
        i++;
	}
	i = 0;
	while(i < num_col){
		
		printf("%s ", result[i]);
		i++;
	}
	printf("\n");
	free(temp);
    return result;
}

int main (int argc, char* argv[]){
	/*declare variable*/
	FILE *fp;
	fp = stdin;

	row first_row;
	first_row.row_text = (char*) malloc (sizeof(char) * BUF_SIZE);
	row rest_row;
	rest_row.row_text = (char*) malloc (sizeof(char) * BUF_SIZE);
	row *data;
	data = (row*) malloc (sizeof(row) * 10000);
	char *token;
	size_t num_col = 1;
	size_t curr_col = 0;
	size_t curr_row = 0; //current row number in row* data
	/*end of declaring variable*/

	/*deal with all titles.*/

	/*split the 1st token by ','*/
	fgets(first_row.row_text, BUF_SIZE-1, fp);

	first_row.row_len = strlen(first_row.row_text);
	first_row.row_token = (char**) malloc(sizeof(char *) * first_row.row_len);

	token = strtok(first_row.row_text, ",");
	first_row.row_token[0] = token;
	
	//split the rest of token in the first row
	while(token = strtok(NULL, ",")){
		first_row.row_token[num_col++] = token;	
	}
	data[curr_row++] = first_row;//stroe first row into the final data

	/*deal with data*/
	while(fgets(rest_row.row_text, BUF_SIZE-1, fp) != NULL){
		rest_row.row_len = strlen(rest_row.row_text);
		rest_row.row_token = (char**) malloc(sizeof(char *) * (num_col+1));
		rest_row.row_token = tokenizer(rest_row.row_text, num_col);
		data[curr_row++] = rest_row;		
	}
	return 0;
}



	/*while(fgets(rest_row.row_text, BUF_SIZE-1, fp) != NULL){
		
		//split the first token by ","

		curr_col = 1;//reset num of col to make sure element store in the right position

		rest_row.row_token = (char**) malloc(sizeof(char *) * num_col);

		token = strtok(rest_row.row_text, ",");
		rest_row.row_token[0] = token;
		
		/*split the rest of token
		while(token = strtok(NULL, ",")){

			rest_row.row_token[curr_col++] = token;

		}

		data[curr_row++] = rest_row;
		printf("%s", data[curr_row - 1].row_token[1]);
		
	}*/