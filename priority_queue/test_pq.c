/*
 * This is a small program to test your priority queue implementation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PriorityQueue.h"

/*
 * This is a comparison function to be used with qsort() to sort an array of
 * integers into ascending order.
 */
int ascending_int_cmp(const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

void test_build_pq_from_dynarray(int data[], int data_size) {
  struct pq* pq;
  struct dynarray* da = dynarray_create();
  printf("Original Array:\t\t");
  for (int i = 0; i < data_size; i++) {
    printf("%d ", data[i]);
    struct elements* curr_element = malloc(sizeof(struct elements));
    *curr_element = (struct elements){.priority = data[i], .value = &data[i]};
    dynarray_insert(da, curr_element);
  }
  if (dynarray_size(da) == 0) { printf("(Empty Array)"); }
  printf("\n");
  pq = build_pq_from_dynarray(da);
  printf("Current priority queue: ");
  pq_print_priority(pq);
  for (int i = 0; i < data_size; i++) {  free(dynarray_get(da, i));  }
  pq_free(pq);
}

void test_pq_heapsort(int data[], int data_size) {
  struct dynarray* da = dynarray_create();
  printf("Original Array:\t\t");
  for (int i = 0; i < data_size; i++) {
    printf("%d ", data[i]);
    struct elements* curr_element = malloc(sizeof(struct elements));
    *curr_element = (struct elements){.priority = data[i], .value = &data[i]};
    dynarray_insert(da, curr_element);
  }
  if (dynarray_size(da) == 0) { printf("(Empty Array)"); }
  printf("\n");
  pq_heapsort(da);
  printf("Sorting Result:\t\t");
  if (dynarray_size(da) > 0) {
    for (int i = 0; i < data_size; i++) {
      struct elements* curr_element = dynarray_get(da, i);
      printf("%d ", curr_element->priority); }
  } else { printf("(Empty Array)"); }
  printf("\n");
  for (int i = 0; i < data_size; i++) {  free(dynarray_get(da, i));  }
  dynarray_free(da);
}


int main(int argc, char** argv) {
  struct pq* pq;
  int* first, * removed;
  int i, k, p;
  const int n = 16, m = 16;
  int vals[n + m], sorted[n + m];

  /*
   * Seed the random number generator with a constant value, so it produces the
   * same sequence of pseudo-random values every time this program is run.
   */
  srand(0);

  /*
   * Create priority queue and insert pointers to pseudo-random integer values
   * into it with the same priority as the value.
   */
  pq = pq_create();
  printf("== Inserting some values into PQ\n");
  for (int i = 0; i < n; i++) {
    vals[i] = rand() % 64;
    pq_insert(pq, &vals[i], vals[i]);
  }

  /*
   * Make a copy of the random value array and sort it by ascending value.  We
   * make a copy here so we can maintain the original array in the same order,
   * thereby ensuring that pointer values stored in the priority queue always
   * point to the same integer values.
   */
  memcpy(sorted, vals, n * sizeof(int));
  qsort(sorted, n, sizeof(int), ascending_int_cmp);

  /*
   * Examine and remove half of the values currently in the PQ.
   */
  k = 0;
  printf("\n== Removing some from PQ: first / removed / priority (expected)\n");
  while (k < n / 2) {
    p = pq_first_priority(pq);
    first = pq_first(pq);
    removed = pq_remove_first(pq);
    if (first && removed) {
      printf("  - %4d / %4d / %4d (%4d)\n", *first, *removed, p, sorted[k]);
    } else {
      printf("  - (NULL) / (NULL) / %4d (%4d)\n", p, sorted[k]);
    }
    k++;
  }

  /*
   * Add a second set of pseudo-random integer values to the end of the array,
   * and add pointers to those values into the priority queue with the same
   * priority as the value.
   */
  printf("\n== Inserting more values into PQ\n");
  for (i = n; i < n + m; i++) {
    vals[i] = rand() % 64;
    pq_insert(pq, &vals[i], vals[i]);
  }

  /*
   * Copy the second array of random values to the end of the sorted array and
   * re-sort all of the the sorted array except the k values that were already
   * examined above (since they were already removed from the PQ, and we won't
   * see them again).  Again, we make a copy here so we can maintain the
   * original array in the same order, thereby ensuring that pointer values
   * stored in the priority queue always point to the same integer values.
   */
  memcpy(sorted + n, vals + n, m * sizeof(int));
  qsort(sorted + k, n - k + m, sizeof(int), ascending_int_cmp);

  printf("\n== Removing remaining from PQ: first / removed / priority (expected)\n");
  while (k < n + m && !pq_isempty(pq)) {
    p = pq_first_priority(pq);
    first = pq_first(pq);
    removed = pq_remove_first(pq);
    if (first && removed) {
      printf("  - %4d / %4d / %4d (%4d)\n", *first, *removed, p, sorted[k]);
    } else {
      printf("  - (NULL) / (NULL) / %4d (%4d)\n", p, sorted[k]);
    }
    k++;
  }

  printf("\n== Is PQ empty (expect 1)? %d\n", pq_isempty(pq));
  printf("== Did we see all values we expected (expect 1)? %d\n", k == m + n);
  pq_free(pq);

  /*
   * Check build_heap_from_dynarray
   */
  {
    printf("\n== Testing function build_heap_from_dynarray\n");
    int TEST_ARR1[9] = {32, 12, 2, 8, 16, 20, 24, 40, 4};
    test_build_pq_from_dynarray(TEST_ARR1, 9);
    printf("(Expected Output)       2 4 20 8 16 32 24 40 12 \n");
    int TEST_ARR2[7] = {500, 20, 6, 200, 90, 150, 300};
    test_build_pq_from_dynarray(TEST_ARR2, 7);
    printf("(Expected Output)       6 20 100 200 90 150 300 \n");
    int TEST_ARR3[0] = {};
    test_build_pq_from_dynarray(TEST_ARR3, 0);
    printf("(Expected Output)       (Empty Queue)\n");
    int TEST_ARR4[1] = {0};
    test_build_pq_from_dynarray(TEST_ARR4, 1);
    printf("(Expected Output)       1\n");
    int TEST_ARR5[3] = {8, 7, 2};
    test_build_pq_from_dynarray(TEST_ARR5, 3);
    printf("(Expected Output)       8 7 2\n");
    int TEST_ARR6[4] = {3, 2, 6, 2};
    test_build_pq_from_dynarray(TEST_ARR6, 4);
    printf("(Expected Output)       2 2 6 3\n");
  }

  /*
   * Check pq_heapsort
   */
  {
    printf("\n== Testing function pq_heapsort\n");
    int TEST_ARR1[7] = {100, 20, 6, 200, 90, 150, 300};
    test_pq_heapsort(TEST_ARR1, 7);
    printf("(Expected Output)       300 200 150 100 90 20 6\n");
    int TEST_ARR2[10] = {3, 4, 7, 12, 13, 16, 17, 18, 19, 20};
    test_pq_heapsort(TEST_ARR2, 10);
    printf("(Expected Output)       20 19 18 17 16 13 12 7 4 3\n");
    int TEST_ARR3[0] = {};
    test_pq_heapsort(TEST_ARR3, 0);
    printf("(Expected Output)       (Empty Array)\n");
    int TEST_ARR4[1] = {0};
    test_pq_heapsort(TEST_ARR4, 1);
    printf("(Expected Output)       0\n");
    int TEST_ARR5[2] = {1, 2};
    test_pq_heapsort(TEST_ARR5, 2);
    printf("(Expected Output)       2 1\n");
    int TEST_ARR6[11] = {-9, 3, 2, 6, 2, 3, 1, 7, 2, 7, -9};
    test_pq_heapsort(TEST_ARR6, 11);
    printf("(Expected Output)       7 7 6 3 3 2 2 2 1 -9 -9\n");
  }
  return 0;

}
