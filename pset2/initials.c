/*Taylor Posey
CS50x 2016
Problem Set 2
This program will print the initials of the given user input. Prints every
character found after a space in the input.*/
#include <cs50.h>
#include <stdio.h>
#include <string.h>

void printinitials(string s);
char toupper(char c);

int main(void) 
{
    string name = GetString();
    if (name != NULL) 
    {
        printinitials(name);
    }
}

void printinitials(string s)
{
    if (s[0] != ' ') {
        printf("%c", toupper(s[0]));
    }
    for (int i = 1; i < strlen(s); i++)
    {
        if (s[i - 1] == ' ') {
            printf("%c", toupper(s[i]));
        }
    }
    printf("\n");
}

char toupper(char c) {
    if (c > 96) {
        c -= 32;
    }
    return c;
}