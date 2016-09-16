/*Taylor Posey
CS50x 2016
Problem Set 1
This file will print the approximate number of 16oz water bottles used up in
a shower, with the duration of the shower being given by user input.*/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("minutes: ");
    int min = GetInt();
    int bottles = (192 * min) / 16;
    printf("bottles: %i\n", bottles);
}