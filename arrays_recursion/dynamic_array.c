#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a dynamic array
typedef struct{
    int *data; // The data stored inside the dynamic array
    int size; // The size of the dynamic array
    int capacity; // The capacity of the dynamic array
} DynamicArray;

// Core Functions

/**
 * Initializes a dynamic array with a given initial capacity.
 * Sets the size to 0 and allocates memory for the specified number of integers
 * 
 * @param arr Pointer to the DynamicArray to initialize
 * @param initial_capacity Number of elements to allocate space for initially
 */
void initArray(DynamicArray *arr, int initial_capacity) {
    arr->data = malloc(sizeof(int) * initial_capacity);
    arr->size = 0;
    arr->capacity = initial_capacity;
}

/**
 * Frees the memory used by a dynamic array.
 * Sets the data pointer to NULL and resets size and capacity to 0.
 * 
 * @param arr Pointer to the DynamicArray to free
 */
void freeArray(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

/**
 * Resizes the dynamic array to a new capacity.
 * Allocates a new memory block, copies existing elements into it,
 * frees the old memory, and updates the capacity field.
 * 
 * @param arr Pointer to the DynamicArray to resize
 * @param new_capacity New number of elements to allocate space for
 */
void resizeArray(DynamicArray *arr, int new_capacity) {
    int *new_data = malloc(sizeof(int) * new_capacity);

    for (int i = 0; i < arr->size; i++) {
        new_data[i] = arr->data[i];
    }

    free(arr->data);
    arr->data = new_data;
    arr->capacity = new_capacity;
}

// Element Insertion

/**
 * Adds a value to the end of a dynamic array.
 * Automatically resizes the array if it has reached capacity.
 * 
 * @param arr Pointer to the DynamicArray
 * @param value The value to be added
 */
void pushBack(DynamicArray *arr, int value) {
    if (arr->size == arr->capacity) {
        resizeArray(arr, (2 * arr->capacity));
    }

    arr->data[arr->size++] = value;
}

/**
 * Inserts a value into a dynamic array at a specific index
 * All elements are shifted right to make room for the inserted value
 * 
 * @param arr Pointer to the DynamicArray
 * @param index the index to insert the value at
 * @param value the value to be inserted 
 */
void insertAt(DynamicArray *arr, int index, int value) {
    if (index < 0 || index > arr->size) {
        fprintf(stderr, "Error: Invalid index");
        exit(EXIT_FAILURE);
    }

    if (arr->size + 1 > arr->capacity) {
        resizeArray(arr, (2 * arr->capacity));
    }

    for (int i = arr->size - 1; i >= index; i--) {
        arr->data[i + 1] = arr->data[i];
    }

    arr->data[index] = value;
    arr->size++;
}


// Element Deletion

int popBack(DynamicArray *arr) {
    if (arr->size == 0) {
        fprintf(stderr, "Error: popBack on empty array\n");
        exit(EXIT_FAILURE);
    }

    int back = arr->data[arr->size -1];
    arr->size--;
    return back;
}

void removeAt(DynamicArray *arr, int index) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Error: Invalid index");
        exit(EXIT_FAILURE);
    }

    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }

    arr->size--;
}


// Access/Utility

int get(DynamicArray *arr, int index) {
    if (index < 0 || index >= size) {
        fprintf(stderr, "Error: Invalid index");
        exit(EXIT_FAILURE);
    }

    return arr->data[index];
}

void set(DynamicArray *arr, int index, int value) {
    if (index < 0 || index > arr->size) {
        fprintf(stderr, "Error: Invalid index");
        exit(EXIT_FAILURE);
    }

    arr->data[index] = value;
}

/**
 * Returns the size of a dynamic array.
 * 
 * @param arr Pointer to the Dynamic Array
 * @return the size of the dynamic array
 */
int size(DynamicArray *arr) {
    return arr->size;
}

/**
 * Checks whether a dynamic array is empty.
 * 
 * @param arr Pointer to the Dynamic Array
 * @return true if empty; false otherwise 
 */
bool isEmpty(DynamicArray *arr) {
    return (arr->size == 0);
}

void printArray(DynamicArray *arr) {
    if (isEmpty(arr)) {
        printf("[]\n");
        return;
    }

    printf("[");
    for (int i = 0; i < arr->size; i++) {
        if (i == (arr->size - 1)) {
            printf("%d]", arr->data[i]);
        } else printf("%d, ", arr->data[i]);
    }

}

int main () {
    DynamicArray arr;
    initArray(&arr, 10);

    printArray(&arr);

    return 0;
}
