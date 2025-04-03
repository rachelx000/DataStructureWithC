#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLTree.h"
#include "test_avl.h"

/*
 * This is a helper function that's used to compare integers when sorting with
 * qsort().
 */
int cmp_ints(const void* a, const void* b) {
  return *(int*)a - *(int*)b;
}

int remove_duplicates(int data[], int data_size) {
  if (data_size == 0 || data_size == 1) {
    return data_size;
  }

  int j = 0;
  for (int i = 0; i < data_size-1; i++) {
    if (data[i] != data[i + 1]) { data[j] = data[i]; j++; }
  }
  data[j] = data[data_size-1];
  return j+1;
}

void test_avl_insert(int data[], int data_size) {
  printf("Array Size: %d, Input Array:\t\t", data_size);
  struct avl* avl = avl_create();
  for (int i = 0; i < data_size; i++) {
    printf("%d ", data[i]);
    avl_insert(avl, data[i], &data[i]);
  }
  printf("\nDFS Size: %d, ", avl_size(avl));
  avl_DFS(avl);
  /*
   * Test that we *can't* successfully find any values we know shouldn't be in
   * the AVL tree. To do this, create a sorted copy of the test data without duplicates
   * that will allow us to more easily determine which values shouldn't be in the AVL.
   */
  int* sorted = malloc(data_size * sizeof(int));
  memcpy(sorted, data, data_size*sizeof(int));
  qsort(sorted, data_size, sizeof(int), cmp_ints);
  int new_data_size = remove_duplicates(sorted, data_size);
  printf("== Looking up values we know should NOT be in the AVL tree...\n");
  for (int i = sorted[0], k = 0; i <= sorted[new_data_size-1]; i++) {
    if (i == sorted[k]) {
      /*
       * If i is equal to a key we know is in the AVL, skip it.
       */
      k++;
    } else if (avl_get(avl, i) != NULL) {
      printf("  -- avl_get(%3d) unexpectedly returned a non-NULL value\n", i);
    }
  }

  // free allocated memory
  avl_free(avl);
  free(sorted);
}

void __print_avl_tree(struct avl* avl) {
  printf("[Size: %d], ", avl_size(avl));
  if (avl_size(avl)) {
    avl_DFS(avl);
    // avl_DFS_detailed(avl);  // For DEBUG
  }
  else { printf("Pre-order DFS Traversal:\t(Empty)\n"); }
}

void test_avl_remove(int data[], int data_size, const char* example_output[]) {
  printf("== Inserting %d elements into from the input array into the AVL tree...\n", data_size);
  printf("Array Size: %d, Input Array:\t\t", data_size);
  struct avl* avl = avl_create();
  for (int i = 0; i < data_size; i++) {
    printf("%d ", data[i]);
    avl_insert(avl, data[i], &data[i]);
  }
  printf("\n== AVL Tree Before removing...\n");
  __print_avl_tree(avl);
  printf("%s\n", example_output[0]);
  for (int i = 0, j = 1; i < data_size; i++, j++) {
    printf("\nRemoving... %d\n", data[i]);
    avl_remove(avl, data[i]);
    __print_avl_tree(avl);
    printf("%s\n", example_output[j]);
  }

  // free allocated memory
  avl_free(avl);
}

void test_avl_remove_one_element(int data[], int data_size, int target) {
  printf("Array Size: %d, Input Array:\t\t", data_size);
  struct avl* avl = avl_create();
  for (int i = 0; i < data_size; i++) {
    printf("%d ", data[i]);
    avl_insert(avl, data[i], &data[i]);
  }
  printf("\n");
  __print_avl_tree(avl);
  printf("Removing... %d\n", target);
  avl_remove(avl, target);
  __print_avl_tree(avl);

  // free allocated memory
  avl_free(avl);
}

