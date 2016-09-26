/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"
int middle(int min, int max);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int min = 0;
    int max = n;
    while (max > min) {
        if (values[middle(min,max)] < value) {
            min = middle(min,max) + 1;
        } else if (values[middle(min,max)] > value) {
            max = middle(min,max);
        } else {
            return true;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (values[j] < values[(j-1)]) {
                int hold = values[j];
                values[j] = values[(j-1)];
                values[(j-1)] = hold;
            } else {
                break;
            }
        }   
    }
}

/**
 * Returns the middle index of a subset defined by
 * the minimum inclusive index and the maximum 
 * exclusive index.
 */
int middle(int min, int max)
{
    return ((max - min) / 2) + min;
}