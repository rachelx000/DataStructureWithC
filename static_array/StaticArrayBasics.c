#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int size) {
  /* function to print array of integers */
  printf("ARR Size: %d [", size);
  for (int i = 0; i < size; i++) {
    printf("%d", arr[i]);
    if (i < size-1) { printf(", "); }
  }
  printf("]\n");
}

typedef struct {
  int a;
  int b;
} tuple;

typedef struct {
  int* arr;
  int size;
} static_array;

tuple min_max(int arr[], int size){
  /* function that receives a 1-D static array of integers and returns a tuple with
   * the minimum and maximum values of the input array. */
  int i = 0;
  tuple extrema = { arr[i], arr[i] };
  for (int i = 1; i < size; i++) {
    if (arr[i] < extrema.a) { extrema.a = arr[i]; }
    if (arr[i] > extrema.b) { extrema.b = arr[i]; }
  }
  return extrema;
}

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void reverse(int arr[], int size) {
  /* function that receives an static array of integers and reverses the order of the elements */
  int p1, p2;
  p2 = size / 2 - 1;
  if ( size % 2 == 0 ) { p1 = size / 2; }
  else { p1 = size / 2 + 1; }
  for (int i = p2; i >= 0; i--) {
    swap(&arr[p1], &arr[p2]);
    p1++; p2--;
  }
}

static_array rotate(int arr[], int size, int step) {
  /* function that creates and returns a new static array of integers, which contains
   * all the elements from the original array, but their position has shifted right or left
   * steps number of times. */
  int* rotated_arr = malloc(size * sizeof(int));
  if (!rotated_arr) {
    printf("Memory allocation failed! \n");
    exit(1);
  }
  step %= size;
  if (step < 0) { step += size; }
  for (int i = 0; i < size; i++) {
    int new_i = i + step;
    if (new_i > size-1) { new_i -= size; }
    rotated_arr[new_i] = arr[i];
  }
  static_array result_arr = {rotated_arr, size};
  return result_arr;
}

static_array sa_range(int start, int end) {
  /* function that receives the two integers start and end, and returns an static
   * array that contains all the consecutive integers between start and end (inclusive). */
  int size = abs(start-end)+1;
  int* range_arr = malloc(size*sizeof(int));
  if (!range_arr) {
    printf("Memory allocation failed! \n");
    exit(1);
  }
  if (end >= start) {
    for (int i = 0, j = start; i < size ; i++, j++) { range_arr[i] = j; }
  }
  else {
    for (int i = 0, j = start; i < size ; i++, j--) { range_arr[i] = j; }
  }
  static_array result_arr = {range_arr, size};
  return result_arr;
}

int is_sorted(int arr[], int size) {
  /*  function that receives a static array and returns an integer that describes whether
   * the array is sorted*/
  if (size != 1) {
    int sorted_status;
    // check the order of the first element
    int init_interval = arr[1]-arr[0];
    if (init_interval > 0) { sorted_status = 1; }
    else if (init_interval < 0) { sorted_status = -1; }
    else { return 0; }

    // then iterate over the array to check if the remaining array follows the order
    int curr_interval;
    for (int i = 1, j = 2; j < size; i++, j++) {
      curr_interval = arr[j] - arr[i];
      if ((sorted_status == 1 && curr_interval < 0) || (sorted_status == -1 && curr_interval > 0)
        || (curr_interval == 0)) { return 0; }
    }
    return sorted_status;
  }
  return 1;
}

tuple find_mode(int arr[], int size) {
  /* receives a static array that is sorted in order, either non-descending or non-ascending,
   * The function will return, in this order, the mode of the array with its frequency
   * If there is more than one value that has the highest frequency, select the one that occurs
   * first in the array.  */
  int curr_num = arr[0];
  int curr_freq = 1;
  tuple mode = { .b = 0 };
  for (int i = 1; i < size; i++) {
    if (arr[i] == curr_num) {
      curr_freq += 1;
      if (curr_freq > mode.b) {
        if ( mode.a != curr_num ) {mode.a = curr_num; }
        mode.b = curr_freq;
      }
    }
    else {
      curr_num = arr[i];
      curr_freq = 1;
    } }
  return mode;
}

