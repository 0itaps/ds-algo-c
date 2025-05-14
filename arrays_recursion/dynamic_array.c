#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int *data;
    int size;
    int capacity;
} DynamicArray;


// Core Functions

void initArray(DynamicArray *arr, int initial_capacity) {
    arr->data = (int *) malloc(initial_capacity * sizeof(int));
    arr->size = 0;
    arr->capacity = initial_capacity;
}

void freeArray(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void resizeArray(DynamicArray *arr, int new_capacity) {
    int *new_data = (int *) malloc(new_capacity * sizeof(int));

    for (int i = 0; i < arr->size; i++) {
        new_data[i] = arr->data[i];
    }

    free(arr->data);
    arr->data = new_data;
    arr->capacity = new_capacity;
}


// Element Insertion

void pushBack(DynamicArray *arr, int value) {
    if (arr->size == arr->capacity) {
        resizeArray(arr, (2 * arr->capacity));
    }

    arr->data[arr->size] = value;
    arr->size++;
}

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
