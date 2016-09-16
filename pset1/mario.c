/*Taylor Posey
CS50x 2016
Problem Set 1
Prints a mario pyramid out of #s, with a height determined by user input.*/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = -1; //priming loop
    while (height > 23 || height < 0)
    {
        printf("height: ");
        height = GetInt();
    }
    for (int line = 1; line <= height; line++) 
    {
        for (int space = 1; space <= (height + 1) - (line + 1); space++)
        {
            printf(" ");
        }
        for (int hash = 1; hash <= line + 1; hash++)
        {
            printf("#");
        }
        printf("\n");
    }
}