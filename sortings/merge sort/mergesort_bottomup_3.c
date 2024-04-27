#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../tests/sort_test.h"

#define min(A,B) (A) > (B) ? (B) : (A)
#define max(A,B) (A) > (B) ? (A) : (B)

// since we are doing the bottom up, we are guarantee that all the segments that passed in here are sorted (left array, right array) in the tmparr
// at very bigin, the left array and right array only contain one element
void mergebottom_up(int *arr, int istart, int imiddle, int iend, int *tmparr) {
  int i = istart, j = imiddle;

  // if(imiddle >= iend) {
  //   return;
  // }

  // printf("before merge bottom up %d, %d, %d:", istart, imiddle, iend);
  // printArr(tmparr + istart, iend - istart);

  for(int index = istart; index < iend; index ++) {
    if(i < imiddle && (j >= iend || tmparr[i] <= tmparr[j])) {
      arr[index] = tmparr[i];
      i ++;
      continue;
    }

    arr[index] = tmparr[j];
    j ++;
  }

  // printf("after merge bottom up: ");
  // printArr(arr + istart, iend - istart);
}

void mergesort_bottomup(int *arr, int nitems, int *tmparr) {
  for(int width = 1; width < nitems; width = width * 2) {
    for(int index = 0; index < nitems; index += width * 2) {
      int middle = min(index + width, nitems);
      int end = min(index + width * 2, nitems);

      mergebottom_up(tmparr, index, middle, end, arr);
    }

    // more efficient way is to swap the role of `arr` and `tmparr`
    copy_array(arr, tmparr, nitems);
  }
}


void mergesort_bottomup_nocopy(int *arr, int nitems, int *tmparr) {
  int *tmp1 = arr, *tmp2 = tmparr, *ptr;

  for(int width = 1; width < nitems; width = width * 2) {
    for(int index = 0; index < nitems; index += width * 2) {
      int middle = min(index + width, nitems);
      int end = min(index + width * 2, nitems);

      mergebottom_up(tmp2, index, middle, end, tmp1);
    }
    ptr = tmp1;
    tmp1 = tmp2;
    tmp2 = ptr;    // <-----------------------------------------------------------------------------------------+
    // copy_array(arr, tmp2, nitems);                                                                        // |
  }                                                                                                          // |
  // the pointer has been swapped before for loop exit, so we should compare with tmp1 instead of tmp2!!! ------+
  if(tmp1 != arr) {
    printf("the final run is in the tmp buffer, copy back to the array\n");
    copy_array(arr, tmparr, nitems);
  }
}

int compare(const void *left, const void * right) {
  int value1 = *(int *)left;
  int value2 = *(int *)right;
  return value1 - value2;
}

int main() {
  srand(time(NULL)); // Initialize the seed, should only be called once, this srand() method will generate same sequence if you pass in the same value

  int arrayLen = (int)(rand() % 100); // this you can call multiple times
  int *array = (int *)malloc(sizeof(int) * arrayLen);
  int *tmpArr = (int *) malloc(sizeof(int) * arrayLen);
  int *testArr = (int *) malloc(sizeof(int) * arrayLen);

  for(int index = 0; index < arrayLen; index ++ ) {
    array[index] = random() % 100;
    testArr[index] = array[index];
  }

  // int arrayLen = 6;
  // int array[] = {8, 7, 1, 3, 5, 2};
  // int tmpArr[] = {0, 0, 0, 0, 0, 0};
  // int testArr[] = {8, 7, 1, 3, 5, 2};

  printf("original number: ");
  printArr(array, arrayLen);
  printf("\n");

  // mergesort_bottomup(array, arrayLen, tmpArr);
  mergesort_bottomup_nocopy(array, arrayLen, tmpArr);
  sys_sort(testArr, arrayLen, sizeof(int), compare);
  printf("Sorted array:");
  printArr(array, arrayLen);
  printf("System Sorted array:");
  printArr(testArr, arrayLen);

  int result = test_result(testArr, array, arrayLen, sizeof(int), compare);
  if(result < 0) {
    printf("Sort Failed!!!!\n");
  }

  free(array);
  free(tmpArr);
  free(testArr);
}