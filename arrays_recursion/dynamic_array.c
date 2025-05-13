#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int *data;
    int size;
    int capacity;
} DynamicArray;


// Core Functions

void initArray(DynamicArray *arr, int initial_capacity) {}

void freeArray(DynamicArray *arr) {}

void resizeArray(DynamicArray *arr) {}


// Element Insertion

void pusBack(DynamicArray *arr, int value) {}

void insertAt(DynamicArray *arr, int index, int value) {}


// Element Deletion

void popBack(DynamicArray *arr) {}

removeAt(DynamicArray *arr) {}


// Access/Utility

int get(DynamicArray *arr, int index) {}

int set(DynamicArray *arr, int index, int value) {}

int size(DynamicArray *arr) {}

bool isEmpty(DynamicArray *arr) {}

void printArray(DynamicArray *arr) {}

int main () {
    return 0;
}
