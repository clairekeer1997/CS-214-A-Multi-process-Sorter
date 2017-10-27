#include "sorter.h"

void mergeSort(ROW *array,int index[], int targetIndex, int l, int r,int num_of_rows, int num_of_cols)
{
    if(l < r){
        int m = l+(r-l)/2;
        //printf("\n\nMergeSort: l is: %d, r is: %d, m is: %d\n\n",l,r,m);
      //  printf("here1\n");
        mergeSort(array,index,targetIndex, l, m, num_of_rows, num_of_cols);
        //printf("here2\n");
        
        mergeSort(array,index,targetIndex, m+1, r, num_of_rows, num_of_cols);
        //print(array, num_of_rows, num_of_cols);
        
        merge(array,index,targetIndex, l, m, r, num_of_rows, num_of_cols);
    }
}

void merge(ROW *arr, int index[], int targetIndex, int l, int m, int r, int num_of_rows, int num_of_cols)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = index[l + i];
    for (j = 0; j < n2; j++)
        R[j] = index[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray

    while (i < n1 && j < n2)
    { 

        DataType t = STRING;
        char *left = arr[L[i]][targetIndex];
        char *right = arr[R[j]][targetIndex];
        if(left != '\0') t = checkType(left);
        if(right != '\0') t = checkType(right);
        int controller = compare(left,right,t);
        //printf("controller = %d\n", controller);
        if(left == '\0' && right == '\0') {           
            controller = 0;
        }        
        if (controller <= 0)
        {
            index[k++] = L[i++];
        }
        else
        {
            index[k++] = R[j++];
        }
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        index[k++] = L[i++];        
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        index[k++] = R[j++];        
    }
}
