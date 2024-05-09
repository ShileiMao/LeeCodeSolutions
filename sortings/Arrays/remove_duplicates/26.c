#include <stdio.h>

int removeDuplicates(int* nums, int numsSize) {
    if(numsSize <= 1) {
        return numsSize;
    }

    int nextIndex = 1;
    int lastValue = nums[0];

    for(int index = 1; index < numsSize; index ++) {
        if(nums[index] != lastValue) {
            lastValue = nums[index];
            nums[nextIndex ++] = lastValue; 
        }
    }
    return nextIndex;
}


int main() {
  printf("Hello world!");
}