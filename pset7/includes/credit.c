/*Taylor Posey
CS50x 2016
Hacker Set 1
This file will classify a given credit card number as American Express,
Mastercard, Visa, or invalid (not a real credit card number). This is done
by computing the check sum and checking the length of given number.
Will print INVALID if checksum is not passed, otherwise will print
AMEX for an American Express card, MASTERCARD, or VISA.*/
#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[]) 
{
    if (argc != 2)
    {
        return 1;
    }
    char* ptr;
    long number = strtol(argv[1], &ptr, 10);
    int firstSum = 0;
    int secondSum = 0;
    int secondToLast = 1;
    int lastDigit;
    int currentDigit;
    int digitCount = 0;
    while (number != 0) 
    {
        lastDigit = currentDigit;
        currentDigit = number % 10;
        number = number / 10;
        if (secondToLast == 1) 
        {
            firstSum += currentDigit;
            secondToLast = 0;
        } else 
        {
            secondSum += (currentDigit*2) % 10;
            secondSum += (currentDigit*2) / 10;
            secondToLast = 1;
        }
        digitCount++;
    }
    if ((firstSum + secondSum) % 10 == 0) 
    {
        if (digitCount == 15 && ((currentDigit*10 + lastDigit) == 34 || (currentDigit*10 + lastDigit) == 37)) 
        {
            printf("AMEX\n");
        } else if (digitCount == 16 && (currentDigit*10 + lastDigit) > 50 && (currentDigit*10 + lastDigit) < 56) 
        {
            printf("MASTERCARD\n");
        } else if ((digitCount == 13 || digitCount == 16) && currentDigit == 4) 
        {
            printf("VISA\n");
        } else 
        {
            printf("INVALID\n");
        }
    } else 
    {
        printf("INVALID\n");
    }
    return 0;
}
