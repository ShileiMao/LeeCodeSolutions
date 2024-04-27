#ifndef __SORT_TEST__
#define __SORT_TEST__
#include <stdio.h>
    void sys_sort(void *base, size_t nitems, size_t size, int (*compare)(const void *, const void *));

    int test_reult(void *arr, void *com, size_t nitems, size_t size, int (*compare)(const void *, const void *));

    void printArr(int *arr, int len);

    
    void copy_array(int *dest, int *src, int nitems);
#endif