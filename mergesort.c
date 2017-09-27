#include "Sorter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//if c1 < c2, return 0; otherwise, return 1;
int compare(char* c1, char* c2){
  int i = 0;
  int c1size = sizeof(c1)/sizeof(char*);
  int c2size = sizeof(c2)/sizeof(char*);

  //compare;
  while(i < c1size && i < c2size){
    if(c1[i] < c2[i]){
      return 0;
    }
    if(c1[i] > c2[i]){
      return 1;
    }
    i++;
  }

  //eg: c1 = app; c2 = apple; return 0; 
  //when the two are same, also return 0;
  if(i == c1size){
    return 0;
  }else{
    return 1;
  }
}



/* This function is used to do mergeing. Merge L and R to Res; 
left is the size of L, right is the size of right; 
col is the column number we need to get; 
*/
void merge(row* L, row* R, row* res, int left, int right, int col){  

    int index = 0;
    int i = 0;
    int j = 0; 

    //compare L and R;
    while(i < left && j < right){
        if(compare(L -> row_token[col], R -> row_token[col]) == 0){
            res[index] = L[i];
            index++;
            i++;
        }else{
            res[index] = R[j];
            index++;
            j++;
        }
    }

    //when one of L and R is done, merge the remainder;
    while(i < left){
        res[index] = L[i];
        i++;
        index++;
    }
    while(j < right){
        res[index] = R[j];
        j++;
        index++;
    }

}
void mergeSort(row* target, int col, int n){

    int i, mid;

    //base;
    if(n < 2){     
        return;
    }
    
    mid = n/2;

    //create the left part and right part of the row;
    row* L = (row*)malloc(mid * sizeof(row));   
    row* R = (row*)malloc((n-mid) * sizeof(row));

    //copy value to left and right row;
    for(i = 0; i < mid; i++){
        L[i] = target[i];
    } 
    for(i = mid; i < n; i++){
        R[i - mid] = target[i];
    }

    //recur;
    mergeSort(L, col, mid);
    mergeSort(R, col, n - mid);
    merge(L, R, target, mid, n - mid, col);

    free(L);
    free(R);

}



int main(int argc, char** argv){
    row* target = (row*)malloc(5*sizeof(row));

    char** c1 = (char**)malloc(5*sizeof(char*));
    row r1;
    r1.row_token = (char**)malloc(5*sizeof(char*));
    int i = 0;
    while(i < 4){
        c1[i] = (char*)malloc(100);
        i++;
    }

    c1[0] = "a";
    c1[1] = "cd";
    c1[2] = "[[";
    c1[3] = "00";
    r1.row_token = c1;

    char** c2 = (char**)malloc(5*sizeof(char*));
    row r2;
    r2.row_token = (char**)malloc(5*sizeof(char*));

    i = 0;
     while(i < 4){
        c2[i] = (char*)malloc(100);
        i++;
    }
    c2[0] = "d";
    c2[1] = "td";
    c2[2] = "--[";
    c2[3] = "34";
    r2.row_token = c2;
    //int* res = (int*)malloc(n * sizeof(int));

    char** c3 = (char**)malloc(5*sizeof(char*));
    row r3;
    r3.row_token = (char**)malloc(5*sizeof(char*));

    i = 0;
    while(i < 4){
        c3[i] = (char*)malloc(100);
        i++;
    }
    c3[0] = "c";
    c3[1] = "432";
    c3[2] = "99[";
    c3[3] = "";
    r3.row_token = c3;

    target[0] = r1;
    target[1] = r2;
    target[2] = r3;

    mergeSort(target,2,3);
   
    printf("%s \n", target[0].row_token[0]);
    return 0;
}
