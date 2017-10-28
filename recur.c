#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

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
void directory(char* path, pid_t* arr, int i){
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
           // printf("I'm directory %s\n", dir_ptr->d_name);
            pid = fork();
            
            if(pid == 0){
                directory(temppath, arr, i);
                exit(1);
            }else if(pid > 0){
                arr[i] = pid;
                i++;
            }
        }
        else{
            char *name = dir_ptr->d_name;
            int length = strlen(name);
            if(name[length - 3] == 'c' &&
            name[length - 2] == 's' &&
            name[length - 1] == 'v'){
               pid = fork();
                if(pid > 0){
                    arr[i] = pid;
                    i++;
                    printf(" my pid is: %d, my ppid is %d\n" , getpid(), getppid());
 							fflush(stdout);               
                }
                else if(pid == 0){
                    printf("I'm a csv. %s\n", dir_ptr->d_name);
                    fflush(stdout);
                    exit(1);
                }
             //   printf("current temppath: %s\n", temppath); 
            }
        }
        
    }
   // printf("process %d terminates %d\n", getpid());

   
}

int main(int argc, char* argv[]){
    char* path= argv[1];
    FILE *file;
    printf("first path: %s\n", path);
    pid_t* arr = (pid_t*)malloc(300 * sizeof(pid_t));
    int i = 0;
     directory(path,arr, i);
    i = 0;
    int status;
    while(i < 10){
        printf("%d \n", arr[i]);
        i++;
        waitpid(arr[i], &status, 0);
    }
    fflush(stdout);
   /* if(file){
        printf("success!");
    }*/
    return 0;
}
