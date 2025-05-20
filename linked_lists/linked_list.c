#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    int size;
} LinkedList;

// Core lifecycle

void initList(LinkedList *list) {
    list->head = NULL;
    list->size = 0;
}

void freeList(LinkedList *list) {
    Node *curr = list->head;

    while (curr != NULL) {
        Node *temp = curr;
        curr = curr->next;
        free (temp);
    }

    list->head = NULL;
    list->size = 0;
}

// Helpers

Node *createNode(int value) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

// Insertion

void insertAtHead(LinkedList *list, int value) {
    Node *new_node = createNode(value);
    if (new_node == NULL) return;

    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

void insertAtTail(LinkedList *list, int value) {
    Node *curr = list->head;

    Node *new_node = createNode(value);
    if (new_node == NULL) return;

    if (list->head == NULL) {
    list->head = new_node;
    list->size++;
    return;
}

    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = new_node;
    list->size++;
}

void insertAtPosition(LinkedList *list, int value, int index) {
    if (index < 0 || index > list->size) {
        fprintf(stderr, "Error: Invalid index");
        exit(EXIT_FAILURE);
    }

    if (index == 0) {
        insertAtHead(list, value);
        return;
    }

    if (index == list->size) {
        insertAtTail(list, value);
        return;
    }

    Node *curr = list->head;
    Node *new_node = createNode(value);
    int count = 0;

    while (count < index -1) {
        curr = curr->next;
        count++;
    }

    new_node->next = curr->next;
    curr->next = new_node;
    list->size++;
}


//Deletion

void deleteByValue(LinkedList *list, int value) {
    Node *curr = list->head;
    Node *prev = NULL;

    while (curr != NULL) {
        if (curr->data == value) {
            if (prev == NULL) {
                list->head = curr->next;
                list->size--;
                free(curr);
                return;
            } else {
                prev->next = curr->next;
                list->size--;
                free(curr);
                return;
            }
        }
        prev = curr;
        curr = curr->next;
    }
}

void deleteByPosition(LinkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Error: invalid index");
        exit(EXIT_FAILURE);
    }

    Node *curr = list->head;

    if (index == 0) {
        list->head = curr->next;
        list->size--;
        free(curr);
        return;
    }

    Node *temp = NULL;
    int count = 0;

    while (count < index -1) {
        curr = curr->next;
        count++;
    }

    temp = curr->next;
    curr->next = temp->next;
    list->size--;
    free(temp);
}

// Utility

bool searchIterative(LinkedList *list, int value) {
    Node *curr = list->head;

    while (curr != NULL) {
        if (curr->data == value) {
            return true;
        }
        curr = curr->next;
    }
    
    return false;
}

bool searchRecursive(Node *node, int value) {
    if (node == NULL) {
        return false;
    } else if (node->data == value) {
        return true;
    } else return searchRecursive(node->next, value);
}

void printList(LinkedList *list) {
    Node *curr = list->head;

    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }

    printf("NULL\n");
}

void printReverse(Node *node) {
    if (node == NULL) return;
    printReverse(node->next);
    printf("%d -> ", node->data);
}

int getLength(LinkedList *list) {
    return list->size;
}

bool isEmpty(LinkedList *list) {
    return (list->size == 0);
}

int main() {
    LinkedList list;
    initList(&list);

    printf("Initializing and printing en empty LinkedList:\n");
    printList(&list);
    printf("isEmpty: %s\n", isEmpty(&list) ? "true" : "false");

    printf("Adding elements to the list:\n");
    for (int i = 0; i < 10; i++) {
        insertAtTail(&list, i);
    }
    printList(&list);

    printf("Size of the list: %d\n", getLength(&list));

    return 0;
}
