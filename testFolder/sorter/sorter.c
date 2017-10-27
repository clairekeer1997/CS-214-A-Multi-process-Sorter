//TODO list
/*
    *when target column doesnt exist?

    *Test compare, test negative numbers in compare

 
 
    * valgrind

    *free data
   
    change compare for strings
*/

#include "sorter.h"
int main(int argc, char** argv)
{   
    char *targetColumn = argv[2];
    int targetIndex = -1;
    int num_of_rows = 0;
    int num_of_cols = 0;      
    
    char *buffer = storeInBuffer(&num_of_rows);

    //printf("%s\n", buffer);
    //the first row should not count
    num_of_rows--;
    num_of_cols = countColumns(buffer, &targetIndex, targetColumn);
    
    //store in data structure
    ROW *data = storeAndOrganize(num_of_rows, num_of_cols, buffer);

    int index[num_of_rows];
    int i =0 ;
    for( i = 0; i < num_of_rows; ++i)
        index[i] = i;


      printf("hello\n");
    mergeSort(data,index,targetIndex,0,num_of_rows-1,num_of_rows,num_of_cols);  
    printf("hi\n");
  
    //printf("result:\n\n");
   // printIndex(index, num_of_rows);
   // print(data,30,num_of_cols,index);
    int  j, k;
    int comma;
  //  printf("%d\n", num_of_rows );

    

    for (i=0; i<num_of_rows; i++){
     
        for(j=0; j< num_of_cols; j++)
        {   
            comma = 0;
		if(data[index[i]][j] == NULL){
			continue;
		}
		else
		{
                for(k=0; k < strlen(data[index[i]][j]); k++)
                {
                    if(data[index[i]][j][k] == ',')
                    {
                        if(j == num_of_cols-1 && k == strlen(data[index[i]][j])){

                            printf("\"%s\"", data[index[i]][j]);

                        }
                       
                       else
                        { printf("\"%s\",", data[index[i]][j]);} 
                        comma = 1;
                   
                    }
		}
    
                }
        if(comma == 0)
        {
		if(data[index[i]][j] != NULL){
            		if(j == num_of_cols-1 && k == strlen(data[index[i]][j])){

                        	    printf("%s", data[index[i]][j]);
                       	 }
          	else  
         	 {
         	   	printf("%s,", data[index[i]][j]);
         	 }
        }
        
	
	else{
		if(j != num_of_cols -1){
			printf(",");
		}
    
        }
	}
	}
        printf("\r\n");
    
}
  //  printf("%s\n", data[index[0]][2]);
      
    return 0;
}


char* storeInBuffer(int *num_of_rows)
{
    int scalar = 1;
    size_t size = 257;
    char *result = malloc(sizeof(char)*scalar*size + 1);
    result[0] = '\0';    
    char *buffer = malloc(sizeof(char)*scalar*size + 1);
    buffer[0] = '\0';    

    while( fgets(buffer,scalar*size*sizeof(char) , stdin) )
    {        
        //When the last char in buffer is not '\n', it means the size of buffer is not large enough
        while(buffer[strlen(buffer)-1] != '\n')
        {
            //This pointer is used to free the memory when realloc fails
            char *current = buffer;
            scalar++;
            buffer = realloc(buffer, scalar*size*sizeof(char)+1);
            if(!buffer){
                perror("Failed to reallocate memory");
                free(current);
                exit(1);
            }
            char *lineBuffer = malloc(sizeof(char)*size+1);
			
			lineBuffer[0] = '\0';		
            fgets(lineBuffer, size, stdin);
            
            strcat(buffer, lineBuffer);
        }
        
        (*num_of_rows)++;
        result = realloc(result, strlen(result) + strlen(buffer) + 1);
        if(!result){
            perror("Failed to reallocate memory");
            free(result);
            exit(1);
        }
        strcat(result,buffer);
    }
    if(ferror(stdin)){
        free(result);
        perror("Error reading from stdin.\n");
        exit(1);
    }


    return result;
}


int countColumns(char *input, int *target, char *targetColumn)
{
    //printf("TargetColumnName: %s\n", targetColumn);
    char *temp = malloc(strlen(input) + 1);
    memcpy(temp, input, strlen(input));
    temp[strlen(input)] = '\0';
   
    int count = 1;  
    int size = sizeof(char)* strlen(input);
    char *firstLine = malloc(size + 1);
    firstLine[0] = '\0';
    firstLine = strtok(temp, "\n");
   
    while((firstLine = strchr(firstLine, ',')) != NULL) {       
        int size = strlen(temp) - strlen(firstLine);
        char *colName = subString(temp,0,size);
        colName = trim(colName);
       // printf("|%s|\n",colName);
        if(strcmp(colName, targetColumn) == 0 ) *target = count-1;       
        temp = subString(temp,size+1,strlen(temp));
        count++;
        firstLine++;
    }   
    if(strcmp(trim(temp), targetColumn) == 0 ) *target = count-1;   
    return count;
}

