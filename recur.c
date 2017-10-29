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
void directory(char* path){
    DIR *dir_p;
    struct dirent *dir_ptr;
    dir_p = opendir(path);
    path = path_contact(path, "/");
    FILE *result;
    pid_t pid;

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
                directory(temppath);
                exit(1);
            }else if(pid > 0){
                printf("pid: %d\n", pid);
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
                    printf("pid: %d\n", pid);     
                }
                else if(pid == 0){
                    exit(1);
                }
            }
        }
        
    }
    pid_t waitid;
    while ((waitid = wait(NULL)) > 0){        
        // exit when -1 all children done;
    }
}

int main(int argc, char* argv[]){
    char* path= argv[1];
    FILE *file;
    printf("first path: %s\n", path);
    pid_t* arr = (pid_t*)malloc(300 * sizeof(pid_t));
    int i = 0;
    directory(path);
    return 0;
}
