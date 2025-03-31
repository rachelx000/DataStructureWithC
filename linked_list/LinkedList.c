#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

/*
 * This function should allocate and initialize a new, empty linked list and
 * return a pointer to it.
 */
struct list* list_create() {
  struct list* new_list = malloc(sizeof(struct list));
  if (!new_list) {
    printf("Memory allocation failed for a new linked list!\n");
    exit(1);
  }
  new_list->head = NULL;
  return new_list;
}

/*
 * This function should free the memory associated with a linked list.  In
 * particular, while this function should up all memory used in the list
 * itself (i.e. the space allocated for all of the individual links), it should
 * not free any memory allocated to the pointer values stored in the list.  In
 * other words, this function does not need to free the `val` fields of the
 * list's links.
 *
 * Params:
 *   list - the linked list to be destroyed.  May not be NULL.
 */
void list_free(struct list* list) {
  struct link* curr_link = list->head;
  struct link* next_link;
  while (curr_link) {
    next_link = curr_link->next;
    free(curr_link);
    curr_link = next_link;
  }
  free(list);
}

/*
 * This function should insert a new value into a given linked list.
 * Importantly, this function will need to allocate a new `struct link` in
 * which to store the new value and add that link at the head of the list.  For
 * simplicity, this function should only insert elements at the *beginning* of
 * the list.  In other words, it should always insert the new element as the
 * head of the list.
 *
 * Params:
 *   list - the linked list into which to insert an element.  May not be NULL.
 *   val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void list_insert(struct list* list, void* val) {
  // Create a new link and store the value
  struct link* new_link = malloc(sizeof(struct link));
  if (!new_link) {
    printf("Memory allocation failed for a new link!\n");
    list_free(list);
    exit(1);
  }
  new_link->val = val;
  // Add the new link to the head of list
  new_link->next = list->head;
  list->head = new_link;
}

/*
 * This function should remove an element with a specified value from a given
 * linked list.  Importantly, if the specified value appears multiple times in
 * the list, the function should only remove the *first* instance of that
 * value (i.e. the one nearest to the head of the list).  For example, if a
 * list stores pointers to integers and contains two instances of the value 4,
 * only the first of those values should be removed, and the other one should
 * remain in the list.  Importantly, this function will also need to free the
 * memory held by the link being removed (it does not need to free the stored
 * value itself, just the link).
 *
 * This function will be passed a *function pointer* called `cmp` that you
 * should use to compare the value `val` to be removed with the values stored
 * in the list to determine which element (if any) to remove.  The cmp function
 * (which will be passed to list_remove() when it's called, so you don't have
 * to worry about writing it yourself) should be passed two void* values,
 * `val` and a value stored in the list against which to compare `val`.  If
 * the two values should be considered as equal, then the function will return
 * 0, and if the two values should be considered as not equal, then the
 * function will return a non-zero value.  For example, part of your code here
 * might look something like this (assuming you're comparing `val` to the `val`
 * field of a specific list link):
 *
 * if (cmp(val, link->val) == 0) {
 *   // Remove link from the list.
 * }
 *
 * For more on function pointers, refer to this tutorial:
 *   https://www.cprogramming.com/tutorial/function-pointers.html
 *
 * Params:
 *   list - the linked list from which to remove an element.  May not be NULL.
 *   val - the value to be removed.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 *   cmp - pointer to a function that can be passed two void* values from
 *     to compare them for equality, as described above.  If the two values
 *     passed are to be considered equal, this function should return 0.
 *     Otherwise, it should return a non-zero value.
 */
void list_remove(struct list* list, void* val, int (*cmp)(void* a, void* b)) {
  struct link* prev_link = NULL;
  struct link* curr_link = list->head;
  while (curr_link) {
    if (cmp(curr_link->val, val) == 0){
      if (!prev_link) { list->head = curr_link->next; }
      else { prev_link->next = curr_link->next; }
      free(curr_link);
      return;
    }
    prev_link = curr_link;
    curr_link = curr_link->next;
  }
  printf("Alert: No Target Element Stored in the list!\n");
}

/* This function should remove the head of a given linked list and free the
 * memory held by the head link being removed
*
 * Params:
 *   list - the linked list from which to remove an element.  May not be NULL.
 * */

void list_remove_head(struct list* list) {
  if (list->head) {
    struct link* curr_head = list->head;
    struct link* new_head = curr_head->next;
    list->head = new_head;
    free(curr_head);
  }
  else {
    printf("The linked list has an empty head.\n");
  }
}

/*
 * This function should return the position (i.e. the 0-based "index") of the
 * first instance of a specified value within a given linked list.  For
 * example, if the list contains the specified in the 4th and 8th links
 * starting at the head, then this function should return 3 (the 0-based
 * "index" of the 4th link.).  If the value is contained in the head link,
 * then this function should return 0 (the 0-based index of the head link).
 * If the list does not contain the specified value, then this function should
 * return the special value -1.
 *
 * This function will be passed a *function pointer* called `cmp` that you
 * should use to compare the value `val` to be located with the values stored
 * in the list to determine which link (if any) contains `val`.  The cmp
 * function (which will be passed to list_remove() when it's called, so you
 * don't have to worry about writing it yourself) should be passed two void*
 * values, `val` and a value stored in the list against which to compare `val`.
 * If the two values should be considered as equal, then the cmp function will
 * return 0, and if the two values should be considered as not equal, then the
 * cmp function will return a non-zero value.  For example, part of your code
 * here might look something like this (assuming you're comparing `val` to the
 * `val` field of a specific list link):
 *
 * if (cmp(val, link->val) == 0) {
 *   // Return the position of link.
 * }
 *
 * For more on function pointers, refer to this tutorial:
 *   https://www.cprogramming.com/tutorial/function-pointers.html
 *
 * Params:
 *   list - the linked list from which to remove an element.  May not be NULL.
 *   val - the value to be located.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 *   cmp - pointer to a function that can be passed two void* values from
 *     to compare them for equality, as described above.  If the two values
 *     passed are to be considered equal, this function should return 0.
 *     Otherwise, it should return a non-zero value.
 *
 * Return:
 *   This function should return the 0-based position of the first instance of
 *   `val` within `list`, as determined by the function `cmp` (i.e. the closest
 *    such instance to the head of the list) or -1 if `list` does not contain
 *    the value `val`.
 */
int list_position(struct list* list, void* val, int (*cmp)(void* a, void* b)) {
  int idx = 0;
  struct link* curr_link = list->head;
  while (curr_link) {
    if (cmp(curr_link->val, val) == 0){ return idx; }
    curr_link = curr_link->next;
    idx++;
  }
  return -1;
}

/*
 * This function should reverse the order of the links in a given linked list.
 * The reversal should be done *in place*, i.e. within the existing list, and
 * new memory should not be allocated to accomplish the reversal.  You should
 * be able to accomplish the reversal with a single pass through the list.
 *
 * Params:
 *   list - the linked list to be reversed.  May not be NULL.  When this
 *     function returns this should contain the reversed list.
 */
void list_reverse(struct list* list) {
  struct link* prev_link = NULL;
  struct link* curr_link = list->head;
  struct link* next_link;
  while (curr_link) {
    next_link = curr_link->next;
    if (!prev_link) { curr_link->next = NULL; }
    else { curr_link->next = prev_link; }
    prev_link = curr_link;
    curr_link = next_link;
  }
  list->head = prev_link;
}