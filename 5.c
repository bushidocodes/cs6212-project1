/* 

Note: I've rephrased the problem statement because I found the existing description to be super confusing.

You are given N number of books, each with a specific number of pages.
Your goal is to allocate these books to M students in a manner that minimizes the maximum number of pages assigned to any single student

For mysterious reasons, the book assignments need to be contiguous subarrays of the array formed by the provided list of page counts.

Each book will be assigned to exactly one student. 
Each student has to be allocated at least one book.

Return the minimized number of pages assigned to the student 

Note: Return -1 if a valid assignment is not possible, and allotment should be in contiguous order (see explanation for better understanding).

Input:
The first line contains 'T' denoting the number of testcases. Then follows description of T 

testcases:
Each case begins with a single positive integer N denoting the number of books.
The second line contains N space separated positive integers denoting the pages of each book.
And the third line contains another integer M, denoting the number of students.

Output:
For each test case, output a single line containing the highest number of pages assigned to a student in the optimal assigment.

Constraints:
1<= T <= 100
1 <= N <= 106
1 <= A [ i ] <= 106
1 <= M <= 106

Example:
Input:
1 (number of test cases)
4 (number of books in test case)
12 34 67 90 (pages of each book in test case)
2 (number of students)

Output:
113

Explaination: Allocation can be done in following ways:
{12} and {34, 67, 90} Maximum Pages = 191
{12, 34} and {67, 90} Maximum Pages = 157
{12, 34, 67} and {90} Maximum Pages = 113
Therefore, the minimum of these cases is 113, which is selected as output. 



NOTE TO GRADER:
To run this program:
gcc 5.c && cat 5.txt | ./a.out

I'm a bit confused if binary search constitutes divide and conquer. Since we are tossing half the results, we are dividing, but we don't need to merge. I could refactor to make the binary search portion to use leftBounds and rightBounds as arguments to a recursive function, but that doesn't seem to provide any additional value in my opinion.

*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXBOOKS 50

typedef struct testcase
{
    int numberOfBooks;
    int pageCountOfBooks[MAXBOOKS];
    int numberOfStudents;
} testcase;

bool canBeAssigned(testcase *thisTestcase, int candidate_min, int *actualMax)
{
    int studentsNeeded = 1, buffer = 0;
    int *studentResults = malloc(sizeof(int) * thisTestcase->numberOfStudents);

    for (int i = 0; i < thisTestcase->numberOfBooks; i++)
    {
        // Does this one book exceed the candidate min?
        if (thisTestcase->pageCountOfBooks[i] > candidate_min)
        {
            free(studentResults);
            return false;
        }

        // Do we have enough students to distribute no more than candidate_min pages and assign all books?

        // We check by assigning consecutive books to a student up to the candidate_min
        if (buffer + thisTestcase->pageCountOfBooks[i] <= candidate_min)
        {
            buffer += thisTestcase->pageCountOfBooks[i];
        }
        else // and then moving on to another student
        {
            studentResults[studentsNeeded - 1] = buffer;
            studentsNeeded++;
            buffer = thisTestcase->pageCountOfBooks[i];

            // We we end up exceeding the number of students allowed in the test case, we know that the candidate_min
            // cannot be assigned
            if (studentsNeeded > thisTestcase->numberOfStudents)
            {
                free(studentResults);
                return false;
            }
        }
    }
    *actualMax = 0;
    for (int i = 0; i < studentsNeeded; i++)
    {
        if (studentResults[i] > *actualMax)
        {
            *actualMax = studentResults[i];
        }
    }
    free(studentResults);
    return true;
}

int assignPages(testcase *thisTestcase)
{
    int actualMax = 0;

    // Each student must be assigned at least one book, so error condition if students > books
    if (thisTestcase->numberOfStudents > thisTestcase->numberOfBooks)
    {
        return -1;
    }

    // Accumulate sum of page count of all books
    long totalPageCount = 0;
    for (int i = 0; i < thisTestcase->numberOfBooks; i++)
    {
        totalPageCount += thisTestcase->pageCountOfBooks[i];
    }

    // Now execute a binary search of the different possible minimums, testing using canBeAssigned above
    int leftBounds = 0;
    int rightBounds = totalPageCount;

    // We know we have the optimal solutions when the bounds cross each other
    while (leftBounds <= rightBounds)
    {
        int midpoint = (leftBounds + rightBounds) / 2;
        if (canBeAssigned(thisTestcase, midpoint, &actualMax))
        {
            // If this is possible, we might be able to do better
            // However, this could also be the best possible solution, so we should keep this midpoint in the test range
            // So we shift the right bounds equal to this midpoint
            rightBounds = midpoint - 1;
        }
        else
        {
            // If this isn't possible, we know that the possible answer is higher than the midpoint
            // So we shift the left bounds to one above the midpoint
            leftBounds = midpoint + 1;
        }
    };
    return actualMax;
}

int main(int argc, char *argv[])
{
    int numberOfTestCases;
    scanf("%d", &numberOfTestCases);
    testcase *testcases[numberOfTestCases];
    for (int i = 0; i < numberOfTestCases; i++)
    {
        testcases[i] = malloc(sizeof(testcase));
        scanf("%d", &testcases[i]->numberOfBooks);
        for (int j = 0; j < testcases[i]->numberOfBooks; j++)
        {
            scanf("%d", &testcases[i]->pageCountOfBooks[j]);
        }
        scanf("%d", &testcases[i]->numberOfStudents);
    }
    for (int i = 0; i < numberOfTestCases; i++)
    {
        printf("%d\n", assignPages(testcases[i]));
    }
    for (int i = 0; i < numberOfTestCases; i++)
    {
        free(testcases[i]);
    }
    return 0;
}