#ifndef __LIST_H
#define __LIST_H

/*
 * This structure is used to represent a single link in a singly-linked list.
 * It is not defined in ll.h, so it is not visible to the user.  You should not
 * modify this structure.
 */
struct link {
    void* val;
    struct link* next;
};

/*
 * This structure is used to represent an entire singly-linked list.  Note that
 * we're keeping track of just the head of the list here, for simplicity.
 */
struct list {
    struct link* head;
};

struct list* list_create();
void list_free(struct list* list);
void list_insert(struct list* list, void* val);
void list_remove(struct list* list, void* val, int (*cmp)(void* a, void* b));
void list_remove_head(struct list* list);
int list_position(struct list* list, void* val, int (*cmp)(void* a, void* b));
void list_reverse(struct list* list);

#endif