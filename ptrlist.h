///////////////////////////////////////////////////////////////////////////////
// ptrlist.h
// Pointer list in C99. 
//
// Date:   13/04/2019
// Author: PotatoMaster101
///////////////////////////////////////////////////////////////////////////////

#ifndef PTRLIST_H
#define PTRLIST_H
#include <stdlib.h>
#include <string.h>

#define PLIST_GOOD 0
#define PLIST_NULL_ERR 1
#define PLIST_ALLOC_ERR 2

// The pointer list type. 
typedef struct ptrlist_t {
    void **ptrs;            // the list of pointers
    size_t len;             // list length
    size_t max;             // maximum length
    void (*free)(void *);   // pointer free function
} plist_t;

// Initialises the specified pointer list. 
//
// PARAMS: 
// l      - the pointer list to initialise
// freefn - the free function for each pointer
//
// RET: 
// Zero on success, non-zero on error. 
int plist_init(plist_t *l, void (*freefn)(void *));

// Adds a new pointer to the end of the given pointer list. 
//
// PARAMS: 
// l - the pointer list to add
// p - the pointer to add
//
// RET: 
// Zero on success, non-zero on error. 
int plist_add(plist_t *l, void *p);

// Inserts a new pointer to the given index in the specified pointer list. 
//
// PARAMS: 
// l - the pointer list to insert
// p - the pointer to insert
// i - the index of the pointer
//
// RET: 
// Zero on success, non-zero on error. 
int plist_ins(plist_t *l, void *p, size_t i);

// Deletes the specified pointer in the given pointer list. 
//
// PARAMS: 
// l - the pointer list to delete the pointer
// i - the index of the pointer to delete
//
// RET: 
// The deleted pointer, or NULL on error. 
void *plist_del(plist_t *l, size_t i);

// Clears the given pointer list, freeing every element. 
//
// PARAMS: 
// l - the pointer list to clear
void plist_clear(plist_t *l);

// Frees the given pointer list along with every pointer. 
//
// PARAMS: 
// l - the pointer list to free
void plist_free(plist_t *l);

#endif

