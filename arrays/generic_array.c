/**
 * @file generic_array.c
 * @brief Implementation of a generic dynamic array using void pointers.
 *
 * Supports storing any data type by specifying the element size.
 * Includes standard array operations like insertion, deletion,
 * access, and resizing, as well as a flexible print mechanism.
 *
 * @author Isaac Tapia
 * @date   May 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Structure to represent a generic dynamic array.
typedef struct {
    void *data;          // pointer to the raw data buffer (element_size * capacity bytes)
    int size;            // number of elements currently stored
    int capacity;        // total number of elements that can be stored before resizing
    size_t element_size; // size (in bytes) of each element stored in the array
} GenericArray;

// Core Functions

/**
 * Initializes a dynamic array with a given element size and initial capacity.
 * Sets the size to 0 and allocates memory for the specified number of elements
 * 
 * @param arr              pointer to the GenericArray to initialize
 * @param element_size     size (in bytes) of each element stored in the array
 * @param initial_capacity number of elements to allocate space for initially
 * 
 */
void initArray(GenericArray *arr, size_t element_size, int initial_capacity) {
    arr->element_size = element_size;
    arr->capacity = initial_capacity;
    arr->data = malloc(arr->capacity * arr->element_size);
    arr->size = 0;

    if (arr->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * Frees the memory used by a generic array.
 * Sets the data pointer to NULL and resets size, capacity, and element_size to 0.abort
 * 
 * @param arr pointer to the GenericArray to free
 */
void freeArray(GenericArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
    arr->element_size = 0;
}

/**
 * Resizes the generic arry to a new capacity.
 * Allocates a new memory block, copies existing elements into it,
 * frees the old memory, and updates the capcity field.
 * 
 * @param arr          pointer to the GenericArray to resize
 * @param new_capacity new number of elements to allocate space for
 */
void resizeArray(GenericArray *arr, int new_capacity) {
    char *new_data = malloc(new_capacity * arr->element_size);
    if (new_data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < arr->size; i++) {
        void *src = (char *)arr->data + i * arr->element_size; 
        void *dest = new_data + i * arr->element_size;
        mempcpy(dest, src, arr->element_size);
    }

    free(arr->data);
    arr->data = new_data;
    arr->capacity = new_capacity;
}

// Element Insertion

/**
 * Add a element to the end of a generic array.
 * Automatically resizes the array if it has reached capacity.
 * 
 * @param arr     pointer to the GenericArray
 * @param element pointer to the element to be added
 */
void pushBack(GenericArray *arr, void *element) {
    if (arr->size == arr->capacity) {
        resizeArray(arr, arr->capacity * 2);
    }

    void *target = (char *)arr->data + arr->size * arr->element_size;
    memcpy(target, element, arr->element_size);
    arr->size++; 
}

/**
 * Inserts a element into a generic array at a specific index.
 * All elements are shifted right to make room for the inserted element.
 * 
 * @param arr     pointer to the GenericArray
 * @param index   the index to insert the element at
 * @param element pointer to the element to be inserted 
 */
void insertAt(GenericArray *arr, int index, void *element) {
    if (index < 0 || index > arr->size) {
        fprintf(stderr, "Error: Invalid index");
        exit(EXIT_FAILURE);
    }

    if (arr->size + 1 > arr->capacity) {
        resizeArray(arr, arr->capacity * 2);
    }

    for (int i = arr->size -1; i >= index; i--) {
        void *src = (char *)arr->data + i * arr->element_size;
        void *dest = (char *)arr->data + (i + 1) * arr->element_size;
        memcpy(dest, src, arr->element_size);
    }

    void *target = (char *)arr->data + index * arr->element_size;
    memcpy(target, element, arr->element_size);
    arr->size++;
}

/**
 * Removes an element from the back of a dynamic array and copies it
 * to the given output location
 * 
 * @param arr         pointer to the GenericArray
 * @param out_element pointer to a memory location where the removed element will be copied
*/
void popBack(GenericArray *arr, void *out_element) {
    if (arr->size == 0) {
        fprintf(stderr, "Error: popBack on empty array\n");
        exit(EXIT_FAILURE);
    }

    void *src = (char *)arr->data + (arr->size -1) * arr->element_size;
    memcpy(out_element, src, arr->element_size);
    arr->size--;
}

/**
 * Removes an element of a generic array at a specific index.
 * 
 * @param arr   pointer to the GenericArray
 * @param index the index to remove the element at
*/
void removeAt(GenericArray *arr, int index) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Error: Invalid index");
        exit(EXIT_FAILURE);
    }

    for (int i = index; i < arr->size - 1; i++) {
        void *src = (char *)arr->data + (i + 1) * arr->element_size;
        void *dest = (char *)arr->data + i * arr->element_size;
        memcpy(dest, src, arr->element_size);
    }
    
    arr->size--;
}

