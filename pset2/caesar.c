/*Taylor Posey
CS50x 2016
Problem Set 2
This file encodes a given phrase using a key of the user's choice via caesar encryption.
Expects an non-negative integer as an arguement, and a phrase to encode as user input.*/
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

int main(int argc, string argv[])
{
    /*If one integer argument isn't given, return error*/
    if (argc != 2 || (atoi(argv[1]) < 1 && argv[1][0] != 48))
    {
        printf("Please give a single non-negative integer.\n");
        return 1;
    }
    string text = GetString();
    int k = atoi(argv[1]);
    char c;
    for (int i = 0; i < strlen(text); i++)
    {
        c = text[i];
        if (c > 64 && c < 91) /*Capitol letters*/
        {
            printf("%c", (((c-64) + k) % 26) + 64);
        }
        else if (c > 96 && c < 123) /*Lowercase letters*/
        {
            printf("%c", (((c-96) + k) % 26) + 96);
        }
        else /*Nonalphabetical*/
        {
            printf("%c", c);    
        }
    }
    printf("\n");
    return 0;
}