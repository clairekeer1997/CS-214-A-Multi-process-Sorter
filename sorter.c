#define BUF_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

typedef struct{
	char **row;	
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

int main(int argc, char* argv[]) {

	FILE * fp;
	fp = stdin;
	char * buffer;
	buffer = (char*) malloc(sizeof(char) * BUF_SIZE);
	*buffer = '\0';
	char* tmp_buffer;
	tmp_buffer = (char*) malloc(sizeof(char) * BUF_SIZE);
	*tmp_buffer = '\0';
	size_t count = 0;


	if(fp == NULL){
		printf("invalid input file");
		exit(1);
	}
		
	int i = 0;

	/*load the whole file into char* buffer*/
	while(!feof(fp)){
		//fread(tmp_buffer, BUF_SIZE-1, 1, fp);
		if(fread(tmp_buffer, BUF_SIZE-1, 1, fp)	== 0){
			printf("no buffer");
			exit(1);
		}
		printf("%s", tmp_buffer);
		strcat(buffer, tmp_buffer);
		//printf("%s", buffer);
		printf("debug");
		realloc(buffer, sizeof(buffer) + BUF_SIZE);
	}

	printf("%s", buffer);
	free(buffer);
	fclose(fp);
	return 0;
}