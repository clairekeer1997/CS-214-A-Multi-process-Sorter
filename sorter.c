#include "Sorter.h"



char *trim(char *word, int index)
{
  char *end;
  while(isspace((unsigned char)*word)){
	word++;
  }
  if(*word == 0)
    return word;
  end = word + index;
  while(end > word && isspace((unsigned char)*end)) {
	  end--;
  }
  *(end+1) = 0;
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
			temp = trim(temp, j - 1);
			strcpy(result[k], temp);
			memset(&temp[0], 0, strlen(temp));
			start_quote = FALSE;
			j = 0;
			k++;
			i++;
		}

		//split by ',' or reach the end of line;
        else if((line[i] == ',' || i == strlen(line) - 1) && start_quote != TRUE){
            //if there is no character; (eg: ,,)
            if(!temp){
                temp[0] = '\0';
			}
			if(i == strlen(line) - 1 && line[i] != '\n' && line[i] != ','){
				temp[j] = line[i];
				j++;
			}
            //store value to result;
			result[k] = (char*)malloc((j+1) * sizeof(char));
			temp = trim(temp, j - 1);			
			strcpy(result[k], temp);
			memset(&temp[0], 0, strlen(temp));			
            j = 0;
			k++;
			//if the last character is ',';
			if(line[i] == ',' && i == strlen(line) - 1){
				temp[0] = '\0';
				result[k] = (char*)malloc((j+1) * sizeof(char));
				strcpy(result[k], temp);
				memset(&temp[0], 0, strlen(temp));								
			}

        }else{
			//copy character from line to temp;
			if(j == 0){
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
	free(temp);
    return result;
}

int tok_file(FILE *fp, row* data, int num_col){
	row rest_row;
	rest_row.row_text = (char*) malloc (sizeof(char) * BUF_SIZE);
	size_t curr_col = 0;
	size_t curr_row = 0; //current row number in row* data
	int i;//loop virable
	/*end of declaring variable*/
	
	/*deal with data*/
	i = 0;
	while(fgets(rest_row.row_text, BUF_SIZE-1, fp) != NULL){
		rest_row.row_len = strlen(rest_row.row_text);
		rest_row.row_token = (char**) malloc(sizeof(char *) * (num_col+1));
		rest_row.row_token = tokenizer(rest_row.row_text, num_col);
		data[curr_row++] = rest_row;		
	}
	return curr_row;
}
void sort(char* filename, char* colname, char* odirname){
		/*declare variable*/
		FILE *fp;
		fp = fopen(filename,"r");
		
		//first row:
		row first_row;
		row *data;
		char *token;
		char* target;
		size_t num_col = 1;
		int length;
		int i;	
		int j;
		int k;
		int num_row; 
		int target_col;
	
		/*split the 1st token by ','*/
		first_row.row_text = (char*) malloc (sizeof(char) * BUF_SIZE);		
		fgets(first_row.row_text, BUF_SIZE-1, fp);
		first_row.row_len = strlen(first_row.row_text);
		first_row.row_token = (char**) malloc(sizeof(char *) * first_row.row_len);
		token = strtok(first_row.row_text, ",");
		first_row.row_token[0] = token;
	
		//split the rest of token in the first row
		while(token = strtok(NULL, ",")){
			first_row.row_token[num_col++] = token;	
		}
		first_row.num_col = num_col;
	
		
		//delete the '\n' in the last word;
		
		length = strlen(first_row.row_token[num_col - 1]);
		if(first_row.row_token[num_col - 1][length - 1] == '\n'){
			first_row.row_token[num_col - 1][length - 2] = '\0';
		}
		
		//trim blank space;
		i = 0;
		while(i < num_col){
			first_row.row_token[i] = trim(first_row.row_token[i], strlen(first_row.row_token[i]) - 1);
			i++;
		}
		
		//deal with rest rows;
		data = (row*) malloc (sizeof(row) * 10000);
		num_row = tok_file(fp, data, num_col);
		
		target = colname;
		
		//find the target column number;
		target_col = 0;
		
		while(target_col < first_row.num_col){
			if(strcmp(first_row.row_token[target_col], target) == 0){
				break;
			}
			target_col++;
		}
	
		//no such title in the first row
		if(target_col == first_row.num_col){
			printf("Wrong input, no such title.\n");
			exit(1);
		}
	
		mergeSort(data, target_col, num_row);

		char* output_filename = filename;
		char* c1 = "-sorted-";
		char* c2 = ".csv";
		strcat(output_filename, c1);
		strcat(output_filename, colname);
		strcat(output_filename, c2);

		FILE* outfptr = fopen(output_filename, "w");
		i = 0;
		//print the first row:
		while(i < num_col){
			fprintf(outfptr, "%s",first_row.row_token[i]);
			if(i != num_col - 1){
				fprintf(outfptr, ",");
			}else{
				fprintf(outfptr, "\n");
			}
			i++;
		}
	
		//print the rest row;
		i = 0;
		j = 0;
		next:
		while(i < num_row){
			while(j < num_col){
				//if(data[i].comma){
					for(k = 0; k < strlen(data[i].row_token[j]); k++){
						if(data[i].row_token[j][k] == ',' && j != num_col - 1){
							fprintf(outfptr, "\"%s\",", data[i].row_token[j]);
							j++;
							break;
						}
						if(data[i].row_token[j][k] == ',' && j == num_col - 1){ 
							fprintf(outfptr, "\"%s\"", data[i].row_token[j]);
							i++;
							j = 0;
							goto next;
						}
					}
				//}
	
				fprintf(outfptr, "%s",data[i].row_token[j]);
				if(j != num_col - 1){
					fprintf(outfptr, ",");
				}else{ 
					fprintf(outfptr, "\n");
				}
				j++;
			}
			i++;
			j = 0;
		}

}
int main (int argc, char* argv[]){

	//declare variables;
	char* colname;
	char* dirname;
	char* odirname;

	//check the flags;
	if(strcmp(argv[1], "-c") != 0 || strcmp(argv[3], "-d") != 0 || strcmp(argv[5], "-o") != 0){ //|| argv[3] != "-d" || argv[5] != "-o"
		printf("Wrong input.");
		exit(0);
	}

	//get the input;
	if(argv[2]){
		colname = argv[2];
		if(argv[4]){
			dirname = argv[4];
		}
	}else{
		printf("Wrong input.");
		exit(0);
	}
	if(argv[6]){
		odirname = argv[6];
	}

	sort(dirname, colname, odirname);

	
	return 0;
}