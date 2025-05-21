/**
 * @file dynamic_array.c
 * @brief Implementation of a simple dynamic array for integers.
 *
 * Provides basic operations such as initialization, insertion,
 * removal, and access for a resizable array of int values.
 *
 * @author Isaac Tapia
 * @date   May 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a dynamic array.
typedef struct{
    int *data;    // pinter to the contiguous block of int elements (capacity elements total)
    int size;     // number of elements currently stored
    int capacity; // total number of elements that can be stored before resizing
} DynamicArray;

// Core Functions

/**
 * Initializes a dynamic array with a given initial capacity.
 * Sets the size to 0 and allocates memory for the specified number of integers.
 * 
 * @param arr              pointer to the DynamicArray to initialize
 * @param initial_capacity number of elements to allocate space for initially
 */
void initArray(DynamicArray *arr, int initial_capacity) {
    arr->data = malloc(sizeof(int) * initial_capacity);
    arr->size = 0;
    arr->capacity = initial_capacity;

    if (arr->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * Frees the memory used by a dynamic array.
 * Sets the data pointer to NULL and resets size and capacity to 0.
 * 
 * @param arr pointer to the DynamicArray to free
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
 * @param arr          pointer to the DynamicArray to resize
 * @param new_capacity new number of elements to allocate space for
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
 * Adds a element to the end of a dynamic array.
 * Automatically resizes the array if it has reached capacity.
 * 
 * @param arr     pointer to the DynamicArray
 * @param element the element to be added
 */
void pushBack(DynamicArray *arr, int element) {
    if (arr->size == arr->capacity) {
        resizeArray(arr, (2 * arr->capacity));
    }

    arr->data[arr->size++] = element;
}

/**
 * Inserts a element into a dynamic array at a specific index.
 * All elements are shifted right to make room for the inserted element.
 * 
 * @param arr     pointer to the DynamicArray
 * @param index   the index to insert the element at
 * @param element the element to be inserted 
 */
void insertAt(DynamicArray *arr, int index, int element) {
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

    arr->data[index] = element;
    arr->size++;
}

// Element Deletion

/**
 * Removes an element from the back of a dynamic array
 * 
 * @param arr pointer to the DynamicArray
 * @return the value removed
*/
int popBack(DynamicArray *arr) {
    if (arr->size == 0) {
        fprintf(stderr, "Error: popBack on empty array\n");
        exit(EXIT_FAILURE);
    }

    int back = arr->data[arr->size -1];
    arr->size--;
    return back;
}

/**
 * Removes an element of a dynamic array at a specific index.
 * 
 * @param arr   pointer to the DynamicArray
 * @param index the index to remove the element at
*/
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

/**
 * Get an element from a dynamic array at a specific index
 * 
 * @param arr   pointer to the DynamicArray
 * @param index the index to get the element at
*/
int get(DynamicArray *arr, int index) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Error: Invalid index");
        exit(EXIT_FAILURE);
    }

    return arr->data[index];
}

/**
 * Sets an element in a dynamic array at a specific index.
 * The previous element at that index will be overriden.
 * 
 * @param arr     pointer to the DynamicArray
 * @param index   the index to set the element at
 * @param element the element to set in the dynamic array
*/
void set(DynamicArray *arr, int index, int element) {
    if (index < 0 || index > arr->size) {
        fprintf(stderr, "Error: Invalid index");
        exit(EXIT_FAILURE);
    }

    arr->data[index] = element;
}

/**
 * Returns the size of a dynamic array.
 * 
 * @param arr pointer to the DynamicArray
 * @return the size of the dynamic array
 */
int size(DynamicArray *arr) {
    return arr->size;
}

/**
 * Checks whether a dynamic array is empty.
 * 
 * @param arr pointer to the DynamicArray
 * @return true if empty; false otherwise 
 */
bool isEmpty(DynamicArray *arr) {
    return (arr->size == 0);
}

/**
 * Prints out a string representation of a dynamic array.
 * 
 * @param arr pointer to the DynamicArray
*/
void printArray(DynamicArray *arr) {
    if (isEmpty(arr)) {
        printf("[]\n");
        return;
    }

    printf("[");
    for (int i = 0; i < arr->size; i++) {
        if (i == (arr->size - 1)) {
            printf("%d]\n", arr->data[i]);
        } else printf("%d,", arr->data[i]);
    }

}

int main () {
    DynamicArray arr;
    initArray(&arr, 10);

    printf("Initializing and printing an empty DynamicArray of size 10: \n");
    printArray(&arr);
    printf("isEmpty: %s\n", isEmpty(&arr) ? "true" : "false");

    printf("Adding elements to the array:\n");
    for (int i = 0 ; i < 10; i++) {
        pushBack(&arr, i);
    }
    printArray(&arr);

    printf("Size of the DynamicArray: %d\n", size(&arr));

    printf("Popping an element from the back:\n");
    int back = popBack(&arr);
    printArray(&arr);

    printf("Adding the element back in the middle:\n");
    insertAt(&arr, 4, back);
    printArray(&arr);

    printf("Removing the element again:\n");
    removeAt(&arr, 4);
    printArray(&arr);

    printf("Getting element at index 0\n");
    int x = get(&arr, 0);

    printf("Adding two values to the back to test resize:\n");
    pushBack(&arr, 9);
    pushBack(&arr, x);
    printArray(&arr);

    freeArray(&arr);

    return 0;
}