ROW* storeAndOrganize(int num_of_rows, int num_of_cols, char *buffer)
{
   // printf("In storeAndOrganize------------------------------------------\n");
    ROW *data = 0;
    size_t size = strlen(buffer);
    //char *ptr = buffer;
    //generate size
    data = malloc(sizeof(ROW)*num_of_rows);
    int i;
    for(i = 0; i < num_of_rows; ++i)
    {
        data[i] = malloc(sizeof(char*)*num_of_cols);
    }

    //get a line then tokenize
    char *line = malloc(size+1);
    int rowCount = 0;
    //get rid of first line
    line = getLineFromString(buffer);

    buffer = subString(buffer,strlen(line), strlen(buffer));
    line = getLineFromString(buffer);
    //printf("%s", line );
    //printf("total rows: %d\n", num_of_rows);
    while(rowCount < num_of_rows){        
      
        char *token = malloc(strlen(line) + 1);
        int colCount = 0;
        int lineSize = strlen(line);
        
        while(strlen(line) != 0)
        {
            token = tokenize(line);
            
            if(token == '\0'){
                line++;
            }else{
                line = (strlen(line) > strlen(token))? subString(line,strlen(token) + 1,strlen(line)) : "\0"; 
                token = trim(token);   
            }
            
            data[rowCount][colCount++] = token;
        }    

        rowCount++;    
        if(rowCount >= num_of_rows) break;
        buffer = subString(buffer,lineSize, strlen(buffer));
        line = getLineFromString(buffer);
        //printf("%s\n",  line );

    }

    //printf("out of storeAndOrganize------------------------------------------\n");
    
    return data;
}

char* getLineFromString(char *buffer)
{
    char *line = malloc(strlen(buffer)+1);

    int index = 0;
    while(buffer[index++] != '\n');

    line = subString(buffer, 0,index);
    line[index] = '\0';

    return line;
}

char *tokenize(char *line)
{
    char *result = 0;
    char *ptr = line;
    int count = 0;
    int index = 0;
    int quote_bool = 0;
    while( (ptr[index] != ',' || quote_bool == 1) && ptr[index] != '\0' ) {
        if(ptr[index] == '\"') quote_bool = !quote_bool;
        count++;
        index++;
    }

    result = (count == 0)? '\0' : subString(line,0,count);
    return result;
}




char *trim(char *str)
{

  //  printf("%s", str);
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)|| *str == '"') str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && (isspace((unsigned char)*end)|| *end == '"')) end--;



 *(end +1)=0;
return str;

 }
DataType checkType(char *str)
{
    if(str == '\0') return STRING;
    int dotCount = 0;
    int index = 0;
    while(str[index] != '\0')
    {
        if(str[index] == '+' || str[index] == '-'){
            if(index != 0){
               // printf("here1\n");
                return STRING;
            }else{
                index++;
                continue;
            }           
        } 
        if(str[index] == '.'){
            if(dotCount == 1 || str[index+1] == '\0'){
               // printf("here2\n");
                return STRING;
            }else{
                dotCount++;
            }            
        }else{
            if(isdigit(str[index]) == 0){
                //printf("here3\n");
                return STRING;
            }   
        }
       
        index++;
    }
    return NUMERIC;
}

int compare(char *data1, char *data2, DataType type)
{
   // printf("In compare--------------------------\n");

    if(strcmp(data1, "\0") == 0 && strcmp(data2, "\0") == 0) {
        
        return 0;
    }
    if(strcmp(data1, "\0") == 0 && strcmp(data2, "\0") != 0) {
      // printf("here1?\n");
        return -1;
    }
    if(strcmp(data1, "\0") != 0 && strcmp(data2, "\0") == 0) {
      //  printf("here2?\n");        
        return 1;
    }
    float num1, num2;  
    switch(type)
    {
        case STRING:
        //printf("STRING!\n");
            return strcasecmp(data1, data2);
            break;
        case NUMERIC:
        //printf("NUMERIC!\n");
        
            num1 = atof(data1);
            num2 = atof(data2);
        
            if(num1-num2 == 0) return 0;
            if(num1-num2 < 0) return -1;
            if(num1-num2 > 0) return 1;           
            
            break;
        default:
            perror("Cannot resolve type.");
            break;
    }
    //printf("Out of compare--------------------------\n");
    return 0;
}

void freeMemory(ROW *data, char *buffer)
{
    free(buffer);
    //for(){}
}
