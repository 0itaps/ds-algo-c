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

// Node structure
typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

// Doubly linked list structure
typedef struct DoublyLinkedList {
    Node *head;
    Node *tail;
    int size;
} DoublyLinkedList;

// Core lifecycle
void initList(DoublyLinkedList *list);
void freeList(DoublyLinkedList *list);
Node* createNode(int value);

// Insertion
void insertAtHead(DoublyLinkedList *list, int value);
void insertAtTail(DoublyLinkedList *list, int value);
void insertAtPosition(DoublyLinkedList *list, int value, int index);

// Deletion
void deleteByValue(DoublyLinkedList *list, int value);
void deleteByPosition(DoublyLinkedList *list, int index);

// Search
bool searchIterative(DoublyLinkedList *list, int value);
bool searchRecursive(Node *node, int value);

// Utility
void printListForward(DoublyLinkedList *list);
void printListBackward(DoublyLinkedList *list);
int getLength(DoublyLinkedList *list);
bool isEmpty(DoublyLinkedList *list);

int main() {
    // Sample test area
    return 0;
}
