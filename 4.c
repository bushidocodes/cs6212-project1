/* Find number of rotations in a circularly sorted array. 
For example, given an array [4, 6, 8, 1, 2, 3], your program should return 3. 
Given array [1, 2, 3, 4, 6, 8], your program should return 0. */
/* Based on my understanding, this is identical to finding the index of the smallest element */

#include <stdio.h>

int findRotationNo(int nums[], int startIdx, int endIdxExclusive)
{
    if (endIdxExclusive - startIdx == 1) /* If one element, just return it */
    {
        return startIdx;
    }
    else if (endIdxExclusive - startIdx == 2) /* If two elements, return the index of the lower value */
    {
        return nums[startIdx] < nums[startIdx + 1] ? startIdx : startIdx + 1;
    }
    else /* Divide and Conquer */
    {
        // This problem seems simpler... no need to check a strip across the two havlves
        int midpoint = (endIdxExclusive - startIdx) / 2;
        int first = findRotationNo(nums, startIdx, midpoint + 1);
        int second = findRotationNo(nums, midpoint + 1, endIdxExclusive);
        return nums[first] <= nums[second] ? first : second;
    }
}

int main(int argc, char *argv[])
{
    int test1[] = {4, 6, 8, 1, 2, 3};
    printf("{4, 6, 8, 1, 2, 3} should rotate %d times\n", findRotationNo(test1, 0, sizeof(test1) / sizeof(test1[0])));
    int test2[] = {1, 2, 3, 4, 6, 8};
    printf("{1, 2, 3, 4, 6, 8} should rotate %d times\n", findRotationNo(test2, 0, sizeof(test2) / sizeof(test2[0])));
    return 0;
}