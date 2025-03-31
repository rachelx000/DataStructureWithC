#ifndef __DYNARRAY_H
#define __DYNARRAY_H

/*
 * This is the definition of the dynamic array structure you'll use for your
 * implementation.  Importantly, your dynamic array implementation will store
 * each data element as a void* value.  This will permit data of any type to
 * be stored in your array.  Because each individual element will be stored in
 * your array as type void*, the data array needs to be an array of void*.
 * Hence it is of type void**.
 *
 * You should not modify this structure.
 */

struct dynarray
{
    void** data;
    int start;
    int size;
    int capacity;
};

struct dynarray* dynarray_create();
void dynarray_free(struct dynarray* da);
int dynarray_size(struct dynarray* da);
int dynarray_start(struct dynarray* da);
void dynarray_insert(struct dynarray* da, void* val);
void dynarray_insert_at_index(struct dynarray* da, int idx, void* val);
void dynarray_remove(struct dynarray* da, int idx);
void* dynarray_get(struct dynarray* da, int idx);
void dynarray_set(struct dynarray* da, int idx, void* val);
void* dynarray_remove_start(struct dynarray* da);
void* dynarray_get_for_queue(struct dynarray* da, int idx);

#endif