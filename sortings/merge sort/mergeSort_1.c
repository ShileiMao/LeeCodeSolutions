#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../tests/sort_test.h"

void test(int *arr1[], int *arr2[], int len) {
  
}

void printArr(int *arr, int len) {
  for(int index = 0; index < len; index ++) {
    printf("%d", arr[index]);
    if(index < len - 1) {
        printf(",");
    }
  }
  printf("\n");
}

void mergeSort(int *arr1, int *arr2, int len) {
   // the both side now breaked down into single element
   if(len <= 1) {
    return;
   }

  if(len == 2) {
    if(arr1[0] > arr1[1]) {
        int tmp = arr1[0];
        arr1[0] = arr1[1];
        arr1[1] = tmp;
    }
    return;
  }

  // break the left array into sections
  
  int centerPoint = len / 2;
  int leftLen = centerPoint;
  int rightLen = len - centerPoint;

  int* leftArr = arr1;
  int* rightArr = arr1 + centerPoint;
  mergeSort(leftArr, arr2, leftLen);
  mergeSort(rightArr, arr2, rightLen);

  // now both sides has been sorted, sort the left and right array
  int leftIndex = 0, rightIndex = 0;
  int index = 0;

  while(leftIndex < leftLen || rightIndex < rightLen) {
    // now we need to swap
    if(leftIndex < leftLen && rightIndex < rightLen) {
      if(leftArr[leftIndex] > rightArr[rightIndex]) {
        arr2[index ++] = rightArr[rightIndex ++];           
        continue;
      }

      arr2[index ++] = leftArr[leftIndex ++];
      continue;
    }

    // no one of the array has finished
    while(leftIndex < leftLen) {
      arr2[index ++] = leftArr[leftIndex ++];
    }

    while(rightIndex < rightLen) {
      arr2[index ++] = rightArr[rightIndex ++];
    }
  }

  index = 0;
  for(index = 0; index < len; index ++) {
    arr1[index] = arr2[index];
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

  // int arrayLen = 5;
  // int array[] = {3,2,1,1,4};
  // int tmpArr[5] = {0, 0, 0, 0, 0};

  printf("original number: ");
  printArr(array, arrayLen);
  printf("\n");

  mergeSort(array, tmpArr, arrayLen);
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