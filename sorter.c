#include "Sorter.h"


char* path_contact(const char* str1,const char* str2){ 
    char* result;  
    result=(char*)malloc(strlen(str1)+strlen(str2)+ 3);
    if(!result){
        printf("fail to allocate memory space\n");  
        exit(1);  
    }  

	strcpy(result,str1);  
	strcat(result,"/");
	strcat(result,str2);  
    return result;  
}  

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
void sort(char* filename, char* colname, char* odirname, char* tmppath){
		/*declare variable*/
		FILE *fp;
		fp = fopen(tmppath,"r");
		
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
		if(target_col == (first_row.num_col)){
            printf("Wrong input, no such title.\n");
			exit(1);
		}
	
		mergeSort(data, target_col, num_row);

		/*cut .csv from original file name*/
		char* ptr_end = filename + (strlen(filename) - 4);
		*ptr_end = 0;


		char* output_filename = (char*) malloc(strlen(filename) + strlen(colname) + 13);
		char* output_path;
		char* c1 = "-sorted-";
		char* c2 = ".csv";
		strcpy(output_filename, filename);
		strcat(output_filename, c1);
		strcat(output_filename, colname);
		strcat(output_filename, c2);

		output_path = path_contact(odirname, output_filename);
		
		FILE* outfptr = fopen(output_path, "w");
		if(outfptr == NULL){
			printf("wrong");
			exit(1);		
		}

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

int isDirectory(char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
 }

int checkcsv(char* path, char* colname){
	FILE *fptr;
	fptr = fopen(path, "r");

	//get the first line of this file;
	char* text = (char*)malloc(500);
	fgets(text, BUF_SIZE-1, fptr);
	
	char* token = malloc(50);
	char** row_token = (char**) malloc(sizeof(char *) * (strlen(text)));
	
	token = strtok(text, ",");
	row_token[0] = token;

	int num_col = 1;
	while(token = strtok(NULL, ",")){
		row_token[num_col++] = token;	
	}

	//find the target column;
	int target_col = 0;
	while(target_col < num_col){
		if(strcmp(row_token[target_col], colname) == 0){
			break;
		}
		target_col++;
	}

	//no such title, not the target csv file;
	if(target_col == num_col){
		return 0;
	}
	return 1; 
	
}
void directory(char* path, char* colname, char* odirname){
    DIR *dir_p;
    struct dirent *dir_ptr;
    dir_p = opendir(path);
    FILE *result;
    pid_t pid;
//dir_ptr = readdir(dir_p);
    if(dir_p == NULL){
        printf("Wrong Path\n");
        exit(1);
    }
    while((dir_ptr = readdir(dir_p)) != NULL){
        char* temppath;
        temppath = path_contact(path, dir_ptr->d_name);
        struct stat st;
        stat(temppath, &st);
        if(strcmp(dir_ptr->d_name, ".") == 0 ||
           strcmp(dir_ptr->d_name, "..") == 0){
            continue;
        }
        
        if(isDirectory(temppath)){
            pid = fork();
            if(pid == 0){
                directory(temppath, colname, odirname);
                exit(1);
            }else if(pid > 0){
                printf("%d\n", pid);
            }
        }
        else{
            char *name = dir_ptr->d_name;
            int length = strlen(name);
            if(name[length - 3] == 'c' &&
            name[length - 2] == 's' &&
            name[length - 1] == 'v'){
				if(checkcsv(temppath, colname)){
					pid = fork();
					if(pid > 0){
						printf("%d\n",pid);     
					}
					else if(pid == 0){
						sort(name, colname, odirname, temppath);
						exit(0);
					}
				}   	
            }
        }
        
    }
    pid_t waitid;
    while ((waitid = wait(NULL)) > 0){        
        // exit when -1 all children done;
    }
}
int main (int argc, char* argv[]){

	//declare variables;
	char* colname;
	char* dirname;
	char* odirname;

	//check the flag;
	if(strcmp(argv[1], "-c") != 0){
		printf("Wrong input.");
		exit(0);
	}

	//get the input;
	if(argv[2]){
		colname = argv[2];
	}else{
		printf("Wrong input.");
		exit(0);
	}
	if(strcmp(argv[1], "-d") && argv[4]){
		dirname = argv[4];
	}
	if(strcmp(argv[1], "-o") && argv[6]){
		odirname = argv[6];
	}

	printf("Initial PID: %d\nPIDS of all child processes: \n", getpid());
	
	directory(dirname, colname, odirname);
	printf("Total Number of processes: \n");
	return 0;
}
