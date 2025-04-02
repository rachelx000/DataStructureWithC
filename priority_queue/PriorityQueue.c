#include <stdlib.h>
#include <stdio.h>
#include "PriorityQueue.h"

/*
 * Helper function for debugging to print all the priority values from the start
 * to the end in the dynamic array for the priority queue
 */
void pq_print_priority(struct pq* pq) {
    if (pq_isempty(pq)) {
        printf("(Empty Queue) \n");
        return;
    }
    for (int i = 0; i < dynarray_size(pq->array); i++) {
        struct elements* curr_element = dynarray_get(pq->array, i);
        printf("%d ", curr_element->priority);
    }
    printf("\n");
}

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
    struct pq* new_pq = malloc(sizeof(struct pq));
    if (!new_pq) {
        printf("Error: Memory allocation to new priority queue failed!\n");
        exit(1);
    }
    new_pq->array = dynarray_create();
    return new_pq;
}

/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq){
    if (pq) {
        dynarray_free(pq->array);
        free(pq);
    } else {
        printf("Invalid priority queue to be removed!\n");
        exit(1);
    }
}

/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
    if (dynarray_size(pq->array) == 0) { return 1; }
    else { return 0; }
}

/*
 * Helper function to swap two elements in the dynamic priority queue at the given indices
 */
void __swap(struct dynarray* arr, int ind1, int ind2)   {
    struct elements* element1 = dynarray_get(arr, ind1);
    struct elements* element2 = dynarray_get(arr, ind2);
    dynarray_set(arr, ind1, element2);
    dynarray_set(arr, ind2, element1);
}

/*
 * Helper function for pq_insert that percolate the newly inserted element up
 * in the dynamic array for the priority queue to maintain the min-heap property
 */
void __percolate_up(struct dynarray* arr, int priority) {
    int new_element_index = dynarray_size(arr)-1;
    int parent_index;
    struct elements* parent;
    while (new_element_index > 0) {
        // swap the two elements until to maintain the min-heap priorty until reaching
        // the beginning of the array
        parent_index = (new_element_index-1) / 2;
        parent = dynarray_get(arr, parent_index);
        if (priority >= parent->priority) { break; }
        else { __swap(arr, parent_index, new_element_index); }
        new_element_index = parent_index;
    }
}

/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
    // initialize the queue element
    struct elements* new_element = malloc(sizeof(struct elements));
    if (!new_element) {
        printf("Error: Memory allocation to new priority queue element failed!\n");
        pq_free(pq);
        exit(1);
    }
    *new_element = (struct elements){.priority = priority, .value=value};

    // insert the new element to the end of the array
    dynarray_insert(pq->array, new_element);
    // printf("\n==Insert element with priority: %d\n", priority);
    //pq_print_priority(pq);
    __percolate_up(pq->array, priority);
    // printf("[After percolate_up]\n");
    // pq_print_priority(pq);
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
    if (pq_isempty(pq)) {
        printf("Error: Attempt to access the root of an empty priorty queue!\n");
        pq_free(pq);
        exit(1);
    }
    struct elements* first = dynarray_get(pq->array, 0);
    return first->value;
}

/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
    if (pq_isempty(pq)) {
        printf("Error: Attempt to access the root of an empty priorty queue!\n");
        pq_free(pq);
        exit(1);
    }
    struct elements* first = dynarray_get(pq->array, 0);
    return first->priority;
}

/*
 * Helper function for percolating down the element at a given index in the dynamic
 * array for the priority queue to maintain the min-heap property
 */
