#ifndef SORTER_H
#define SORTER_H

#define BUF_SIZE 1025
#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char** row_token;
    char * row_text;
    size_t row_len;
    size_t num_col;
    int comma;
}row;

int compare(char* c1, char* c2);
void merge(row* L, row* R, row* res, int left, int right, int col);
void mergeSort(row* target, int col, int n);


#endif