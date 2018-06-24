#include <micronix/klist.h>
#include <micronix/string.h>
#include <generated/autoconf.h>
#include <micronix/errno.h>

#ifdef CONFIG_STATIC_KLIST
static struct KListNode nodes[ CONFIG_KLIST_NODES ];
static struct KListNode* free_nodes;

int klist_init(){
    int x;
    free_nodes = NULL;

    kmemset(nodes, 0, sizeof( struct KListNode ) * CONFIG_KLIST_NODES );

    /* Add all nodes to our free list in reverse order -
     * the first free KListNode is nodes[ CONFIG_KLIST_NODES - 1 ]
     */
    for( x = 0; x < CONFIG_KLIST_NODES; ++x ) {
        nodes[ x ].next = free_nodes;
        free_nodes = &nodes[ x ];
    }

    return 0;
}

static int klist_new_node( struct KListNode** newnode ){
    if( newnode == NULL ){
        return -EINVAL;
    }

    if( free_nodes == NULL ){
        return -EINVAL;
    }

    *newnode = free_nodes;
    free_nodes = free_nodes->next;

    return 0;
}
#else
int klist_init(){
    return 0;
}
#endif

int klist_reset(struct KList* list, klist_compare_fn comp, klist_remove_fn remove){
    if( list == NULL ){
        return -EINVAL;
    }

    list->compare = comp;
    list->remove = remove;
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;

    return 0;
}

int klist_append(struct KList* list, union KListKey key, void* data){
    struct KListNode* newnode;
    struct KListNode* tail = list->tail;
    int rc;

    if( list == NULL ){
        return -EINVAL;
    }

    rc = klist_new_node( &newnode );
    if( rc ){
        return rc;
    }

    newnode->key = key;
    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = tail;
    if( tail ){
        tail->next = newnode;
    }
    
    return 0;
}

int klist_pop_front(struct KList* list, void** data ){
    if( list == NULL || *data == NULL ){
        return -EINVAL;
    }

    if( list->length == 0 ){
        return -EAGAIN;
    }

    *data = list->head->data;
    list->head = list->head->next;
    list->head->prev = NULL;

    return 0;
}