// Access/Utility

/**
 * Get an element from a generic array at a specific index and 
 * copies it to the given output location
 * 
 * @param arr         pointer to the GenericArray
 * @param index       the index to get the element at
 * @param out_element pointer to a memory location where the removed element will be copied
*/
void get(GenericArray *arr, int index, void *out_element) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Error: Invalid index");
        exit(EXIT_FAILURE);
    }

    void *src = (char *)arr->data + index * arr->element_size;
    memcpy(out_element, src, arr->element_size);
}

/**
 * Sets an element in a generic array at a specific index.
 * The previous element at that index will be overriden.
 * 
 * @param arr     pointer to the GenericArray
 * @param index   the index to set the element at
 * @param element the element to set in the generic array
*/
void set(GenericArray *arr, int index, void *element) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Error: Invalid index");
        exit(EXIT_FAILURE);
    }

    void *dest = (char *)arr->data + index * arr->element_size;
    memcpy(dest, element, arr->element_size);
}

/**
 * Returns the size of a generic array.
 * 
 * @param arr pointer to the GenericArray
 * @return the size of the generic array
 */
int size(GenericArray *arr) {
    return arr->size;
}

/**
 * Checks whether a generic array is empty.
 * 
 * @param arr pointer to the GenericArray
 * @return true if empty; false otherwise 
 */
bool isEmpty(GenericArray *arr) {
    return (arr->size == 0);
}

/**
 * Prints the contents of a generic array using a user-provided print function.
 * 
 * @param arr       pointer to the GenericArray
 * @param printFunc function that prints a single element; accepts a void pointer to the element
 */
void printArray(GenericArray *arr, void (*printFunc)(void *)) {
    if (isEmpty(arr)) {
        printf("[]\n");
        return;
    }

    printf("[");
    for (int i = 0; i < arr->size; i++) {
        void *elem = (char *)arr->data + i * arr->element_size;
        printFunc(elem);
        if (i < arr->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

/**
 * Print function for elements of type char.
 * 
 * @param elem pointer to the element to print
 */
void printChar(void *elem) {
    printf("%c", *(char *)elem);
}

int main() {
    GenericArray arr;
    initArray(&arr, sizeof(char), 10);

    printf("Initializing and printing an empty GenericArray of chars:\n");
    printArray(&arr, printChar);
    printf("isEmpty: %s\n", isEmpty(&arr) ? "true" : "false");

    printf("Adding elements to the array:\n");
    for (char c = 'a'; c < 'a' + 10; c++) {
        pushBack(&arr, &c);
    }
    printArray(&arr, printChar);

    printf("Size of the GenericArray: %d\n", size(&arr));

    printf("Popping an element from the back:\n");
    char back;
    popBack(&arr, &back);
    printArray(&arr, printChar);

    printf("Adding the popped element '%c' back in the middle:\n", back);
    insertAt(&arr, 4, &back);
    printArray(&arr, printChar);

    printf("Removing the element again:\n");
    removeAt(&arr, 4);
    printArray(&arr, printChar);

    printf("Getting element at index 0:\n");
    char x;
    get(&arr, 0, &x);
    printf("Element at index 0: '%c'\n", x);

    printf("Adding two values to the back to test resize:\n");
    pushBack(&arr, &back);
    pushBack(&arr, &x);
    printArray(&arr, printChar);

    freeArray(&arr);

    return 0;
}