static_array remove_duplicates(int arr[], int size) {
  /* function that returns a new static array that has removed the duplicate elements
   * from the original sorted static array. */
  int* new_arr = malloc(size*sizeof(int));
  if (!new_arr) {
    printf("Memory allocation failed! \n");
    exit(1);
  }
  new_arr[0] = arr[0];
  int j = 0;
  for (int i = 1; i < size; i++) {
    if ( arr[i] != new_arr[j] ) {
      j++;
      new_arr[j] = arr[i];
    }
  }
  int new_size = j+1;
  if ( new_size < size ) {
    // reallocate the size of result array if there are duplicates present
    int* temp = realloc(new_arr, new_size * sizeof(int));
    if (!temp) {
      printf("Memory reallocation failed!\n");
      free(new_arr);
      exit(1);
    }
    new_arr = temp;
  }
  static_array result_arr = {new_arr, new_size};
  return result_arr;
}

static_array count_sort(int arr[], int size) {
  /* function that returns a new static array with the same content from the original
   * array but sorted in non-ascending order, using the count sort algorithm */

  // get the minimum and maximum of the array
  tuple extrema = min_max(arr, size);

  // generate the count array
  int count_arr_size = extrema.b - extrema.a + 1;
  int* count_arr = calloc(count_arr_size, sizeof(int));
  if (!count_arr) {
    printf("Memory allocation failed! \n");
    exit(1);
  }
  for (int i = 0; i < size; i++) {
    count_arr[arr[i]-extrema.a] += 1;
  }

  // generate the sorted array based on the count array
  int* sorted_arr = malloc(size*sizeof(int));
  if (!sorted_arr) {
    printf("Memory allocation failed! \n");
    exit(1);
  }
  int j = 0;
  for (int i = count_arr_size-1; i >= 0; i--) {
    if (count_arr[i] > 0) {
      do {
        sorted_arr[j] = extrema.a+i;
        j++;
        count_arr[i] -= 1;
      } while (count_arr[i] > 0);
    }
  }
  free(count_arr);
  static_array result_arr = { sorted_arr, size };
  return result_arr;
}

static_array sorted_squares(int arr[], int size) {
  /* function that returns a non-descending array containing the squares of each element
   * in staticArray by taking a sorted static array in the same order. */
  int* square_arr = malloc(size*sizeof(int));
  // find the indices of the largest negative number (if exists) and the smallest positive number
  int neg_ptr = -1;
  int pos_ptr = 0;

  for (int i=0; i < size; i++) {
    if (arr[i] < 0) { neg_ptr = i; }
    if (i == size-1 && neg_ptr ) { pos_ptr = neg_ptr + 1; }
  }

  for (int i = 0; i < size; i++) {
    if (pos_ptr == 0) {
      square_arr[i] = arr[i]*arr[i];
      printf("squared: %d \n", square_arr[i]);
    }
    else if (neg_ptr == size-1) {
      square_arr[size-i-1] = arr[i]*arr[i];
    }
    else {
      if ( pos_ptr < size && neg_ptr >= 0 ) {
        if (arr[pos_ptr] <= abs(arr[neg_ptr])) {
          square_arr[i] = arr[pos_ptr]*arr[pos_ptr];
          pos_ptr++;
        }
        else {
          square_arr[i] = arr[neg_ptr]*arr[neg_ptr];
          neg_ptr--;
        }
      }
      else if ( pos_ptr < size ) {
        square_arr[i] = arr[pos_ptr]*arr[pos_ptr];
        pos_ptr++;
      }
      else if ( neg_ptr >= 0 ) {
        square_arr[i] = arr[neg_ptr]*arr[neg_ptr];
        neg_ptr--;
      }
    }
  }
  static_array result_arr = { square_arr, size };
  return result_arr;
}

