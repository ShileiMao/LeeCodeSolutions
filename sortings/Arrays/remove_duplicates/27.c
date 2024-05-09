int removeDuplicates(int* nums, int numsSize) {
    if(numsSize <= 2) {
        return numsSize;
    }

    int nextIndex = 1;
    int occurrence = 1;
    int lastValue = nums[0];
    for(int index = 1; index < numsSize; index ++) {
        if(nums[index] != lastValue) {
            lastValue = nums[index];
            nums[nextIndex ++] = nums[index];
            occurrence = 1;
            continue;
        }

        occurrence ++;
        if(occurrence <= 2) {
            lastValue = nums[index];
            nums[nextIndex ++] = nums[index];
            continue;
        }
    }
    return nextIndex;
}


// this uses fewer variables so it produces better results
int removeDuplicates_2(int* nums, int numsSize) {
    if(numsSize <= 2) {
        return numsSize;
    }

    int lastIndex = 2;
    for(int index = 2; index < numsSize; index ++) {
        if(nums[index] != nums[lastIndex - 1] || nums[index] != nums[lastIndex - 2]) {
            nums[lastIndex ++] = nums[index];
        }
    }
    return lastIndex;
}