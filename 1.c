// Find the contiguous sub array which has the largest sum and return its sum. This array may contain negative numbers.
// I understand a subarray to be a continuous sequence of elements from the source array

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

// Preprocessor macro to find length of an Array.
// Must be used in block where declared so array doesn't degrade to pointers
#define length(n) (sizeof(n) / sizeof(n[0]))

int max(int count, ...);
int _maxSubArray(int nums[], int startIdx, int endIdxInclusive, bool isCheckingFromMidpoint);
int maxSubArray(int nums[], int startIdx, int endIdxInclusive);

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

int _maxSubArray(int nums[], int startIdx, int endIdxInclusive, bool isCheckingFromMidpoint)
{
    if (startIdx == endIdxInclusive) // One element
    {
        return nums[startIdx];
    }
    else if (startIdx + 1 == endIdxInclusive) // Two elements
    {
        return max(2, _maxSubArray(nums, startIdx, startIdx, false),
                   _maxSubArray(nums, endIdxInclusive, endIdxInclusive, false));
    }
    else if (isCheckingFromMidpoint) // Checking the middle of three or more
    {
        int midpoint = (endIdxInclusive + 1 - startIdx) / 2;
        int maxLeft = INT_MIN;
        int maxRight = INT_MIN;
        int buffer = 0;

        // Find the best left
        for (int i = midpoint; i >= startIdx; i--)
        {
            buffer += nums[i];
            maxLeft = buffer > maxLeft ? buffer : maxLeft;
        }

        // Find the best right
        buffer = 0;
        for (int i = midpoint + 1; i <= endIdxInclusive; i++)
        {
            buffer += nums[i];
            maxRight = buffer > maxRight ? buffer : maxRight;
        }

        return maxLeft + maxRight;
    }
    else // Divide and Conquer of three or more
    {
        int midpoint = startIdx + (endIdxInclusive + 1 - startIdx) / 2;
        return max(3,
                   _maxSubArray(nums, startIdx, midpoint - 1, false),
                   _maxSubArray(nums, startIdx, endIdxInclusive, true),
                   _maxSubArray(nums, midpoint, endIdxInclusive, false));
    }
}

// I need to pass indices because the function loses state about the length of the array when passed as an arg
// I abstract my kludgey flag on the external API to be close to the original spirit of the problem
int maxSubArray(int nums[], int startIdx, int endIdxInclusive)
{
    return _maxSubArray(nums, startIdx, endIdxInclusive, false);
}

int main(int argc, char *argv[])
{
    int test[] = {4, 1, 8, -12, 4, 32, -99, 12};
    // int test[] = {2, 3, 4, 5, 7};
    printf("The sum of the max sub array is %d", maxSubArray(test, 0, length(test) - 1));
}