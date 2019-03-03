// utility.c
//
// Phi Luu
//
// Oregon State University
// CS_344_001_W2019 Operating Systems 1
// Program 3: Smallsh
//
// This module contains constants, parameters, and functions that are useful
// for the program but might seem too general to be related to a certain module.
// They are essentially the "helpers" of the program.

#include "utility.h"
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Dynamically allocates an array of strings structure with the given capacity.
//
// Argument:
//   capacity  the initial capacity of the array
//
// Returns:
//   A newly allocated structure of dynamic array of strings
void InitDynStrArr(DynStrArr* arr, int capacity) {
    assert(arr && capacity > 0);

    // allocate dynamic memory for the array
    arr->strings = malloc(capacity * sizeof(*(arr->strings)));
    assert(arr->strings);  // make sure allocation was succesful

    // init the array's size and capacity
    arr->size = 0;
    arr->capacity = capacity;
}

// Pushes a string to the back of the dynamic array (double the capacity if
// needed).
//
// Arguments:
//   arr         the structure of dynamic array of strings
//   new_string  the string to be pushed to the back of  arr->strings
//
// The array of strings inside  arr  will have an additional string at its back.
// The capacity of the array will be doubled if necessary.
void PushBackDynStrArr(DynStrArr* arr, char* new_string) {
    assert(arr && arr->strings && new_string);

    // before adding, must double the capacity if array is full
    if (arr->size == arr->capacity) {
        arr->strings = realloc(arr->strings, arr->capacity * 2
                               * sizeof(*(arr->strings)));
        arr->capacity *= 2;
    }

    // allocate memory and copy the new string to the back of the array
    arr->strings[arr->size] = malloc((strlen(new_string) + 1)
                                     * sizeof(*(arr->strings[arr->size])));
    assert(arr->strings[arr->size]);
    strcpy(arr->strings[arr->size], new_string);
    arr->size++;
}

// Special push: Pushes a  NULL  to the back of the array of strings.
// This NULL element will be considered an element of the array.
//
// Argument:
//   arr  the structure of dynamic array of strings
void PushBackNullDynStrArr(DynStrArr* arr) {
    assert(arr);

    // before adding, must double the capacity if the array is full
    if (arr->size == arr->capacity) {
        arr->strings = realloc(arr->strings, arr->capacity * 2
                               * sizeof(*(arr->strings)));
        arr->capacity *= 2;
    }

    // no need to allocate memory, this signals the end of the array
    arr->strings[arr->size++] = NULL;
}

// Deallocates the array of strings in the structure and resets the parameters.
//
// Argument:
//   arr  the structure of dynamic array of strings to be deallocated
//
// arr->strings  will be freed, and  arr->size  and arr->capacity  will be reset
// to zero.
void DeleteDynStrArr(DynStrArr* arr) {
    // do nothing if the structure or the array is NULL
    if (!arr || !arr->strings) return;

    // clean up the strings if needed
    for (int i = 0; i < arr->size; i++)
        if (arr->strings[i]) free(arr->strings[i]);

    // clean up the array and reset parameters
    free(arr->strings);
    arr->size = 0;
    arr->capacity = 0;
}

// Dynamically allocates an array of PIDs structure with the given capacity.
//
// Argument:
//   capacity  the initial capacity of the array
//
// Returns:
//   A newly allocated structure of dynamic array of PIDs
void InitDynPidArr(DynPidArr* arr, int capacity) {
    assert(arr && capacity > 0);

    // allocate dynamic memory for the array
    arr->pids = malloc(capacity * sizeof(*(arr->pids)));
    assert(arr->pids);  // make sure allocation was succesful

    // init the array's size and capacity
    arr->size = 0;
    arr->capacity = capacity;
}

// Pushes a PID to the back of the dynamic array (double the capacity if
// needed).
//
// Arguments:
//   arr      the structure of dynamic array of PIDs
//   new_pid  the PID to be pushed to the back of  arr->pids
//
// The array of PIDs inside  arr  will have an additional PID at its back.
// The capacity of the array will be doubled if necessary.
void PushBackDynPidArr(DynPidArr* arr, pid_t new_pid) {
    assert(arr && arr->pids && new_pid > 0);

    // before adding, must double the capacity if array is full
    if (arr->size == arr->capacity) {
        arr->pids = realloc(arr->pids, arr->capacity * 2
                            * sizeof(*(arr->pids)));
        arr->capacity *= 2;
    }

    arr->pids[arr->size++] = new_pid;
}

// Pops the PID at the back of the dynamic array. Returns a pointer to the value
// of the PID and removes the PID from the array.
//
// Argument:
//   arr  the structure of dynamic array of PIDs
//
// Returns:
//   A pointer to the PID of the latest children (the back of the array)
pid_t* PopBackDynPidArr(DynPidArr* arr) {
    assert(arr);

    // if array is empty, return NULL
    if (arr->size == 0) return NULL;

    // otherwise, return the address of the last PID and update size
    return &(arr->pids[--arr->size]);
}

// Deallocates the array of PIDs in the structure and resets the parameters.
//
// Argument:
//   arr  the structure of dynamic array of PIDs to be deallocated
//
// arr->pids  will be freed, and  arr->size  and arr->capacity  will be reset
// to zero.
void DeleteDynPidArr(DynPidArr* arr) {
    // do nothing if the structure or the array is NULL
    if (!arr) return;

    // clean up the array and reset parameters
    free(arr->pids);
    arr->size = 0;
    arr->capacity = 0;
}
