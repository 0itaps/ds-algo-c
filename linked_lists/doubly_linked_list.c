/**
 * @file doubly_linked_list.c
 * @brief Implementation of a doubly linked list for integers.
 * 
 * Provides operations for insertion, deletion, search, and traversal 
 * using both next and prev pointers.
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
    struct Node *next; // pointer to the next node in the list (NULL if last node)
    struct Node *prev; // pointer to the previous node in the list (NULL if head node or list is of size 1)
} Node;

// Structure to represent a doubly linked list
typedef struct DoublyLinkedList {
    Node *head; // pointer to the head node of the doubly linked list
    Node *tail; // pointer to the tail node of the doubly linked list
    int size;   // number of elements currently 
} DoublyLinkedList;

// Core lifecycle

/**
 * Initializes a doubly linked list.
 * Sets the head & tail node to NULL and the size to 0.
 * 
 * @param list pointer to the DoublyLinkedList to initialize
 */
void initList(DoublyLinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

/**
 * Frees the memory used by a doubly linked list.
 * Traverses the linked list and frees every node.
 * Sets the head & tail to NULL and resets size to 0.
 * 
 * @param list pointer to the DoublyLinkedList to free
 */
void freeList(DoublyLinkedList *list) {
    Node *curr = list->head;

    while (curr != NULL) {
        Node *temp = curr;
        curr = curr->next;
        free(temp);
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Helpers

/**
 * Helper function  to create and allocate memory for a node.
 * 
 * @param value the value to create the node with
 * @return a pointer to  the newly created node, or NULL if memory allocation fails
 */
Node* createNode(int value) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    } 
    
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// Insertion

/**
 * Inserts a value at the head of a doubly linked list.
 * 
 * @param list  pointer to the DoublyLinkedList
 * @param value the value to insert at the head
 */
void insertAtHead(DoublyLinkedList *list, int value) {
    Node *new_node = createNode(value);
    if (new_node == NULL) return;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
        list->size++;
    } else {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
        list->size++;
    }
}

/**
 * Inserts a value at the tail of a doubly linked list.
 * 
 * @param list  pointer to the DoublyLinkedList
 * @param value the value to insert at the tail
 */
void insertAtTail(DoublyLinkedList *list, int value) {
    Node *new_node = createNode(value);
    if (new_node == NULL) return;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
        list->size++;
    } else {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
        list->size++;
    }
}

/**
 * Inserts a value at a specific position in a doubly linked list.
 * Traveres the list either from the head or the tail depending on the index.
 * 
 * @param list  pointer to the DoublyLinkedList
 * @param value the value to insert
 * @param index the index to insert the value at 
 */
void insertAtPosition(DoublyLinkedList *list, int value, int index) {
    if (index < 0 || index > list->size) {
        fprintf(stderr, "Error: invalid index\n");
        return;
    }

    if (index == 0) {
        insertAtHead(list, value);
        return;
    }

    if (index == list->size) {
        insertAtTail(list, value);
        return;
    }

    Node *new_node = createNode(value);
    if (new_node == NULL) return;

    if (index < list->size / 2) {
        Node *curr = list->head;
        int count = 0;

        while (count < index - 1) {
            curr = curr->next;
            count++;
        }
        new_node->prev = curr;
        new_node->next = curr->next;
        curr->next->prev = new_node;
        curr->next = new_node;
        list->size++;
    } else {
        Node *curr = list->tail;
        int count = list->size - 1;

        while (count > index - 1) {
            curr = curr->prev;
            count--;
        }
        new_node->prev = curr;
        new_node->next = curr->next;
        curr->next->prev = new_node;
        curr->next = new_node;
        list->size++;
    }
}

// Deletion

/**
 * Deletes the head node from a doubly linked list.
 * 
 * @param list pointer to the DoublyLinkedList
 */
void deleteHead(DoublyLinkedList *list) {
    if (list->head == NULL) return;

    Node *temp = list->head;
    list->head = temp->next;

    if (list->head == NULL) {
        list->tail = NULL;
    } else {
        list->head->prev = NULL;
    }

    free(temp);
    list->size--;
}

/**
 * Deletes the tail node from a doubly linked list.
 * 
 * @param list pointer to the DoublyLinkedList 
 */
void deleteTail(DoublyLinkedList *list) {
    if (list->tail == NULL) return;

    Node *temp = list->tail;
    list->tail = temp->prev;

    if (list->tail == NULL) {
        list->head = NULL;
    } else {
        list->tail->next = NULL;
    }

    free(temp);
    list->size--;
}

/**
 * Deletes a node from a doubly linked list based on a given value.
 * If the value is not found, the doubly linked list remains the same.
 * 
 * @param list  pointer to the DoublyLinkedList
 * @param value the value to delete
 */
