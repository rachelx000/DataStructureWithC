#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"
#include "../dynamic_array/DynamicArray.h"

/*
 * This function should allocate and initialize a new, empty queue and return
 * a pointer to it.
 */
struct queue* queue_create(){
    struct queue* new_queue = malloc(sizeof(struct queue));
    if (!new_queue) {
        printf("Memory allocation failed for the new queue!\n");
        exit(1);
    }
    new_queue->array = dynarray_create();
    return new_queue;
}

/*
 * This function should free the memory associated with a queue.  While this
 * function should up all memory used in the queue itself, it should not free
 * any memory allocated to the pointer values stored in the queue.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   queue - the queue to be destroyed.  May not be NULL.
 */
void queue_free(struct queue* queue){
    if (queue) {
        dynarray_free(queue->array);
        free(queue);
    }
    else {
        printf("Invalid queue!\n");
        exit(1);
    }
}

/*
 * This function should indicate whether a given queue is currently empty.
 * Specifically, it should return 1 if the specified queue is empty (i.e.
 * contains no elements) and 0 otherwise.
 *
 * Params:
 *   queue - the queue whose emptiness is being questioned.  May not be NULL.
 */
int queue_isempty(struct queue* queue) {
    if (queue) {
        return dynarray_size(queue->array)==0 ? 1 : 0;
    }
    else {
        printf("Invalid queue!\n");
        exit(1);
    }
};

/*
 * This function should enqueue a new value into a given queue.  The value to
 * be enqueued is specified as a void pointer.  This function must have O(1)
 * average runtime complexity.
 *
 * Params:
 *   queue - the queue into which a value is to be enqueued.  May not be NULL.
 *   val - the value to be enqueued.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void queue_enqueue(struct queue* queue, void* val){
    if (queue) {
        int idx = (dynarray_start(queue->array) + dynarray_size(queue->array)) % queue->array->capacity;
        dynarray_insert_at_index(queue->array, idx, val);
    }
    else {
        printf("Invalid queue!\n");
        exit(1);
    }
}

/*
 * This function should return the value stored at the front of a given queue
 * *without* removing that value.  This function must have O(1) average runtime
 * complexity.
 *
 * Params:
 *   queue - the queue from which to query the front value.  May not be NULL.
 */
void* queue_front(struct queue* queue){
    if (queue_isempty(queue)) {
      printf("Alert: Attempt to access the front of an empty queue!\n");
      return NULL;
    }
    else { return dynarray_get_for_queue(queue->array, dynarray_start(queue->array)); }
}

/*
 * This function should dequeue a value from a given queue and return the
 * dequeued value.  This function must have O(1) average runtime complexity.
 *
 * Params:
 *   queue - the queue from which a value is to be dequeued.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was dequeued.
 */
void* queue_dequeue(struct queue* queue){
    if (queue) {
        if (queue_isempty(queue)) {
            printf("Alert: Attempt to dequeue an empty queue.\n");
            return NULL;
        } else {
            void* deq_val = dynarray_remove_start(queue->array);
            return deq_val;
        }
    }
    else {
        printf("Invalid queue!\n");
        exit(1);
    }
}