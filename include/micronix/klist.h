#ifndef MICRONIX_KLIST_H
#define MICRONIX_KLIST_H

#include <micronix/compiler_types.h>

#define klist_empty(KList) (KList.length == 0)

/**
 * A generic linked-list implementation for
 * kernel data structures
 */

union KListKey{
    int32_t   i;
    uint32_t  ui;
    char      c[4];
};

struct KListNode{
    union KListKey  key;
    void*    data;
    struct KListNode* next;
    struct KListNode* prev;
};

/**
 * Compare functions for KList nodes.  Returns <0 if first argument
 * is less than second, 0 if equal, >0 if first argument greater than second
 */
typedef int (*klist_compare_fn)(struct KListNode*, struct KListNode*);

/**
 * A custom function to remove nodes by key.
 *
 * First argument: The current node's key
 * Second argument: The key to remove
 * Return: non-negative integer if this node is to be removed, 0 otherwise
 */
typedef int (*klist_remove_fn)(union KListKey, union KListKey);

struct KList{
    klist_compare_fn compare;
    klist_remove_fn remove;
    uint32_t length;
    struct KListNode* head;
    struct KListNode* tail;
};

/**
 * Initialize the KList module
 */
int klist_init(void);

/**
 * Reset the KList struct - set all values to default
 */
int klist_reset(struct KList*, klist_compare_fn, klist_remove_fn);

/**
 * Append the given node to the KList
 */
int klist_append(struct KList*, union KListKey, void*);

/**
 * Pop the first element off of the list
 */
int klist_pop_front(struct KList*, void** );

#endif
