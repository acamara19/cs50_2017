/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
//binary search function declaration
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    //check if value is not negative
    if(value < 0)
    {
        //return false
        return false;
    }
    //define lower and upper limit
    int low = 0, up = n - 1;
    // check is low is less than or equal to upper limit
    while(low <= up)
    {
        //define middle of stack
        int mid = (up + low)/2;
        //check if the value is in the middle of stack
        if(value == values[mid])
        {
            //return true
            return true;
        }
        //check if the value is on the left side of stack
        else if(value < values[mid])
        {
            //reset the upper limit
            up = mid - 1;
        }
        //check if the value is on the right side of stack
        else if(value > values[mid])
        {
            //reset the lower limit
            low = mid + 1;
        }
    }
    //return false if value is not in stack
    return false;
}

/**
 * Sorts array of n values.
 */
//selection sort function declaration
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    //loop from minimum value to maximum - 1
    for(int i = 0; i < (n - 1); i++)
    {
        //declare an integer minimum and assign the value of i
        int min = i;
        //loop through all elements of unsorted array
        for(int j = (i + 1); j < n; j++)
        {
            //if element of j is smaller than minimum
            if(values[j] < values[min])
            {
                //assign j to minimum
                min = j;
            }
        }
        //make sure minimum is not i
        if(min != i)
        {
            //declare in integer temp and assign the current value to it
            int temp = values[min];
            //assign the current value of i as the new min
            values[min] = values[i];
            //assign the value in temp as the new value of i
            values[i] = temp;
        }
    }
    return;
}
