
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <ctype.h>

    
    //a (dynamic size) array of strings that represents a row in the csv
    typedef char** ROW;
    typedef enum {STRING,NUMERIC} DataType;

    //Utilities
    static inline int checkArguments(int argc, char** argv);
    static inline char* subString(char* input, int start, int end);
    static inline void printIndex(int array[], int size);
    static inline void print(ROW *data, int num_of_rows, int num_of_cols, int index[]);
    char *trim(char *str);
    DataType checkType(char *str);

    //StoreData
    static inline int countColumns(char *input, int *target, char *targetColumn);
    char* storeInBuffer(int *num_of_rows);
    ROW* storeAndOrganize(int num_of_rows, int num_of_cols, char *buffer);
    char* getLineFromString(char *buffer);
    char* tokenize(char *line);

    void freeMemory(ROW *data, char *buffer);


    //Sorting

    int compare(char *data1, char *data2, DataType type);
    void mergeSort(ROW *array, int index[],int targetIndex, int l, int r, int num_of_rows, int num_of_cols);
    void merge(ROW *array, int index[], int targetIndex, int l, int mid, int r, int num_of_rows, int num_of_cols);


    int checkArguments(int argc, char** argv)
    {
        //check argument
        if(argc != 3)
        {
            printf("Wrong number of arguments ");
            printf("<-c> <column name>\n");
            return 1;
        }
        else if(argc == 2 && strcmp(argv[1], "-h") == 0){
            printf("<-c> <column name>\n");
        }
        return 0;
    }
    
    char* subString(char* input, int start, int end)
    {
        char* result = malloc(end-start+1);
        memcpy(result, &input[start], end-start);
        result[end - start] = '\0';
        return result; 
    }
   


