#define BUF_SIZE 1025
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct{
    char** row_token;
    char * row_text;
    size_t row_size;
    size_t num_col;
}row;

/*char *self_strcat(char *str1, char *str2)
{

    int len1=strlen(str1),len2=strlen(str2);
    for(int i=strlen(str1);i<len1+len2;i++){
        str1[i]=str2[i-len1];
    }
    str1 [len1+len2]= '\0';
    return str1;
}*/
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
int main(int argc, char* argv[]) {

	FILE * fp;
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
    return 0;

}

