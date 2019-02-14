#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_ints(const void *p, const void *q)
{
    int x = *(const int *)p;
    int y = *(const int *)q;
    if (x < y)
        return -1; // Return -1 if you want ascending, 1 if you want descending order.
    else if (x > y)
        return 1; // Return 1 if you want ascending, -1 if you want descending order.
    return 0;
}

int _findKthLargest(int nums[], int startIdx, int endIdxInclusive, int k)
{
    int count = endIdxInclusive - startIdx + 1;
    printf("%d - %d - %d\n", startIdx, endIdxInclusive, k);
    if (count < k)
    {
        printf("%d < k of %d\n", count, k);
        return INT_MIN;
    }
    else if (count <= 2 * k)
    {
        printf("%d <= 2k of %d\n", count, 2 * k);
        int temp[count];
        memcpy(temp, &nums[startIdx], count * sizeof(*nums));
        // Maybe this should be insertion sort or something simple?
        qsort(temp, endIdxInclusive - startIdx + 1, sizeof(int), &compare_ints);
        return nums[k - 1];
    }
    else
    {
        int results[count / k];

        for (int i = startIdx; i < endIdxInclusive - k; i += k)
        {
            // printf("%d && %d\n", i, i < endIdxInclusive - 2 * k ? i + k : count - 1);
            // results[i] = _findKthLargest(nums, i, i + k, k);
            results[i] = _findKthLargest(nums, i, i < endIdxInclusive - 2 * k ? i + k : count - 1, k);
            printf("Result is %d\n", results[i]);
        }
        return _findKthLargest(results, 0, sizeof(results) / sizeof(results[0]), k);
    }
}

// Find the kth largest number in an unsorted array.
int findKthLargest(int count, int nums[], int k)
{
    return _findKthLargest(nums, 0, count - 1, k);
    // return 9;
};

int main(int argc, char *argv[])
{
    int test[] = {2, 4, 6, 7, 8, 34, 7, 2, 4, 543, 3, 1, -56, 3242, -9, 45, 2, 3, 4, 65, 7, 43, 76, 14, 4, 14, 76};
    printf("K is %d\n", findKthLargest(sizeof(test) / sizeof(test[0]), test, 3));
}