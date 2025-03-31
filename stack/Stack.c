#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"
#include "../linked_list/LinkedList.h"

/*
 * This is the structure that will be used to represent a stack.  This
 * structure specifically contains a single field representing a linked list
 * that should be used as the underlying data storage for the stack.
 *
 * You should not modify this structure.
 */
struct stack
{
    struct list* list;
};

/*
 * This function should allocate and initialize a new, empty stack and return
 * a pointer to it.
 */
struct stack* stack_create()
{
    struct stack* new_stack = malloc(sizeof(struct stack));
    if (!new_stack) {
        printf("Memory allocation failed for a new stack!\n");
        exit(1);
    }
    new_stack->list = list_create();
    return new_stack;
}

/*
 * This function should free the memory associated with a stack.  While this
 * function should up all memory used in the stack itself, it should not free
 * any memory allocated to the pointer values stored in the stack.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   stack - the stack to be destroyed.  May not be NULL.
 */
void stack_free(struct stack* stack){
  if (stack) {
    list_free(stack->list);
    free(stack);
  }
  else {
    printf("Invalid stack!\n");
    exit(1);
  }
}

/*
 * This function should indicate whether a given stack is currently empty.
 * Specifically, it should return 1 if the specified stack is empty (i.e.
 * contains no elements) and 0 otherwise.
 *
 * Params:
 *   stack - the stack whose emptiness is being questioned.  May not be NULL.
 */
int stack_isempty(struct stack* stack) {
    if (!stack->list->head) { return 1; }
    else { return 0; }
}

/*
 * This function should push a new value onto a given stack.  The value to be
 * pushed is specified as a void pointer.  This function must have O(1)
 * average runtime complexity.
 *
 * Params:
 *   stack - the stack onto which a value is to be pushed.  May not be NULL.
 *   val - the value to be pushed.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void stack_push(struct stack* stack, void* val){
    if (stack) {
        list_insert(stack->list, val);
    }
    else {
        printf("invalid stack!\n");
        exit(1);
    }
}

/*
 * This function should return the value stored at the top of a given stack
 * *without* removing that value.  This function must have O(1) average runtime
 * complexity.
 *
 * Params:
 *   stack - the stack from which to query the top value.  May not be NULL.
 */
void* stack_top(struct stack* stack){
    if (stack) {
        if (stack_isempty(stack)) {
            printf("Alert: Accessing the top of an empty stack!\n");
            return NULL;
        }
        else { return stack->list->head->val; }
    }
    else {
        printf("invalid stack!\n");
        exit(1);
    }
}

/*
 * This function should pop a value from a given stack and return the popped
 * value.  This function must have O(1) average runtime complexity.
 *
 * Params:
 *   stack - the stack from which a value is to be popped.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was popped.
 */
void* stack_pop(struct stack* stack) {
    if (stack_isempty(stack)) {
        printf("Error: There is no element that can be popped in the stack!\n");
        stack_free(stack);
        exit(1);
    }
    else {
        void* popped_val = stack_top(stack);
        list_remove_head(stack->list);
        return popped_val;
    }
}
