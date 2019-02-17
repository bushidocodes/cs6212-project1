/* Find the missing number from a given array. Your array will be in form [n, n+c, n+2c, …]. */
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int max(int count, ...);
int _findMissNo(int nums[], int startIdx, int endIdxExclusive);
int findMissNo(int nums[], int startIdx, int endIdxExclusive);

// Variadic function that takes a count followed by a variable number of integers equal to count
// Returns the max int
int max(int count, ...)
{
    va_list args;
    int val, max = INT_MIN;
    va_start(args, count);
    for (int i = 0; i < count; i++)
    {
        val = va_arg(args, int);
        max = max >= val ? max : val;
    }
    va_end(args);
    return max;
}

int findMissNo(int nums[], int startIdx, int endIdxExclusive)
{

    if (endIdxExclusive - startIdx < 3) /* Error Condition - Can't find missing value with a sequence of only two*/
    {
        printf("Error: Cannot solve with less than three numbers!\n");
        exit(0);
    }
    else if (endIdxExclusive - startIdx < 6) /* Base Case */
    {
        // The common difference is assumed to be the smallest difference because we are checking for missing terms
        // not extra terms

        int commonDifference = INT_MAX;
        for (int i = startIdx; i + 1 < endIdxExclusive; i++)
        {
            int diff = nums[i + 1] - nums[i];
            commonDifference = diff < commonDifference ? diff : commonDifference;
        }
        for (int i = startIdx + 1; i < endIdxExclusive; i++)
        {
            if (nums[i] > nums[startIdx] + (i - startIdx) * commonDifference)
            {
                return nums[startIdx] + (i - startIdx) * commonDifference;
            }
        }
        return INT_MIN;
    }
    else if (endIdxExclusive - startIdx >= 6) /* Divide and Conquer */
    {
        int midpoint = startIdx + (endIdxExclusive - startIdx) / 2; //(6 - 0) => 3
        // Partition, but be sure the check the middle band of three
        return max(3,
                   findMissNo(nums, startIdx, midpoint),
                   findMissNo(nums, midpoint - 1, midpoint + 2),
                   findMissNo(nums, midpoint, endIdxExclusive));
    }
}

int main(int argc, char *argv[])
{
    // int test[] = {1, 5, 7, 9, 11, 13, 15, 17, 19, 21}; // Test Missing in front
    int test[] = {1, 3, 5, 7, 9, 13, 15, 17, 19, 21}; // Test Missing in middle
    // int test[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 21}; // Test Missing in back
    // int test[] = {19, 21}; // Test error handling of too small unsorted array
    int missingTerm = findMissNo(test, 0, sizeof(test) / sizeof(test[0]));
    if (missingTerm == INT_MIN)
    {
        printf("No terms are missing\n");
    }
    else
    {
        printf("Sequence is missing %d\n", missingTerm);
    }
}