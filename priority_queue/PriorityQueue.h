#ifndef __PQ_H
#define __PQ_H
#include "../dynamic_array/DynamicArray.h"
/*
 * Visualization tool for debugging min-heap: https://www.cs.usfca.edu/~galles/visualization/Heap.html
 */

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */

struct elements
{
    int priority;
    void* value;
};

struct pq
{
    struct dynarray* array;
};

struct pq* pq_create();
void pq_print_priority(struct pq* pq);
void pq_free(struct pq* pq);
int pq_isempty(struct pq* pq);
void pq_insert(struct pq* pq, void* value, int priority);
void* pq_first(struct pq* pq);
int pq_first_priority(struct pq* pq);
void* pq_remove_first(struct pq* pq);
struct pq* build_pq_from_dynarray(struct dynarray* arr);
void pq_heapsort(struct dynarray* arr);

#endif