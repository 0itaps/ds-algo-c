#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    void *data;
    int size;
    int capacity;
    size_t element_size;
} GenericArray;

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

void freeArray(GenericArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
    arr->element_size = 0;
}

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

void pushBack(GenericArray *arr, void *element) {


    void *target = (char *)arr->data + arr->size * arr->element_size;
    memcpy(target, element, arr->element_size);
    arr->size++; 
}