void __percolate_down(struct dynarray* arr, int ind) {
    struct elements* target = dynarray_get(arr, ind);
    struct elements* left_child;
    struct elements* right_child;
    int curr_index = ind;
    int left_child_index = 2*curr_index+1;
    int right_child_index = 2*curr_index+2;
    int size = dynarray_size(arr);
    while (left_child_index < size) {
        // swap the two elements until to maintain the min-heap priorty until reaching
        // the beginning of the array
        left_child = dynarray_get(arr, left_child_index);
        right_child = (right_child_index < size) ? dynarray_get(arr, right_child_index) : NULL;
        if (!right_child) {
            // if there is only one child
            if (target->priority >= left_child->priority) {
                __swap(arr, curr_index, left_child_index);
                curr_index = left_child_index;
            } else { break; }
        } else {
            // if there are two children
            if (left_child->priority < right_child->priority && target->priority > left_child->priority) {
                __swap(arr, curr_index, left_child_index);
                curr_index = left_child_index;
            }
            else if (left_child->priority >= right_child->priority && target->priority > right_child->priority) {
                __swap(arr, curr_index, right_child_index);
                curr_index = right_child_index;
            } else { break; }
        }
        left_child_index = 2*curr_index+1;
        right_child_index = 2*curr_index+2;
    }
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
    void* removed_val = pq_first(pq);       // value of the first item (root)

    // printf("\n==Before removal of the root: %d\n", pq_first_priority(pq));
    // pq_print_priority(pq);

    int size = dynarray_size(pq->array);
    if ( size > 1 ) {
        // swap the last item with the root
        __swap(pq->array, 0, size-1);
    }

    // printf("[After swapping the root with the last element]\n");
    // pq_print_priority(pq);

    // remove the last item from memory and free the allocated memory
    struct elements* removed_element = dynarray_get(pq->array, size-1);
    dynarray_remove(pq->array, size-1);
    free(removed_element);

    // printf("[After removing the root (located at the end of the array now)]\n");
    // printf("Current Size = %d, ", dynarray_size(pq->array));
    // pq_print_priority(pq);

    // if there are more than one elements left in the array, percolate
    // down the new root to maintain the min-heap property
    if (dynarray_size(pq->array) > 1) { __percolate_down(pq->array, 0); }

    // printf("[After percolating down the new root)]\n");
    // pq_print_priority(pq);

    return removed_val;
}

/*
 * This function should create a priority queue from a given dynamic array in O(n)
 *
 * Params:
 *   arr - the dynamic array of elements that is used to build the priority queue.
 *     May not be NULL or empty.
 *   pq - the pointer to the target priority queue
 *
 * Return:
 *   Should return a pointer to the created priority queue
 */
struct pq* build_pq_from_dynarray(struct dynarray* arr) {
    if (arr) {
        struct pq* new_pq = malloc(sizeof(struct pq));
        new_pq->array = arr;
        if (dynarray_size(arr)>3) {
            // perform percolation down starting from the first non-leaf element
            int non_leaf_index = dynarray_size(new_pq->array)/2 - 1;
            for (int i = non_leaf_index ; i >= 0; i--) {
                  __percolate_down(arr, i);
            }
        }
        return new_pq;
    } else {
        printf("Error: Invalid array that is used to build the priority queue!\n");
        exit(1);
    }
}

/*
 * Helper function for percolating down the element at a given index before the k index
 * in the dynamic array for the priority queue to maintain the min-heap property
 */
void __percolate_down_with_k(struct dynarray* arr, int ind, int k) {
    struct elements* target = dynarray_get(arr, ind);
    struct elements* left_child;
    struct elements* right_child;
    int curr_index = ind;
    int left_child_index = 2*curr_index+1;
    int right_child_index = 2*curr_index+2;
    while (left_child_index <= k) {
        // swap the two elements until to maintain the min-heap priorty until reaching
        // the beginning of the array
        left_child = dynarray_get(arr, left_child_index);
        right_child = (right_child_index <= k) ? dynarray_get(arr, right_child_index) : NULL;
        if (!right_child) {
            // if there is only one child
            if (target->priority >= left_child->priority) {
                __swap(arr, curr_index, left_child_index);
                curr_index = left_child_index;
            } else { break; }
        } else {
            // if there are two children
            if (left_child->priority < right_child->priority && target->priority > left_child->priority) {
                __swap(arr, curr_index, left_child_index);
                curr_index = left_child_index;
            }
            else if (left_child->priority >= right_child->priority && target->priority > right_child->priority) {
                __swap(arr, curr_index, right_child_index);
                curr_index = right_child_index;
            } else { break; }
        }
        left_child_index = 2*curr_index+1;
        right_child_index = 2*curr_index+2;
    }
}

/*
 * This function should perform sorting on a given dynamic array to an descending order
 * using the priority queue with a min-heap in O(nlogn)
 *
 * Params:
 *   arr - the pointer to dynamic array of elements to be sorted. May not be NULL or empty.
 *
 * Return: the pointer to the sorted array of elements. May not be NULL or empty.
 */
void pq_heapsort(struct dynarray* arr) {
    if (arr) {
        struct pq* pq;
        // build a min-heap from the array
        pq = build_pq_from_dynarray(arr);

        int k = dynarray_size(pq->array)-1;
        // printf("Heap Before Sorting:\t");
        // pq_print_priority(pq);
        while (k > 0) {
            // swap the min-priority element with the last element
            __swap(pq->array, 0, k);
            // shrink the heap portion using the indicator k
            k -= 1;
            // percolate down the new root in the heap portion
            __percolate_down_with_k(pq->array, 0, k);
        }
        free(pq);
    } else {
        printf("Error: Invalid array that is used to build the priority queue!\n");
        exit(1);
    }
}
