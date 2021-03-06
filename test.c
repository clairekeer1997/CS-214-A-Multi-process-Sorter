#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#define BUF_SIZE 1025

int isDirectory(char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
 }
char* path_contact(const char* str1,const char* str2){ 
    char* result;  
    result=(char*)malloc(strlen(str1)+strlen(str2)+ 1);
    if(!result){
        printf("fail to allocate memory space\n");  
        exit(1);  
    }  
    strcpy(result,str1);  
    strcat(result,str2);  
    return result;  
}  

void directory(char* path){
    DIR *dir_p;
    struct dirent *dir_ptr;
    dir_p = opendir(path);
  //  printf("original path: %s\n", path);
    path = path_contact(path, "/");
    FILE *result;
    pid_t pid;
    int status;

    while((dir_ptr = readdir(dir_p)) != NULL){
        //printf("process %d enters %s\n", getpid(), dir_ptr->d_name);
        char* temppath;
        temppath = path_contact(path, dir_ptr->d_name);
        struct stat st;
        stat(temppath, &st);
       // printf("current temppath: %s\n", temppath);   

        /*skip . and .. maybe hide folders to avoid dead loop*/
        if(strcmp(dir_ptr->d_name, ".") == 0 ||
           strcmp(dir_ptr->d_name, "..") == 0){
           // printf("file %s skip here\n", dir_ptr->d_name);
            continue;
        }

        if(isDirectory(temppath)){
            printf("I'm directory %s\n", dir_ptr->d_name);
            pid = fork();
            if(pid == 0){
                directory(temppath);
                exit(1);
            }
        }
        else{
            char *name = dir_ptr->d_name;
            int length = strlen(name);
            if(name[length - 3] == 'c' &&
            name[length - 2] == 's' &&
            name[length - 1] == 'v'){
                printf("I'm a csv. %s\n", dir_ptr->d_name);
                printf(" my pid is: %d, my ppid is %d\n" , getpid(), getppid());
                printf("current temppath: %s\n", temppath); 
                
            }
        }
        
    }
    waitpid(pid, &status, 0);
   // printf("process %d terminates %d\n", getpid());
    
   
}

int main(int argc, char* argv[]){
    char* path= argv[1];
    FILE *fp;
    FILE *fp2;
    fp = fopen(path, "r");
    fp2 = fopen(path, "r");
    char* text = (char*)malloc(1000);
    fgets(text, BUF_SIZE-1, fp2);
    printf("---%s\n", text);
    fgets(text, BUF_SIZE-1, fp);
    printf("%s\n", text);
    fgets(text, BUF_SIZE-1, fp2);
    printf("---%s\n", text);
    return 0;
}
