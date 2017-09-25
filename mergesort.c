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
void merge(struct row* L, struct row* R, struct row* res, int left, int right, int col){  

    int index = 0;
    int i = 0;
    int j = 0; 

    //compare L and R;
    while(i < left && j < right){
        if(compare(L -> record[col], R -> record[col]) == 0){
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
void mergeSort(struct row* target, int col, int n){

    int i, mid;

    //base;
    if(n < 2){     
        return;
    }
    
    mid = n/2;

    //create the left part and right part of the row;
    struct row* L = (struct row*)malloc(mid * sizeof(struct row));   
    struct row* R = (struct row*)malloc((n-mid) * sizeof(struct row));

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
 
    int a[3] = {3, 2, 1};
    int n = sizeof(a) / sizeof(a[0]);
    //int* res = (int*)malloc(n * sizeof(int));
    mergeSort(a,n);
    int i = 0;
    while(i < n){
        printf("%d \n", a[i]);
        i++;
    }
    return 0;
}