// Find the kth largest number in an unsorted array.
// int findKthLargest(int[] nums, int k){}

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int _findKthLargest(int nums[], int count, int k)
{
    // Pick a random element to act as a pivot
    int pivotIdx = rand() % (count);
    int pivot = nums[pivotIdx]; /* This is technically not cryptographically secure, but I assume this is not important here */
    // Partition
    int left[count];
    int leftLength = 0;
    int right[count];
    int rightLength = 0;
    for (int i = 0; i < count; i++)
    {
        if (nums[i] <= pivot)
        {
            left[leftLength] = nums[i];
            leftLength++;
        }
        else if (nums[i] > pivot)
        {
            right[rightLength] = nums[i];
            rightLength++;
        }
    }
    if (rightLength < k - 1) /* We got unlucky, and the kth is in the left side, so search the left side, reducing by the magnitude of the union of the pivot and the right side */
    {
        return _findKthLargest(left, leftLength, k - rightLength);
    }
    // if the right partion is one less than k, we got lucky and our partition is the kth
    else if (rightLength == k - 1)
    {
        return pivot;
    }
    else if (rightLength < 2 * k) // Not enough to partition, just use insertion sort and return kth
    {
        int i, key, j;
        for (i = 0; i < rightLength; i++)
        {
            key = right[i];
            j = i - 1;
            while (j >= 0 && right[j] < key)
            {
                right[j + 1] = right[j];
                j = j - 1;
            }
            right[j + 1] = key;
        }
        return right[k - 1];
    }
    else /* right has 2k or more */
    {
        return _findKthLargest(right, rightLength, k);
    }
}

int findKthLargest(int nums[], int count, int k)
{
    srand(time(NULL)); // Initialization, should only be called once.
    return _findKthLargest(nums, count, k);
}

int main(int argc, char *argv[])
{
    int test[] = {2, 4, 6, 7, 8, 34, 7, 2, 4, 543, 3, 1, -56, 3242, -9, 45, 2, 3, 4, 65, 7, 43, 76, 14, 4, 14, 76};
    int k = 3;
    printf("Term %d is %d\n", k, findKthLargest(test, sizeof(test) / sizeof(test[0]), k));
}