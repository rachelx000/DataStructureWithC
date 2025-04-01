#ifndef __QUEUE_H
#define __QUEUE_H

/*
 * This is the structure that will be used to represent a queue.  This
 * structure specifically contains a single field representing a dynamic array
 * that should be used as the underlying data storage for the queue.
 *
 * You should not modify this structure.
 */
struct queue
{
    struct dynarray* array;
};

struct queue* queue_create();
void queue_free(struct queue* queue);
int queue_isempty(struct queue* queue);
void queue_enqueue(struct queue* queue, void* val);
void* queue_front(struct queue* queue);
void* queue_dequeue(struct queue* queue);

#endif