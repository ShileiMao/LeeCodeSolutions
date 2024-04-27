#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../tests/sort_test.h"

void copy_array(int *dest, int *src, int nitems) {
    for(int index = 0; index < nitems; index ++) {
        dest[index] = src[index];
    }
}

void topdowm_merge(int *arr, int ileft, int center, int iright, int *tmparr) {
// Now the tmparr is considered `sorted` in both left part and right part
    int i = ileft, j = center;
    for(int index = ileft; index < iright; index ++) {
        // either way is working
        
        if(i < center && (j >= iright || tmparr[i] <= tmparr[j])) {
            arr[index] = tmparr[i];
            i ++;
            continue;;
        }

        arr[index] = tmparr[j];
        j ++;
        

        /*
        if(j < iright && (i >= center || tmparr[i] >= tmparr[j])) {
            arr[index] = tmparr[j];
            j ++;
            continue;
        }
        
        arr[index] = tmparr[i];
        i ++;
        */


        /* most intuitive code
        if(i < center && j < iright) {
            if(tmparr[i] <= tmparr[j]) {
                arr[index] = tmparr[i];
                i ++;
                continue;
            }
            arr[index] = tmparr[j];
            j ++;
            continue;
        }
        if(i >= center) {
            arr[index] = tmparr[j];
            j ++;
            continue;
        }
       
       arr[index] = tmparr[i];
       i++;
        */
        
    }
}

// this version is copied from the online tutorials 
void mergesplit_topdown(int *arr, int ileft, int iright, int *tmparr) {
    if(iright - ileft <= 1) {
        return;
    }

    // important! the following must go! otherwise it won't work!

    // if(iright - ileft == 2) {
    //     if(tmparr[ileft] > tmparr[iright - 1]) {
    //         int tmp = tmparr[ileft];
    //         tmparr[ileft] = tmparr[iright - 1];
    //         tmparr[iright - 1] = tmp;
    //     }
    //     return;
    // }

    // now split
    // int center = ileft + (iright - ileft) / 2;
    int center = (iright + ileft) / 2; // better way

    // important! notice that we flip the position of tmparr and ---------------+
    mergesplit_topdown(tmparr, ileft, center, arr);                         //  |
    mergesplit_topdown(tmparr, center, iright, arr);                        //  |
                                                                            //  |
    topdowm_merge(arr, ileft, center, iright, tmparr);   // <----- and here  ---+ the reason behind:
    /*
        every round of the merge, it only make sure the partial of the array gets sorted, and we will then need additional 
        array to use as intermedia to help us to merge the 'left array' and 'right array'.

        the easiest way is to have an empty tmparr, then after merge, we copy over the sorted values from tmparr, it will be easy to understand (like the version one (mergeSort_1.c))
        however, this would increase the time complexity

        In the current way, we will swap the order of both arries, which means they are alternatively holding current sorted values, that will save us both time of copy and allocating 
        new temp arries.
    */
}

void mergesort_topdown(int *arr, int nitems, int *tmparr)
{
    // copy all elements to tmparr
    copy_array(tmparr, arr, nitems);

    mergesplit_topdown(arr, 0, nitems, tmparr);
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

//   int arrayLen = 6;
//   int array[] = {8, 7, 1, 3, 5, 2};
//   int tmpArr[] = {0, 0, 0, 0, 0, 0};
//   int testArr[] = {8, 7, 1, 3, 5, 2};

  printf("original number: ");
  printArr(array, arrayLen);
  printf("\n");

  mergesort_topdown(array, arrayLen, tmpArr);
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



