#ifndef SORTER_H
#define SORTER_H

#define BUF_SIZE 1025
#define MAX_LINE 10000
#define TRUE 1
#define FALSE 0
#define MAX_DIR 4097

#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

typedef struct{
    char** row_token;
    char * row_text;
    size_t row_len;
    size_t num_col;
    int comma;//true if there is no comma, false if there is a comma in the row
}row;

//mergesort.c

int compare(char* c1, char* c2);
void merge(row* L, row* R, row* res, int left, int right, int col);
void mergeSort(row* target, int col, int n);

//sorter.c
char* path_contact(const char* str1,const char* str2);
char *trim(char *word, int index);
char** tokenizer(char* line, size_t num_col);
int tok_file(FILE *fp, row* data, int num_col);
void sort(char* filename, char* colname, char* odirname, char* tmppath, char* currPath, char** colarr, int num);
int isDirectory(char *path);
int checkcsv(char* path, char* colname);
void count_process(char* path, char* colname);
void directory(char* path, char* colname, char* odirname, char** colarr, int num_col);

#endif