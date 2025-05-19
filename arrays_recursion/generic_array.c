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
    if (arr->size == arr->capacity) {
        resizeArray(arr, arr->capacity * 2);
    }

    void *target = (char *)arr->data + arr->size * arr->element_size;
    memcpy(target, element, arr->element_size);
    arr->size++; 
}

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

void popBack(GenericArray *arr, void *out_element) {
    if (arr->size == 0) {
        fprintf(stderr, "Error: popBack on empty array\n");
        exit(EXIT_FAILURE);
    }

    void *src = (char *)arr->data + (arr->size -1) * arr->element_size;
    memcpy(out_element, src, arr->element_size);
    arr->size--;
}

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

void get(GenericArray *arr, int index, void *out_element) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Error: Invalid index");
        exit(EXIT_FAILURE);
    }

    void *src = (char *)arr->data + index * arr->element_size;
    memcpy(out_element, src, arr->element_size);
}

void set(GenericArray *arr, int index, void *element) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Error: Invalid index");
        exit(EXIT_FAILURE);
    }

    void *dest = (char *)arr->data + index * arr->element_size;
    memcpy(dest, element, arr->element_size);
}

int size(GenericArray *arr) {
    return arr->size;
}

bool isEmpty(GenericArray *arr) {
    return (arr->size == 0);
}

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

void printChar(void *elem) {
    printf("%c", *(char *)elem);
}

int main() {
    
}