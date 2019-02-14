#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// int _findMissNo(int count, int nums[], int commonDifference)
// {
//     if
//         count
// }

/* Find the missing number from a given array. Your array will be in form [n, n+c, n+2c, …]. */
int findMissNo(int count, int nums[])
{
    // find the difference of the arithmetic series.
    int commonDifference = 0;

    for (int i = 0; i <= count - 1; i++)
    {
        if (commonDifference != 0 && nums[i] + commonDifference == nums[i + 1])
        {
            break;
        }
        else
        {
            commonDifference = nums[i + 1] - nums[i];
        }
    }

    for (int i = 1; i < count; i++)
    {
        if (nums[i] > nums[0] + i * commonDifference)
        {
            return nums[0] + i * commonDifference;
        }
    }
}

int main(int argc, char *argv[])
{
    int test[] = {1, 3, 5, 9};
    printf("Missing %d\n", findMissNo(sizeof(test) / sizeof(test[0]), test));
}