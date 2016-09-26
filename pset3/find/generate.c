/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // If one or two arguments are not given, 
    // print usage specification and return 1
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // Set the integer n to the first given argument,
    // representing the number of pseudorandom numbers
    int n = atoi(argv[1]);

    // If there is a second argument then seed the 
    // random number generator using that argument,
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else // otherwise seed with the current time
    {
        srand48((long int) time(NULL));
    }

    // Using the seeded generator, print requested
    // number of pseudorandom numbers
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}