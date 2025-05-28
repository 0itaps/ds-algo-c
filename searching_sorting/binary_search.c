/**
 * @file binary_search.c
 * @brief Implementation of binary search (iterative and recursive) on sorted arrays.
 * 
 * Provides functions to perform binary search on a sorted array using 
 * both iterative and recursive methods.
 * 
 * @author Isaac Tapia
 * @date   May 2025
 */

#include <stdio.h>
#include <stdbool.h>

/**
 * Performs binary search using iteration.
 * 
 * @param arr    the sorted array to search
 * @param size   the number of elements in the array
 * @param target the value to search for
 * @return the index of the target if found; -1 otherwise
 */
int binarySearchIterative(int arr[], int size, int target) {
    int middle = 0;
    int left = 0;
    int right = size -1;

    while (left <= right) {
        middle = left + (right - left) / 2;

        if (arr[middle] == target) {
            return middle;
        } else if (arr[middle] < target) {
            left = middle + 1;
        } else if (arr[middle] > target) {
            right = middle - 1;
        }
    }
    return -1;
}

/**
 * Performs binary search using recursion.
 * 
 * @param arr    the sorted array to search
 * @param left   the starting index for the current search range
 * @param right  the ending index for the current search range
 * @param target the value to search for
 * @return the index of the target if found; -1 otherwise
 */
int binarySearchRecursive(int arr[], int left, int right, int target) {
    if (left > right) return -1;

    int middle = left + (right - left) / 2;

    if (arr[middle] == target) return middle;
    if (arr[middle] < target)  return binarySearchRecursive(arr, middle + 1, right, target);
    if (arr[middle] > target)  return binarySearchRecursive(arr, left, middle - 1, target); 
}

int main() {
    // Sample sorted array
    int arr[] = {1, 3 ,5, 7, 9, 11, 13};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Sample targets to test
    int targets[] = {7, 2, 11, 14};
    int num_tests = sizeof(targets) / sizeof(targets[0]);

    printf("Testing binary search:\n");

    for (int i = 0; i < num_tests; i++) {
        int target = targets[i];
        int index_iter = binarySearchIterative(arr, size, target);
        int index_rec = binarySearchRecursive(arr, 0, size -1, target);

        printf("Target %d: Iterative index = %d, Recurisve index = %d\n",
                target, index_iter, index_rec);
    }
    
    return 0;
}