void test_avl_remove_with_order(int data[], int data_size, int order[], int order_size, const char* example_output[]) {
  printf("Array Size: %d, Input Array:\t\t", data_size);
  struct avl* avl = avl_create();
  for (int i = 0; i < data_size; i++) {
    printf("%d ", data[i]);
    avl_insert(avl, data[i], &data[i]);
  }

  printf("\n== AVL Tree Before removing...\n");
  __print_avl_tree(avl);
  printf("%s\n", example_output[0]);
  for (int i = 0, j=1; i < order_size; i++, j++) {
    printf("\nRemoving... %d\n", order[i]);
    avl_remove(avl, order[i]);
    __print_avl_tree(avl);
    printf("%s\n", example_output[j]);
  }

  // free allocated memory
  avl_free(avl);
}

int main() {
  /*
   * Testing AVL's functionality of inserting nodes and self-rebalancing
   */
  {
    printf("============ Testing avl_insert ============\n");
    printf("------------    Base cases      ------------\n");
    printf("\n== Test Case #1: RR (Expect: 2 1 3)\n");
    int TEST_ARR[3] = {1, 2, 3};   // RR
    test_avl_insert(TEST_ARR, 3);
    printf("\n== Test Case #2: LL (Expect: 2 1 3)\n");
    int TEST_ARR2[3] = {3, 2, 1};   // LL
    test_avl_insert(TEST_ARR2, 3);
    printf("\n== Test Case #3: RL (Expect: 2 1 3)\n");
    int TEST_ARR3[3] = {1, 3, 2};   // RL
    test_avl_insert(TEST_ARR3, 3);
    printf("\n== Test Case #4: LR (Expect: 2 1 3)\n");
    int TEST_ARR4[3] = {3, 1, 2};   // LR
    test_avl_insert(TEST_ARR4, 3);

    printf("\n------------    More cases      ------------\n");
    printf("\n== Test Case #5\n");
    int TEST_ARR5[5] = {10, 20, 30, 40, 50};
    test_avl_insert(TEST_ARR5, 5);
    printf("Expected Pre-order DFS Traversal:\t20 10 40 30 50\n");
    printf("\n== Test Case 6\n");
    int TEST_ARR6[6] = {10, 20, 30, 50, 40};
    test_avl_insert(TEST_ARR6, 5);
    printf("Expected Pre-order DFS Traversal:\t20 10 40 30 50\n");
    printf("\n== Test Case 7\n");
    int TEST_ARR7[5] = {30, 20, 10, 5, 1};
    test_avl_insert(TEST_ARR7, 5);
    printf("Expected Pre-order DFS Traversal:\t20 5 1 10 30\n");
    printf("\n== Test Case 8\n");
    int TEST_ARR8[5] = {30, 20, 10, 1, 5};
    test_avl_insert(TEST_ARR8, 5);
    printf("Expected Pre-order DFS Traversal:\t20 5 1 10 30\n");
    printf("\n== Test Case 9\n");
    int TEST_ARR9[7] = {5, 4, 6, 3, 7, 2, 8};
    test_avl_insert(TEST_ARR9, 7);
    printf("Expected Pre-order DFS Traversal:\t5 3 2 4 7 6 8 \n");
    printf("\n== Test Case 10\n");
    int TEST_ARR10[10] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27};
    test_avl_insert(TEST_ARR10, 10);
    printf("Expected Pre-order DFS Traversal:\t9 3 0 6 21 15 12 18 24 27\n");
    printf("\n== Test Case 11\n");
    int TEST_ARR11[11] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30};
    test_avl_insert(TEST_ARR11, 11);
    printf("Expected Pre-order DFS Traversal:\t9 3 0 6 21 15 12 18 27 24 30\n");
    printf("\n== Test Case 12\n");
    int TEST_ARR12[12] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33};
    test_avl_insert(TEST_ARR12, 12);
    printf("Expected Pre-order DFS Traversal:\t21 9 3 0 6 15 12 18 27 24 30 33\n");
    printf("\n== Test Case 13\n");
    int TEST_ARR13[10] = {10, 8, 6, 4, 2, 0, -2, -4, -6, -8};
    test_avl_insert(TEST_ARR13, 10);
    printf("Expected Pre-order DFS Traversal:\t4 -4 -6 -8 0 -2 2 8 6 10\n");
    int TEST_ARR14[12] = {3, 2, 1, 1, 2, 0, 3, 0, 1, 0, 3, 3};
    test_avl_insert(TEST_ARR14, 12);
    printf("Expected Pre-order DFS Traversal:\t2 1 0 0 0 1 1 3 2 3 3 3\n");
  }
  {
    printf("\n============ Testing avl_remove ============\n");
    printf("------------    Base cases      ------------\n");
    {
      printf("\n== Test Case #1: RR\n");
      int TEST_ARR[8] = {50, 40, 60, 30, 70, 20, 80, 45};   // RR
      test_avl_remove_one_element(TEST_ARR, 8, 20);
      printf("Expected Pre-order DFS Traversal:\t50 40 30 45 70 60 80\n");
      printf("\n== Test Case #2: LL\n");
      int TEST_ARR1[8] = {50, 40, 60, 30, 70, 20, 80, 15};   // RR
      test_avl_remove_one_element(TEST_ARR1, 8, 40);
      printf("Expected Pre-order DFS Traversal:\t50 20 15 30 70 60 80\n");
      printf("\n== Test Case #3: RL\n");
      int TEST_ARR2[8] = {50, 40, 60, 30, 70, 20, 80, 35};   // RR
      test_avl_remove_one_element(TEST_ARR2, 8, 20);
      printf("Expected Pre-order DFS Traversal:\t50 35 30 40 70 60 80\n");
      printf("\n== Test Case #4: LR\n");
      int TEST_ARR3[8] = {50, 40, 60, 30, 70, 20, 80, 25};   // RR
      test_avl_remove_one_element(TEST_ARR3, 8, 40);
      printf("Expected Pre-order DFS Traversal:\t50 25 20 30 70 60 80\n");
      printf("\n== Test Case #5: non-existed element\n");
      test_avl_remove_one_element(TEST_ARR, 8, 0);
      printf("Expected Pre-order DFS Traversal:\t50 30 20 40 45 70 60 80\n");
    }
    printf("\n------------    More cases      ------------\n");
    {
      printf("\n== Test Case #1:\n");
      int TEST_ARR[3] = {1, 2, 3};   // RR
      test_avl_remove(TEST_ARR, 3, REMOVE_CASE1_EXPECTED_OUTPUT);
      printf("\n== Test Case #2:\n");
      int TEST_ARR2[3] = {3, 2, 1};   // LL
      test_avl_remove(TEST_ARR2, 3, REMOVE_CASE2_EXPECTED_OUTPUT);
      printf("\n== Test Case #3:\n");
      int TEST_ARR3[3] = {2, 3, 1};
      test_avl_remove(TEST_ARR3, 3, REMOVE_CASE3_EXPECTED_OUTPUT);
      printf("\n== Test Case #4:\n");
      int TEST_ARR4[8] = {50, 30, 20, 40, 45, 70, 60, 80};
      test_avl_remove(TEST_ARR4, 8, REMOVE_CASE4_EXPECTED_OUTPUT);
      printf("\n== Test Case #5:\n");
      int TEST_ARR5[13] = {-9, -7, -5, -3, -1, 1, 3, 5, 7, 9, 11, 13, 15};
      test_avl_remove(TEST_ARR5, 13, REMOVE_CASE5_EXPECTED_OUTPUT);
      printf("\n== Test Case #6:\n");
      int TEST_ARR6[12] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33};
      int REMOVE_ORDER[11] = {21, 24, 1, 27, 9, 12, 15, 18, 30, 3, 6};
      test_avl_remove_with_order(TEST_ARR6, 12, REMOVE_ORDER, 11, REMOVE_CASE6_EXPECTED_OUTPUT);
      printf("\n== Test Case #7:\n");
      int TEST_ARR7[14] = {72, 0, 59, 33, 76, -23, -24, -38, 7, -61, -88, 5, 1, -7};
      int REMOVE_ORDER2[14] = {-7, -61, -38, -24, 0, 1, 5, 7, 33, 59, 72, -23, 76, -88};
      test_avl_remove_with_order(TEST_ARR7, 14, REMOVE_ORDER2, 14, REMOVE_CASE7_EXPECTED_OUTPUT);

    }

  }

  return 0;
}