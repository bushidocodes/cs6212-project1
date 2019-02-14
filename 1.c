#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Preprocessor macro to find length of an Array. Must be used in block where declared so array doesn't degrade
// to pointers
#define length(n) (sizeof(n) / sizeof(n[0]))
// Find the contiguous sub array which has the largest sum and return its sum. This array may contain negative numbers.
// I understand a subarray to be a continuous sequence of elements from the source array
// I assum that an empty array is a valid subarray

// int length(void *elems[])
// {
//     return sizeof(*elems[0]) / sizeof(elems);
// }

// Variadic function to be cute
int max(int count, ...)
{
    va_list args;
    int val, max = 0;
    va_start(args, count);
    for (int i = 0; i < count; i++)
    {
        val = va_arg(args, int);
        max = max >= val ? max : val;
    }
    va_end(args);
    return max;
}

int sum(int nums[], int startIdx, int endIdxInclusive)
{
    char buffer[100] = "";
    char temp[100] = "";
    strcat(buffer, "For {");
    for (int i = startIdx; i <= endIdxInclusive; i++)
    {
        snprintf(temp, 100, "%d, ", nums[i]);
        strcat(buffer, temp);
    }
    int sum = 0;
    for (int i = startIdx; i <= endIdxInclusive; i++)
    {
        sum += nums[i];
    }
    strcat(buffer, "}, sum is ");
    snprintf(temp, 100, "%d", sum);
    strcat(buffer, temp);
    strcat(buffer, "\n");
    printf(buffer);
    return sum;
}

// Due to preprocessing, we should be guaranteed to have an odd number of elements with positive numbers in the first
// and last positions. This allows us to recursively 
int _maxSubArray(int nums[], int startIdx, int endIdxInclusive)
{
    char buffer[100] = "";
    char temp[100] = "";
    strcat(buffer, "For {");
    for (int i = startIdx; i <= endIdxInclusive; i++)
    {
        snprintf(temp, 100, "%d, ", nums[i]);
        strcat(buffer, temp);
    }
    if (endIdxInclusive == startIdx)
    {

        strcat(buffer, "}, max is ");
        snprintf(temp, 100, "%d", nums[startIdx]);
        strcat(buffer, temp);
        strcat(buffer, "\n");
        printf(buffer);
        return nums[startIdx];
    }
    int result = max(3, _maxSubArray(nums, startIdx, midpoint), _maxSubArray(nums, midpoint + 1, endIdxInclusive), sum(nums, startIdx, endIdxInclusive - 1));
    snprintf(temp, 100, " }, the max is %d\n", result);
    strcat(buffer, temp);
    printf(buffer);
    return result;
}

int maxSubArray(int nums[], int startIdx, int endIdxInclusive)
{
    // We do some initial preprocessing to ensure that positive and negative numbers alternate
    // for the divide and conquer portion
    int simplifiedNums[endIdxInclusive - startIdx];
    int simplifiedNumsLength = 0;
    int accumulator = 0;
    bool isPos = true;
    for (int i = startIdx; i <= endIdxInclusive; i++)
    {
        // We would never include leading or trailing negatives, so drop them
        if (nums[i] == 0 || (i == 0 || i == endIdxInclusive) && nums[i] <= 0)
        {
            continue;
        }
        else if (nums[i] > 0 == isPos)
        {
            accumulator += nums[i];
        }
        else
        {
            simplifiedNums[simplifiedNumsLength] = accumulator;
            simplifiedNumsLength++;
            accumulator = 0;
            isPos = !isPos;
            accumulator += nums[i];
        }
    }
    return _maxSubArray(simplifiedNums, 0, simplifiedNumsLength - 1);
}

int main(int argc, char *argv[])
{
    int test[] = {3, 1, 8, -12, 4, 32, -99, 12};
    // int test[] = {2, 3, 4, 5, 7};
    printf("The size of the arr is %d", maxSubArray(test, 0, length(test) - 1));
}