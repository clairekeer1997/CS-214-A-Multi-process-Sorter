#ifndef SORTER_H
#define SORTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char** row_token;
    char * row_text;
    size_t row_len;
    size_t num_col;
}row;
int compare(char* c1, char* c2);
void merge(row* L, row* R, row* res, int left, int right, int col);
void mergeSort(row* target, int col, int n);


#endif