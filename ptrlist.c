///////////////////////////////////////////////////////////////////////////////
// ptrlist.c
// Pointer list in C99. 
//
// Date:   13/04/2019
// Author: PotatoMaster101
///////////////////////////////////////////////////////////////////////////////

#include "ptrlist.h"
#define DEF_MAX 10

static int plist_alloc(plist_t *l);
static inline _Bool plist_check(const plist_t *l);
static void def_free(void *p);

// Initialises the specified pointer list. 
//
// PARAMS: 
// l      - the pointer list to initialise
// freefn - the free function for each pointer
//
// RET: 
// Zero on success, non-zero on error. 
int plist_init(plist_t *l, void (*freefn)(void *)) {
    if (l == NULL)
        return PLIST_NULL_ERR;

    int ret = PLIST_GOOD;
    l->free = (freefn == NULL) ? def_free : freefn;
    l->max = DEF_MAX;
    l->len = 0;
    l->ptrs = malloc(DEF_MAX * sizeof(void *));
    if (l->ptrs == NULL)
        ret = PLIST_ALLOC_ERR;
    return ret;
}

// Adds a new pointer to the end of the given pointer list. 
//
// PARAMS: 
// l - the pointer list to add
// p - the pointer to add
//
// RET: 
// Zero on success, non-zero on error. 
int plist_add(plist_t *l, void *p) {
    if (!plist_check(l) || p == NULL)
        return PLIST_NULL_ERR;
    if (plist_alloc(l) != 0)
        return PLIST_ALLOC_ERR;

    l->ptrs[l->len++] = p;
    return PLIST_GOOD;
}

// Inserts a new pointer to the given index in the specified pointer list. 
//
// PARAMS: 
// l - the pointer list to insert
// p - the pointer to insert
// i - the index of the pointer
//
// RET: 
// Zero on success, non-zero on error. 
int plist_ins(plist_t *l, void *p, size_t i) {
    if (!plist_check(l) || p == NULL)
        return PLIST_NULL_ERR;
    if (i >= l->len)
        return plist_add(l, p);
    if (plist_alloc(l) != 0)
        return PLIST_ALLOC_ERR;

    size_t sh = l->len - i;
    memmove(l->ptrs + i + 1, l->ptrs + i, sh * sizeof(void *));
    l->ptrs[i] = p;
    l->len++;
    return PLIST_GOOD;
}

// Deletes the specified pointer in the given pointer list. 
//
// PARAMS: 
// l - the pointer list to delete the pointer
// i - the index of the pointer to delete
//
// RET: 
// The deleted pointer, or NULL on error. 
void *plist_del(plist_t *l, size_t i) {
    if (!plist_check(l))
        return NULL;

    void *ret = NULL;
    if (i >= l->len - 1) {          // remove last if out of range
        ret = l->ptrs[l->len - 1];
    } else {
        ret = l->ptrs[i];
        size_t sh = l->len - i;
        memmove(l->ptrs + i, l->ptrs + i + 1, sh * sizeof(void *));
    }
    l->ptrs[--l->len] = NULL;
    return ret;
}

// Clears the given pointer list, freeing every element. 
//
// PARAMS: 
// l - the pointer list to clear
void plist_clear(plist_t *l) {
    if (plist_check(l)) {
        for (size_t i = 0; i < l->len; i++) {
            l->free(l->ptrs[i]);
            l->ptrs[i] = NULL;
        }
        l->len = 0;
    }
}

// Frees the given pointer list along with every pointer. 
//
// PARAMS: 
// l - the pointer list to free
void plist_free(plist_t *l) {
    if (plist_check(l)) {
        for (size_t i = 0; i < l->len; i++)
            l->free(l->ptrs[i]);
        free(l->ptrs);
        l->ptrs = NULL;
    }
}

// Allocates more memory for the internal buffer if required. 
//
// PARAMS: 
// l - the pointer list to allocate more memory
//
// RET: 
// Zero if the pointer list can hold one more element, non-zero on error. 
static int plist_alloc(plist_t *l) {
    if (l->len < l->max)
        return PLIST_GOOD;

    int ret = PLIST_ALLOC_ERR;
    void **temp = realloc(l->ptrs, 2 * l->max * (sizeof *temp));
    if (temp != NULL) {
        ret = PLIST_GOOD;
        l->max *= 2;
        l->ptrs = temp;
    }
    return ret;
}

// Checks whether the given pointer list is valid. 
//
// PARAMS: 
// l - the pointer list to check
//
// RET: 
// True if the given pointer list is valid, false otherwise. 
static inline _Bool plist_check(const plist_t *l) {
    return (l != NULL && l->ptrs != NULL);
}

// Frees the given pointer. 
//
// PARAMS: 
// p - the pointer to free
static void def_free(void *p) {
    if (p != NULL)
        free(p);
}