void deleteByValue(DoublyLinkedList *list, int value) {
    Node *curr = list->head;

    while (curr != NULL) {
        if (curr->data == value) {
            if (curr->prev == NULL) {
                deleteHead(list);
                return;
            } else if (curr->next == NULL) {
                deleteTail(list);
                return;
            } else {
                curr->next->prev = curr->prev;
                curr->prev->next = curr->next;
                free(curr);
                list->size--;
                return;
            }

        }
        curr = curr->next;
    }
}

/**
 * Deletes a node from a doubly linked list based on a given position.
 * 
 * @param list  pointer to the DoublyLinkedList
 * @param index the index to delete a node at
 */
void deleteByPosition(DoublyLinkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Error: invalid index\n");
        return;
    }

    if (index == 0) {
        deleteHead(list);
        return;
    }

    if (index == list->size - 1) {
        deleteTail(list);
        return;
    }

    if (index < list->size / 2) {
        Node *curr = list->head;
        int count = 0;

        while (count < index) {
            curr = curr->next;
            count++;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        free(curr);
        list->size--;
        return;
    } else {
        Node *curr = list->tail;
        int count = list->size - 1;

        while (count > index) {
            curr = curr->prev;
            count--;
        }

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        free(curr);
        list->size--;
        return;
    }
}

// Utility

/**
 * Iteratively searches for a value in a doubly linked list.
 * 
 * @param list  pointer to the DoublyLinkedList
 * @param value the value to search for
 * @return true if the value was found; false otherwise
 */
bool searchIterative(DoublyLinkedList *list, int value) {
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
 * Recursively searches for a value in a doubly linked list.
 * 
 * @param node  pointer to the head node
 * @param value the value to search for
 * @return true if the value was found; false otherwise
 */
bool searchRecursive(Node *node, int value) {
    if (node == NULL) return false;
    if(node->data == value) return true;
    return searchRecursive(node->next, value);
}

/**
 * Prints out a string representation of a doubly linked list.
 * 
 * @param list pointer to the DoublyLinkedList
 */
void printList(DoublyLinkedList *list) {
    Node *curr = list->head;

    while (curr != NULL) {
        printf("%d <-> ", curr->data);
        curr = curr->next;
    }

    printf("NULL\n");
}

/**
 * Prints out a string representation of a linked list in reverse order.
 * 
 * @param list pointer to the DoublyLinkedList
 */
void printReverse(DoublyLinkedList *list) {
    Node *curr = list ->tail;

    while (curr != NULL) {
        printf("%d <-> ", curr->data);
        curr = curr->prev;
    }

    printf("NULL\n");
}

/**
 * Returns the size of a doubly linked list
 * 
 * @param list pointer to the DoublyLinkedList
 * @return the size of a linked list
 */
int getLength(DoublyLinkedList *list) {
    return list->size;
}

/**
 * Checks whether a doubly linked list is empty
 * 
 * @param list pointer to the DoublyLinkedList
 * @return true if the linked list is empty; false otherwise 
 */
bool isEmpty(DoublyLinkedList *list) {
    return (list->size == 0);
}

int main() {
    DoublyLinkedList list;
    initList(&list);

    printf("Initializing and printing an empty DoublyLinkedList:\n");
    printList(&list);
    printf("isEmpty: %s\n", isEmpty(&list) ? "True" : "False");

    printf("Adding elements 0-9 to the list:\n");
    for (int i = 0; i < 10; i++) {
        insertAtTail(&list, i);
    }
    printList(&list);
    printf("Size of the list: %d\n", getLength(&list));

    printf("Inserting 99 at the head:\n");
    insertAtHead(&list, 99);
    printList(&list);

    printf("Inserting 88 at the tail:\n");
    insertAtTail(&list, 88);
    printList(&list);

    printf("Inserting 77 at index 5:\n");
    insertAtPosition(&list, 77, 5);
    printList(&list);

    printf("Deleting value 77:\n");
    deleteByValue(&list, 77);
    printList(&list);

    printf("Deleting head:\n");
    deleteHead(&list);
    printList(&list);

    printf("Deleting tail:\n");
    deleteTail(&list);
    printList(&list);

    printf("Deleting node at index 4:\n");
    deleteByPosition(&list, 4);
    printList(&list);

    printf("Searching for value 6 (iterative): %s\n", searchIterative(&list, 6) ? "True" : "False");
    printf("Searching for value 6 (recursive): %s\n", searchRecursive(list.head, 6) ? "True" : "False");

    printf("Printing the list in reverse:\n");
    printReverse(&list);

    printf("Freeing the list:\n");
    freeList(&list);
    printList(&list);
    printf("isEmpty: %s\n", isEmpty(&list) ? "True" : "False");

    return 0;
}

