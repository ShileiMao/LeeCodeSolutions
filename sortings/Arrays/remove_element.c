#include<stdio.h>

int get_tail(int *nums, int tail, int val) {
    while(tail > 0) {
        if(nums[tail - 1] != val) {
            return tail;
        }
        tail --;
    }
    return tail;
}

int removeElement(int* nums, int numsSize, int val) {
    int tail = get_tail(nums, numsSize, val);
    printf("tail location: %d\n", tail);
    if(tail == 0) {
        return 0;
    }
    
    for (int index = 0; index < tail; index ++) {
        if(nums[index] == val) {
            if(index == tail - 1) {
                return tail - 1; // the last index isn't equal to the value, return the index (substract by 1 of the total value)
            }
            nums[index] = nums[--tail];
            tail = get_tail(nums, tail, val);
        }
    }
    return tail;
}


int tuncateTail(int *nums, int tail, int val) {
    while(tail > 0 && nums[tail - 1] == val) {
        tail --;
    }
    return tail;
}


int removeElement2(int* nums, int numsSize, int val) {
    int tail = numsSize;
    for (int index = 0; index < tail; index ++) {
        if(nums[index] == val) {
            //get a new tail in case there are more values in the end
            tail = tuncateTail(nums, tail, val);
            if(tail <= index) {
                return tail;
            }
            nums[index] = nums[--tail];
        }
    }
    return tail;
}

int main() {
  int nums[] = {3,2,2,3};
  int size = 4;
  int val = 3;

  int num_values = removeElement2(nums, size, val);
  printf("size after remove: %d\n", num_values);
} 