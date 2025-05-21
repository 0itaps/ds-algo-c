/**
 * @file linked_list.c
 * @brief Implementation of a simple linked list for integers.
 * 
 * Provides basic operations such as initialization, insertion, 
 * removal, and access for a resizeable linked list of int values.
 * 
 * @author Isaac Tapia
 * @date   May 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a node.
typedef struct Node {
    int data;          // the value stored in this node
    struct Node *next; // pointer to the next node in the list (NULL if last node);
} Node;

// Structure to represent a linked list 
typedef struct LinkedList {
    Node *head; // pointer to the head node of the linked list 
    int size;   // number of elements currently stored
} LinkedList;

// Core lifecycle

/**
 * Initializes a linked list.
 * Sets the head node to NULL and the size to 0.
 * 
 * @param list pointer to the LinkedList to initialize
 */
void initList(LinkedList *list) {
    list->head = NULL;
    list->size = 0;
}

/**
 * Frees the memory used by a linked list.
 * Traverses the linked list and frees every node.
 * Sets the head to NULL and resets size to 0.
 * 
 * @param list pointer to the LinkedList to free
 */
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

/**
 * Helper function to create and allocate memory for a node.
 * 
 * @param value the value to create the node with
 * @return a pointer to the newly created node, or NULL if memory allocation fails
 */
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

/**
 * Inserts a value at the head of a linked list.
 * 
 * @param list  pointer to the LinkedList
 * @param value the value to insert at the head
 */
void insertAtHead(LinkedList *list, int value) {
    Node *new_node = createNode(value);
    if (new_node == NULL) return;

    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

/**
 * Inserts a value at the tail of a linked list. 
 * 
 * @param list  pointer to the LinkedList
 * @param value the value to insert at the tail 
 */
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

/**
 * Inserts a value at a specific position in a linked list. 
 * 
 * @param list  pointer to the LinkedList
 * @param value the value to insert
 * @param index the index to insert the value at 
 */
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

/**
 * Deletes a node from a linked list based on a given value.
 * If the value is not found, the linked list remains the same. 
 * 
 * @param list  pointer to the LinkedList
 * @param value the value to delete
 */
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

/**
 * Deletes a node from a linked list based on a given position. 
 * 
 * @param list  pointer to the LinkedList
 * @param index the index to delete a node at 
 */
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

/**
 * Iteratively searches for a value in a linked list. 
 * 
 * @param list  pointer to the LinkedList
 * @param value the value to search for
 * @return true if the value was found; false otherwise
 */
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

/**
 * Recursively searches for a value in a linked list. 
 * 
 * @param node  pointer to the head node
 * @param value the value to search for 
 * @return true if the value was found; false otherwise
 */
bool searchRecursive(Node *node, int value) {
    if (node == NULL) {
        return false;
    } else if (node->data == value) {
        return true;
    } else return searchRecursive(node->next, value);
}

/**
 * Prints out a string representation of a linked list. 
 * 
 * @param list pointer to the LinkedList
 */
void printList(LinkedList *list) {
    Node *curr = list->head;

    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }

    printf("NULL\n");
}

/**
 * Prints out a string representation of a linked list in reverse order.
 * 
 * @param node pointer to the head node
 */
void printReverse(Node *node) {
    if (node == NULL) return;
    printReverse(node->next);
    printf("%d -> ", node->data);
}

/**
 * Returns the size of a linked list.
 * 
 * @param list pointer to the LinkedList
 * @return the size of a linked list
 */
int getLength(LinkedList *list) {
    return list->size;
}

/**
 * Checks whether a linked list is empty
 * 
 * @param list pointer to the LinkedList
 * @return true if the linked list is empty; false otherwise
 */
bool isEmpty(LinkedList *list) {
    return (list->size == 0);
}

int main() {
    LinkedList list;
    initList(&list);

    printf("Initializing and printing en empty LinkedList:\n");
    printList(&list);
    printf("isEmpty: %s\n", isEmpty(&list) ? "True" : "False");

    printf("Adding elements to the list:\n");
    for (int i = 0; i < 10; i++) {
        insertAtTail(&list, i);
    }
    printList(&list);

    printf("Size of the list: %d\n", getLength(&list));

    printf("Removing value 9 & node at index 4:\n");
    deleteByValue(&list, 9);
    deleteByPosition(&list, 4);
    printList(&list);

    printf("Inserting value at head and also at index 4:\n");
    insertAtHead(&list, 9);
    insertAtPosition(&list, 4, 4);
    printList(&list);

    printf("Searching for value 6 iteratively:\n Found? (T/F): %s\n", searchIterative(&list, 6) ? "True" : "False");
    printf("Searching for value 6 recursively:\n Found? (T/F): %s\n", searchRecursive(list.head, 6) ? "True" : "False");

    printf("Printing the list in reverse:\n");
    printReverse(list.head);
    
    return 0;
}