int main() {
  // -------------------------------
  // function min_max()
  // -------------------------------
  {
    // Example #1:
    tuple result;
    printf("\n# min_max example 1:\n");
    int arr1[5] = {7, 8, 6, -5, 4};
    printArray(arr1, sizeof(arr1)/sizeof(arr1[0]));
    result = min_max(arr1, sizeof(arr1) / sizeof(arr1[0]));
    printf("Min: %d, Max: %d\n", result.a, result.b);
    printArray(arr1, sizeof(arr1)/sizeof(arr1[0]));

    // Example #2:
    printf("\n# min_max example 2:\n");
    int arr2[1] = {100};
    printArray(arr2, sizeof(arr2)/sizeof(arr2[0]));
    result = min_max(arr2, sizeof(arr2) / sizeof(arr2[0]));
    printf("Min: %d, Max: %d\n", result.a, result.b);
    printArray(arr2, sizeof(arr2)/sizeof(arr2[0]));

    // Example #3:
    printf("\n# min_max example 3:\n");
    int arr3[3] = {3, 3, 3};
    int arr4[5] = {-10, -30, -5, 0, -10};
    int arr5[4] = {25, 50, 0, 10};
    printArray(arr3, sizeof(arr3)/sizeof(arr3[0]));
    result = min_max(arr3, sizeof(arr3) / sizeof(arr3[0]));
    printf("Min: %d, Max: %d\n", result.a, result.b);
    printArray(arr4, sizeof(arr4)/sizeof(arr4[0]));
    result = min_max(arr4, sizeof(arr4) / sizeof(arr4[0]));
    printf("Min: %d, Max: %d\n", result.a, result.b);
    printArray(arr5, sizeof(arr5)/sizeof(arr5[0]));
    result = min_max(arr5, sizeof(arr5) / sizeof(arr5[0]));
    printf("Min: %d, Max: %d\n", result.a, result.b);
  }

  // -------------------------------
  // function reverse()
  // -------------------------------
  {

    // Example #1:
    printf("\n# reverse example 1:\n");
    int even_arr[6] = {-20, -13, -6, 1, 8, 5};
    printArray(even_arr, 6);
    reverse(even_arr, 6);
    printArray(even_arr, 6);
    reverse(even_arr, 6);
    printArray(even_arr, 6);

    // Example #2:
    printf("\n# reverse example 2:\n");
    int odd_arr[5] = {1, -3, 5, 3, -1};
    printArray(odd_arr, 5);
    reverse(odd_arr, 5);
    printArray(odd_arr, 5);
    reverse(odd_arr, 5);
    printArray(odd_arr, 5);

    // Example #3:
    printf("\n# reverse example 3:\n");
    int single_arr[1] = {1};
    printArray(odd_arr, 1);
    reverse(single_arr, 1);
    printArray(single_arr, 1);
  }

  // -------------------------------
  // function rotate()
  // -------------------------------
  {
    printf("\n# rotate example:\n");
    int arr[6] = {-20, -13, -6, 1, 8, 15};
    int steps[9] = {1, 2, 0, -1, -2, 28, -100, 268435456, -2147483648};
    printArray(arr, 6);
    static_array result_arr;
    for (int i = 0; i < 9; i++) {
      printf("Step: %d, ", steps[i]);
      result_arr = rotate(arr, 6, steps[i]);
      printArray(result_arr.arr, result_arr.size);
      free(result_arr.arr);
    }
    printArray(arr, 6);
  }
  // -------------------------------
  // function sa_range()
  // -------------------------------
  {
    printf("\n# sa_range example:\n");
    int start[6] = {1, -1, 0, 0, -95, -89};
    int end[6] = {3, 2, 0, -3, -89, -95};
    static_array result_arr;
    for (int i = 0; i < 6; i++) {
      printf("Start: %d, ", start[i]);
      printf("End: %d, ", end[i]);
      result_arr = sa_range(start[i], end[i]);
      printArray(result_arr.arr, result_arr.size);
      free(result_arr.arr);
    }
  }
  // -------------------------------
  // function is_sorted()
  // -------------------------------
  {
    printf("\n# is_sorted example:\n");
    int arr1[8] = {-100, -8, 0, 2, 3, 10, 20, 100};
    printf("Result: %d, ", is_sorted(arr1, 8));
    printArray(arr1, 8);
    int arr2[6] = {1, 3, -10, 20, -30, 0};
    printf("Result: %d, ", is_sorted(arr2, 6));
    printArray(arr2, 6);
    int arr3[6] = {-10, 0, 0, 10, 20, 30};
    printf("Result: %d, ", is_sorted(arr3, 6));
    printArray(arr3, 6);
    int arr4[5] = {100, 90, 0, -90, -200};
    printf("Result: %d, ", is_sorted(arr4, 5));
    printArray(arr4, 5);
    int arr5[1] = {0};
    printf("Result: %d, ", is_sorted(arr5, 1));
    printArray(arr5, 1);
    int arr6[2] = {1, 0};
    printf("Result: %d, ", is_sorted(arr6, 2));
    printArray(arr6, 2);
    int arr7[3] = {-1, -1, 3};
    printf("Result: %d, ", is_sorted(arr7, 3));
    printArray(arr7, 3);
    int arr8[5] = {-1, -2, -3, 5, 3};
    printf("Result: %d, ", is_sorted(arr8, 5));
    printArray(arr8, 5);
    int arr9[6] = {3847, 0, -2, -9, -100, -3874532};
    printf("Result: %d, ", is_sorted(arr9, 6));
    printArray(arr9, 6);
  }
  // -------------------------------
  // function find_mode()
  // -------------------------------
  {
    tuple result;
    printf("\n# find_mode:\n");
    int arr1[7] = {1, 20, 30, 40, 500, 500, 500};
    printArray(arr1, 7);
    result = find_mode(arr1, 7);
    printf("Mode: %d , Frequency: %d \n", result.a, result.b);
    int arr2[8] = {2, 2, 2, 2, 1, 1, 1, 1};
    printArray(arr2, 8);
    result = find_mode(arr2, 8);
    printf("Mode: %d , Frequency: %d \n", result.a, result.b);
    int arr3[9] = {3, 4, 5, 5, 6, 7, 7, 7, 10};
    printArray(arr3, 9);
    result = find_mode(arr3, 9);
    printf("Mode: %d , Frequency: %d \n", result.a, result.b);
    int arr4[1] = {0};
    printArray(arr4, 1);
    result = find_mode(arr4, 1);
    printf("Mode: %d , Frequency: %d \n", result.a, result.b);
    int arr5[6] = {0, -1, -2, -3, -4, -5};
    printArray(arr5, 6);
    result = find_mode(arr5, 6);
    printf("Mode: %d , Frequency: %d \n", result.a, result.b);
  }
  // -------------------------------
  // function remove_duplicates()
  // -------------------------------
  {
    printf("\n# remove_duplicates example:\n");
    static_array result_arr;
    int arr1[1] = {0};
    printArray(arr1, 1);
    result_arr = remove_duplicates(arr1, 1);
    printArray(result_arr.arr, result_arr.size);
    free(result_arr.arr);
    int arr2[2] = {1, 2};
    printArray(arr2, 2);
    result_arr = remove_duplicates(arr2, 2);
    printArray(result_arr.arr, result_arr.size);
    free(result_arr.arr);
    int arr3[3] = {1, 1, 2};
    printArray(arr3, 3);
    result_arr = remove_duplicates(arr3, 3);
    printArray(result_arr.arr, result_arr.size);
    free(result_arr.arr);
    int arr4[7] = {1, 20, 30, 40, 500, 500, 500};
    printArray(arr4, 7);
    result_arr = remove_duplicates(arr4, 7);
    printArray(result_arr.arr, result_arr.size);
    free(result_arr.arr);
    int arr5[9] = {5, 5, 5, 4, 4, 3, 2, 1, 1};
    printArray(arr5, 9);
    result_arr = remove_duplicates(arr5, 9);
    printArray(result_arr.arr, result_arr.size);
    free(result_arr.arr);
    int arr6[8] = {2, 2, 2, 2, 1, 1, 1, 1};
    printArray(arr6, 8);
    result_arr = remove_duplicates(arr6, 8);
    printArray(result_arr.arr, result_arr.size);
    free(result_arr.arr);
  }
  // -------------------------------
  // function count_sort()
  // -------------------------------
  {
    printf("\n# count_sort example:\n");
    static_array result_arr;
    int arr1[5] = {1, 2, 4, 3, 5};
    printArray(arr1, 5);
    result_arr = count_sort(arr1, 5);
    printArray(result_arr.arr, 5);
    free(result_arr.arr);
    int arr2[5] = {5, 4, 3, 2, 1};
    printArray(arr2, 5);
    result_arr = count_sort(arr2, 5);
    printArray(result_arr.arr, 5);
    free(result_arr.arr);
    int arr3[7] = {0, -5, -4, -3, -2, -1, 0};
    printArray(arr3, 7);
    result_arr = count_sort(arr3, 7);
    printArray(result_arr.arr, 7);
    free(result_arr.arr);
    int arr4[7] = {-1, -1, -3, 0,-3,-5, -4};
    printArray(arr4, 7);
    result_arr = count_sort(arr4, 7);
    printArray(result_arr.arr, 7);
    free(result_arr.arr);
    int arr5[7] = {-3, -2, -1, 0, 1, 2, 3};
    printArray(arr5, 7);
    result_arr = count_sort(arr5, 7);
    printArray(result_arr.arr, 7);
    free(result_arr.arr);
    int arr6[12] = {1, 2, 3, 4, 3, 2, 1, 5, 5, 2, 3, 1};
    printArray(arr6, 12);
    result_arr = count_sort(arr6, 12);
    printArray(result_arr.arr, 12);
    free(result_arr.arr);
    int arr7[4] = {10100, 10721, 10320, 10998};
    printArray(arr7, 4);
    result_arr = count_sort(arr7, 4);
    printArray(result_arr.arr, 4);
    free(result_arr.arr);
    int arr8[4] = {-100320, -100450, -100999, -100001};
    printArray(arr8, 4);
    result_arr = count_sort(arr8, 4);
    printArray(result_arr.arr, 4);
    free(result_arr.arr);
  }
  // -------------------------------
  // function sorted_squares()
  // -------------------------------
  printf("\n# sorted_squares example:\n");
  static_array result_arr;
  int arr1[5] = {1, 2, 3, 4, 5};
  printArray(arr1, 5);
  result_arr = sorted_squares(arr1, 5);
  printArray(result_arr.arr, 5);
  free(result_arr.arr);
  int arr2[6] = {-5,-4,-3,-2,-1, 0};
  printArray(arr2, 6);
  result_arr = sorted_squares(arr2, 6);
  printArray(result_arr.arr, 6);
  free(result_arr.arr);
  int arr3[7] = {-3,-2,-2, 0, 1, 2, 3};
  printArray(arr3, 7);
  result_arr = sorted_squares(arr3, 7);
  printArray(result_arr.arr, 7);
  free(result_arr.arr);
  int arr4[12] = {-9,-4,-2, -2, 2, 5, 7, 8, 8, 10, 11, 20};
  printArray(arr4, 12);
  result_arr = sorted_squares(arr4, 12);
  printArray(result_arr.arr, 12);
  free(result_arr.arr);
  int arr5[7] = {-4, -4, -3,-2, -1, 0, 1};
  printArray(arr5, 7);
  result_arr = sorted_squares(arr5, 7);
  printArray(result_arr.arr, 7);
  free(result_arr.arr);

  return 0;
}