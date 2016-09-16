/*Taylor Posey
CS50x 2016
Problem Set 1
This file will print the total number of coins required to create the
change owed (determined by user input). Assumes American currency.*/
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) {
    printf("O hai! How much change is owed?\n");
    float change = -1; //priming the loop
    while (change < 0) {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
    int remaining = round(change * 100);
    int coins = 0;
    int types[] = {25, 10, 5, 1};
    for (int type = 0; type < 4; type++) {
        coins += remaining / types[type];
        remaining = remaining % types[type];
    }
    printf("%i\n", coins);
}