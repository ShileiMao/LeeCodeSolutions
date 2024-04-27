#include "sort_test.h"
#include <stdlib.h>

void sys_sort(void *base, size_t nitems, size_t size, int (*compare)(const void *, const void *))
{
    qsort(base, nitems, size, compare);
}

int test_result(void *arr, void *comp, size_t nitems, size_t size, int (*compare)(const void *, const void *))
{
    for(size_t index = 0; index < nitems; index ++) {
        size_t offset = index * size;
        int result = compare(arr + offset, comp + offset);
        if(result != 0) {
            printf("Failed to compare array at %d, they are not match, %d <=> %d ", index, arr + offset, comp + offset);
            return -1;
        }
    }

    return 0;
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


void copy_array(int *dest, int *src, int nitems) {
    for(int index = 0; index < nitems; index ++) {
        dest[index] = src[index];
    }
}